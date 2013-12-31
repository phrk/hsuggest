#include "SuggestServer.h"
#include <fstream>
#include <iostream>
#include <algorithm>

void SuggestServer::httpHandler(HttpSrv::ConnectionPtr http_conn,
							HttpSrv::RequestPtr req)
{
	
	std::tr1::unordered_map<std::string, std::string>::iterator it =
					req->values_GET.begin();
	while (it != req->values_GET.end()) {
		std::cout << it->first << "/" << it->second << std::endl;
		it++;
	}
	
	//std::tr1::unordered_map<std::string, std::string>::iterator 
	it =
			req->values_GET.find("prefix");
	if (it == req->values_GET.end()) {
		http_conn->close();
		return;
	}
	
	std::string prefix = it->second;
	
	std::vector<std::string> suggestions;
	suggest_core->getSuggest(prefix, suggestions);
	
	std::string reponse_json = "{ [ ";
	for (int i = 0; i<suggestions.size(); i++) {
		std::transform(suggestions[i].begin(),
						suggestions[i].end(), suggestions[i].begin(), ::tolower);
		//reponse_json += "{ \"label\" : \""+suggestions[i]+"\", ";
		//reponse_json += "\"value\" : \""+suggestions[i]+"\" }";
		reponse_json += "\""+suggestions[i]+"\"";
		if (i != suggestions.size()-1)
			reponse_json += ", ";
	}
	reponse_json += " ] }";
	http_conn->sendResponse(reponse_json);
}

SuggestServer::SuggestServer(TaskLauncherPtr launcher, int port)
{	
	suggest_core.reset(new Suggestions());
	
	
	std::ifstream in ("queries.in");
	char query_c[100];
	while (!in.eof()) {
		in.getline(query_c, 100);
		std::string query(query_c);
		std::transform(query.begin(),
						query.end(), query.begin(), ::tolower);
		suggest_core->addQuery(Suggestions::QueryInfo(query, 1));
	}
	in.close();
	
	http_server.reset(new HttpSrv(launcher,
							HttpSrv::ResponseInfo("application/json; charset=utf-8",
								"highinit suggest server"), 
							boost::bind(&SuggestServer::httpHandler, this, _1, _2)));
	http_server->start(port);
}
