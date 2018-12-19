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
#include <string.h>

#include <sys/types.h>
#include <WinSock2.h>

//For Unix
//#include <sys/socket.h>
//#include <netinet/in.h>


#define MAX_RESPONSE_LENGTH 1024
#define HTTP_HEADER_LENGTH 2048

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


	// Open a file to serve
	FILE *html_data;
	html_data = fopen("../HTTP-Server/index.html", "r");
	if (html_data == NULL) printf("Couldn't open index.html\n");

	char response_data[MAX_RESPONSE_LENGTH];
	fgets(response_data, MAX_RESPONSE_LENGTH, html_data);
	fclose(html_data);

	// Response for the request is OK
	char http_header[HTTP_HEADER_LENGTH] = "HTTP/1.1 200 OK\r\n\n";

	strcat(http_header, response_data);


	// Create a socket
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Specify an address for the socket
	const unsigned short port = 8080;
	const char ipAddress[10] = "127.0.0.1";
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port); // Convert integer port number to correct byte order
	server_address.sin_addr.S_un.S_addr = inet_addr(ipAddress); // INADDR_ANY; // Connect to 0.0.0.0

	// Bind the socket to our specified UP and port
	if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == 0)
		printf("Socket bound to %s:%d\n", ipAddress, port);
	else {
		printf("Error while trying to bind the socket to an address: %d\n", WSAGetLastError());
		return;
	}

	listen(server_socket, 5); // At least an int of 1


	int client_socket;
	while (1)
	{	
		client_socket = accept(server_socket, NULL, NULL); // Could write the client address into a string instead of NULL

		// Send the message
		if (send(client_socket, http_header, sizeof(http_header), 0) != SOCKET_ERROR)
			printf("Send message to client\n");
		else {
			printf("Error while sending a message to the client: %d\n", WSAGetLastError());
			return;
		}

		
		//closesocket(client_socket);
		//WSACleanup();
	}

	// And then close the socket    //close(network_socket) in UNIX?
	closesocket(server_socket);
}
