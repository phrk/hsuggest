#include "SuggestCore.h"

bool QueryInfoComp(Suggestions::QueryInfo* a, Suggestions::QueryInfo *b)
{
	return a->freq > b->freq;
}

Suggestions::QueryInfo::QueryInfo(const std::string &_query, uint32_t _freq)
{
	query = _query;
	freq = _freq;
}

std::string Suggestions::QueryInfo::getQuery() const
{
	return query;
}

void Suggestions::addQuery(const QueryInfo &_query_info)
{
	QueryInfo *query_info = new QueryInfo(_query_info);
	queries.push_back(query_info);
	
	for (int i = 0; i <= query_info->query.size(); i++) {
		std::string prefix = query_info->query.substr(0, i);
		std::tr1::unordered_map<std::string, std::list<QueryInfo*> >::iterator it =
				prefix_to_queries.find(prefix);
		if (it != prefix_to_queries.end()) {
			//it->second.push_back(query_info);
			//std::sort(it->second.begin(), it->second.end(), QueryInfoComp);
			std::list<QueryInfo*> q_vec;
			q_vec.push_back(query_info);
			it->second.merge(q_vec, QueryInfoComp);
			while (it->second.size() > 10)
				it->second.pop_back();
		} else {
			std::list<QueryInfo*> q_vec;
			q_vec.push_back(query_info);
			prefix_to_queries.insert(std::pair<std::string, std::list<QueryInfo*> >
				(prefix, q_vec) );
		}
	}		
		
}

void Suggestions::getSuggest(const std::string &prefix,
					std::vector<std::string> &suggest) const
{
	std::tr1::unordered_map<std::string, std::list<QueryInfo*> >::const_iterator pit =
			prefix_to_queries.find(prefix);
	if (pit != prefix_to_queries.end()) {
		std::list<QueryInfo*>::const_iterator q_it = pit->second.begin();
				
		while (q_it != pit->second.end()) {
			suggest.push_back((*q_it)->query);
			q_it++;
		}
	}
}
