/* 
 * File:   test.cpp
 * Author: phrk
 *
 * Created on December 22, 2013, 10:53 PM
 */

#include <cstdlib>
#include "SuggestCore.h"

#include <iostream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

	
	Suggestions suggest;
	
	for (int i = 0; i<1000000; i++) {
		char bf[255];
		sprintf(bf, "foo bar %d", i);
		//std::cout << bf << std::endl;
		std::string query(bf);
		suggest.addQuery(Suggestions::QueryInfo(query, i));
	}
	
	std::string query("foo bar 120");
	std::cout << "\nquering " << query << std::endl;
	
	std::vector<std::string> suggests;
	suggest.getSuggest(query, suggests);
	
	for (int i = 0; i<suggests.size(); i++) {
		std::cout << suggests[i] << std::endl;
	}
	
	return 0;
}

