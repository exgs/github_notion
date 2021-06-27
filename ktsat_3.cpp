#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 1. node의 속성
// - 내 노드의 아이디
// - 인형의 이름 혹은 특징
// - 부모 노드의 아이디
// 2. 리프노드는 인형의 이름, 리프 노드가 아닌 경우에는 특징이 담김

// TODO list
// 데이터를 구조체에 담고, leaf, non-leaf 나누기
// 일치하는 것을 다 뽑아내기
// 그 다음에 순서를 정해서 알맞은 형태로 return하는 것으로 하자

struct Rank
{
	int same_word = 0;
	vector<int> same_word_idx; // same_word_idx.size() == same_word
};

class Node
{
	public:
		int inode;
		std::string value;
		int pnode;
		int dnode_num = 0;
		int totalnode;

	// dnode_num == 0인 경우에, 아래 있는 속성값들을 채워나간다.
	public:
		Rank rank;

};

void print_nodes(Node *nodelist);
void print_vnodes(std::vector<Node> v_nodes);



void SetAnswer(std::vector<string> answer, std::vector<Node> find_list)
{
	std::vector<Node> arranged_list;
	bool flag = false;
	for (size_t i = 0; i < find_list.size(); i++)
	{
		if (arranged_list.size() == 0)
			arranged_list.push_back(find_list[i]);
		else
		{
			Rank &rank = find_list[i].rank;
			vector<Node>::iterator it = arranged_list.begin();
			while (it != arranged_list.end())
			{
				if (it->rank.same_word < rank.same_word)
				{
					arranged_list.insert(it, find_list[i]);
					flag = true;
					break ;
				}
				else if (it->rank.same_word == rank.same_word) // 이 코드 블록에 들어오면, 결판 보게 됨
				{
					while (it != arranged_list.end())
					{
						int x = 0;
						while (x < rank.same_word_idx.size())
						{
							if (it->rank.same_word_idx[x] > rank.same_word_idx[x])
							{

								arranged_list.insert(it, find_list[i]);
								flag = true;
								break ;
							}
							if (x == rank.same_word_idx.size())
							{
								if (it->inode > find_list[i].inode)
								{
									arranged_list.insert(it, find_list[i]);
									flag = true;
									break ;
								}
								else
								{
									it++;
									arranged_list.insert(it, find_list[i]);
									flag = true;
									break ;
								}
							}
							x++;
							if (flag == true)
								break;
						}
						if (flag == true)
							break;
						it++;
					}
					if (flag == true)
						break;
					// arranged_list.insert(it, find_list[i]);
					// break;
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

void SetLeafRank(Node &leafnode, string word)
{
	
	std::string &name = leafnode.value;
	Rank &rank = leafnode.rank;
	size_t before_length = 0;
	size_t idx = 0;
	while ((idx = name.find(word, before_length)) != string::npos)
	{

		rank.same_word++;
		rank.same_word_idx.push_back(idx);
		before_length += idx + word.length();
	}
}


vector<string> solution(vector<string> data, string word)
{
	Node nodelist[data.size()];
	vector<string> answer;

	for (size_t i = 0; i < data.size(); i++)
	{
		std::string temp;
		int idx;
		idx = data[i].find(' ');
		temp = data[i].substr(0, idx);
		nodelist[i].inode = stoi(temp);
		data[i] = data[i].substr(idx + 1, string::npos);
		
		idx = data[i].find(' ');
		temp = data[i].substr(0, idx);
		nodelist[i].value = temp;
		data[i] = data[i].substr(idx + 1, string::npos);
		
		idx = data[i].find(' ');
		temp = data[i].substr(0, idx);
		nodelist[i].pnode = stoi(temp);
		data[i] = data[i].substr(idx + 1, string::npos);

		nodelist[i].totalnode = data.size();
	}

	// STUB leaf와 non-leaf를 나눔
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

	vector<Node> find_list;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (nodelist[i].dnode_num != 0)
			continue;
		if (nodelist[i].value.find(word) != string::npos)
		{
			// TODO function
			SetLeafRank(nodelist[i], word);
			find_list.push_back(nodelist[i]);
		}
	}
	

	cout << "Total find: " << find_list.size() << endl;

	//TODO find_list에 있는 것들

	// STUB debugging
	print_vnodes(find_list);
	// print_nodes(nodelist);
	return (answer);
}

int main()
{
	string arr[] = {"1 GRAY 0", "2 MUSSEUK 0", "3 DOLL 1", "4 DOLL 2", "5 LARGE-GRAY 3", "6 SMALL-GRAY 3", "7 WHITE-MUSSEUK 4", "8 GRAY-MUSSEUK 4"};
	std::vector<string> v;
	for (size_t i = 0; i < 8; i++)
	{
		std::string temp = arr[i];
		v.push_back(temp);
	}
	vector<string> answer =  solution(v, "GRAY");

	// for (size_t i = 0; i < 8; i++)
	// {
	// 	cout << v[i] << endl;
	// }	
	return (0);
}


void print_nodes(Node *nodelist)
{
	int total_node = nodelist->totalnode;
	for (size_t i = 0; i < total_node; i++)
	{
		cout << "------------------" << endl;
		cout << "inode: " << nodelist[i].inode << endl;
		cout << "value: " << nodelist[i].value << endl;
		cout << "pnode: " << nodelist[i].pnode << endl;
		cout << "dnodenum: " << nodelist[i].dnode_num << endl;
		cout << "totalnode: " << nodelist[i].totalnode << endl;
	}
}

void print_vnodes(std::vector<Node> v_nodes)
{
	for (size_t i = 0; i < v_nodes.size(); i++)
	{
		cout << "------------------" << endl;
		cout << "inode: " << v_nodes[i].inode << endl;
		cout << "value: " << v_nodes[i].value << endl;
		cout << "pnode: " << v_nodes[i].pnode << endl;
		cout << "dnodenum: " << v_nodes[i].dnode_num << endl;
		cout << "totalnode: " << v_nodes[i].totalnode << endl;
		cout << "rank.same_word: " << v_nodes[i].rank.same_word << endl;
		for (size_t j = 0; j < v_nodes[i].rank.same_word_idx.size(); j++)
		{
			cout << "    rank.same_word_idx: " << v_nodes[i].rank.same_word_idx[j] << endl;
		}
	}
}

/*

["1 GRAY 0", "2 MUSSEUK 0", "3 DOLL 1", "4 DOLL 2", "5 LARGE-GRAY 3", "6 SMALL-GRAY 3", "7 WHITE-MUSSEUK 4", "8 GRAY-MUSSEUK 4"]
"GRAY"
["MUSSEUK/DOLL/GRAY-MUSSEUK", "GRAY/DOLL/LARGE-GRAY", "GRAY/DOLL/SMALL-GRAY"]

["1 GRAY 0", "2 MUSSEUK 0", "3 DOLL 1", "4 DOLL 2", "5 LARGE-GRAY 3", "6 SMALL-GRAY 3", "7 WHITE-MUSSEUK 4", "8 GRAY-MUSSEUK 4"]
"KITTY"
["Your search for (KITTY) didn't return any results"]

["1 ROOTA 0", "2 AA 1", "3 ZZI 1", "4 AABAA 1", "5 AAAAA 1", "6 AAAA 1", "7 BAAAAAAA 1", "8 BBAA 1", "9 CAA 1", "10 ROOTB 0", "11 AA 10"]
"AA"
["ROOTA/AA", "ROOTB/AA", "ROOTA/BAAAAAAA", "ROOTA/AAAAA", "ROOTA/AAAA", "ROOTA/AABAA", "ROOTA/CAA", "ROOTA/BBAA")

*/