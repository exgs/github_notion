#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
using namespace std;

char buffer[100];

int main()
{
	int fd;
	int n;
	fd = open("./test2", O_RDONLY);
	perror("Error: ");
	cout << "fd: " << fd << endl;
	n = read(fd, buffer, 100);
	perror("Error: ");
	cout << "read: " << n << endl;
	close(fd);
	return (1);
}