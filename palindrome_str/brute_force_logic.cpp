#include<assert.h>
#include<stdlib.h>
#include<time.h>

#include<string>
#include<iostream>
using namespace std;
class plm
{
	private:
		string str;
		string palindrome_str;

		void find_max_len_palindrome();
		void generate_string();
	public:
		plm() { srand(time(NULL)); }
		string process_input();
		string process_input(string s);
};

void plm::generate_string()
{
	string &buf = str;
	str.clear(); palindrome_str.clear();
	int min_str_len = rand()%30;
	for(int i=0; i<min_str_len; i++)
	{
		buf.push_back(97+ rand()%26);
	}
	int palindrome_size=0;
	int odd = 0;
	if(min_str_len > 5)
	{
		palindrome_size= rand()% (min_str_len-5);
		int cur_index = buf.size()-1;

		if(rand()%2)
		{
			odd++;
			buf.push_back(97+ rand()%26);
		}

		for(int i=0; i<palindrome_size; i++)
			buf.push_back(buf[cur_index-i]);
	}
	for(int i=0; i<min_str_len; i++)
	{
		buf.push_back(97+ rand()%26);
	}

	cout<<"\tin-Palindrome-len= " << palindrome_size*2 + odd  <<" string= " << str << endl;
}

string plm::process_input()
{
	generate_string();
	find_max_len_palindrome();
	return palindrome_str;
}

string plm::process_input(string s)
{
	str = s;
	find_max_len_palindrome();
	return palindrome_str;
}


void plm::find_max_len_palindrome()
{
	int plen=-1, pstart=0;
#if 1
	if(str.size() <2)
	{
		plen = str.size();
	} else if(str.size() == 2)
	{
		if(str[0] == str[1])
			plen= 2;
		else
			plen= 1;
	}
#endif
	else
	for(int len = str.size()-1; len>1; len--)
	{
		int start = -1;
		for(start=0; start<str.size()-1; start++)
		{
				int start_index = start;
				int end_index = start+len;
				if(end_index > str.size()-1)
					break;
				while(start_index < end_index)
				{
					if(str[start_index ] == str[end_index])
					{
						start_index ++; end_index--;
					}
					else
						break;

				}
				if(start_index  >end_index && start_index >start)
				{
					if(2*(start_index -start) > plen) { plen = 2*(start_index-start); pstart = start; };
				}
				else if(start_index  == end_index && start_index >start)
				{
					if(2*(start_index -start)+1 > plen) { plen = 2*(start_index-start)+1; pstart = start; };
				}
		}
	}

	if(plen > 0)
	{
		cout <<"\tout- Palindrome-len= " << plen << " Palindrome= ";
		for(int i=0; i<plen; i++)
		{
			cout << str[pstart+i];
			palindrome_str.push_back(str[pstart+i]);
		}
		if (string::npos == str.find(palindrome_str))
		{
			assert(false);
		}
		cout << endl;
	}
}
class Solution {
public:
    string longestPalindrome(string s)
	{
		plm obj;
		return obj.process_input(s);

	}
};

int main(int argc, char* argv[])
{
plm obj;
int loop = atoi(argv[1]);
for(int i=0; i<loop; i++)
{
	obj.process_input();
	cout << i+1 << " loop completed\n";
}
return 0;
}
