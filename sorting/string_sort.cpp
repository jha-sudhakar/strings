#include <assert.h> 
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
//----------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;
typedef unsigned int myint;
#define DEBUG_ENABLE 1

/*
	1 Million entries = (1000000 * 12)/(1024*1024) = 11.44MB // Assuming text of length 12 chars.
	1 Billion entries = 11.44 * 1000 =  11.44 GB
	4 Billion entries = 11.44 * 4 = 45.77 GB approx.
*/

class Str_sort
{
	private:
		unsigned long _index;
	public:
		Str_sort();
		~Str_sort();
		void merge_sorted_files(string file1, string file2, string out_file);
		void my_assert(bool val);

		void sort_string_vector(vector<string>& str_vec);
		//Read 'count' entries from the file and store it in the vector. If (count == 0), read complete file.
		void readFromFile_to_string_vector(vector<string>& str_vec, string filename, const myint count=0);
		void writeToFile_from_string_vector(vector<string>& str_vec, string filename);
		void sort_text_file_using_chunks(const string rand_text_file, const myint chunk_size = 100000);

		
		// Automatic test methods.
		void test_sort_and_save_random_file(string filename);
		void test_merge_sorted_files(string filename1, string filename2);
		void test_generate_random_text_file(string filename, const myint no_of_lines, const myint min_str_size=5, const myint max_str_size=15);
		void test_sorting_of_random_file(string random_filename, const long lines, const long chunk);
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
}

Str_sort::~Str_sort() { }

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

void Str_sort::merge_sorted_files(string file1, string file2, string out_file)
{
	ifstream in1(file1.c_str());
	ifstream in2(file2.c_str());
	
	string num_str = to_string(_index);

	ofstream out1(out_file.c_str());

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
			out1 << str1 <<endl; //cout<<"\n line:  " << __LINE__ << ", writing " << str1;
			getline(in1, str1);
		} else //if (val >= 0)
		{
			out1 << str2 << endl; //cout<<"\n line:  " << __LINE__ << ", writing " << str2;
			getline(in2, str2);
		}
	}

    if (!in1.eof())
	{
		out1 << str1 << endl; //cout<<"\n line:  " << __LINE__ << ", writing " << str1;
		out1 << in1.rdbuf();
	} else if (!in2.eof())
	{
		out1 << str2 << endl; //cout<<"\n line:  " << __LINE__ << ", writing " << str2;
		out1 << in2.rdbuf();
	}

	out1.close();
	in1.close();
	in2.close();
}


void Str_sort::sort_text_file_using_chunks(const string rand_text_file, const myint chunk_size)
{
	string old_chunk_file_list =  "config_file_1.txt";
	string new_chunk_file_list = "config_file_2.txt";
	
	ifstream rand_f(rand_text_file.c_str()); // Read the random text file.
	if(!rand_f.is_open()) assert(false);
	
	ofstream chunk_files(old_chunk_file_list.c_str()); // Read the random text file.
	if(!chunk_files.is_open()) assert(false);
	
	string str_rand_text;
	myint line_count = 0;
	vector<string> str_vec;
	
	// Step 1 :- Split the file into smaller chunks and sort individual chunks.
	while(!rand_f.eof())
	{
		getline(rand_f, str_rand_text);
		line_count++;
		str_vec.push_back(str_rand_text);
		if(line_count == chunk_size)
		{
			// Sort this chunk and write to a temporary file.
			sort_string_vector(str_vec);
			string temp_file_name = string("file_") + to_string(_index++);
			writeToFile_from_string_vector(str_vec, temp_file_name);

			// Save the names of partailly sorted file, will use during merge.
			chunk_files << temp_file_name << endl;
			//cout<< "\n created chunk file " << temp_file_name;
			str_vec.clear();
			line_count = 0;
		}
	}
	
	// End of file is reached so vector-size may be less than chunk size.
	if(0 != str_vec.size())
	{
		sort_string_vector(str_vec);
		string temp_file_name = string("file_") + to_string(_index++);
		writeToFile_from_string_vector(str_vec, temp_file_name);
		chunk_files << temp_file_name << endl;
		//cout<< "\n created chunk file " << temp_file_name;
	}
	chunk_files.close();
	rand_f.close();

	// Step 2 :- Merge the sorted chunks.
	//TODO:- Try to read few thousand lines of text once instead of each line.
	while(1)
	{
		ifstream in_f(old_chunk_file_list.c_str());
		ofstream out_f(new_chunk_file_list.c_str());
		string file1, file2;
		uint64_t line_no = 0;
		while(!in_f.eof())
		{
			getline(in_f, file1);
			line_no++;
			if(in_f.eof())
			{
				if(file1.size())
					out_f << file1 << endl; // Odd no of files.
				break;
			}
			getline(in_f, file2);
			
			if(file1.size() && file2.size())
			{
				string temp_file_name = string("file_") + to_string(_index++);
				merge_sorted_files(file1, file2, temp_file_name);
				out_f << temp_file_name << endl;
				remove(file1.c_str()); remove(file2.c_str());
			} else if(file1.size())
			{
				out_f << file1 << endl;
			} else if(file2.size())
			{
				out_f << file2 << endl;
			} 

		}

		in_f.close();
		out_f.close();
		string tmp_str_filename = old_chunk_file_list;
		old_chunk_file_list = new_chunk_file_list;
		new_chunk_file_list = tmp_str_filename;

		//cout<<"\n No of lines= " << line_no;
		if(1 == line_no)
		{
			rename( file1.c_str() , "final_sorted_file.txt");
			break;
		}
	}

	remove(old_chunk_file_list.c_str()); remove(new_chunk_file_list.c_str());
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
	
	string output_file_name = string("file_") + to_string(_index++);
	merge_sorted_files(filename1, filename2, output_file_name);
	
	test_generate_random_text_file("rand_file1.txt", 10);
	test_generate_random_text_file("rand_file2.txt", 15);
}

void Str_sort::test_generate_random_text_file(string filename, const myint no_of_lines, const myint min_str_size, const myint max_str_size)
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

void Str_sort::test_sorting_of_random_file(string random_filename, const long lines, const long  chunk)
{
	test_generate_random_text_file(random_filename, lines);
	sort_text_file_using_chunks(random_filename, chunk);
}

int main(int argc, char* argv[])
{
	if(argc != 4)
	{
		cout<<"\nUsage: exe input-filename no_of_lines_to_add_in_input no_of_lines_to_fetch_in_main_memory";
		cout<<"\n\t 1) exe:-                                 Executable from source code.";
		cout<<"\n\t 2) input-filename:-                      Code generates a random text file as input to sorting algorithm.";
		cout<<"\n\t 3) no_of_lines_to_add_in_input:-         No of lines in the input text file.";
		cout<<"\n\t 4) no_of_lines_to_fetch_in_main_memory:- Code reads these many lines in main memory and executes.\n";
		exit(0);
	}

	long no_of_lines_in_text_file= stol(argv[2]);
	long file_chunk_to_sort_in_memory= stol(argv[3]);
	Str_sort obj2;
	obj2.test_sorting_of_random_file(argv[1], no_of_lines_in_text_file, file_chunk_to_sort_in_memory);
	cout << endl;
	return 0;	
}
