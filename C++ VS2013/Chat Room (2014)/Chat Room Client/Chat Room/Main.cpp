#undef UNICODE

#pragma comment(lib, "WS2_32.lib")

#include "Packet.h"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <thread>
#include <mutex>

void typeline(std::string &line)
{
	std::cin >> line;
}

int main(int argc, char **argv)
{
	//Check arguments
	if((argc > 3) || (argc == 2))
	{
		std::cout << "Error: Invalid usage! Usage is as follows:\n";
		std::cout << argv[0] << "\n";
		std::cout << argv[0] << "node service\n";
		return 1;
	}

	//Startup WSA
	WSADATA wsadata;
	int wsaerror = WSAStartup(MAKEWORD(2, 2), &wsadata);

	if(wsaerror != 0)
	{
		std::cout << "Error: Failed to startup WSA! Code: " << WSAGetLastError() << "\n";
		return 2;
	}

	//Load server file
	std::string servernode;
	std::string serverservice;
	if(argc == 1)
	{
		std::ifstream serverfile("serverfile.txt");

		if(!serverfile.is_open())
		{
			std::cout << "Error: Couldn't find \"serverfile.txt\"!\n";
			return 3;
		}

		if(!serverfile.good())
		{
			std::cout << "Error: Failed to load node from server file!\n";
			return 3;
		}

		//Load node
		std::getline(serverfile, servernode);

		if(!serverfile.good())
		{
			std::cout << "Error: Failed to load port from server file!\n";
			return 3;
		}

		//Load port
		std::getline(serverfile, serverservice);

		serverfile.close();
	}
	else //Get server info from console arguments
	{
		servernode = argv[1];
		serverservice = argv[2];
	}

	//Fill in hints for lookup
	addrinfo hints; 
	memset(&hints, 0, sizeof(addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_UNSPEC;
	
	//Lookup server
	addrinfo *results = nullptr;
	if(getaddrinfo(servernode.c_str(), serverservice.c_str(), &hints, &results) != 0)
	{
		std::cout << "Error: Failed to find server! Code: " << WSAGetLastError() << "\n";
		WSACleanup();
		return 4;
	}
	
	//Convert IPs to readable format
	std::vector<std::string> serverips;
	DWORD iplength = DWORD(INET6_ADDRSTRLEN);
	char ipbuffer[INET6_ADDRSTRLEN];
	for(addrinfo *iter = results; iter != nullptr; iter = iter->ai_next)
	{
		//Convert IP
		iplength = DWORD(INET6_ADDRSTRLEN);
		LPSOCKADDR sockaddr_ip = (LPSOCKADDR)iter->ai_addr;
		if(WSAAddressToString(sockaddr_ip, iter->ai_addrlen, 0, ipbuffer, &iplength) != 0)
		{
			std::cout << "Error: Failed to convert IP to readable format! Code: " << WSAGetLastError() << "\n";
			WSACleanup();
			return 5;
		}

		//Add IP to vector
		serverips.push_back(ipbuffer);
	}


	//Connect to server
	int whichip = 0;
	SOCKET server = 0;
	for(addrinfo *iter = results; iter != nullptr; iter = iter->ai_next)
	{
		//Print status
		std::cout << "Attempting to connect to " << serverips[whichip] << " on port " << serverservice << "...\n";

		//Get socket
		server = socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol);
		if(server != INVALID_SOCKET)
		{
			//Connect to server
			if(connect(server, iter->ai_addr, iter->ai_addrlen) == 0)
			{
				std::cout << "Connection successful!\n";
				break;
			}
		}

		//Failure
		if(iter->ai_next == 0)
		{
			std::cout << "Error: Failed to connect to server! Code: " << WSAGetLastError() << "\n";
			closesocket(server);
			freeaddrinfo(results);
			WSACleanup();
			return 6;
		}

		++whichip;
	}

	//Free server lookup results
	freeaddrinfo(results);

	//Input username
	std::string line;
	std::cout << "Enter a username: ";
	std::cin >> line;

	//Send username
	if(send(server, line.c_str(), line.size()+1, 0) != 0)
	{
		std::cout << "Error: Failed to send username! Code: " << WSAGetLastError() << "\n";
		closesocket(server);
		WSACleanup();
		return 7;
	}

	//Main loop
	std::thread inputthread(typeline, line);

	while(true)
	{
		inputthread.
	}

	//Close socket
	closesocket(server);

	//Clean up WSA
	WSACleanup();

	return 0;
}