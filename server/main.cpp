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

