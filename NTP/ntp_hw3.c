//Burak Koçak
//26185037068
//NTP Hw3

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define NTP_TIMESTAMP_DELTA 2208988800ull

int main()
{
	int sock, n;

	int port_no = 123;

	char* host_name = "tr.pool.ntp.org";

	typedef struct
	{

		uint8_t li_v_mode4;
		uint8_t stratum;
		uint8_t poll;
		uint8_t precision;

		uint32_t rootDelay;
		uint32_t rootDispersion;
		uint32_t refId;

		uint32_t refTm_s;
		uint32_t refTm_f;

		uint32_t origTm_s;
		uint32_t origTm_f;

		uint32_t rxTm_s;
		uint32_t rxTm_f;

		uint32_t txTm_s;
		uint32_t txTm_f;

	} ntp_packet;

	ntp_packet my_time_packet;
	memset(&my_time_packet, 0, sizeof(ntp_packet));
	*((char *)&my_time_packet + 0) = 0x1b;

	struct sockaddr_in serv_addr; 
	struct hostent *host_ip;      

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 

	if (sock == -1) printf("socket error");

	host_ip = gethostbyname(host_name); 

	bzero(&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;

	bcopy((char*)host_ip->h_addr, (char*)&serv_addr.sin_addr.s_addr, host_ip->h_length); 

	serv_addr.sin_port = htons(port_no);

	if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) !=0 ) printf("connect error");

	n = write(sock, (char*)&my_time_packet, sizeof(ntp_packet));
	n = read(sock, (char*)&my_time_packet, sizeof(ntp_packet));

	my_time_packet.txTm_s = ntohl(my_time_packet.txTm_s);
	my_time_packet.txTm_f = ntohl(my_time_packet.txTm_f); 

	time_t txTm = (time_t)(my_time_packet.txTm_s - NTP_TIMESTAMP_DELTA);

	printf("The Current Time: %s", ctime((const time_t*)&txTm));

	return 0;
}
