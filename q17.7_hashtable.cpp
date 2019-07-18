#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility> //pair

using namespace std;

typedef vector<pair<string, int>> FREQVEC;
typedef vector<pair<string, string>> SYNVEC;
typedef map<string, string> SYNMAP;
typedef map<string, int> FREQMAP;


template <class T1, class T2>
bool isExists(T1 key, T2& hashmap){
	if(hashmap.find(key) == hashmap.end())
		return false;
	else
		return true;
}

void fill_synonyms_map(SYNMAP& syn_map, SYNVEC& syn_vec){

	for(auto& pairs : syn_vec){
		if(!isExists(pairs.second, syn_map)){

			if(isExists(pairs.first, syn_map))
				syn_map[pairs.second] = syn_map[pairs.first];
			else
				syn_map[pairs.second] = pairs.first;
		}

		else{
			// need to trace back to adjust evertyhing
			string final_key = syn_map[pairs.second];
			string current_key = pairs.first;
			string temp;

			while(true){

				if(!isExists(current_key, syn_map)){
					syn_map[current_key] = final_key;
					break;
				}

				if(syn_map[current_key] == final_key)
					break;

				temp = syn_map[current_key];
				syn_map[current_key] = final_key;
				current_key = temp;
			}
		}
	}

	return;
}

void fill_freq_map(FREQMAP& freq_map, FREQVEC& freq_vec, SYNMAP& syn_map){

	string freq_key;

	for(auto& pairs : freq_vec){

		if(isExists(pairs.first, syn_map))
			freq_key = syn_map[pairs.first];
		else
			freq_key = pairs.first;


		if(isExists(freq_key, freq_map))
			freq_map[freq_key] += pairs.second;
		else
			freq_map[freq_key] = pairs.second;
	}

	return;
}

void fill_final_vec(FREQVEC& final_vec, FREQMAP& freq_map){
	for(auto& pairs : freq_map)
		final_vec.push_back(pairs);

	return;
}

void get_final_freq_list(FREQVEC& final_vec, FREQVEC& freq_vec, SYNVEC& syn_vec){

	SYNMAP syn_map;
	FREQMAP freq_map;

	fill_synonyms_map(syn_map, syn_vec);
	fill_freq_map(freq_map, freq_vec, syn_map);
	fill_final_vec(final_vec, freq_map);

	return;
}

void fill_syn_vec(SYNVEC& syn_vec, string n1, string n2){
	syn_vec.push_back(make_pair(n1, n2));
	return;
}

void fill_freq_vec(FREQVEC& freq_vec, string name, int freq){
	freq_vec.push_back(make_pair(name, freq));
	return;
}

void print_results(FREQVEC& final_vec, FREQVEC& freq_vec, SYNVEC& syn_vec){

	cout << "initial freq vector: " << endl;

	for(auto& pairs : freq_vec){
		cout << pairs.first << ": " << pairs.second << endl;
	}

	cout << endl;

	cout << "synonyms list:" << endl;
	for (auto& pairs : syn_vec){
		cout << "(" << pairs.first << ", " << pairs.second << ") ";
	}

	cout << endl << endl;

	for(auto& pairs : final_vec){
		cout << pairs.first << " : " << pairs.second << endl;
	}

	return;
}


void add_inputs(FREQVEC& freq_vec, SYNVEC& syn_vec){
	// fill_freq_vec(freq_vec, "John", 15);
	// fill_freq_vec(freq_vec, "Jon", 12);
	// fill_freq_vec(freq_vec, "Chris", 13);
	// fill_freq_vec(freq_vec, "Kris", 4);
	// fill_freq_vec(freq_vec, "Christopher", 19);

	// fill_syn_vec(syn_vec, "Jon", "John");
	// fill_syn_vec(syn_vec, "John", "Johnny");
	// fill_syn_vec(syn_vec, "Chris", "Kris");
	// fill_syn_vec(syn_vec, "Chris", "Christopher");


	fill_freq_vec(freq_vec, "John", 10);
	fill_freq_vec(freq_vec, "Jon", 3);
	fill_freq_vec(freq_vec, "Davis", 2);
	fill_freq_vec(freq_vec, "Kari", 3);
	fill_freq_vec(freq_vec, "Johnny", 11);
	fill_freq_vec(freq_vec, "Carlton", 8);
	fill_freq_vec(freq_vec, "Carleton", 2);
	fill_freq_vec(freq_vec, "Jonathan", 9);
	fill_freq_vec(freq_vec, "Carrie", 5);

	fill_syn_vec(syn_vec, "Jonathan", "John");
	fill_syn_vec(syn_vec, "Jon", "Johnny");
	fill_syn_vec(syn_vec, "Johnny", "John");
	fill_syn_vec(syn_vec, "Kari", "Carrie");
	fill_syn_vec(syn_vec, "Carleton", "Carlton");

	return;
}

int main(void){

	SYNVEC syn_vec;
	FREQVEC freq_vec;
	FREQVEC final_vec;

	add_inputs(freq_vec, syn_vec);
	get_final_freq_list(final_vec, freq_vec, syn_vec);

	print_results(final_vec, freq_vec, syn_vec);

	return 0;
}