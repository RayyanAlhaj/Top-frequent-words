#pragma once
#include <string>
using namespace std;

struct nodeType {
public:
	std::string info1; //word
	int info2; //number of word
	nodeType *link;
};
class hashT
{
public:
	void inserting_hash_a(int num,  string& word);
	long long tabHash(string & s); //hash-function

	hashT();
	~hashT();


	nodeType* hash_table_a[4000]; //= new nodeType[8000]; //array of nodeType heads
	int tabHashSize; //8000
	
};

//tabHash functtion:

/*<Ayan Ghosal> (<11.09.2020>) 
< String hashing using Polynomial rolling hash function > (<?>)[<type>]
https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/ */

