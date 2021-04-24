#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

using namespace std;

int main()
{
	int fd;
	int n;
	fd = open("test2", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	// fd = open("output", O_CREAT|O_WRONLY, 0777)
	perror("Error: ");
	cout << "fd: " << fd << endl;
	n = write(fd, "abc\0", 4);
	perror("Error: ");
	cout << "write: " << n << endl;
	close(fd);
	return (1);
}