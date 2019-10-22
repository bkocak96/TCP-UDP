#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

void main(int argc, char* argv[]) 
{
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);

	if (wsOk != 0)
	{
		cout << "Can't start Winsock! " << wsOk;
		return;
	}
		
	sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(1337);
	inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
														  
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

	const char* message = { "selamlar herkese!!" };
	
	int n = sendto(sock, message, strlen(message), 0, (sockaddr*)&server_address, sizeof(server_address));

	if (n == SOCKET_ERROR)
	{
		cout << "That didn't work! " << WSAGetLastError() << endl;
	}

	char buffer[100];
	recvfrom(sock, buffer, n, 0, NULL, NULL);

	buffer[n] = '\0';

	cout << "message:" << buffer << " " << "from server\n";
	
	closesocket(sock);
	WSACleanup();
}