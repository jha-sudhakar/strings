#include <string>
#include <vector>
#include <stdint.h>
#include<iostream>
using namespace std;

typedef uint64_t myint;
class rk_substr
{
	private:
		string key, text;
		myint hash_p, R, RM, Q;;
		vector<myint> index;
		void print_pattern_start_index();
		void set_key_hash();
	public:
		void read_input(string p, string t);
		bool is_pattern_found();
};

void rk_substr::read_input(string p, string t)
{
	//cin >> key >> text;
	key=p; text=t;
	cout<<"\nPattern= " <<key <<", Text= " << text << endl;

	set_key_hash();

	if(is_pattern_found())
		cout<<"Pattern matched\n";
	else
		cout<<"Pattern not matched\n";

	print_pattern_start_index();	
}

void rk_substr::print_pattern_start_index()
{
	if(index.size() == 0)
		return;

	cout<<"Matching index= ";
	for(int i=0; i< index.size(); i++)
		cout << index[i] << " ";
	cout<<endl;
}

void rk_substr::set_key_hash()
{
	Q = 997;
	R = 128;
	hash_p = 0;
	for(int i=0; i<key.size(); i++)
	{
		hash_p = (hash_p*R+ key[i])%Q;
	}

	RM = 1;
	for(int i=0; i<key.size()-1; i++)
	{
		RM = (RM*R) % Q;
	}
}

bool rk_substr::is_pattern_found()
{
	myint hash_t=0;

	if(text.size() < key.size())
	{
		return false;
	}


	for(int i=0; i<key.size(); i++)
	{
		hash_t = (hash_t*R+ text[i]) % Q;
	}

	for(int i=key.size(); i<text.size(); i++)
	{
		cout<<"Pattern_Hash= " << hash_p <<", Text_hash= " << hash_t << endl;
		if(hash_t == hash_p)
		{
			if(
			index.push_back(i-key.size());
		}
		myint tmp = (hash_t + Q - (RM*text[i-key.size()])%Q) % Q;
		hash_t = (tmp*R + text[i])%Q;

	}

	cout<<"Pattern_Hash= " << hash_p <<", Text_hash= " << hash_t << endl;

	if(hash_t == hash_p)
	{
		index.push_back(text.size() - key.size());
	}
	if(index.size())
		return true;
	
	return false;
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		cout<<"\nUsage:- exe pattern tex\n";
		return (0);
	}

	rk_substr obj;
	obj.read_input(string(argv[1]), string(argv[2]));

	return 0;
}
