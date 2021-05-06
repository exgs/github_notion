#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <fcntl.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
using namespace nlohmann;



int main()
{
	const char *filename = "serverconfig.json";
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
	std::cout << buffer << endl;

	std::string temp2;
	temp2.assign(buffer, strlen(buffer));
	json j;
	std::ifstream infile("serverconfig.json");
	infile >> j;
	std::cout << j.is_null() << std::endl;
	// j.parse(buffer);
	auto j3 = json::parse(R"({"happy": true, "pi": 3.141})");
	
	
	std::vector<std::uint8_t>v(temp2.begin(), temp2.end());
	std::cout << v.size() << std::endl;
	json j4 = json::parse(v.begin(), v.end());
	std::cout << j4.dump() << std::endl;
	// j.sax_parse(temp2);
	// j.sax
	
	// ofstream outfile("pretty.json");
	// outfile << std::setw(4) << j << std::endl;
	


	return (1);
}