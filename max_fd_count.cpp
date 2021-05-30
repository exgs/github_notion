#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

// NOTE 이런 뉘앙스로 fd_max 값을 계산하고 관리하자

int main()
{
	int server_socket_count = 3;
	int max_fd = 2 + server_socket_count;

	int client_socket_count = 0;
	while (1)
	{
		int new_fd;
		new_fd = open("./example.json", O_RDONLY);
		cout << "new_fd " << new_fd << endl;
		close(new_fd);
		client_socket_count++;
		if (new_fd > max_fd)
		{
			max_fd = new_fd;
		}

		// STUB 시간이 지나면 연결이 끊어지는 순간이 있겠지
		if (client_socket_count == 1000)
			client_socket_count = 0;

		if (client_socket_count == 0)
		{
			max_fd = 2 + server_socket_count;
		}
	}
	// 0,1,2, (server socket count)..3~5

	return (1);
}