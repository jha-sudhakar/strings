#include <assert.h> 
#include <stdint.h>
#include <stdlib.h>
//----------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;
typedef unsigned int myint;
#define DEBUG_ENABLE 1


class Str_sort
{
	private:
		string sorted_files_to_read;
		string sorted_files_to_write;
		unsigned long _index;
	public:
		Str_sort();
		~Str_sort();
		void merge_sorted_files(string file1, string file2);
		void my_assert(bool val);

		void sort_string_vector(vector<string>& str_vec);
		//Read 'count' entries from the file and store it in the vector. If (count == 0), read complete file.
		void readFromFile_to_string_vector(vector<string>& str_vec, string filename, const myint count=0);
		void writeToFile_from_string_vector(vector<string>& str_vec, string filename);


		// Automatic test methods.
		void test_sort_and_save_random_file(string filename);
		void test_merge_sorted_files(string filename1, string filename2);
		void generate_random_text_file(string filename, const myint no_of_lines, const myint min_str_size=5, const myint max_str_size=15);
};

void Str_sort::my_assert(bool val)
{
#ifdef DEBUG_ENABLE
	assert(val);
#endif
	
}

Str_sort::Str_sort()
{
	_index = 0;
	string sorted_files_to_read =  "file_1.txt";
	string sorted_files_to_write = "file_2.txt";
}

Str_sort::~Str_sort()
{
	
}

void Str_sort::readFromFile_to_string_vector(vector<string>& str_vec, string filename, const myint count)
{
	ifstream in_file(filename.c_str());
	if(!in_file.is_open())
		assert(false);

	myint local_count = count;
	string str;
	getline(in_file, str);
	while (!in_file.eof() && ((count == 0) || (count !=0 && local_count != 0)))
	{
		str_vec.push_back(str);
		getline(in_file, str);
		local_count--;
	}
	in_file.close();
}

void Str_sort::sort_string_vector(vector<string>& str_vec)
{
	sort(str_vec.begin(), str_vec.end());
}

void Str_sort::writeToFile_from_string_vector(vector<string>& str_vec, string filename)
{
	ofstream out_file(filename.c_str());
	for(myint i=0; i<str_vec.size(); i++)
	{
		out_file << str_vec[i] << endl;
	}
	out_file.close();
}

void Str_sort::merge_sorted_files(string file1, string file2)
{
	ifstream in1(file1.c_str());
	ifstream in2(file2.c_str());
	
	string num_str = to_string(_index);

	string output_file_name = string("file_") + to_string(_index);
	ofstream out1(output_file_name.c_str());
	_index++;			

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
		//cout << "file1-str= "<< str1 <<", file2-str= " << str2 << endl;
	
		int val = str1.compare(str2);
		if(val < 0)
		{
			out1 << str1 <<endl;
			cout<<"\n line:  " << __LINE__ << ", writing " << str1;
			getline(in1, str1);
		} else //if (val >= 0)
		{
			out1 << str2 << endl;
			cout<<"\n line:  " << __LINE__ << ", writing " << str2;
			getline(in2, str2);
		}
	}

    if (!in1.eof())
	{
		out1 << str1 << endl; cout<<"\n line:  " << __LINE__ << ", writing " << str1;
		while(1)
		{
			getline(in1, str1);
			if (!in1.eof()) {  out1 << str1 << endl; cout<<"\n line:  " << __LINE__ << ", writing " << str1; }
			else break;
		}
	} else if (!in2.eof())
	{
		out1 << str2 << endl; cout<<"\n line:  " << __LINE__ << ", writing " << str2;
		while(1)
		{
			getline(in2, str2);
			if (!in2.eof()) {  out1 << str2 << endl; cout<<"\n line:  " << __LINE__ << ", writing " << str2;}
			else break;
		}
	}

	out1.close();
	in1.close();
	in2.close();
}


void Str_sort::test_sort_and_save_random_file(string filename)
{
	vector<string> str_vec;
	readFromFile_to_string_vector(str_vec, filename);
	sort_string_vector(str_vec);
	writeToFile_from_string_vector(str_vec, filename);
}


void Str_sort::test_merge_sorted_files(string filename1, string filename2)
{
	test_sort_and_save_random_file(filename1);
	test_sort_and_save_random_file(filename2);
	merge_sorted_files(filename1, filename2);
	
	generate_random_text_file("rand_file1.txt", 10);
	generate_random_text_file("rand_file2.txt", 15);
}

void Str_sort::generate_random_text_file(string filename, const myint no_of_lines, const myint min_str_size, const myint max_str_size)
{
	ofstream out_f(filename.c_str());
	if(!out_f.is_open()) assert (false);

	char buf[max_str_size +4];
	myint buf_len = 0;

	static char sample[] = 
	{'0','1', '2', '3','4','5', '6', '7', '8', '9',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};
	const uint8_t sample_size = sizeof(sample)/sizeof(sample[0]);


	out_f << "abcd";
	for(myint i=0; i<no_of_lines; i++)
	{
		out_f << endl;
		// Generate random strings of length buf_len(between 5 to 12 by default).
		buf_len = min_str_size + (rand() % (int)(max_str_size - min_str_size + 1));
		for(uint8_t j=0; j<buf_len; j++)
		{
			buf[j] = sample[rand() % sample_size];
		}
		buf[buf_len] = '\0';
		out_f << buf;
	}
	out_f.close();
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
	//obj1.merge_sorted_files(file1, file2);
	obj1.test_merge_sorted_files(file1, file2);
	cout << endl;
	return 0;	
}
