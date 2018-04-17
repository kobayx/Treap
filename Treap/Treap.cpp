#include "Treap.h"
#include <fstream>

using namespace std;
void main()
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
		cout<< item.second << "\t" << item.first << endl;

	return;
}

