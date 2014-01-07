/* 
 * File:   main.cpp
 * Author: phrk
 *
 * Created on December 29, 2013, 11:10 PM
 */

#include <cstdlib>
#include "SuggestServer.h"

using namespace std;

void onFinished()
{

}

int main(int argc, char** argv) {

	SuggestionsPtr suggest_core = SuggestionsPtr(new Suggestions);
	
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
				std::cout << i <<  query << std::endl;
			i++;
			std::transform(query.begin(),
							query.end(), query.begin(), ::tolower);
			suggest_core->addQuery(QueryInfo(query, 1));
			if (i>=10000) break;
		}
	}
	
	std::vector<std::string> suggest;
	
	suggest_core->getSuggest("how", suggest);
	
	return 0;
	std::cout << "Suggest server\n";
	
	const int port = 12345;
	hThreadPool *pool = new hThreadPool(10);
	TaskLauncherPtr launcher (new TaskLauncher(
					pool, 10, boost::bind(&onFinished)));
	
	SuggestServerPtr server(new SuggestServer(launcher, port));
	
	pool->run();
	pool->join();

	return 0;
}

