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

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <WinSock2.h>

//For Unix
//#include <sys/socket.h>
//#include <netinet/in.h>

void main() {
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

	char server_message[255] = "You have reached the server";

	// Create a socket
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	// Specify an address for the socket
	const unsigned short port = 8080;
	const char ipAddress[10] = "127.0.0.1";
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080); // Convert integer port number to correct byte order
	server_address.sin_addr.S_un.S_addr = inet_addr(ipAddress); // INADDR_ANY; // Connect to 0.0.0.0

	// Bind the socket to our specified UP and port
	if(bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == 0)
		printf("Socket bound to %s:%d\n", ipAddress, port);
	else {
		printf("%d\n", WSAGetLastError());
		return;
	}

	listen(server_socket, 5); // At least an int of 1

	int res = -1;
	while (res == -1)
	{
		int client_socket;
		client_socket = accept(server_socket, NULL, NULL); // Could write the client address into a string instead of NULL

		// Send the message
		res = send(client_socket, server_message, sizeof(server_message), 0);
	}

	// And then close the socket    //close(network_socket) in UNIX?
	closesocket(server_socket);
}
