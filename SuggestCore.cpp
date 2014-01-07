#include "SuggestCore.h"
#include "../tetramorph/common/string_utils.h"

bool QueryInfoComp(WordInfo* a, WordInfo *b)
{
	return a->freq > b->freq;
}

QueryInfo::QueryInfo(const std::string &_query,
			uint32_t _freq):
		query(_query),
		freq(_freq)
{
}

WordInfo::WordInfo(const std::string &_word, uint32_t _freq)
{
	word = _word;
	freq = _freq;
}

void WordInfo::addOccur(QueryInfo *query_info)
{
	occurs.push_back(query_info);
}

std::string WordInfo::getWord() const
{
	return word;
}

WordsPrefixes::WordsPrefixes()
{

}

WordInfo* WordsPrefixes::addWord(const std::string &_word)
{
	std::tr1::unordered_map<std::string, WordInfo*>::iterator it =
		word_to_wordinfo.find(_word);
	if (it != word_to_wordinfo.end())
		return it->second;
	
	WordInfo *word_info = new WordInfo(_word, 1);
	word_to_wordinfo.insert(std::pair<std::string, WordInfo*>
									(word_info->word, word_info));

	for (int i = 0; i < word_info->word.size(); i++) {
		std::string prefix = word_info->word.substr(0, i);
		std::tr1::unordered_map<std::string, std::list<WordInfo*> >::iterator it =
				prefix_to_wordinfo.find(prefix);
		if (it != prefix_to_wordinfo.end()) {
			//it->second.push_back(query_info);
			//std::sort(it->second.begin(), it->second.end(), QueryInfoComp);
			std::list<WordInfo*> q_vec;
			q_vec.push_back(word_info);
			it->second.merge(q_vec, QueryInfoComp);
			while (it->second.size() > 10)
				it->second.pop_back();
		} else {
			std::list<WordInfo*> q_vec;
			q_vec.push_back(word_info);
			prefix_to_wordinfo.insert(std::pair<std::string, std::list<WordInfo*> >
				(prefix, q_vec) );
		}
	}
	word_info->freq++;
	return word_info;	
}

void WordsPrefixes::getWords(const std::string &prefix,
					std::vector<WordInfo*> &words) const
{
	std::tr1::unordered_map<std::string, WordInfo*>::const_iterator it = 
			word_to_wordinfo.find(prefix);
	if (it != word_to_wordinfo.end()) {
		words.push_back(it->second);
		return;
	}
	
	std::tr1::unordered_map<std::string, std::list<WordInfo*> >::const_iterator pit =
			prefix_to_wordinfo.find(prefix);
	if (pit != prefix_to_wordinfo.end()) {
		std::list<WordInfo*>::const_iterator q_it = pit->second.begin();
				
		while (q_it != pit->second.end()) {
			words.push_back(*q_it);
			q_it++;
		}
	}
}

Suggestions::Suggestions()
{
	m_prefixes.reset(new WordsPrefixes);
}

void Suggestions::addQuery(const QueryInfo &_query_info)
{
	QueryInfo *query_info = new QueryInfo(_query_info);
	m_queries.insert(std::pair<std::string, QueryInfo*>
					(query_info->query, query_info) );
	
	// fill invert index
	std::vector<std::string> words;
	split(query_info->query, ' ', words);
	for (int i = 0; i<words.size(); i++) 
		if (words[i].size() >= 1) {
			WordInfo *word_info = m_prefixes->addWord(words[i]);
			word_info->addOccur(query_info);
		}
}

void Suggestions::intersectQueriesLists(std::vector<QueryInfo*> &a,
								const std::vector<QueryInfo*> &b) const
{
	
}

void Suggestions::mergeQueriesLists(std::vector<QueryInfo*> &a,
					const std::vector<QueryInfo*> &b) const
{
	std::tr1::unordered_map<QueryInfo*, bool> _map;
	for (int i = 0; i<a.size(); i++)
		_map[a[i]] = true;
	for (int i = 0; i<b.size(); i++)
		_map[b[i]] = true;
	a.clear();
	std::tr1::unordered_map<QueryInfo*, bool>::iterator it = _map.begin();
	while (it != _map.end()) {
		a.push_back(it->first);
		it++;
	}
}

void Suggestions::getSuggest(const std::string &_prefix,
					std::vector<std::string> &suggest) const
{
	std::string prefix = "and";// _prefix;
	std::vector<std::string> words;
	std::vector<QueryInfo*> query_infos;
	
	split(prefix, ' ', words);
	for (int i = 0; i<words.size(); i++) 
		if (words[i].size() >= 1) {
			std::vector<WordInfo*> word_infos;
			std::cout << "word: " << words[i] << std::endl;
			m_prefixes->getWords(words[i], word_infos);
			
			std::vector<QueryInfo*> word_queries; 
			for (int j = 0; j<word_infos.size(); j++)
				for (int k = 0; k<word_infos[j]->occurs.size(); k++) {
					word_queries.push_back(word_infos[j]->occurs[k]);
				}
			
		}
	
	/*
	for (int i = 0; i<word_infos.size(); i++) {
		std::cout << "wordinfo: " << word_infos[i]->word << " \n";
		std::cout << "occurs: " << word_infos[i]->occurs.size() << std::endl;
		for (int j = 0; j< word_infos[i]->occurs.size(); j++)
			std::cout <<  word_infos[i]->occurs[j]->query << std::endl;
	}
	
	std::cout << "prefixes: " << m_prefixes->prefix_to_wordinfo.size() << std::endl;
	std::cout << "words: " << m_prefixes->word_to_wordinfo.size() << std::endl;*/
}
