#include "std_lab_facilities.h"
#define MAX 256

struct item {
        string name;
        int value;
};

class person {
        private:
                string name;
                int money;
                int n;
                item item_list[MAX];
        public:
                person();
                void person_info(string name_info, int money_info);
                void insert(string item_name, int value);
                string get_name() { return name; }
                void print(ofstream &ofs);
                bool buy(string item_name, int value);
		int have(string item_name);
		void sell(string item_name);
};

person::person() {
        this->n = 0;
}

void person::person_info(string name_info, int money_info) {
        name = name_info;
        money = money_info;
}

void person::insert(string item_name, int value) {
	item it;
	it.name = item_name;
	it.value = value;
	item_list[n] = it;
        n++;
}

void person::print(ofstream &ofs) {
        ofs << name << " " << n << " " << money <<endl;
	for (int i = 0; i < n; i++) { ofs << item_list[i].name << " " << item_list[i].value <<endl; }
}

bool person::buy(string item_name, int value) {
	if (money >= value) {
		money -= value;
		insert(item_name, value);
		return true;
	}
	else return false;
}

int person::have(string item_name) {
	int min = -1;

	for (int i = 0; i < n; i++) {
		if (item_name != item_list[i].name) continue;
		if (min == -1) min = item_list[i].value;
		else if (min > item_list[i].value) min = item_list[i].value;
	}
	return min;
}

void person::sell(string item_name) {
	int min = -1;

	for (int i = 0; i < n; i++) {
		if (item_name != item_list[i].name) continue;
		if (min == -1) min = i;
		else if (item_list[min].value > item_list[i].value) min = i;
	}
	money += item_list[min].value;
	for (int j = min; j < n-1; j++) { item_list[j] = item_list[j+1]; }
	item_list[n-1].name = "";
	item_list[n-1].value = 0;
	n--;	
}

string find_seller(person people[], string req_item, string buyer_list[], int people_num, int buyer_num);
bool trade(person people[], string req_item, string buyer, string seller, int people_num);

int main(int argc, char* argv[])
{
        ifstream ifs(argv[1]);
        string line;
        int people_num, req_num;

        if (ifs.is_open()) {
                stringstream iss;
		getline(ifs, line);
		iss << line;
		getline(iss, line, ' ');
		people_num = atoi(line.c_str());
		getline(iss, line);
		req_num = atoi(line.c_str());

		person people[people_num];

		for (int i = 0; i < people_num; i++) {
                	stringstream iss2;
			getline(ifs, line);
                        iss2 << line;
			getline(iss2, line, ' ');
                        string name = line;
                        getline(iss2, line, ' ');
                        int item_num = atoi(line.c_str());
			getline(iss2, line);
                        int money = atoi(line.c_str());
                        
			people[i].person_info(name, money);

                        for (int j = 0; j < item_num; j++) {
				stringstream iss3;
				getline(ifs, line);
				iss3 << line;
				getline(iss3, line, ' ');
				string item_name = line;
				getline(iss3, line);
				int value = atoi(line.c_str());
				people[i].insert(item_name, value);
			}
				
                }

		for (int i = 0; i < req_num; i++) {
			stringstream iss2;
			getline(ifs, line);
			iss2 << line;
			getline(iss2, line, ' ');
			string req_item = line;
			string buyer_list[people_num];
			int buyer_num = 0;

			while (getline(iss2, line, ' ')) {
				string seller = find_seller(people, req_item, buyer_list, people_num, buyer_num);
				if (seller == "0") break;
				
				if (trade(people, req_item, line, seller, people_num)) {
					buyer_list[buyer_num] = line;
					buyer_num++;
				}
			}
		}
                ifs.close();

	        ofstream ofs(argv[2]);

        	if (ofs.is_open()) {
                	ofs << people_num <<endl;
			for (int i = 0; i < people_num; i++) { people[i].print(ofs); }
		}
                ofs.close();
        }
        return 0;
}

string find_seller(person people[], string req_item, string buyer_list[], int people_num, int buyer_num) {
	int value_list[people_num];
	string seller_list[people_num];
	int n = 0;

	for (int i = 0; i < people_num; i++) {
		int checker = 0;
		for (int j = 0; j < buyer_num; j++) {
			if (people[i].get_name() == buyer_list[j]) {
				checker = 1;
				break;
			}
		}
		if (checker == 1) continue;	
		if (people[i].have(req_item) != -1) {
			seller_list[n] = people[i].get_name();
			value_list[n] = people[i].have(req_item);
			n++;
		}
	}
	if (n == 0) return "0";

	int min = 0;
	for (int i = 0; i < n; i++) { if (value_list[min] > value_list[i]) min = i; }
	return seller_list[min];
}

bool trade(person people[], string req_item, string buyer, string seller, int people_num) {
	int b, s;

	for (int i = 0; i < people_num; i++) {
		if (people[i].get_name() == buyer) b = i;
		else if (people[i].get_name() == seller) s = i;
	}

	if (people[b].buy(req_item, people[s].have(req_item))) {
		people[s].sell(req_item);
		return true;
	}
	else return false;
}
