#include "Treap.h"
#include <fstream>
#include <string>
using namespace std;
int main()
{
	Treap<string, int> count;
	string words;
	ifstream fin;

	fin.open("words.txt");
	if (fin.fail())
		cout << "faill" << endl;
	while (fin >> words)
	{
		++count[words];
	}
	for (auto& item : count)
		cerr << item.second << "\t" << item.first << endl;

 	return 0;
}

