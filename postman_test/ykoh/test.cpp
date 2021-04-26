#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
using namespace std;

int main()
{
	int fd;
	char *buf;
	int size = 2100000000;
	buf = (char *)malloc(sizeof(char) * size);
	memset(buf, 0, size);
	int sum = 0;
	fd = open("./100,000,000byte", O_RDONLY); cout << fd << endl;
	int ret = read(fd, buf, size); cout << ret << endl;
	sum += ret;
	ret = read(fd, buf, size); cout << ret << endl;
	sum += ret;
	ret = read(fd, buf, size); cout << ret << endl;
	sum += ret;
	close(fd);
	return (1);
}