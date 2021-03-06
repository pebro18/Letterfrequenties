#include "MaxEntClassifier.h"


// originele code van het optellen doet ongeveer hetzelfde als de functie execute_counter
void MaxEntClassifier::input_counter(string& input)
{
	if (input.size() == 0) return;

	for (size_t i = 0; i < input.size() - 1; i++)
	{
		int x = translate_into_int(input[i]);
		int y = translate_into_int(input[i + 1]);

		matrix[x][y]++;
	}
}

// met gebruik van de unigram en een meegegeven matrix wordt hier de kans berekent
// en maakt er mee een nieuwe matrix aan van alle kansen
vector<vector<float>> MaxEntClassifier::create_prob_matrix(vector<int>& unigram, vector<vector<int>>& input)
{
	vector<vector<float>> output = vector<vector<float>>(unigram.size(), std::vector<float>(unigram.size()));
	for (size_t i = 0; i < input.size(); i++)
	{
		for (size_t j = 1; j < input[i].size(); j++)
		{
			// deze berekening is volgens mij nog niet correct
			// maar door lichte tijdnood doe ik dit later
			float prob_a = (float)input[i][j - 1] / (float)unigram[i];
			float prob_b = (prob_a * ((float)input[i][j] / (float)unigram[i]));

			output[i][j] = prob_b * prob_a;
		}
	}

	return output;
}

// zet een 2d matrix om to een 1d lijst
// deze functie telt alle verschillende letters op
vector<int> MaxEntClassifier::normalize_bigram(vector<vector<int>>& input)
{
	vector<int> output = vector<int>(input.size());

	for (size_t row = 0; row < input.size(); row++)
	{
		for (size_t columm = 0; columm < input[row].size(); columm++)
		{
			output[columm] += input[row][columm];
		}
	}

	return output;
}


// deze functie vergelijkt 2 bigrammen met elkaar
float MaxEntClassifier::compare(vector<vector<int>>& input)
{
	// hier wordt voor beide matrixen een unigram gemaakt
	vector<int> normalized_self = normalize_bigram(matrix);
	vector<int> normalized_input = normalize_bigram(input);

	// maakt van beide matrixen een kans matrix
	vector<vector<float>> probabilty_matrix_self = create_prob_matrix(normalized_self, matrix);
	vector<vector<float>> probabilty_matrix_input = create_prob_matrix(normalized_input, input);

	unsigned int count = 0;

	// vergelijkt de 2 matrixen en telt op hoevaak de meegegeven matrix een hogere kans heeft dan de klasse matrix
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input[i].size(); j++)
		{
			float x = probabilty_matrix_self[i][j];
			float y = probabilty_matrix_input[i][j];

			if (probabilty_matrix_self[i][j] < probabilty_matrix_input[i][j])
			{
				count++;
			}
		}
	}
	return (float)count;
}

// deze functie categoriseerd elke lettercombinatie in een string en returns een dictionary met de hoeveelheid
map<string, int> MaxEntClassifier::map_counter(string& input)
{
	map<string, int> mapper;
	// een check voor wanneer een string leeg is
	if (input.size() == 0) return map<string, int>();

	for (size_t i = 0; i < input.size() - 1; i++)
	{
		string input_string;
		// pakt een letter en zijn naaste en maakt zet het om in lowercase
		input_string += (char)tolower(input[i]);
		input_string += (char)tolower(input[i + 1]);

		// check of het in de dict bestaat
		if (mapper.find(input_string) == mapper.end())
		{
			mapper.insert({ input_string, 1 });
		}
		else
		{
			mapper[input_string]++;
		}
	}

	return mapper;
}

//deze functie combineert alle verschillende mapper/dict samen en reduceer het tot 1 map
map<string, int> MaxEntClassifier::reduce_counter(vector<map<string, int>>& input)
{
	map<string, int> reducer;

	// loop over de vector
	for (size_t i = 0; i < input.size(); i++)
	{
		map<string, int>::iterator it;

		// for loop over de map/dict 
		for (it = input[i].begin(); it != input[i].end(); it++)
		{
			// check of het in de dict bestaat
			if (reducer.find(it->first) == reducer.end())
			{
				reducer.insert({ it->first,it->second });
			}
			else
			{
				reducer[it->first] += it->second;
			}
		}
	}

	return reducer;
}

// deze functie zet de meegegeven map/dict om tot een matrix
void MaxEntClassifier::execute_counter(map<string, int>& input)
{
	map<string, int>::iterator it;

	for (it = input.begin(); it != input.end(); it++)
	{
		// zet char om in int voor makkelijker indexing
		int x = translate_into_int(it->first[0]);
		int y = translate_into_int(it->first[1]);

		matrix[x][y] += it->second;
	}
}

// zet een char om in een int voor lijst index
// werkt ook als tolower()
// speciale tekens wordt omgezet tot een 0
// de rest gaat van 1 tot 27
int MaxEntClassifier::translate_into_int(char letter)
{
	int ascii = letter;

	if (ascii >= 65 && ascii <= 90)
	{
		return ascii - 64;
	}
	else if (ascii >= 97 && ascii <= 122)
	{
		return ascii - 96;
	}
	else
	{
		return 0;
	}
}

// een getter voor de matrix
vector<vector<int>> MaxEntClassifier::get_weights()
{
	return matrix;
}

