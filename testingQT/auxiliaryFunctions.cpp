#include <iostream>
#include <fstream>

using namespace std;
#include <vector>

vector< vector<int> > readingBoard()
{
	ifstream indata; 
	int num; 
	indata.open("numeros"); 
	
	if(!indata) { 
		cerr << "Error: file could not be opened" << endl;
	}

	vector< vector<int> > res;

	res.resize(15);
	
	for(int i = 0; i < 15; i++)
	{
		res.at(i).resize(30);

		for(int j = 0; j < 30; j++)
		{
			indata >> num;

			res.at(i).at(j) = num;
		}
		
	}

	indata.close();
	cout << "End-of-file reached.." << endl;

	return res;
}
