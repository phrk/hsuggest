#ifndef _SUGGESTCORE_H_
#define _SUGGESTCORE_H_

#include "hiconfig.h"

#include <vector>
#include <stdint.h>
#include "hiaux/structs/hashtable.h"
#include <string>
#include <list>
#include <boost/shared_ptr.hpp>
#include "hiaux/strings/string_utils.h"

#include "ranker.h"

class Suggestions {

	hiaux::hashtable<uint64_t, std::string> m_queries;
	RankerPtr m_ranker;
	
public:

	Suggestions();
	void addQuery(const std::string &_query);
	void getSuggest(const std::string &prefix,
					std::vector<std::string> &suggest) const;
	
};

typedef boost::shared_ptr<Suggestions> SuggestionsPtr;

#endif
