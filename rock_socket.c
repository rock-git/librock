
#define ROCK_REUSEADDR 0x00000001


int rock_create_listen(int port, int flags)
{
	int fd;
	int addrlen;
	struct sockaddr_in la;
	
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) return -1;
	
	addrlen = sizeof(struct sockaddr);
	memset(&la, 0, addrlen);
	la.sin_family = AF_INET;
	la.sin_port = htons(port);
	la.sin_addr.s_addr = ;
	
	if (bind(fd, (struct sockaddr*)&la, &addrlen) != 0)
	{
		printf("bind error: %d\n", errno);
		close(fd);
		return -1;
	}
	
	if (listen(fd, 5) != 0)
	{
		printf("listen error: %d\n", errno);
		close(fd);
		return -1;
	}
	
	return fd;
}


int rock_connect(char *host, int port, int flags)
{
	int fd;
	int addrlen;
	struct sockaddr_in sa;
	
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) return -1;
	
	addrlen = sizeof(struct sockaddr);
	memset(&sa, 0, addrlen);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.s_addr = inet_addr(host);
	
	if (connect(fd, (struct sockaddr*)&sa, addrlen) != 0)
	{
		printf("connect error: %d\n", errno);
		close(fd);
		return -1;
	}
	
	return 0;
}











