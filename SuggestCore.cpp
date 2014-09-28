#include "SuggestCore.h"

Suggestions::Suggestions() {
	
	m_ranker.reset(new Ranker);
	
}

void Suggestions::addQuery(const std::string &_query) {
	
	Doc* doc = new Doc();
	doc->id = m_queries.size();
	
	m_queries.insert(std::pair<uint64_t, std::string> (doc->id, _query));
	
	m_ranker->m_tokenizer.tokenizeTextPrefixes(_query, doc->text);
	m_ranker->addDoc(doc);
}

void Suggestions::getSuggest(const std::string &_prefix,
					std::vector<std::string> &_suggest) const {
	
	std::vector<uint64_t> result;
	m_ranker->query(_prefix, result);

	hiaux::hashtable<uint64_t, std::string>::const_iterator it;

	for (int i = 0; i< fmin(10, result.size()) ; i++) {
		
		it = m_queries.find(result[i]);
		if (it != m_queries.end())
			_suggest.push_back(it->second);
	}
}
