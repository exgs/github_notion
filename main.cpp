#include "json_parsing.hpp"

int main()
{
	const char *filename = "1.json";
	int read_size = 10000;

	int buffer_size = read_size + 1;


	int fd = open(filename, O_RDWR | O_CREAT, 0755);
	if (fd < 0)
	{
		std::cout << "fd_error: " << fd << endl;
		return (-1);
	}
	char buffer[buffer_size];
	memset(buffer, 0, buffer_size);

	int ret = read(fd, buffer, read_size);
	if (ret < 0)
	{
		std::cout << "read_error: " << fd << endl;
		return (-1);
	}

	int sz_file  = lseek(fd,  0, SEEK_END);		// 파일의 끝 위치를 반환
	printf( "file size = %d\n", (int)sz_file);
	lseek(fd, 0, SEEK_SET);
	ret = read(fd, buffer, read_size);
	cout << ret << endl;
	cout << buffer << endl;
	char *doc = buffer;
	
	JSON json; memset(&json, 0, sizeof(JSON));
	parseJSON(doc, sz_file, &json);
	cout << "---------- ----------" << endl;
	for (size_t i = 0; i < json.token_count; i++)
	{
		cout << "i: " << i << " | " << json.tokens[i].string << endl;
	}


	return (1);
}