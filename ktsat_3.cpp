#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

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

	public:
		// dnode_num == 0인 경우에, rank 구조체 값을 채움
		Rank rank;

};

void print_nodes(Node *nodelist);
void print_vnodes(std::vector<Node> v_nodes);

#define CHANGE 1
#define SAME 0
#define UNCHANGE -1

vector<string> Setanswer(std::vector<Node> &find_list, Node *nodelist, int nodelist_total)
{
	vector<string> answer;
	string temp;
	int pnode = -1;
	std::vector<Node>::iterator it = find_list.begin();
	while (it != find_list.end())
	{
		temp = it->value;
		pnode = it->pnode;
		while (pnode != 0)
		{
			for (size_t i = 0; i < nodelist_total; i++)
			{
				if (pnode == nodelist[i].inode)
				{
					pnode = nodelist[i].pnode;
					temp.insert(0, nodelist[i].value + "/");
					break;
				}
			}
		}
		answer.push_back(temp);
		it++;
	}
	return (answer);
}

int classify_same_word_idx(std::vector<int> cur, std::vector<int> before)
{
	for (size_t i = 0; i < cur.size(); i++)
	{
		if (cur[i] < before[i])
			return (CHANGE);
		else if (cur[i] > before[i])
			return (UNCHANGE);
	}
	return SAME;
}

void Sort_find_list(std::vector<Node> &find_list, string word)
{
	if (find_list.size() == 0)
		return ;
	std::vector<Node>::iterator cur = find_list.begin();
	std::vector<Node>::iterator before = cur;
	int i = 0;
	while (cur != find_list.end())
	{
		bool flag = false;
		if ((cur->value.size() != word.size() && before->value.size() == word.size()))
		{

		}
		else if ((cur->value.size() == word.size() && before->value.size() != word.size()))
		{
			iter_swap(cur, before);
			flag = true;
		}
		else if ((cur->value.size() == word.size() && before->value.size() == word.size()))
		{
			if (cur->inode < before->inode)
			{
				iter_swap(cur, before);
				flag = true;
			}
		}
		else
		{
			if (cur->rank.same_word < before->rank.same_word)
			{}
			else if (cur->rank.same_word > before->rank.same_word)
			{
				iter_swap(cur, before);
				flag = true;
			}
			else // (cur->rank.same_word == before->rank.same_word)
			{
				int flag_same_word = classify_same_word_idx(cur->rank.same_word_idx, 
											before->rank.same_word_idx);
				if (flag_same_word == UNCHANGE)
				{}
				else if (flag_same_word == CHANGE)
				{
					iter_swap(cur, before);
					flag = true;
				}
				else // SAME
				{
					if (cur->inode < before->inode)
					{
						iter_swap(cur, before);
						flag = true;
					}
				}
			}
		}
		if (flag == true)
		{
			cur = find_list.begin();
			before = cur;
		}
		else
		{
			before = cur;
		}
		cur++;
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
		before_length = idx + word.length();
	}
}


vector<string> solution(vector<string> data, string word)
{
	Node nodelist[data.size()];
	vector<string> answer;

	// STUB 1. string 데이터를 struct 데이터로 변환해서 담음
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

	// STUB 2. leaf와 non-leaf를 나누는 기준을 만들기위해서 구조체에 dnode_num을 추가함
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

	// STUB 3. word가 들어가는 node를 find_list에 넣어둠
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
	if (find_list.size() == 0)
	{
		string temp = "Your search for (" + word + ") didn't return any results";
		answer.push_back(temp);
		return (answer);
	}

	// STUB 4. find_list를 문제조건에 따라서, Sorting함
	Sort_find_list(find_list, word);
	// STUB 5. find_list value값을 가공하여 string 형태로 return함.
	answer = Setanswer(find_list, nodelist, data.size());

	// STUB PRINT
	print_vnodes(find_list);
	cout << "Total find: " << find_list.size() << endl;
	for (size_t i = 0; i < answer.size(); i++)
	{
		cout << answer[i] << endl;
	}
	return (answer);
}

int main()
{
	std::vector<string> v = {"1 ROOTA 0", "2 AA 1", "3 ZZI 1", "4 AABAA 1", "5 AAAAA 1", "6 AAAA 1", "7 BAAAAAAA 1", "8 BBAA 1", "9 CAA 1", "10 ROOTB 0", "11 AA 10"};
	vector<string> answer =  solution(v, "AA");

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