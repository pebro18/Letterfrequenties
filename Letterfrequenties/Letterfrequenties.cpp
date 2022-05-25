#include <iostream>
#include <fstream>
#include <string>

#include "MaxEntClassifier.h"
#include "Letterfrequenties.h"

using namespace std;

void ReadOverTxt(std::ifstream& textfile, std::string& input_string, MaxEntClassifier& classifier)
{
	vector<map<string, int>> test;

	while (getline(textfile, input_string))
	{
		test.push_back(classifier.map_counter(input_string));
	}

	map<string, int > test2;
	test2 = classifier.reduce_counter(test);
	classifier.execute_counter(test2);
	test.clear();
	test2.clear();
}

int main()
{
	cout << "Hello World!\n";

	MaxEntClassifier Dutch(28);
	MaxEntClassifier English(28);
	MaxEntClassifier CompareMatrix(28);

	string input_string;

	ifstream textfile_dutch("C:/Users/pebro/source/repos/Letterfrequenties/Letterfrequenties/Dutch Text/pg14559.txt");
	ReadOverTxt(textfile_dutch, input_string, Dutch);
	textfile_dutch.close();

	ifstream textfile_english("C:/Users/pebro/source/repos/Letterfrequenties/Letterfrequenties/English Text/pg33044.txt");
	ReadOverTxt(textfile_english, input_string, English);
	textfile_english.close();

	ifstream textfile("C:/Users/pebro/source/repos/Letterfrequenties/Letterfrequenties/Test Text/test.txt");
	ReadOverTxt(textfile, input_string, CompareMatrix);
	textfile.close();

	vector<vector<int>> compare_weight = CompareMatrix.get_weights();
	float dutch_result = Dutch.compare(compare_weight);
	float english_result = English.compare(compare_weight);

	cout << "Dutch regels gevonden" << dutch_result << endl;
	cout << "English regels gevonden" << english_result << endl;

	return 0;
}