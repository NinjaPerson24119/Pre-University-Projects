#undef UNICODE

#pragma comment(lib, "WS2_32.lib")

#include "Client.h"
#include "StopWatch.h"

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

//Globals
const char *localaddr = "localhost";
double const secondstodisconnect = 10;


int main(int argc, char **argv)
{
	//Check arguments
	if(argc != 2)
	{
		std::cout << "Error: Invalid usage!\n" << "Correct usage is as follows: \n" << argv[0] << "service" << "\n";
		return 1;
	}

	//Startup WSA
	WSADATA wsadata;
	int wsaerror = WSAStartup(MAKEWORD(2, 2), &wsadata);
	
	if(wsaerror != 0)
	{
		std::cout << "Error: Failed to startup WSA! Code: " << wsaerror << "\n";
		return 2;
	}

	//Fill out hints for address lookup
	addrinfo hints;
	memset(&hints, 0, sizeof(addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

	//Lookup local address
	addrinfo *results;
	if(getaddrinfo(localaddr, argv[1], &hints, &results) != 0)
	{
		std::cout << "Error: Failed to lookup local address! Code: " << WSAGetLastError() << "\n";
		return 3;
	}

	//Translate local address to readable format
	DWORD iplength = DWORD(INET6_ADDRSTRLEN);
	char ipbuffer[INET6_ADDRSTRLEN];

	//Convert IP
	LPSOCKADDR sockaddr_ip = (LPSOCKADDR)results->ai_addr;
	if(WSAAddressToString(sockaddr_ip, results->ai_addrlen, 0, ipbuffer, &iplength) != 0)
	{
		std::cout << "Error: Failed to convert IP to readable format! Code: " << WSAGetLastError() << "\n";
		freeaddrinfo(results);
		WSACleanup();
		return 4;
	}

	//Get socket
	SOCKET listener = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

	if(listener == INVALID_SOCKET)
	{
		std::cout << "Error: Failed to get socket! Code: " << WSAGetLastError() << "\n";
		freeaddrinfo(results);
		WSACleanup();
		return 5;
	}

	//Bind socket to port
	if(bind(listener, results->ai_addr, results->ai_addrlen) != 0)
	{
		std::cout << "Reseting socket and retrying bind!\n";
		bool optionval = true;
		if(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char*)&optionval, sizeof(bool)) != 0)
		{
			std::cout << "Error: Failed to bind socket to port! Code: " << WSAGetLastError() << "\n";
			freeaddrinfo(results);
			closesocket(listener);
			WSACleanup();
			return 6;
		}
		if(bind(listener, results->ai_addr, results->ai_addrlen) != 0)
		{
			std::cout << "Error: Failed to bind socket to port! Code: " << WSAGetLastError() << "\n";
			freeaddrinfo(results);
			closesocket(listener);
			WSACleanup();
			return 6;
		}
	}

	//Free lookup results
	freeaddrinfo(results);

	//Listen for clients
	if(listen(listener, 3) != 0)
	{
		std::cout << "Error: Failed to listen for clients! Code: " << WSAGetLastError() << "\n";
		closesocket(listener);
		WSACleanup();
		return 7;
	}
	
	//Print status
	std::cout << "Listening at " << ipbuffer << " on port " << argv[1] << "!\n";

	//Connect to client
	socklen_t addrsize; //Length of a sockaddr_storage
	ctm::client user; //Client

	while(true)
	{
		//Accept connections to clients
		addrsize = sizeof(user.addr);
		user.socket = accept(listener, (sockaddr*)&user.addr, &addrsize);
		
		if(user.socket == INVALID_SOCKET)
		{
			std::cout << "Failed to connect to a client! Code: " << WSAGetLastError() << "\n";
		}
	}

	//Close listener socket
	closesocket(listener);

	//Print client info
	inet_ntop(user.addr.ss_family, (sockaddr*)&user.addr, ipbuffer, INET6_ADDRSTRLEN);
	std::cout << "Connected to " << ipbuffer << "!\n";

	//Main loop
	while(true)
	{
		
	}

	//Disconnect from client
	closesocket(user.socket);

	//Cleanup WSA
	WSACleanup();

	return 0;
}