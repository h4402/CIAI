#include "telnet.h"
#include <sysLib.h>

int telnet()
{
	char buff[SIZE_BUFF];
	int sock, nb;
	
	struct sockaddr_in saddr;
	int size_addr;
	size_addr = sizeof(struct sockaddr_in);
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	FAIL(sock)
		
	memset(&saddr, 0, sizeof(struct sockaddr_in));
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(1234);
	
	puts(inet_ntoa(saddr.sin_addr));
	
	FAIL(bind(sock,  (struct sockaddr *)&saddr, sizeof(saddr)))
	saddr.sin_port = htons(PORT);
	FAIL(connect(sock, (struct sockaddr *)&saddr, size_addr))
	puts("connected");
	
	taskDelay(sysClkRateGet()*3);
	
	nb = send(sock, "plop\n", 6, 0);
	printf("send : %d",nb);
	
	nb = recv(sock, buff, SIZE_BUFF, 0);
	
	puts(buff);
}

