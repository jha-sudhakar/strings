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
		void sort_using_insertion(const unsigned int low, const unsigned int high, const unsigned int d);
		void sort_using_key_index(const unsigned int low, const unsigned int high, const unsigned int d);
		void sort_using_key_index();
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
	unsigned int in_size = 5+rand()%10000;

	for(int i=0; i<in_size; i++)
	{
		unsigned int len = 1+rand()%1000;
		string buf; buf.resize(len);
		for(unsigned int i=0; i<len; i++)
		{
			unsigned int val = rand()%26;
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

void key_index_sort::sort_using_insertion(const unsigned int low, const unsigned int high, const unsigned int d)
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

void key_index_sort::sort_using_key_index(const unsigned int low, const unsigned int high, const unsigned int d)
{
	if(low == high)
		return;
	if(high-low < 10)
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

	bool is_valid_at_d = false;;
	vector<string*> arr_vp;
	arr_vp.resize(1+ high-low);
	for(unsigned int i=low; i<=high ; i++)
	{
		arr_vp[i-low] = &(arr_v[i]);
		if(d+1 <= arr_v[i].size())
			is_valid_at_d = true;
	}

	if(is_valid_at_d == false)
		return;

	vector<string*> buf;
	buf.resize(1+high-low);

	int count_v[R];
	for(int i=0; i<R; i++)
		count_v[i] = 0;

	for(int i=0; i<arr_vp.size(); i++)
	{
		char index = 0;
		if(d < arr_vp[i]->size())
			index = arr_vp[i]->at(d);
		count_v[1+index]++;
	}	
	
	for(int i=1; i<R; i++)
		count_v[i] += count_v[i-1];
	
	for(unsigned int i=0; i<arr_vp.size(); i++)
	{
		char index = 0;
		if(d < arr_vp[i]->size())
			index = arr_vp[i]->at(d);

		buf[count_v[index]] = arr_vp[i];
		count_v[index]++;
	}
	
	vector<string> tmp_str;
	for(int i=0; i<buf.size(); i++)
		tmp_str.push_back(*(buf[i]));

	for(int i=low; i<= high; i++)
		arr_v[i]  = tmp_str[i-low];

#if 0
	cout<<"\n Sorted by Index " << d <<", low= " << low <<", high= " << high <<endl;
	for(int i=low; i<=high; i++)
		cout << arr_v[i] << endl;
	cout<<endl;
#endif

	for(int i=0; i<R-1; i++)
	{
		if(count_v[i+1] > count_v[i])
			sort_using_key_index(low+count_v[i], low+count_v[i+1]-1, d+1);
	}
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
