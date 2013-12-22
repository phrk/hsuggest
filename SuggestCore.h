#ifndef _SUGGESTCORE_H_
#define _SUGGESTCORE_H_

#include <vector>
#include <stdint.h>
#include <tr1/unordered_map>
#include <string>
#include <list>

class Suggestions
{
public:
	class QueryInfo
	{
	public:
		std::string query;
		uint32_t freq;
		
		std::string getQuery() const;
		
		QueryInfo(const std::string &_query, uint32_t _freq);
	};
private:
	std::tr1::unordered_map<std::string, std::list<QueryInfo*> >
		prefix_to_queries;

	std::vector<QueryInfo*> queries;
	
	//void insertQueryInfoInList(std::list<QueryInfo*> &q_list, QueryInfo* qi);
public:
	
	void addQuery(const QueryInfo &_query_info);
	void getSuggest(const std::string &prefix,
					std::vector<std::string> &suggest) const;
};

#endif
