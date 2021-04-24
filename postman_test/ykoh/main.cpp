#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#include "HttpMessage.hpp"

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
    if (-1 == bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
	{
		write(1, "bind error\n", 11);
		exit(1);
	}
	if (-1 == listen(server_socket, 5))
	{
		write(1, "listen error\n", 13);
		exit(1);
	}


    /* 1. client socket(연결 소켓) 을 만들자. */
    struct sockaddr_in client_addr;
    memset(&server_addr, 0, sizeof(client_addr));
    unsigned int client_addr_size = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);

    if (-1 == client_socket)
    {
        write(1, "client socket error\n", 20);
        exit(1);
    }
	// std::cout << "read size: " << read(client_socket, buff_rcv, buf_size) << std::endl;

	int		read_ret = 0;
	int		sum = 0;

	int flags = fcntl(client_socket, F_GETFL, 0);
	flags |= O_NONBLOCK;	
	fcntl(client_socket, F_SETFL, flags);
	errno = 0;
	signal(SIGINT, SIG_IGN);

	buf_size = 100000;
    char buff_rcv[buf_size];
	memset(buff_rcv, 0, buf_size);
	// std::cout << "read: " << (read_ret = read(client_socket, buff_rcv, buf_size)) << std::endl;

	char *temp3 = buff_rcv;
	for (size_t i = 0; i < 10; i++)
	{
		if (-1 == (read_ret = read(client_socket, temp3, buf_size/10)))
			continue;
		temp3 += read_ret;
		std::cout << "-" << std::endl;
	}
	

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
		perror("error: ");
		return (0);
	}
	int num = 0;
	char *temp2 = buff_rcv + num;
	write(fd, temp2, buf_size - num);
	close(fd);

	std::cout << "-=" << std::endl;
	std::cout << std::strerror(errno) << std::endl;
	std::cout << "-=" << std::endl;

	std::cout << buff_rcv << std::endl;

	// NOTE 버퍼에 모든게 다들어 왔다는 가정하에 작업중
	//		실제로는 긴 경우 나눠 담기게 될탠데 이럴땐 먼저 다 받아 놓은 다음 작업하는게 맞지 않을까? RFC에서 비슷한 내용 본것같음 invalid message
	//		buffer의 마지막을 판단하려면..? NULL문자 붙여주면 베스트이긴한데..
    //*****************************************************//
	// HttpMessageRequest	message(const_cast<char*>(temp.c_str()));
	// HttpMessageRequest	message(buff_rcv);
    //*****************************************************//

    // write(1, buff_rcv, strlen(buff_rcv));

    close(client_socket);
    return (0);
}