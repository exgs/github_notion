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
	fd = open("./test.png", O_RDONLY);
	perror("Error: ");
	cout << "fd: " << fd << endl;
	while ((n = read(fd, buffer, 100)) > 0)
	{
		cout << "read: " << n << endl;
	}
	perror("Error: ");
	close(fd);
	return (1);
}