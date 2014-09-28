#include "SuggestServer.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdio>

void SuggestServer::httpHandler(HttpConnectionPtr http_conn,
							HttpRequestPtr req)
{
	
	hiaux::hashtable<std::string, std::string>::iterator it =
					req->values_GET.begin();
/*	while (it != req->values_GET.end()) {
		std::cout << it->first << "/" << it->second << std::endl;
		it++;
	}
*/	
	it = req->values_GET.find("term");
	
	if (it == req->values_GET.end()) {
		return;
	}
	
	std::string prefix = it->second;
	
	std::vector<std::string> suggestions;
	suggest_core->getSuggest(prefix, suggestions);
	
	std::string reponse_json = " [ ";
	for (int i = 0; i<suggestions.size(); i++) {
		//std::transform(suggestions[i].begin(),
		//				suggestions[i].end(), suggestions[i].begin(), ::tolower);
		reponse_json += "{ \"id\" : \""+suggestions[i]+"\", ";
		reponse_json += "\"label\" : \""+suggestions[i]+"\",";
		reponse_json += "\"value\" : \""+suggestions[i]+"\" }";
		//reponse_json += "\""+suggestions[i]+"\"";
		if (i != suggestions.size()-1)
			reponse_json += ", ";
	}
	reponse_json += " ] ";
	http_conn->sendResponse(reponse_json);
	//http_conn->close();
}

SuggestServer::SuggestServer(TaskLauncherPtr launcher, int port)
{
	suggest_core.reset(new Suggestions());
	int i = 0;
	{
		FILE *f = fopen("../crawlers/queries.in", "r");
		char query_c[200];
		
		std::string query = "";
		while (!feof(f)) {
			fgets(query_c, 200, f);
			query = std::string(query_c);
			query = query.substr(0, query.size()-1);
			if (i%1000==0)
				std::cout << i << " " << query << std::endl;
			i++;
			//std::transform(query.begin(),
			//				query.end(), query.begin(), ::tolower);
			toLowerUtf8(query);
			suggest_core->addQuery(query);
			
			//if (i>10000) break;
			
		}
	}
	
	{
		FILE *f = fopen("../crawlers/so_queries.in", "r");
		char query_c[200];
		int i = 0;
		std::string query = "";
		while (!feof(f)) {
			fgets(query_c, 200, f);
			query = std::string(query_c);
			query = query.substr(0, query.size()-1);
			if (i%1000==0)
				std::cout << i << " " <<  query << std::endl;
			i++;
			//std::transform(query.begin(),
			//				query.end(), query.begin(), ::tolower);
			toLowerUtf8(query);
			suggest_core->addQuery(query);
			
			//if (i>10000) break;
		}
	}
	
	std::cout << "loaded: " << i << std::endl;
	
	http_server.reset(new HttpServer(launcher,
							ResponseInfo("application/json; charset=utf-8",
								"highinit suggest server"), 
							boost::bind(&SuggestServer::httpHandler, this, _1, _2),
							port));
}
