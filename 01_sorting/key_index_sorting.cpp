#include<stdlib.h>
#include<assert.h>


#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

class key_index_sort
{
	private:
		unsigned int range_num;
		vector<int> arr_v;
		vector<int> count_v;

		void init();
		void sort_using_key_index();
	public:
		key_index_sort();
		void generate_input();
		void automated_test(unsigned int loop);
};

key_index_sort::key_index_sort()
{
	range_num = 0;
	srand(time(NULL));
}

void key_index_sort::init()
{
	range_num = 0;
	arr_v.clear();
	count_v.clear();
}

void key_index_sort::generate_input()
{
	unsigned int in_size = 5+rand()%30;
	range_num = 5+rand()%100;

	for(int i=0; i<in_size; i++)
		arr_v.push_back(rand()%range_num);
}

void key_index_sort::sort_using_key_index()
{

	vector<int> buf;
	buf.resize(arr_v.size());

	count_v.resize(range_num+1);
	for(int i=0; i<=range_num; i++)
		count_v[i] = 0;

	for(int i=0; i<arr_v.size(); i++)
		count_v[1+arr_v[i]]++;

	for(int i=1; i<count_v.size(); i++)
		count_v[i] += count_v[i-1];

	for(unsigned int i=0; i<arr_v.size(); i++)
	{
		buf[count_v[arr_v[i]]] = arr_v[i];
		 count_v[arr_v[i]]++;
	}	
	
	for(unsigned int i=0; i<buf.size(); i++)
		arr_v[i] = buf[i];
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

		vector<int> std_sort_input = arr_v;
		sort(std_sort_input.begin(), std_sort_input.end());
		sort_using_key_index();
		for(int i=0; i<std_sort_input.size(); i++)
		{
			if(std_sort_input[i] != arr_v[i])
				assert(false);
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
