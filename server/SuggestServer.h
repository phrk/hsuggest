/* 
 * File:   SuggestServer.h
 * Author: phrk
 *
 * Created on December 29, 2013, 11:13 PM
 */

#ifndef SUGGESTSERVER_H
#define	SUGGESTSERVER_H

#include "../SuggestCore.h"
#include "../../tetramorph/hpoolserver/http/HttpSrv.h"

class SuggestServer
{
	SuggestionsPtr suggest_core;
	HttpSrvPtr http_server;
public:
	void httpHandler(HttpSrv::ConnectionPtr, HttpSrv::RequestPtr);
	SuggestServer(TaskLauncherPtr launcher, int port);
};

typedef boost::shared_ptr<SuggestServer> SuggestServerPtr;

#endif	/* SUGGESTSERVER_H */

