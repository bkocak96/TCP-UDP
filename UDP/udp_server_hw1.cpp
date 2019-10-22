#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

void main()
{
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);

	if (wsOk != 0)
	{
		cout << "Can't start Winsock! " << wsOk;
		return;
	}
		
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

	sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(1337);
												 
	if (bind(sock, (sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
	{
		cout << "Can't bind socket! " << WSAGetLastError() << endl;
		return;
	}
	
	sockaddr_in client;
	int client_size = sizeof(client);
											
	while (true)
	{
		char buffer[100];
				
		int n = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&client,&client_size);

		if (n == SOCKET_ERROR)
		{
			cout << "Error receiving from client " << WSAGetLastError() << endl;
			continue;
		}
		buffer[n] = '\0';
		
		cout << "message: " << buffer << " from client\n";

		sendto(sock, buffer, n, 0, (sockaddr*)&client, sizeof(client));
	}

	closesocket(sock);
	WSACleanup();
}