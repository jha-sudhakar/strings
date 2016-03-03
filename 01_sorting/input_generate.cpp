#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

class test_input
{
	private:
		unsigned int T;
		unsigned int min_s, max_s, fixed_s;
		const int is_fixed;
	public:
		test_input(unsigned int _T, unsigned int _fixed_s);
		test_input(unsigned int _T, unsigned int _min_s,  unsigned int _max_s);
		void generate_test_input(vector<string>& str_vec);
};

test_input::test_input(unsigned int _T, unsigned int _fixed_s): is_fixed(true)
{
	T = _T;
	fixed_s = _fixed_s;
}

test_input::test_input(unsigned int _T, unsigned int _min_s,  unsigned int _max_s) :is_fixed(false)
{
	T = _T;
	min_s = _min_s;
	max_s = _max_s;
}
	
void test_input::generate_test_input(vector<string>& str_vec)
{
	srand(time(NULL));
	for(int i=0; i<T; i++)
	{
		string buf; buf.resize(fixed_s);
		for(int j=0; j<fixed_s; j++)
		{
			int val = rand()%26;
			if(val%2)
				buf[j] = 'A'+val;
			else
				buf[j] = 'a'+val;
		}
		str_vec.push_back(buf);
	}
}

#if 0
int main()
{
test_input obj(10,5);
vector<string> string_v;
obj.generate_test_input(string_v);
for(int i=0; i<string_v.size(); i++)
{
	cout<<string_v[i] << endl;
}
cout<<endl;
return 0;
}
#endif
