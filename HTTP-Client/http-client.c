#pragma comment(lib, "Ws2_32.lib")
//Otherwise link error appears
//1>tcp_client.obj : error LNK2019 : Verweis auf nicht aufgelöstes externes Symbol "__imp__closesocket@4" in Funktion "_main".
//1>tcp_client.obj : error LNK2019 : Verweis auf nicht aufgelöstes externes Symbol "__imp__connect@12" in Funktion "_main".
//1>tcp_client.obj : error LNK2019 : Verweis auf nicht aufgelöstes externes Symbol "__imp__htons@4" in Funktion "_main".
//1>tcp_client.obj : error LNK2019 : Verweis auf nicht aufgelöstes externes Symbol "__imp__recv@16" in Funktion "_main".
//1>tcp_client.obj : error LNK2019 : Verweis auf nicht aufgelöstes externes Symbol "__imp__socket@12" in Funktion "_main"
//
//Otherwise: 
//The problem is you are not linking against the Ws2_32.lib library. 
//To fix this you can add that to your additional dependencies tab of linker/Input settings for your project.

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include <sys/types.h>
#include <WinSock2.h>


//For Unix
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>

void main(int argc, char *argv[]) {
	#ifdef WIN32
	// Initialize Winsock
	int iResult;
	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return;
	}
	#endif

	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Specify an address for the socket
	const unsigned short port = 80; //?
	const char* ipAddress = argv[1]; //printf("Address: %s\n", argv[1]);
	struct sockaddr_in remote_address;
	remote_address.sin_family = AF_INET;
	remote_address.sin_port = htons(port); // Convert integer port number to correct byte order
	remote_address.sin_addr.S_un.S_addr = inet_addr(ipAddress); // inet_aton(ipAddress, &remote_address.sin_addr.s_addr)  // For  unix

	// Check for error with the connection
	if (connect(client_socket, (struct sockaddr *) &remote_address, sizeof(remote_address)) == 0)
		printf("Connected to server socket at %s:%d\n", ipAddress, port);
	else {
		printf("There was an error making a connection to %s.\n%d\n", ipAddress, WSAGetLastError());
		return;
	}

	char request[] = "GET / HTTP/1.1\r\n\r\n";
	char response[4096];

	send(client_socket, request, sizeof(request), 0);
	recv(client_socket, &response, sizeof(response), 0);

	printf("response from the server: %s\n", response);

	closesocket(client_socket); // close() for unix
}