#include<stdlib.h>
#include<assert.h>


#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

// Can be 26 or 52 for string only input.
#define R 256 

class key_index_sort
{
	private:
		vector<string> arr_v;
		vector<string> std_sort_input;

		void init();
		void print_time();
		void generate_input();

		bool is_rhs_str_smaller(unsigned int i, unsigned int j, unsigned int d);
		bool is_rhs_str_less(vector<string*>& in_v, unsigned int i, unsigned int j, unsigned int d);
		bool is_rhs_str_equal(vector<string*>& in_v, unsigned int i, unsigned int j, unsigned int d);
		void sort_using_insertion(const int low, const int high, const unsigned int d);
		void sort_using_key_index(const int low, const int high, const unsigned int d);
		void sort_using_key_index();
		void swap(vector<string*>& in_v, int i, int j);
	public:
		key_index_sort();
		void automated_test(unsigned int loop);
};
void key_index_sort::print_time()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[180];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,180,"Time %d-%m-%Y %I:%M:%S",timeinfo);
	std::string str(buffer);
	std::cout << str << endl;;
}

key_index_sort::key_index_sort()
{
	srand(time(NULL));
}

void key_index_sort::init()
{
	arr_v.clear();
	std_sort_input.clear();
}

void key_index_sort::generate_input()
{
	unsigned int in_size = 5+rand()%1000;

	for(int i=0; i<in_size; i++)
	{
		unsigned int len = 1+rand()%100;
		string buf; buf.resize(len);
		for(unsigned int i=0; i<len; i++)
		{
			unsigned int val = rand()%8;
			buf[i] = ('a'+val);
		}
		arr_v.push_back(buf);
		std_sort_input.push_back(buf);
	}
}


bool key_index_sort::is_rhs_str_smaller(unsigned int i, unsigned int j, unsigned int d)
{
	while(d<arr_v[i].size() && d<arr_v[j].size())
	{
		if(arr_v[j][d] < arr_v[i][d])
			return true;
		else if(arr_v[j][d] > arr_v[i][d])
			return false;
		d++;
	}
	if(d == arr_v[i].size())
		return false;
	else
		return true;
}



bool key_index_sort::is_rhs_str_less(vector<string*>& in_v, unsigned int i, unsigned int j, unsigned int d)
{
	if(d<in_v[i]->size() && d<in_v[j]->size())
	{
		if(in_v[j]->at(d) < in_v[i]->at(d))
			return true;
		else
			return false;
	}
	if(d == in_v[j]->size())
		return true;
	else
		return false;
}

bool key_index_sort::is_rhs_str_equal(vector<string*>& in_v, unsigned int i, unsigned int j, unsigned int d)
{
	if(d>=in_v[i]->size() && d>=in_v[j]->size())
		return true;
		
	if(d<in_v[i]->size() && d<in_v[j]->size())
	{
		if(in_v[j]->at(d) == in_v[i]->at(d))
			return true;
		else
			return false;
	}
	return false;
}


void key_index_sort::sort_using_insertion(const int low, const int high, const unsigned int d)
{
	for(unsigned int i=low; i<high; i++)
	{
		for(unsigned int j=i+1; j<=high; j++)
		{
			if(is_rhs_str_smaller(i,j,d))
			{
				string tmp_str_i = arr_v[i];
				string tmp_str_j = arr_v[j];
				arr_v[i] = tmp_str_j;
				arr_v[j] = tmp_str_i;
			}
		}
	}

}

void key_index_sort::swap(vector<string*>& in_v, int i, int j)
{
	string* ptr_str = in_v[i];
	in_v[i] = in_v[j];
	in_v[j] = ptr_str;
}

void key_index_sort::sort_using_key_index(const int low, const int high, const unsigned int d)
{
	if(low >= high)
		return;

#if 1
	if(high-low  < 15)
	{
		sort_using_insertion(low, high, d);
#if 0
	cout<<"\n Insertion sort:- Sorted by Index " << d <<", low= " << low <<", high= " << high <<endl;
	for(int i=low; i<=high; i++)
		cout << arr_v[i] << endl;
	cout<<endl;
#endif
		return;
	}
#endif

	bool is_valid_at_d = false;;
	vector<string*> arr_vp;
	arr_vp.resize(1+ high-low);
	for(int i=low; i<=high ; i++)
	{
		arr_vp[i-low] = &(arr_v[i]);
		if(d+1 <= arr_v[i].size())
			is_valid_at_d = true;
	}

	if(is_valid_at_d == false)
		return;

	int key = 0;
	int i=1, j=arr_vp.size()-1;
	int mid = i;
	while(i<=j)
	{
		if(is_rhs_str_less(arr_vp, key,i,d))
		{
			swap(arr_vp,mid,i);
			mid++;
			i++;
		} else if(is_rhs_str_equal(arr_vp, key,i,d))
		{
			swap(arr_vp,mid,i);
			i++;
		} else
		{
			swap(arr_vp, j, i);
			j--;
		}
	}	

	swap(arr_vp ,0, mid-1);
	mid--;
	
	vector<string> tmp_str;
	for(int i=0; i<arr_vp.size(); i++)
		tmp_str.push_back(*(arr_vp[i]));

	for(int i=low; i<= high; i++)
	arr_v[i]  = tmp_str[i-low];


	sort_using_key_index(low, low+mid-1, d);
	sort_using_key_index(low+mid, low+j,     d+1);
	sort_using_key_index(low+j+1, high,  d);
}

void key_index_sort::sort_using_key_index()
{
	if(arr_v.size() <2)
		return;
	sort_using_key_index(0, arr_v.size()-1, 0);
}



void key_index_sort::automated_test(unsigned int loop)
{
	while(loop)
	{
		init();
		generate_input();
#ifdef DEBUG
		cout<<"\t Input  arr= ";
		for(int i=0; i<arr_v.size(); i++)
			cout << arr_v[i] <<" ";
		cout<<endl;	
#endif
		sort(std_sort_input.begin(), std_sort_input.end());
		sort_using_key_index();
		for(int i=0; i<std_sort_input.size(); i++)
		{
			if(std_sort_input[i] != arr_v[i])
			{
				cout<<"Index= " << i <<", Exp= " << std_sort_input[i] <<", actual= " << arr_v[i] << endl;	
				assert(false);
			}	
		}

#ifdef DEBUG
		cout<<"\t Sorted arr= ";
		for(int i=0; i<arr_v.size(); i++)
			cout << arr_v[i] <<" ";
		cout<<endl;	
#endif
		cout <<"Executed loop " << loop << endl;
		loop--;
	}
}


int main(int argc, char* argv[])
{
	key_index_sort obj;
	obj.automated_test(atoi(argv[1]));
	return 0;
}
