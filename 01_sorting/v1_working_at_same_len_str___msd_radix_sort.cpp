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
		unsigned int len;
		vector<string> arr_v;
		//int count_v[R];

		void init();
		void sort_using_key_index(const unsigned int low, const unsigned int high, const unsigned int d);
		void sort_using_key_index();
	public:
		key_index_sort();
		void generate_input();
		void automated_test(unsigned int loop);
};

key_index_sort::key_index_sort()
{
	srand(time(NULL));
}

void key_index_sort::init()
{
	len = 0;
	arr_v.clear();
	//count_v.clear();
}

void key_index_sort::generate_input()
{
	unsigned int in_size = 5+rand()%50;
	len = 1+rand()%30;

	for(int i=0; i<in_size; i++)
	{
		string buf; buf.resize(len);
		for(unsigned int i=0; i<len; i++)
		{
			unsigned int val = rand()%26;
			buf[i] = ('a'+val);
		}
		arr_v.push_back(buf);
	}
}

void key_index_sort::sort_using_key_index(const unsigned int low, const unsigned int high, const unsigned int d)
{
	if(low == high)
		return;

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

#if 1
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
		cout<<"\t Input  arr= ";
		for(int i=0; i<arr_v.size(); i++)
			cout << arr_v[i] <<" ";
		cout<<endl;	

		vector<string> std_sort_input = arr_v;
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
		cout<<"\t Sorted arr= ";
		for(int i=0; i<arr_v.size(); i++)
			cout << arr_v[i] <<" ";
		cout<<endl;	

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
