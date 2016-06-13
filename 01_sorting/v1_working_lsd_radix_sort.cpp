#include<stdlib.h>
#include<assert.h>


#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

#define R 256

class key_index_sort
{
	private:
		unsigned int len;
		vector<string> arr_v;
		int count_v[R];

		void init();
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
	unsigned int in_size = 5+rand()%500;
	len = 5+rand()%500;

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

void key_index_sort::sort_using_key_index()
{
	for(int pos=len-1; pos>-1; pos--)
	{
		vector<string> buf;
		buf.resize(arr_v.size());

		for(int i=0; i<R; i++)
			count_v[i] = 0;

		for(int i=0; i<arr_v.size(); i++)
		{
			char index = arr_v[i].at(pos);
			//cout <<"Pos= " << pos <<", at index " << index <<" char = "<< arr_v[i].at(pos) << endl;
			count_v[1+index]++;
		}	
		
#if 0		
		for(int i=0; i<R; i++)
		{
			if(count_v[i] != 0)
				cout <<"count_v[" << i <<"]= " << count_v[i] << endl;
		}
#endif
		for(int i=1; i<R; i++)
			count_v[i] += count_v[i-1];
		
		for(unsigned int i=0; i<arr_v.size(); i++)
		{
			buf[count_v[arr_v[i][pos]]] = arr_v[i];
			 count_v[arr_v[i][pos]]++;
		}
		
		for(unsigned int i=0; i<buf.size(); i++)
			arr_v[i] = buf[i];

#if 0
		cout<<"\n Sorted by Index " << pos <<endl;
		for(int i=0; i< arr_v.size(); i++)
			cout << arr_v[i] << endl;
		cout<<endl;
#endif		
	}
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
				cout<<"Exp= " << std_sort_input[i] <<", actual= " << arr_v[i] << endl;	
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
