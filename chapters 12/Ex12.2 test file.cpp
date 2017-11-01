#include<iostream>
#include"my_StrBlob.h"
using namespace std;

int main(int argc, char **argv)
{
	StrBlob b1;
	{
		StrBlob b2 = {"test1","test2"};
		b1 = b2;
		b2.push_back("test3");
		cout<< b2.size() << endl;
	}
	cout << b1.size() << endl;
	cout << b1.front() << "  " << b1.back() << endl;
	
	const StrBlob b3 = b1;
	cout << b3.front() << "  " << b3.back() << endl;
	
	return 0;
}