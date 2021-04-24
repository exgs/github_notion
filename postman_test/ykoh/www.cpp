#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	unsigned int buf_size = 4200000000;
	char *buff_rcv = (char *)malloc(sizeof(char) * buf_size);

	int fd = open("www", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		perror("error: ");
		return (0);
	}
	// memset(buff_rcv, 0, buf_size);
	int num = 0;
	char *temp2 = buff_rcv + num;
	std::cout << write(fd, temp2, buf_size) << std::endl;
	close(fd);



	std::cout << "-=" << std::endl;
	std::cout << errno << " : "<< std::strerror(errno) << std::endl;
	perror("error: ");
	std::cout << "-=" << std::endl;
	// std::cout << buff_rcv << std::endl;
	return (1);
}
