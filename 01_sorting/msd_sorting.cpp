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

class msd
{
	private:
		vector<mytype> vec;
		vector<mytype> tmp_vec;
		unsigned int T;
		unsigned int get_char_at(string& str, int pos);
		void my_assert();
	public:
		void sort_array(int start, int end, unsigned int d);
		void sort_fun();
		void print_array();
		void validate_sorting();
		void validate_sorting_v2();
		msd() {}
//		void print_stl_sorted_array();
		void print_stl_sorted_array();
		bool is_smaller(string& v1, string& v2);
		bool is_smaller(unsigned char& v1, unsigned char& v2) { return (v1 < v2); }
		void read_input();
		void read_random_input(test_input& obj);
};

unsigned int msd::get_char_at(string& str, int pos)
{
	if(pos <= str.size()-1)
	{
		return str[pos];
	} else
	{
		return 0;
	}

}

void msd::my_assert()
{	
//	cout<<"Org- "; 
	cout<<"My - "; print_array();
	cout<<"Stl- "; print_stl_sorted_array();
	cout<<endl;
	assert(false);
}

void msd::read_input()
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

void msd::read_random_input(test_input& obj)
{
	vector<string> string_v;
	obj.generate_test_input(string_v);

	tmp_vec = vec = string_v;
}

void msd::sort_fun()
{
	sort(tmp_vec.begin(), tmp_vec.end());
	sort_array(0, vec.size()-1, 0);
}

void msd::sort_array(int start, int end, unsigned int d)
{
	if(start >= end)
		return ;

	vector<string> buf_vec = vec;

	int count[R+1];
	// Step 1:- Initialize the counter to 0.
	for(int i=0; i<=R; i++)
	{
		count[i] = 0;
	}

	//Step 2:- Fill the counter.
	for(int i=start; i<=end; i++)
	{
		count[1+get_char_at(vec[i],d)]++;
	}

	//Step 3:- Calculate the effective indexes.
	for(int i=1; i<=R; i++)
	{
		count[i] += count[i-1];
	}
	
	//Step 4:- Fill the final sorted values.
	for(int i=start; i<=end; i++)
	{
		buf_vec[start+count[get_char_at(vec[i],d)]] = vec[i];
		count[get_char_at(vec[i],d)]++;
	}
	vec = buf_vec;

	//Step 5:- Recursively sort the individual char positions.
	for(int i=0; i<R; i++)
	{
		sort_array(start+count[i],start+count[i+1]-1,d+1);
	}
}

void msd::print_array()
{
	for(int i=0; i<vec.size(); i++)
	{
		cout<<(vec[i]) <<" ";
	}
	cout<<endl;
}

void msd::print_stl_sorted_array()
{
    for(int i=0; i<tmp_vec.size(); i++)
    {
        cout<<(tmp_vec[i]) <<" ";
    }
    cout<<endl;
}

void msd::validate_sorting()
{
	if(tmp_vec.size() != vec.size())
	{
		assert(false);
	}

	for(int i=1; i<vec.size(); i++)
	{
		if(is_smaller(vec[i], vec[i-1]))
			my_assert();
	}
}

void msd::validate_sorting_v2()
{
	//sort(tmp_vec.begin(), tmp_vec.end());

    if(tmp_vec.size() != vec.size())
    {
        my_assert();
    }
	
    for(int i=0; i<vec.size(); i++)
    {
        if(tmp_vec[i] != vec[i])
            my_assert();
    }
	return;
}

bool msd::is_smaller(string& v1, string& v2)
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

	test_input in_obj(atoi(argv[1]), atoi(argv[2]));

	for(int k=1; k<10001; k++)
	{
		msd obj;
		obj.read_random_input(in_obj);
		//cout<<"Org- "; obj.print_array();
		obj.sort_fun(); 
		obj.validate_sorting(); obj.validate_sorting_v2();
		//cout<<"My - "; obj.print_array(); cout<<"Stl- "; obj.print_stl_sorted_array();
		if(k%100 == 0)
			cout<<"Executed test_count " << k << endl;
	}
	cout<<endl;
	return 0;
}
