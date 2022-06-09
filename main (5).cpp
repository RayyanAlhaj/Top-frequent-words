#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include "hashtabA.h"
#include "heapA.h"
using namespace std;
class topTen {

public:
	
	void swap(heaping& a, heaping& b)  
	{
		string tempW = a.name_pub_data;
		int tempN = a.num_pub_data;

		a.name_pub_data = b.name_pub_data;
		b.name_pub_data = tempW;

		a.num_pub_data = b.num_pub_data;
		b.num_pub_data = tempN;
	}
	

	void heaping_a(heaping order_array[], int n, int r)
	{
		int wide = r;
		int back = 2 * r + 1;
		int next = 2 * r + 2;
		
		(back < n && (order_array[back].num_pub_data < order_array[wide].num_pub_data)) ? wide = back : wide;

		
		
		

		(next < n && (order_array[next].num_pub_data < order_array[wide].num_pub_data)) ? wide = next :wide;
		
		
		if (wide != r)
		{
			swap(order_array[r], order_array[wide]);
			heaping_a(order_array, n, wide);
		}	




	}
	void sortHeap(heaping order_array[], int n)
	{
		for (int r = n / 2 - 1; r >= 0; r--)
		{
			heaping_a(order_array, n, r);
		}
		for (int r = n - 1; r >= 0; r--)
		{
			swap(order_array[0], order_array[r]);
			heaping_a(order_array, r, 0);
		}
	}
	int getNum(string str) {
		int num;
		stringstream ss;
		ss << str;
		ss >> num;

		return num;
	}
	string splitGetpub_data(string pub_data) {
		string sppub_data = "";

		int pub_datalength = pub_data.length();
		bool mark = true;
		for (int i = 0; i < pub_datalength; i++) {

			if (pub_data[i] == ':') {
				mark = false;
			}
			if (pub_data[i] != '"' && mark) {
				sppub_data += pub_data[i];
			}
		}
		return sppub_data;
	}
	string splitGetNum(string w) {
		string pub_datacount = "";

		int pub_datalength = w.length();
		bool mark = true;

		for (int i = 0; i < pub_datalength; i++) {

			if (w[i] == ':') {
				mark = false;
				for (int j = pub_datalength; j > i; j--) {
					pub_datacount += w[j];
				}
			}
		}
		return pub_datacount;
	}

	bool valid(string pub_data) {
		int quotCount = 0, colonCount = 0;
		for (int i = 0; i < pub_data.length(); i++) {
			if (pub_data[i] == '"') {
				quotCount++;
			}
			if (pub_data[i] == ':') {
				colonCount++;
			}
		}
		if (quotCount == 2 && colonCount == 1) {
			return true;
		}
		return false;
	}
	
	bool isValidpub_data(string w) {
		for (int i = 0; i < w.length(); i++) {
			if (((int)w[i] >= 97 && (int)w[i] <= 122) || ((int)w[i] >= 65 && (int)w[i] <= 90)) {// why sis 

			}
			else {
				return false;
			}
		}
		return true;
	}

	bool isValidNum(string count) {
		for (int i = 0; i < count.length(); i++) {
			if ((int)count[i] < 48 || (int)count[i] > 57) {
				return false;
			}
		}
		return true;
	}

	string trim(string pub_data) {
		string trimmed = "";
		for (int i = 0; i < pub_data.size(); i++) {
			if ((int)pub_data[i] != 32 && (int)pub_data[i] != 10 && (int)pub_data[i] != 0) {// why did we use these numbers 0,10,and32
				trimmed += pub_data[i];
			}
		}
		return trimmed;
	}
	void startProgram() {
		
		hashT tab_hash; 
		fstream pross_file; 
		string pub_data; 
		string border;
		fstream freeze_file;
		string jumpW;
		bool unigramFound = false;


		string path = "E:/PublicationsDataSet.txt";
		int pub_datasInserted = 0;
		pross_file.open(path, ios::in); 
		if (!pross_file) { 
			cerr << "Unable to open file.";
			exit(1);
		}
		else {
			
			while (pross_file >> border) {
				if (border.find("unigramCount") != string::npos) { 
					unigramFound = true; 
					int b = border.find("unigramCount") + 15; 
					border.erase(0, b); 
				}
				else if (border.find("{\"creator") != string::npos) { 
					unigramFound = false; 
				}

				if (unigramFound == true) {
					string pub_data;
					stringstream all(border);
					while (getline(all, pub_data, ',')) {
						
						if (!valid(pub_data)) {
							continue;
						}
						
						string pub_dataCount = splitGetNum(pub_data); //"another" : 1

						pub_dataCount = trim(pub_dataCount);
						
						pub_data = splitGetpub_data(pub_data);
						if (isValidpub_data(pub_data) && isValidNum(pub_dataCount)) { 
						
							for (int i = 0, stringSize = pub_data.size(); i < stringSize; i++) {
								pub_data[i] = tolower(pub_data[i]); 
				
								ispunct(pub_data[i]) ? pub_data.erase(i--, 1),stringSize = pub_data.size(): stringSize = pub_data.size();
								isdigit(pub_data[i]) ? pub_data.erase(i--, 1),stringSize = pub_data.size(): stringSize = pub_data.size();
							}
							
							int n = getNum(pub_dataCount);
							
							tab_hash.inserting_hash_a(n, pub_data);
							pub_datasInserted++;
						}
					}
				    ;
				}
			}
			
			
			
			
			freeze_file.open("E:/stopwords.txt", ios::in);
			while (getline(freeze_file, jumpW, ' '))
			{
				for (int i = 0, stringSize = jumpW.size(); i < stringSize; i++) { 
					jumpW[i] = tolower(jumpW[i]); 
					ispunct(jumpW[i]) ?  jumpW.erase(i--, 1),stringSize = jumpW.size(): stringSize = jumpW.size();
				}
			}
			
			freeze_file.close();
		}

		pross_file.close();

		heaping* arr = new heaping[pub_datasInserted];
		
		int k = 0; 
		nodeType* current;
		for (int i = 0; i < tab_hash.tabHashSize; i++) 
		{
			current = tab_hash.hash_table_a[i];
			while (current != NULL)
			{
				arr[k].name_pub_data = current->info1; 
				arr[k].num_pub_data = current->info2;
				current = current->link;
				k++;
			}
		}
		sortHeap(arr, k);
		int counter = 0; 
		int i = 0;
		while (counter < 10)
		{
			if (jumpW.find(arr[i].name_pub_data) != string::npos) 
			{
				i++;
				continue;
			}
			else 
			{
				cout << "<" << arr[i].name_pub_data << ">      <" << arr[i].num_pub_data << ">" << std::endl;
				i++;
				counter++;
			}
		}
		
	
		delete[] arr;
	}
};
int main() {
	cout << "Started Computing .." << endl;
	clock_t A , Z;
	A = clock();
	topTen object;
	object.startProgram();
	Z = clock();
	cout << "Total Elapsed Time: " <<  "seconds " <<  (((double) (Z- A))  ) / CLOCKS_PER_SEC <<endl;
	return 0;
}
