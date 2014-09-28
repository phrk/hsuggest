/* 
 * File:   SuggestServer.h
 * Author: phrk
 *
 * Created on December 29, 2013, 11:13 PM
 */

#ifndef SUGGESTSERVER_H
#define	SUGGESTSERVER_H

#include "SuggestCore.h"
#include "hiaux/network/HttpServer/HttpServer.h"

class SuggestServer
{
	SuggestionsPtr suggest_core;
	HttpServerPtr http_server;
public:
	void httpHandler(HttpConnectionPtr, HttpRequestPtr);
	SuggestServer(TaskLauncherPtr launcher, int port);
};

typedef boost::shared_ptr<SuggestServer> SuggestServerPtr;

#endif	/* SUGGESTSERVER_H */

