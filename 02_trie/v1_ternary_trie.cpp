#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

#include<vector>
#include<map>
#include<string>
#include<iostream>
using namespace std;

#define CHAR_COUNT 256

enum POS
{
LEFT,
MID,
RIGHT
};

struct node
{
	unsigned int count;
	unsigned char ch;
	struct node *lt, *eq, *gt;
	node() { count=0;ch=0; lt=eq=gt=NULL;}
	node(unsigned char _ch) { count = 0; ch=_ch; lt=eq=gt=NULL; }
};

struct pnode
{
	POS dir;
	node* n;
	pnode(POS _dir, node* _node) { dir=_dir; n=_node;}
};

class Trie3
{
	private:
		struct node root[CHAR_COUNT][CHAR_COUNT];
		void insert(node* cur_node, const string& str, unsigned int index);
		unsigned int word_count(const string& str);
	public:
		Trie3();
		void insert2(char c_str[]);
		void insert(const string& str);
		void delete2(string& str); //Will do last.
		bool find(const string& str);
		unsigned int frequency(const string& str);
};

Trie3::Trie3()
{
	for(int i=0; i<CHAR_COUNT; i++)
	{
		for(int j=0; j<CHAR_COUNT; j++)
		{
			root[i][j].ch = j;
		}
	}
}

void Trie3::insert2(char c_str[]) 
{ 
	const string& ref_str = string(c_str);
	insert(ref_str);; 
}

void Trie3::insert(const string& str)
{
	if(str.size() == 0)
	{
		return;
	}	
	else if(str.size() == 1)
	{
		root[str[0]][0].count++;
		return;
	}
	else if(str.size() == 2)
	{
		root[str[0]][str[1]].count++;
		return;
	}

	insert(&root[str[0]][str[1]], str,2);
}

void Trie3::insert(node* base_parent, const string& str, unsigned int index)
{
	node* parent = base_parent;
	while(index < str.size())
	{
		if(parent->ch < str[index])
		{
			if(parent->gt == NULL)
			{
				parent->gt = new node(str[index]);
			}	
			index++;
			parent = parent->gt;
		}
		else if(parent->ch == str[index])
		{
			if(parent->eq == NULL)
			{
				parent->eq = new node(str[index]);
			}	
			index++;
			parent = parent->eq;
		}
		else
		{
			if(parent->lt == NULL)
			{
				parent->lt = new node(str[index]);
			}	
			index++;
			parent = parent->lt;
		}
	}
	// Once the loop ends, pointer is at node having last char so increment it;
	parent->count++;
}

void Trie3::delete2(string& str)
{

	if(str.size() == 0)
	{
		return;
	}	
	else if(str.size() == 1)
	{
		root[str[0]][0].count--;
		return;
	}
	else if(str.size() == 2)
	{
		root[str[0]][str[1]].count--;
		return;
	}

	unsigned int index = 2;
	node* parent = &root[str[0]][str[1]];
	vector<pnode> search_path;

	while(index < str.size())
	{

		if(parent->ch < str[index])
		{
			if(parent->gt == NULL)
			{
				return;
			}	
			index++;
			search_path.push_back(pnode(RIGHT,parent));
			parent = parent->gt;
		}
		else if(parent->ch == str[index])
		{
			if(parent->eq == NULL)
			{
				return;
			}	
			index++;
			search_path.push_back(pnode(MID,parent));
			parent = parent->eq;
		}
		else
		{
			if(parent->lt == NULL)
			{
				return;
			}	
			index++;
			search_path.push_back(pnode(LEFT,parent));
			parent = parent->lt;
		}
	}
	node* child = parent;
	// Once the loop ends, pointer is at node having last char so decrement it;
	if(parent->count >0)
	{
		parent->count--;
	} else
	{
		search_path.clear(); // Not found so clear the path.
		return;
	}

	// Delete the path/sub-path if this is the only word on this path.
	while(search_path.size())
	{
		pnode pn = search_path[search_path.size()-1];
		search_path.pop_back();
		switch (pn.dir)
		{
			case LEFT:
				delete child;
				child = pn.n;
				pn.n->lt = NULL;
				break;
			case MID:
				delete child;
				child = pn.n;
				pn.n->eq = NULL;
				break;

			case RIGHT:
				delete child;
				child = pn.n;
				pn.n->gt = NULL;
				break;
		}
	}
}

unsigned int Trie3::word_count(const string& str)
{
	if(str.size() == 0)
	{
		return 0;
	}	
	else if(str.size() == 1)
	{
		return root[str[0]][0].count;
	}
	else if(str.size() == 2)
	{
		return root[str[0]][str[1]].count;
	}

	unsigned int index = 2;
	node* parent = &(root[str[0]][str[1]]);
	while(index < str.size())
	{
		if(parent->ch < str[index])
		{
			if(parent->gt == NULL)
			{
				return 0;
			}	
			index++;
			parent = parent->gt;
		}
		else if(parent->ch == str[index])
		{
			if(parent->eq == NULL)
			{
				return 0;
			}	
			index++;
			parent = parent->eq;
		}
		else
		{
			if(parent->lt == NULL)
			{
				return 0;
			}	
			index++;
			parent = parent->lt;
		}
	}
	return parent->count;
}

unsigned int Trie3::frequency(const string& str)
{
	return word_count(str);
}

bool Trie3::find(const string& str)
{
	unsigned int ret= word_count(str);
	if(ret)
		return true;
	else
		return false;
}

int main(int argc, char* argv[])
{

if(argc != 4)
{
cout<<" exe insert/delete-op-count validate-op-count iteration-count\n";
cout<<" Example ==>  ./a.out 200 40 10\n";
return 0;
}

Trie3 obj1;
map<string, unsigned int> dict;
map<string, unsigned int>::iterator map_itr;

const char* words_arr[]= {"abc", "pqr", "lmn", "xyz", "zzz", "aaa", "pqrz", "pq", "pqq", "pqrr"};
vector<string> str_vec(words_arr, words_arr+sizeof(words_arr)/sizeof(words_arr[0])); 
unsigned int v_len = str_vec.size();

unsigned int loop = atoi(argv[3]);
while(loop > 0)
{
	unsigned int count = atoi(argv[1]);
	srand(time(NULL));

	for(int i=0; i<count; i++)
	{

		unsigned int random_int = rand()%v_len;
		if(random_int%2)// Odd num then insert else delete;
		{
			//cout<< i+1 << "  Inserting " << str_vec[random_int] << endl;
			obj1.insert(str_vec[random_int]);
			map_itr = dict.find(str_vec[random_int]);
			if(map_itr == dict.end())
				dict[str_vec[random_int]] = 1;
			else
				map_itr->second++;
		} 
		else
		{
			//cout<< i+1 << "  Deleting " << str_vec[random_int] << endl;
			obj1.delete2(str_vec[random_int]);
			map_itr = dict.find(str_vec[random_int]);
			if(map_itr != dict.end())
				if(map_itr->second >0)
					map_itr->second--;

		}
	}

	unsigned int search_count = atoi(argv[2]);
	for(unsigned int i=0; i<search_count; i++)
	{
		unsigned int random_int = rand()%v_len;
		unsigned int trie_ret=0, map_ret=0;

		trie_ret = obj1.frequency(str_vec[random_int]);
		
		map_itr = dict.find(str_vec[random_int]);
		if(map_itr != dict.end()) map_ret = map_itr->second;

		if(trie_ret != map_ret)
			assert(false);

		//cout<< i+1 <<"  " << str_vec[random_int] << " matched , count= " << map_ret << endl;
	}
	
	cout <<" Loop " << loop <<" finished\n";
	loop--;
}

return 0;
}
