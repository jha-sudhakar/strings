#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include<algorithm>
#include <iostream>
#include <vector>

using namespace std;

class ThreeWayQuickSort
{
	private:
		void qsort(vector<int>&a, int low, int hight);

	public:
		ThreeWayQuickSort() { srand(time(NULL)); }		
		void sort(vector<int>& a);
		void test_sorting(unsigned int input_size);
};


void ThreeWayQuickSort::sort(vector<int>& a)
{
	qsort(a, 0, a.size()-1);
}


void ThreeWayQuickSort::test_sorting(unsigned int input_size)
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

void ThreeWayQuickSort:: qsort(vector<int>&a, int low, int high)
{
	if(low >= high)
		return;

	int pivot = a[low];
	int lt = low;
	int gt = high;
	int i=low+1;
	while(i<=gt)
	{
		if(a[i] < pivot)
		{	
			int tmp = a[i];a[i] = a[lt]; a[lt] = tmp;
			i++;lt++;
		}
		else if(a[i] > pivot)
		{
			int tmp = a[gt]; a[gt] = a[i]; a[i]= tmp; gt--;
		}
		else
		{
			i++;
		}
	}

	int k=0;

#if 0
	for(k=low; k<lt; k++)
		cout<< a[k] << " ";
	cout<< " *** < *** ";
	for(k=lt; k<=gt; k++)
		cout << a[k] << " ";
	cout<< " *** < *** ";
	for(k=gt+1; k<=high; k++)
		cout << a[k] << " ";
	cout << endl;
#endif

	qsort(a, low, lt-1);
	qsort(a, gt+1, high);
}


int main(int argc, char* argv[])
{
ThreeWayQuickSort obj;
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
