#include "std_lab_facilities.h"
#define MAX 256

struct item {
	string name;
	int size;
	char type;
};

class container {
	private:
		char type;
		int cost;
		int size;
		int n;
		item item_list[MAX];
	public:
		container();
		void cont_info(char type_info, int cost_info, int size_info);
		bool insert(item it);
		char get_type() { return type;}
		int get_cost() {return cost;}
		int get_size() {return size;}
		int get_item_num() {return n;}
		void print_status(ofstream &ofs);
		void get_item_list(item cpy_item_list[]);
		void initialize();
};

container::container() {
	this->n = 0;
}

void container::initialize() {
	for (int i = 0; i < n; i++) {
		item_list[i].name = "";
	        item_list[i].size = 0;
        	item_list[i].type = ' ';
	}
	n = 0;
}		

void container::get_item_list(item cpy_item_list[]) {
	for (int i = 0; i < n; i++) { cpy_item_list[i] = item_list[i]; }
}

void container::cont_info(char type_info, int cost_info, int size_info) {
	type = type_info;
	cost = cost_info;
	size = size_info;
}

bool container::insert(item it) {
	int total = 0;
	for (int i = 0; i < n; i++) { total += item_list[i].size; }
	if ((total + it.size) <= size) {
		item_list[n] = it;
		n++;
		return true;
	}

	return false;
}

void container::print_status(ofstream &ofs) {
        ofs << "Size: " << size <<endl;
	ofs << "Type: " << type <<endl;
        ofs << "Cost: " << cost <<endl;
        ofs << "Total items: " << n <<endl;
        ofs << "Items:" <<endl;

	for (int i = 0; i < n; i++) {
		ofs << item_list[i].name << "," << item_list[i].size << "," << item_list[i].type <<endl;
	}
}

void match_type(container cont[], int *N, int *P, int *C);
void remove(item item_list[], int i, int n);
void put_FI(container cont[], item item_list[], int* num);
void copy_item_list(item item_list[], item cpy_item_list[], int num);
void copy_container(container org_cont[], container cpy_cont[]);
int cal_cost(container cont[]);
bool checker(int cost[], int ch_cost);
int min_cost(container cont[], item item_list[], int num);

int main(int argc, char* argv[])
{
	ifstream ifs(argv[1]);
	string line;
	int size, cost, total_cost;
	char type;
	container cont[3];

	if (ifs.is_open()) {
		getline(ifs, line);
		int num = atoi(line.c_str());
		
		for (int i = 0; i < 3; i++) {
			stringstream iss;
			getline(ifs, line);
			iss << line;
			getline(iss, line, ' ');
			size = atoi(line.c_str());
			getline(iss, line, ' ');
			type = line[0];
			getline(iss, line);
			cost = atoi(line.c_str());
			
			cont[i].cont_info(type, cost, size);
		}

		item item_list[num];
		
		for (int i = 0; i < num; i++) {
			stringstream iss;
			getline(ifs, line);
			iss << line;
			getline(iss, line, ' ');
			item_list[i].name = line;
			getline(iss, line, ' ');
			item_list[i].size = atoi(line.c_str());
			getline(iss, line);
			item_list[i].type = line[0];
		}
		
		put_FI(cont, item_list, &num);//if there are F or I type items, put them first

		total_cost = min_cost(cont, item_list, num);
		
		ifs.close();
	}
	
	ofstream ofs(argv[2]);

	if (ofs.is_open()) {
		int total_cont = 0;
		int n = 1;

		for (int i = 0; i < 3; i++) { if (cont[i].get_item_num() > 0) total_cont++; }
			
		ofs << "Warehouse status report" <<endl;
		ofs << "Total cost: " << total_cost <<endl;
		ofs << "Total containers: " << total_cont <<endl;
		
		for (int i = 0; i < 3; i++) {
			if (cont[i].get_item_num() == 0) continue;

			ofs << "Container" << n << " status"<<endl;
			cont[i].print_status(ofs);
			ofs << "Container" << n << " end"<<endl;
			n++;
		}

		ofs.close();
	}
	return 0;	
}

void remove(item item_list[], int i, int n)
{
	for (int j = i; j < (n - 1); j++) {
		item_list[j] = item_list[j+1];
	}

	item_list[n-1].name = "";
	item_list[n-1].size = 0;
	item_list[n-1].type = ' ';
}

void match_type(container cont[], int *N, int *P, int *C)
{
	for (int i = 0; i < 3; i++) {
		if (cont[i].get_type() == 'N') *N = i;
		else if (cont[i].get_type() == 'P') *P = i;
		else *C = i;
	}
}

void put_FI(container cont[], item item_list[], int *num)
{
	int n = *num;
	int N, P, C;

	match_type(cont, &N, &P, &C);

	for (int i = 0; i < n; i++) {
		if (item_list[i].type == 'F') {
			cont[P].insert(item_list[i]);
			remove(item_list, i, n);
			n--;
			i--;
		}
		else if (item_list[i].type == 'I') {
			cont[C].insert(item_list[i]);
			remove(item_list, i, n);
			n--;
			i--;
		}
		else continue;
	}

	*num = n;
}

void copy_item_list(item item_list[], item cpy_item_list[], int num)
{
	for (int i = 0; i < num; i++) { cpy_item_list[i] = item_list[i]; } //copy item list
	remove(cpy_item_list, 0, num);
}

void copy_container(container org_cont[], container cpy_cont[])
{
	for (int i = 0; i < 3; i++) {
		cpy_cont[i].cont_info(org_cont[i].get_type(), org_cont[i].get_cost(), org_cont[i].get_size());
		item item_list[org_cont[i].get_item_num()];
		org_cont[i].get_item_list(item_list);
		for (int j = 0; j < org_cont[i].get_item_num(); j++) { cpy_cont[i].insert(item_list[j]); }
	}
}

int cal_cost(container cont[])
{
	int total_cost = 0;
	for (int i = 0; i < 3; i++) { if (cont[i].get_item_num() > 0) total_cost += cont[i].get_cost(); }
	return total_cost;
}

bool checker(int cost[], int ch_cost)
{
	int min = -1;
	for (int i = 0; i < 3; i++) {
		if (cost[i] < 0) continue;
		if (min == -1) min = cost[i];
		else if (min > cost[i]) min = cost[i];
	}
	if (min == -1) return true;
	if (min > ch_cost) return true;
	else return false;
}

int min_cost(container cont[], item item_list[], int num)
{
	if (num == 0) return cal_cost(cont);

	container cpy_cont[3];
	copy_container(cont, cpy_cont);

	item cpy_item_list[num];
	item ITEM = item_list[0];
	int cost[3] = {-1, -1, -1};

	copy_item_list(item_list, cpy_item_list, num);
	
	for (int i = 0; i < 3; i++) {
		if (cpy_cont[i].insert(ITEM)) {
			if (checker(cost, cal_cost(cpy_cont)) == false) continue;

			cost[i] = min_cost(cpy_cont, cpy_item_list, num-1);
			for (int j = 0; j < 3; j++) { cpy_cont[j].initialize(); }
			copy_container(cont, cpy_cont);
			copy_item_list(item_list, cpy_item_list, num);//copy itemlist to cpy_itemlist
		}
	}

	int min[2] = {-1, -1};

	for (int i = 0; i < 3; i++) {
		if (cost[i] < 0) continue;
		if (min[0] == -1) {
			min[0] = cost[i];
			min[1] = i;
		}
		else if (min[0] > cost[i]) {
			min[0] = cost[i];
			min[1] = i;
		}
	}
	
	if (min[1] == 0) {
		cont[0].insert(ITEM);
		min_cost(cont, cpy_item_list, num-1);
	}
	else if (min[1] == 1) {
                cont[1].insert(ITEM);
                min_cost(cont, cpy_item_list, num-1);
	}
	else if (min[1] == 2) {
                cont[2].insert(ITEM);
                min_cost(cont, cpy_item_list, num-1);
	}

	return min[0];
}
