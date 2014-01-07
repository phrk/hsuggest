#ifndef _SUGGESTCORE_H_
#define _SUGGESTCORE_H_

#include <vector>
#include <stdint.h>
#include <tr1/unordered_map>
#include <string>
#include <list>
#include <boost/shared_ptr.hpp>

class QueryInfo
{
public:
	std::string query;
	uint32_t freq;
	
	QueryInfo(const std::string &_query,
			uint32_t _freq);
};

class WordInfo
{
public:
	std::string word;
	uint32_t freq;
	
	// sorted
	std::vector<QueryInfo*> occurs;
	
	void addOccur(QueryInfo *query_info);
	std::string getWord() const;

	WordInfo(const std::string &_word, uint32_t _freq);
};

class WordsPrefixes
{
	
public:
	std::tr1::unordered_map<std::string, std::list<WordInfo*> >
		prefix_to_wordinfo;
	
	std::tr1::unordered_map<std::string, WordInfo*>
		word_to_wordinfo;
	
public:
	WordsPrefixes();
	WordInfo* addWord(const std::string &_word);
	void getWords(const std::string &prefix,
					std::vector<WordInfo*> &words) const;
};

typedef boost::shared_ptr<WordsPrefixes> WordPrefixesPtr;

class Suggestions
{
	WordPrefixesPtr m_prefixes;
	std::tr1::unordered_map<std::string, QueryInfo*> m_queries;
	
	void intersectQueriesLists(std::vector<QueryInfo*> &a,
							const std::vector<QueryInfo*> &b) const;
	
	void mergeQueriesLists(std::vector<QueryInfo*> &a,
							const std::vector<QueryInfo*> &b) const;
	
public:

	Suggestions();
	void addQuery(const QueryInfo &_query_info);
	void getSuggest(const std::string &prefix,
					std::vector<std::string> &suggest) const;
	
};

typedef boost::shared_ptr<Suggestions> SuggestionsPtr;

#endif
