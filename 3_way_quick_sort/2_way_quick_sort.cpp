#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include<algorithm>
#include <iostream>
#include <vector>

using namespace std;

class TwoWayQuickSort
{
	private:
		void qsort(vector<int>&a, int low, int hight);

	public:
		TwoWayQuickSort() { srand(time(NULL)); }		
		void sort(vector<int>& a);
		void test_sorting(unsigned int input_size);
};


void TwoWayQuickSort::sort(vector<int>& a)
{
	qsort(a, 0, a.size()-1);
}


void TwoWayQuickSort::test_sorting(unsigned int input_size)
{
	vector<int> in_vec, stl_in_vec;
	for(unsigned int i=0; i<input_size; i++)
	{
		int tmp_val = rand()%10000;
		in_vec.push_back(tmp_val);
		stl_in_vec.push_back(tmp_val);
	}

	sort(in_vec);
	std::sort(stl_in_vec.begin(), stl_in_vec.end());
	for(unsigned int i=0; i<input_size; i++)
	{
		if(in_vec[i] != stl_in_vec[i])
			assert(false);
		cout<< in_vec[i] << " ";		
	}
	cout<< endl;
}

void TwoWayQuickSort:: qsort(vector<int>&a, int low, int high)
{
	if(low >= high)
		return ;

	int pivot = a[low];
	int gt = high;
	for(int i=low+1; i<=gt;)
	{
		if(a[i] <= pivot)
			i++;
		else
		{
			int tmp = a[i];
			a[i] = a[gt];
			a[gt] = tmp;
			gt--;
		}
	}
	a[low] = a[gt];
	a[gt] = pivot;
	qsort(a, low, gt-1);
	qsort(a, gt+1, high);
}


int main(int argc, char* argv[])
{
TwoWayQuickSort obj;
int test_iteration = atoi(argv[1]);
int input_size = atoi(argv[2]);
for(int i=0; i<test_iteration; i++)
{
	obj.test_sorting(input_size);
	cout<<" Completed iteration " << i+1 << endl;
}

#if 0
vector<int> inp;
for(int i=1; i<argc; i++)
	inp.push_back(atoi(argv[i]));

obj.sort(inp);

cout<<"\nsorted array -- ";
for(int k=0; k<inp.size(); k++)
	cout << inp[k] << " ";
cout << endl;
#endif

return 0;
}
