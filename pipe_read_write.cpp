#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int     main(void) {
	int pid;
	int pipe_fd[2];
	pipe(pipe_fd);

	pid = fork();
	if (pid == 0)
	{
		char buffer[200];
		int ret = read(pipe_fd[0], buffer, 200);
		buffer[ret] = '\0';
		cout << "child: " <<buffer << endl;
		sleep(100);
		return (1);
	}
	else
	{
		// close(pipe_fd[0]);
		// close(pipe_fd[1]);
		const char *str = "hello world!";
		write(pipe_fd[1], str, strlen(str));
		char buffer[200];
		// sleep(1); // NOTE 어떤 프로세스에 먼저 도착하게 할지 알 수 없는데, 동기식으로 만들기위해 쉬어줌. 
		int ret = read(pipe_fd[0], buffer, 200);
		buffer[ret] = '\0';
		cout << "parent: " <<buffer << endl;


		waitpid(-1, NULL, 0);
		while(1);
		printf("I am parents process");
	}
	return 0;
}
// ./a.out & lsof -c a.out && ps au