#pragma once

#include <vector>
#include <string>
#include <map>

using std::vector;
using std::string;
using std::map;

class MaxEntClassifier
{
private:
	vector<vector<int>> matrix;

public:
	MaxEntClassifier(int amount_weights)
	{
		matrix = vector<vector<int>>(amount_weights, std::vector<int>(amount_weights));
	}

	void input_counter(string& input);

	vector<vector<float>> create_prob_matrix(vector<int>& unigram,vector<vector<int>>& input);

	vector<int> normalize_bigram(vector<vector<int>>& input);

	float compare(vector<vector<int>> &input);

	map<string, int> map_counter(string& input);

	map<string, int> reduce_counter(vector<map<string, int>>& input);

	void execute_counter(map<string, int>& input);

	int translate_into_int(char letter);

	vector<vector<int>> get_weights();

};