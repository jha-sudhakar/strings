
#include <string>
#include <iostream>
#include <fstream>

#include <assert.h> 
#define DEBUG_ENABLE 1

class Str_sort
{
	private:
		string sorted_files_to_read;
		string sorted_files_to_write;
		unsigned int index;
	public:
		Str_sort();
		~Str_sort();
		void merge_sorted_files(string file1, string file2);
		void my_assert(bool val);
};

void Str_sort::my_assert(bool val)
{
#ifdef DEBUG_ENABLE
	assert(val);
#endif
	
}

Str_sort::Str_sort()
{
	index = 0;
	string sorted_files_to_read =  "file_1.txt"
	string sorted_files_to_write = "file_2.txt"
}

Str_sort::~Str_sort()
{
	
}

void Str_sort::merge_sorted_files(string file1, string file2)
{
	ifstream in1(file1.c_str());
	ifstream in2(file2.c_str());
	
	
	string output_file_name = string("file_") + to_string(index);
	ofstream out1(output_file_name.c_str);
	index++;			

	//Are files open?
	if(!in1.is_open() || !in2.is_open())
	{
		cout<<"\n in1 status= " << in1.is_open() <<", in2 status= " << in2.is_open() <<endl;
		my_assert(false);
	}
	
	string str1, str2;
	getline(in1, str1);
	getline(in2, str2);
		
	while (!in1.eof() && !in2.eof())
	{
		cout << "file1-str= "<< str1 <<", file2-str= " << str2 << endl;
	
		int val = str1.compare(str2);
		if(val < 0)
		{
			out1 << str1;
			getline(in1, str1);
		} else if (val1)
		{
			out1 << str2;
			getline(in2, str2);
		}
	}

    if (!in1.eof())
	{
		while(1)
		{
			getline(in1, str1);
			if (!in1.eof()) {  out1 << str1; }
			else break;
		}
	} else if (!in2.eof())
	{
		while(1)
		{
			getline(in2, str2);
			if (!in2.eof()) {  out2 << str2; }
			else break;
		}
	}

	out1.close();
	in1.close();
	in2.close();
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		cout <<"\n Usage: exe fileName1 fileName2\n";
		exit(0);
	}

	string file1(argv[1]);
	string file2(argv[2]);
	Str_sort obj1;
	obj1.merge_sorted_files(file1, file2);
	
	return 0;	
}
