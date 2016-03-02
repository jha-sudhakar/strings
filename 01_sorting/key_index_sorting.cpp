#include <stdlib.h>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <iostream>
using namespace std;

typedef unsigned char mytype;
#define R 256
class key_index_count
{
	private:
		vector<mytype> vec;
		vector<mytype> tmp_vec;

	public:
		void sort_array();
		void print_array();
		void validate_sorting();
		key_index_count(vector<mytype>& arg_v) {vec = arg_v; tmp_vec = arg_v; sort(tmp_vec.begin(), tmp_vec.end());}
		void print_stl_sorted_array();
};

void key_index_count::sort_array()
{
	mytype count[R];
	// Step 1:- Initialize the counter to 0.
	for(int i=0; i<R; i++)
	{
		count[i] = 0;
	}

	//Step 2:- Fill the counter.
	for(int i=0; i<vec.size(); i++)
	{
		count[vec[i]] ++;
	}

	//Step 3:- Calculate the effective indexes.
	for(int i=1; i<R; i++)
	{
		count[i] += count[i-1];
	}
	
	//Step 4:- Fill the final sorted values.
	unsigned int cur_index = 0;
	vec.clear();
	for(int i=0; i<R; i++)
	{
		for(int k=cur_index; k<count[i];k++)
		{
			vec.push_back(i);
			cur_index++;
		}
	}
}

void key_index_count::print_array()
{
	for(int i=0; i<vec.size(); i++)
	{
		cout<<int(vec[i]) <<" ";
	}
	cout<<endl;
}

void key_index_count::print_stl_sorted_array()
{
    for(int i=0; i<tmp_vec.size(); i++)
    {
        cout<<int(tmp_vec[i]) <<" ";
    }
    cout<<endl;
}

void key_index_count::validate_sorting()
{
	if(tmp_vec.size() != vec.size())
	{
		assert(false);
	}

	for(int i=1; i<vec.size(); i++)
	{
		if(vec[i] < vec[i-1])
			assert(false);
	}
}


int main(int argc, char* argv[])
{
	if(argc !=2)
	{
		cout<<"\n Usage:- exe arr-size\n";
		exit(0);
	}

	int size_of_arr = atoi(argv[1]);
	srand((unsigned)time(0));
	vector<mytype> buf;

	for(int i=0; i< size_of_arr; i++)
	{
		int val = rand()%256;
		buf.push_back(val);
	}

	key_index_count obj(buf);
	cout<<"Org- "; obj.print_array();
	obj.sort_array();
	cout<<"My - "; obj.print_array();
	cout<<"Stl- "; obj.print_stl_sorted_array();
	cout<<endl;
	return 0;
}
