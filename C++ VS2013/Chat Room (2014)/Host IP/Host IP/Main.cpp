#undef UNICODE

#pragma comment(lib, "WS2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

int main(int argc, char **argv)
{
	//Check parameters
	if(argc > 3)
	{
		std::cout << "Error: Invalid usage! Usage is as shown below:\n";
		std::cout << argv[0] << " " << "node" << "\n";
		std::cout << argv[0] << " " << "node" << " " << "port" << "\n";
		return 1;
	}

	//Initialize WSA
	WSADATA wsadata;
	if(WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		std::cout << "Error: Failed to initialize windows sockets!\n";
		return 2;
	}

	//Lookup address
	addrinfo hints;
	memset(&hints, 0, sizeof(addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	addrinfo *lookupresults = nullptr;
	int error = 0;
	if(argc == 2)
		error = getaddrinfo(argv[1], 0, &hints, &lookupresults);
	else
		error = getaddrinfo(argv[1], argv[2], &hints, &lookupresults);
	
	if(error != 0)
	{
		std::cout << "Error: Failed to get server info!\n";
		WSACleanup();
		return 3;
	}

	//Make new line
	std::cout << "\n";

	//Translate addresses
	DWORD iplength = 46;
	char ipbuffer[46];
	for(addrinfo *iter = lookupresults; iter != nullptr; iter = iter->ai_next)
	{
		//Check address family
		if(iter->ai_family == AF_INET)
		{
			std::cout << "IPv4 - ";
			LPSOCKADDR sockaddr_ipv4 = (LPSOCKADDR)iter->ai_addr;
			WSAAddressToString(sockaddr_ipv4, iter->ai_addrlen, 0, ipbuffer, &iplength);
			std::cout << ipbuffer;
		}

		if(iter->ai_family == AF_INET6)
		{
			iplength = 46;
			std::cout << "IPv6 - ";
			LPSOCKADDR sockaddr_ipv6 = (LPSOCKADDR)iter->ai_addr;
			WSAAddressToString(sockaddr_ipv6, iter->ai_addrlen, 0, ipbuffer, &iplength);
			std::cout << ipbuffer;
		}

		//Get name
		getnameinfo(iter, sizeof(*iter)
	}

	//Cleanup
	freeaddrinfo(lookupresults);
	WSACleanup();

	return 0;
}