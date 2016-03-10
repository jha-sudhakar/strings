
#include <iostream>
using namespace std;

class bm
{
	private:
		string pattern, text;
		bool is_sub_str();
		int  index[256];
		int p_len, t_len;
	public:
		void process_input();
		void process_input(string _pattern, string _text);
		void build_index_table();

};

bool bm::is_sub_str()
{
	if( text.size() < pattern.size())
	{
		cout<<"No :- Match not found!\n";
		return false;
	}

	cout<<"Pattern= " <<pattern <<", Text= " << text << endl;
	for(int i=0; i<=(text.size()-pattern.size()); )
	{	
		bool is_found = true;
		for(int k=pattern.size()-1; k>=0; k--)
		{
		
			if(pattern[k] != text[i+k])
			{
				is_found = false;
				if(index[text[i+k]] == pattern.size())
				{
					i = i+pattern.size();
				}
				 else
				{
					int shift = k - index[text[i+k]];
					if(shift<0)
						shift = 1;

					i = i+shift;
				}
				break;
			}
		}
		if(true == is_found)
		{
			cout<<"Yes:- Match found!\n";
			return true;
		}

	}

	cout<<"No :- Match not found!\n";
}


void bm::process_input(string _pattern, string _text)
{
    pattern = _pattern;
    text = _text;

    p_len = pattern.size();
    t_len = text.size();

    build_index_table();
    is_sub_str();
}

void bm::process_input()
{
	cin >> pattern;
	cin >> text;

	p_len = pattern.size();
	t_len = text.size();

	build_index_table();
	is_sub_str();
}


void bm::build_index_table()
{
	for(int i=0; i<256; i++)
	{
		index[i] = pattern.size();
	}

	for(int i=0; i<pattern.size(); i++)
	{
		index[pattern[i]] = i;
	}
}


int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		cout<<"Usage:- exe pattern text\n";
		return 0;
	}

bm obj;
obj.process_input(string(argv[1]), string(argv[2]));
return 0;
}
