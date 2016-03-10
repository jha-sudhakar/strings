#include<vector>
#include<algorithm>
#include <iostream>
#include<assert.h>

using namespace std;

class ThreeWayQuickSort
{

private:
	vector<int> arr, stl_arr;
	void sort_3q(const int low, const int high);
public:
	void sort_arr();
	void print_arr();
	void validate_self();
	void validate_stl();
	ThreeWayQuickSort() { srand(time(NULL)); }
	void generate_input();

};

void ThreeWayQuickSort::generate_input()
{
	arr.clear();
	stl_arr.clear();
	int len = 5; //rand()%25;
	while(len--)
	{
		int val = rand()%100;
		arr.push_back(val);
		stl_arr.push_back(val);
	}
}

void ThreeWayQuickSort::sort_3q(const int low, const int high)
{
	if(low >= high)
	{
		return;
	} else if (high-low == 1)
	{
		if(arr[high] < arr[low])
		{
			int tmp = arr[high]; arr[high] = arr[low]; arr[low] = tmp;
		}
		return;
	}
	

	int lt=low+1, gt= high;
	int key = arr[low];
	
	while(lt < gt)
	{
		while(arr[lt] < key && lt<high)
		{
			lt++;
		} 

		while(arr[gt] > key && gt>low)
		{
			gt--;
		}
		
		int tmp = arr[lt];
		arr[lt] = arr[gt];
		arr[gt] = tmp;

	}
	int tmp = arr[lt-1];
	arr[lt-1] = key;
	arr[low] = tmp;

    cout<<"Sorted by arr[" << lt <<"] = " << key<< endl;
    print_arr();
    cout<<endl;

	sort_3q(low,lt-1);
	sort_3q(lt+1, high);
}

void ThreeWayQuickSort::sort_arr()
{
	sort(stl_arr.begin(), stl_arr.end());
	sort_3q(0, arr.size()-1);
}

void ThreeWayQuickSort::print_arr()
{
    for(int i=0; i<arr.size(); i++)
    {
        cout<< arr[i] << " ";
    }
	cout << endl;
}

void ThreeWayQuickSort::validate_self()
{
	if(arr.size() <=1)
		return;

	for(int i=1; i<arr.size(); i++)
	{
		if(arr[i] < arr[i-1])
			assert(false);
	}
}

void ThreeWayQuickSort::validate_stl()
{
	//sort(stl_arr.begin(), stl_arr.end());
	if(stl_arr.size() != arr.size())
	{
		assert(false);
	}

	for(int i=0; i<arr.size(); i++)
	{
		if(arr[i] != stl_arr[i])
		{
			assert(false);
		}
	}
}

int main(int argc, char* argv[])
{
	ThreeWayQuickSort obj;
	for(int i=0; i<1; i++)
	{
		obj.generate_input();
		cout<<"Org :- ";
		obj.print_arr();

		obj.sort_arr();

        cout<<"Sort:-";
        obj.print_arr();

		obj.validate_self(); obj.validate_stl();
	}

	return 0;
}
