// Burak Koçak 26185037068
// HW #2 TCP ECHO SERVER

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

void main()
{
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsOk = WSAStartup(ver, &wsData);

	if (wsOk != 0)
	{
		cout << "Can't Initialize winsock! Quitting" << endl;
		return;
	}

	SOCKET sock_server = socket(AF_INET, SOCK_STREAM, 0); // socket creation and verify

	if (sock_server == INVALID_SOCKET)
	{
		cout << "Socket error" << endl;
		return;
	}

	// Port and IP Assignments
	int PORT_NO = 1337;
	sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT_NO);
	server_address.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(sock_server, (sockaddr*)&server_address, sizeof(server_address)); // bind function

	listen(sock_server, SOMAXCONN);  // listen function

	sockaddr_in client;
	int clientSize = sizeof(client);
	SOCKET clientSocket = accept(sock_server, (sockaddr*)&client, &clientSize); // accept function
	char host[NI_MAXHOST];		
	char service[NI_MAXSERV];	
	memset(host, 0, NI_MAXHOST); 
	memset(service, 0, NI_MAXSERV);
	
	closesocket(sock_server);
	char buffer[100];

	while (true)
	{
		memset(buffer, 0, 100); 
		int n = recv(clientSocket, buffer, 100, 0); // read or recv function

		if (n == SOCKET_ERROR)
		{
			cout << "Recv error" << endl;
			break;
		}

		if (n == 0)
		{
			cout << "Client disconnected " << endl;
			break;
		}

		cout << "message: '" << string(buffer, 0, n) << "' from client" << endl;
		send(clientSocket, buffer, n + 1, 0); // write or send function
	}

	closesocket(clientSocket);
	WSACleanup();
	system("pause");
}