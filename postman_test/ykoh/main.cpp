#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <cstring>


int buf_size = 1024;

int main(void)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == server_socket)
	{
		write(1, "server socket error\n", 20);
		exit(1);
	}
	int value = 1;
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) == -1)
	{
		write(1, "server socket opt error\n", 24);
        return (0);
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4000); // port 번호는 endian 변환
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (-1 == bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) || errno != 0)
	{
		write(1, "bind error\n", 11);
		exit(1);
	}
	if (-1 == listen(server_socket, 5) || errno != 0)
	{
		write(1, "listen error\n", 13);
		exit(1);
	}


    /* 1. client socket(연결 소켓) 을 만들자. */
    struct sockaddr_in client_addr;
    memset(&server_addr, 0, sizeof(client_addr));
    unsigned int client_addr_size = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);

	std::cout << "1" << std::endl;
    if (-1 == client_socket)
    {
        write(1, "client socket error\n", 20);
        exit(1);
    }
	int		read_ret = 0;
	int		sum = 0;

	buf_size = 100000;
    char buff_rcv[buf_size];
	memset(buff_rcv, 0, buf_size);

	// ANCHOR read() BLOCKING
	std::cout << "read: " << (read_ret = read(client_socket, buff_rcv, buf_size)) << std::endl;


	// ANCHOR read() NONBLOCKING
	// int flags = fcntl(client_socket, F_GETFL, 0);
	// flags |= O_NONBLOCK;	
	// fcntl(client_socket, F_SETFL, flags);
	// while ((read_ret = read(client_socket, buff_rcv, buf_size/100)))
	// {
	// 	if (n <= 0)
	// 	{
	// 		std::cout << "break 전에 n값은?: " << n <<  std::endl;
	// 		break ;
	// 	}
	// 	buff_rcv[n] = 0;
	// 	sum += n;
	// 	std::cout << n << std::endl;
	// 	std::cout << "sum : " << sum << std::endl;
	// 	temp += buff_rcv; // 연결 소켓으로 받았다.
	// }
	int fd = open("file", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		perror("open_error: ");
		return (0);
	}
	int num = 0;
	char *temp2 = buff_rcv + num;
	if (write(fd, temp2, read_ret - num) < 0)
	{
		perror("close_error: ");
		close(fd);
		return (0);
	}
	close(fd);
	std::cout << "-= errno: " << errno << " " << std::strerror(errno) << " =-" << std::endl;
	// std::cout << buff_rcv << std::endl;
	close(server_socket);
	close(client_socket);
	return (0);
}