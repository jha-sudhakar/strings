#include<assert.h>
#include<stdlib.h>
#include<time.h>

#include<vector>
#include<string>
#include<iostream>
using namespace std;
class plm
{
	private:
		string str;
		string palindrome_str;
		vector< vector<int> > a;

		void find_max_len_palindrome();
		void find_max_len_palindrome_dp();
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
	//str = string("abcba");

	find_max_len_palindrome();
	string str_bf = palindrome_str;

	palindrome_str.clear();
	find_max_len_palindrome_dp();
	string str_dp = palindrome_str;
	
	if(str_bf != str_dp);
	{
		//assert(false);
	}
	return str_dp;
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
			cout<<"Palindrome not found so asserting\n"; assert(false);
		}
		cout << endl;
	}
}


void plm::find_max_len_palindrome_dp()
{
	int plen=0, pstart=0;
	
	a.clear();
	const int n=str.size();
	a.resize(n); for(int i=0; i<n; i++) a[i].resize(n);
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			a[i][j] = 0;
	for(int i=0; i<n; i++)
	{
		a[i][i] = 1;
		pstart=i; plen = 1;
	}	
	for(int i=0; i<n-1; i++)
	{
		if(str[i] == str[i+1])
		{	a[i][i+1] = 1;
			pstart = i; plen = 2;
		}	
	}

	int start=0, end=0;
	for(int len=2; len<n; len++)
	{
		start=0;
		for(start=0; start<n; start++)
		{
			end = start + len;
			if(end > n-1)
				break;
			if(str[start] != str[end])
			{
				a[start][end] = 0;
			} else
			{
				a[start][end] = 1 * a[start+1][end-1];
				if(a[start][end])
				{
					if(end-start+1 > plen) 
					{ 
						plen = end-start+1; 
						pstart = start; 
					}
				}
			}
		}
	}
	if(plen > 0)
	{
		cout <<"\tdp-out- Palindrome-len= " << plen << " Palindrome= ";
		for(int i=0; i<plen; i++)
		{
			cout << str[pstart+i];
			palindrome_str.push_back(str[pstart+i]);
		}
		if (string::npos == str.find(palindrome_str))
		{
			cout<<"dp-palindrome not found so asserting\n"; assert(false);
		}
		cout << endl;
	} else
	{
		cout<<"\tdp- ***palindrome not found***, string= " << str <<"\n";
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
				cout << a[i][j] <<" ";
			cout<<endl;
		}	
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
