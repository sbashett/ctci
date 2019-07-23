#include <iostream>
#include <map>
#include <vector>
#include <algorithm> //max
#include <utility> // pair

using namespace std;

class MapValue{
public:
	int max_min;
	bool present_flag;
	int next_index_link;
	MapValue(int, bool, int);
};

MapValue::MapValue(int max_min, bool present_flag, int next_index_link) : 
			max_min(max_min), present_flag(present_flag), 
			next_index_link(next_index_link) {}

bool isKeyExists(int key, map<int,MapValue*>& mem_table){

	if(mem_table.find(key) == mem_table.end())
		return false;
	else
		return true;
}

MapValue* get_max_minutes(vector<int>& appointments, int index, map<int,MapValue*>& mem_table){

	if(isKeyExists(index, mem_table))
		return mem_table[index];

	if(index == static_cast<int>(appointments.size() - 2)){ // two elements remaining
		if(appointments[index] >= appointments[index+1])
			mem_table.insert(make_pair(index, new MapValue(appointments[index], true, appointments.size())));
		else{
			mem_table.insert(make_pair(index, new MapValue(appointments[index+1], false, index+1)));
			mem_table.insert(make_pair(index+1, new MapValue(appointments[index+1], true, appointments.size())));
		}
		return mem_table[index];
	}

	if(index == static_cast<int>(appointments.size() - 1)){ // one element remaining
		mem_table.insert(make_pair(index, new MapValue(appointments[index], true, appointments.size())));
		return mem_table[index];
	}

	int compVal1 = appointments[index] + get_max_minutes(appointments, index+2, mem_table)->max_min;
	int compVal2 = get_max_minutes(appointments, index+1, mem_table)->max_min;
	if(compVal1 >= compVal2 )
		mem_table.insert(make_pair(index, new MapValue(compVal1, true, index+2)));
	else
		mem_table.insert(make_pair(index, new MapValue(compVal2, false, index+1)));

	return mem_table[index];
}

int main(void){

	vector<int> appointments {30, 15, 60, 75, 45, 15, 15, 45};
	// vector<int> appointments {75, 105, 120, 75, 90, 135};
	// vector<int> appointments {45, 60, 45, 15};
	map<int, MapValue*> mem_table;

	MapValue* ret_val = get_max_minutes(appointments, 0, mem_table);

	cout << "max minutes scheduled: " << ret_val->max_min << endl;

	int index = 0;

	while(true){

		if(mem_table[index]->present_flag)
			cout << appointments[index] << ", ";

		index = mem_table[index]->next_index_link;

		if(index == static_cast<int>(appointments.size()))
			break;
	}
	cout << endl;

	return 0;
}