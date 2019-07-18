#include<iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <algorithm>

using namespace std;

bool isKeyExists(int key, const map<int,int>& hashmap){
	if(hashmap.find(key) == hashmap.end())
		return false;
	else
		return true;
}

void getMaxPopulation_v1(vector<int>& birthYears, vector<int>& deathYears, int startYear, int endYear){

	map<int, int> yearlyPopCount;

	for(int it = startYear; it <= endYear; it++)
		yearlyPopCount[it] = 0;

	sort(birthYears.begin(), birthYears.end());
	sort(deathYears.begin(), deathYears.end());

	// since death in an year should reduce dec pop in next year
	// also this solves the problem of person born and dead in same year 
	for(auto& item:deathYears) {item++;}

	vector<int>::iterator birth_iter, death_iter;
	
	birth_iter = birthYears.begin();
	death_iter = deathYears.begin();
	int counter = 0;

	while((birth_iter != birthYears.end()) || (death_iter != deathYears.end())){

		if((*birth_iter <= *death_iter) && (birth_iter != birthYears.end()) ){ 
			counter++;
			while(*birth_iter == *(birth_iter+1)){
				counter++;
				birth_iter++;
			}

			assert((isKeyExists(*birth_iter, yearlyPopCount), "given input is not within the possible year range"));
			yearlyPopCount[*birth_iter] += counter;
			birth_iter++;
			counter = 0;
		}

		else{
			counter++;
			while(*death_iter == *(death_iter+1)){
				counter++;
				death_iter++;
			}

			assert((isKeyExists(*death_iter, yearlyPopCount), "given input is not within the possible year range"));
			yearlyPopCount[*death_iter] -= counter;
			death_iter++;
			counter = 0;
		}
	}

	// go through all the keys of hashmap
	int cum_pop = 0;
	int max_pop = 0;
	int max_pop_yr = startYear-1;

	for(auto& map_pair : yearlyPopCount){
		cum_pop += map_pair.second;
		map_pair.second = cum_pop;
		if(cum_pop > max_pop){
			max_pop = cum_pop;
			max_pop_yr = map_pair.first;
		}
	}

	cout << "max population is " << max_pop << " in year " << max_pop_yr << endl;
	// cout << "cum_pops: " << endl;
	// for(auto& map_pair : yearlyPopCount){
	// 	// cout << map_pair.first << ": " << map_pair.second << endl;
	// 	cout << map_pair.second << ", " ;
	// }
	// cout << endl;
}

void getMaxPopulation_v2(vector<int>& birthYears, vector<int>& deathYears, int startYear, int endYear){

	map<int, int> yearlyPopCount;
	for(int it = startYear; it<endYear; it++)
		yearlyPopCount[it] = 0;

	for(auto& byear : birthYears){
		assert((isKeyExists(byear, yearlyPopCount), "given input year is not in expected range"));
		yearlyPopCount[byear]++;
	}

	for(auto& dyear : deathYears){
		assert((isKeyExists(dyear, yearlyPopCount), "given input year is not in expected range"));
		yearlyPopCount[dyear+1]--;
	}

		// go through all the keys of hashmap
	int cum_pop = 0;
	int max_pop = 0;
	int max_pop_yr = startYear-1;

	for(auto& map_pair : yearlyPopCount){
		cum_pop += map_pair.second;
		map_pair.second = cum_pop;
		if(cum_pop > max_pop){
			max_pop = cum_pop;
			max_pop_yr = map_pair.first;
		}
	}

	cout << "max population is " << max_pop << " in year " << max_pop_yr << endl;
	// for(auto& map_pair : yearlyPopCount){
	// 	// cout << map_pair.first << ": " << map_pair.second << endl;
	// 	cout << map_pair.second << ", " ;
	// }
	// cout << endl;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv){
	vector<pair<int,int>> peopleList;
	vector<int> birthYears{10,15,25,46,83,91,39,72,96,64};
	vector<int> deathYears{40,29,25,48,100,98,64,100,101,92};

	cout << "birth years: " << endl;
	for(auto& elem : birthYears)
		cout << elem << ", ";
	cout << endl;

	cout << "birth years: " << endl;
	for(auto& elem : deathYears)
		cout << elem << ", ";
	cout << endl;

	// getMaxPopulation_v1(birthYears, deathYears, 0, 101);
	getMaxPopulation_v2(birthYears, deathYears, 0, 101);
	return 0;
}