#include "input_generate.cpp"

#include <stdlib.h>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <iostream>
using namespace std;

//typedef unsigned char mytype;
typedef string  mytype;
#define R 256

class lsd
{
	private:
		vector<mytype> vec;
		vector<mytype> tmp_vec;
		unsigned int T;

	public:
		void sort_array();
		void print_array();
		void validate_sorting();
		void validate_sorting_v2();
		lsd() {}
//		void print_stl_sorted_array();
		void print_stl_sorted_array();
		bool is_smaller(string& v1, string& v2);
		bool is_smaller(unsigned char& v1, unsigned char& v2) { return (v1 < v2); }
		void read_input();
		void read_random_input(unsigned int testcase_count, unsigned int string_length);
};

void lsd::read_input()
{
	cin >> T;
	string buf;
	while(cin >> buf)
	{
		vec.push_back(buf);
	}
	if(T != vec.size())
		assert(false);

	tmp_vec = vec;
	cout<<"\n Input size= " << T << endl;
}

void lsd::read_random_input(unsigned int testcase_count, unsigned int string_length)
{
	test_input obj(testcase_count, string_length);
	vector<string> string_v;
	obj.generate_test_input(string_v);

	tmp_vec = vec = string_v;
}


void lsd::sort_array()
{
	vector<string> prev; prev.resize(vec.size());
	vector<string> cur; cur = vec;

	for(int d=vec[0].size()-1; d>=0; d--)
	{
		unsigned int count[R+1];
		// Step 1:- Initialize the counter to 0.
		for(int i=0; i<=R; i++)
		{
			count[i] = 0;
		}

		//Step 2:- Fill the counter.
		for(int i=0; i<vec.size(); i++)
		{
			count[1+cur[i][d]] ++;
		}

		//Step 3:- Calculate the effective indexes.
		for(int i=1; i<R; i++)
		{
			count[i] += count[i-1];
		}
		
		//Step 4:- Fill the final sorted values.
		unsigned int cur_index = 0;
		prev.clear(); prev.resize(vec.size());

		for(int i=0; i<cur.size(); i++)
		{
			prev[count[cur[i][d]]] = cur[i];
			count[cur[i][d]]++;
		}
		cur = prev;	
	}
	vec = cur;
}

void lsd::print_array()
{
	for(int i=0; i<vec.size(); i++)
	{
		cout<<(vec[i]) <<" ";
	}
	cout<<endl;
}

void lsd::print_stl_sorted_array()
{
    for(int i=0; i<tmp_vec.size(); i++)
    {
        cout<<(tmp_vec[i]) <<" ";
    }
    cout<<endl;
}

void lsd::validate_sorting()
{
	if(tmp_vec.size() != vec.size())
	{
		assert(false);
	}

	for(int i=1; i<vec.size(); i++)
	{
		if(is_smaller(vec[i], vec[i-1]))
			assert(false);
	}
}

void lsd::validate_sorting_v2()
{
	sort(tmp_vec.begin(), tmp_vec.end());

    if(tmp_vec.size() != vec.size())
    {
        assert(false);
    }
	
    for(int i=0; i<vec.size(); i++)
    {
        if(tmp_vec[i] != vec[i])
            assert(false);
    }
	return;
}

bool lsd::is_smaller(string& v1, string& v2)
{
	if(v1.compare(v2) < 0)
	{
		return true;
	} else
	{
		return false;
	}
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		cout<<"\n Usage:- Exe Test-count Str-len\n";
		exit(0);
	}

	for(int k=1; k<3; k++)
	{
		lsd obj;
		obj.read_random_input(atoi(argv[1]), atoi(argv[2]));
		cout<<"Org- "; obj.print_array();
		obj.sort_array(); 
		obj.validate_sorting(); obj.validate_sorting_v2();
		cout<<"My - "; obj.print_array();
		cout<<"Stl- "; obj.print_stl_sorted_array();
		if(k%25 == 0)
			cout<<"Executed test_count " << k << endl;
	}
	cout<<endl;
	return 0;
}
