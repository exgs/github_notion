//test_ktsat3.cpp
#include <iostream>

vector<string> solution(vector<string> data, string word)
{
	node nodelist[data.size()];
	vector<string> answer;

	for (size_t i = 0; i < data.size(); i++)
	{
		char *stringToChar = new char[data[i].size() + 1];
		strlcpy(stringToChar, data[i].c_str(), data[i].size() + 1);
		char *ptr = NULL;
		ptr = strtok(stringToChar, " ");
		std::string temp(ptr);
		// cout << "ptr: " << ptr << endl;
		nodelist[i].inode = stoi(temp);
		ptr = strtok(NULL, " ");
		std::string temp1(ptr);
		cout << "ptr: " << temp1 << endl;
		nodelist[i].value = temp1;
		ptr = strtok(NULL, " ");
		cout << "ptr: " << ptr << endl;
		std::string temp2(ptr);
		cout << "string_size: " << temp2.size() << endl;
		// if (temp2[0] == '0')
			temp2 = "0";
		cout << "string: " << temp2 << endl;
		nodelist[i].pnode = stoi(temp2);
		// ptr = strtok(NULL, " ");
		nodelist[i].Totalnode = data.size();
		if (ptr == NULL)
		{
			cout << "OK" << endl;
		}
		delete []stringToChar;
	}



	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = 0; j < data.size(); j++)
		{
			if (nodelist[i].inode == nodelist[j].pnode)
			{
				nodelist[i].dnode_num++;
			}
		}
	}

	print_nodes(nodelist);

	return (answer);
}

/*
*/

void SetAnswer(std::vector<string> answer, std::vector<node> find_list)
{
	std::vector<node> arranged_list;
	for (size_t i = 0; i < find_list.size(); i++)
	{
		if (arranged_list.size() == 0)
			arranged_list.push_back(find_list[i]);
		else
		{
			Rank &rank = find_list[i].rank;
			vector<node>::iterator it = arranged_list.begin();
			while (it != arranged_list.end())
			{
				if (it->rank.same_word <= rank.same_word)
				{
					arranged_list.insert(it, find_list[i]);
					break;
				}
				it++;
			}
			if (it == arranged_list.end())
				arranged_list.insert(it, find_list[i]);
			it = arranged_list.begin(); // 재할당이 필요함.

			while (it != arranged_list.end())
			{
				if (it->rank.same_word != rank.same_word)
					continue;
				else
				{
					int z = 0;
					while (z < rank.same_word_idx.size())
					{
						if ()
						z++;
					}
				}
				it++;
			}
			
			// for (size_t j = 0; j < arranged_list.size(); j++)
			// {
			// 	if (arranged_list[i].rank.same_word != find_list[i].rank.same_word)
			// 		continue;
			// 	else
			// 	{

			// 	}
			// }
			
		}
	}
}