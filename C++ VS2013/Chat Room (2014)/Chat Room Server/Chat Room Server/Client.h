#ifndef CTM_CLIENT_H
#define CTM_CLIENT_H

#include "StopWatch.h"

#include <WinSock2.h>
#include <string>

namespace ctm
{

//////
//Client
class client
{
public: 
	ctm::stopwatch timeout; //Time since last connection check
	SOCKET socket; //Socket to communicate with client
	sockaddr_storage addr; //Client address
	std::string username; //Client username
};
//////

}

#endif