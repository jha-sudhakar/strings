#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

class ThreeWayQuickSort
{
	private:
		void qsort(vector<int>&a, int low, int hight);

	public:
		void sort(vector<int>& a);
};


void ThreeWayQuickSort::sort(vector<int>& a)
{
	qsort(a, 0, a.size()-1);
}


void ThreeWayQuickSort:: qsort(vector<int>&a, int low, int high)
{
	if(low >= high)
		return;

	int pivot = a[low];
	int lt = low;
	int gt = high;
	int i=low+1;
	while(i<gt)
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
	for(k=low; k<lt; k++)
		cout<< a[k] << " ";
	cout<< " *** < *** ";
	for(k=lt; k<=gt; k++)
		cout << a[k] << " ";
	cout<< " *** < *** ";
	for(k=gt+1; k<=high; k++)
		cout << a[k] << " ";
	cout << endl;

	qsort(a, low, lt-1);
	qsort(a, gt+1, high);
}


int main(int argc, char* argv[])
{
ThreeWayQuickSort obj;
vector<int> inp;
for(int i=1; i<argc; i++)
	inp.push_back(atoi(argv[i]));

obj.sort(inp);

cout<<"\nsorted array -- ";
for(int k=0; k<inp.size(); k++)
	cout << inp[k] << " ";
cout << endl;
return 0;
}
