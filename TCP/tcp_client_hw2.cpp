// Burak Koçak 26185037068
// HW #2 TCP ECHO CLIENT

#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

void main()
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);

	if (wsResult != 0)
	{
		cout << "Can't start Winsock" << wsResult << endl;
		return;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // Socket creation and verify

	if (sock == INVALID_SOCKET)
	{
		cout << "Socket error" << endl;
		WSACleanup();
		return;
	}
	// Port and IP Assignments
	int PORT_NO = 1337;
	sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT_NO);
	inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

	int connecting = connect(sock, (sockaddr*)&server_address, sizeof(server_address)); // connect function

	if (connecting == SOCKET_ERROR)
	{
		cout << "Connect error" << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	char buffer[100];
	string message;

	while (1) {
		cout << "enter your message to send server: ";
		getline(cin, message);

		int n = send(sock, message.c_str(), message.size() + 1, 0); // write or send function

		if (n != SOCKET_ERROR)
		{

			memset(buffer, 0, 100);
			int n = recv(sock, buffer, 100, 0); // read or recv function
			if (n > 0)
			{
				cout << "message: '" << string(buffer, 0, n) << "' from server" << endl;
			}
		}
	}

	closesocket(sock);
	WSACleanup();
}