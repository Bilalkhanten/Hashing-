#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class MyHash
{
private:
	string ** table;
	int * maxind;
	long width;
	long depth;
	
protected:
	bool insert(long value,string s);
	void printone(long v);		
	
public:
	MyHash(long N, long Depth);
	long apply(string s);
	void printall();
};

MyHash::MyHash(long N, long Depth)
{
	this->width = N;
	this->depth = Depth;
	table = new string*[N];
	maxind = new int[N];
	for(long i =0; i < N ;i++)
	{
		table[i] = NULL;
	}
}

long MyHash::apply(string s)
{
	long accum = 0; 
	const int size = s.size();
	const char * bytes = s.c_str();
	for(int i =0; i < size; i++)
	{
		accum+= bytes[i];
		
	} 
	accum  = (accum & (0x3FFFFFFF)) % width; 
	if(!insert(accum,s)) printf("Hash Table is full. Value is lost. \n");
	return accum;
}

bool MyHash::insert(long v, string s)
{
	if(table[v] == NULL)
	{
		table[v] = new string[depth];
		maxind[v] = 0; 	
		table[v][maxind[v]] = s;
		maxind[v]++;
	}
	else
	{
		if(maxind[v] == depth)
		{
		  return false;		
		}
		table[v][maxind[v]] = s;
		maxind[v]++;
	}
	
	return true;
}

void MyHash::printone(long v)
{
	if(table[v] == NULL)
		return;
	
	for(int i =0; i < maxind[v]; i++)
	{
		cout << "(" << i <<") " <<table[v][i];
	}
	
}

void MyHash::printall()
{
	for(long i =0; i < width; i++)
	{
		cout << i << ": ";
		printone(i);
		printf("\n");
	}
}

int main()
{
	MyHash hinst(10,3);
	hinst.apply("HelloWorld !");
	hinst.apply("Hellold !") ;
	hinst.apply("He= !") ;
	hinst.apply("HelloWorld ! dfdfd");
	hinst.apply("HelloWorld !");
	hinst.apply("Abc") ;
	hinst.apply("efg") ;
	hinst.apply("He= !") ;
	hinst.apply("He= !") ;
	
	hinst.printall();
	
}
