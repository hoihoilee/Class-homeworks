#include "std_lab_facilities.h"

struct node {
	int x;
	node *next;
};

class lifo {
	private:
		node *head;
		node *tail;
		void print(node *p);
	public:
		lifo(void);
		~lifo(void);
		void push(int val);
		int pop();
		void print();
};

lifo::lifo() {
	head = tail = NULL;
}

lifo::~lifo() {
	node *p = head;
	node *p2;
	while(p != NULL) {
		p2 = p;
		p = p->next;
		delete p2;
	}
}

void lifo::push(int val) {
	node *p = new node;
	p->x = val;
	p->next = NULL;

	if (head == NULL) {
		head = p;
		tail = p;
	}
	else {
		tail->next = p;
		tail = p;
	}
}

int lifo::pop() {
	int value = tail->x;
	node *p = head;
	while((p->next) != tail) {
		p = p->next;
	}
	tail = p;
	delete p;
	return value;
}

void lifo::print() {
	node *p = head;
	while(p != NULL) {
		cout << p->x << " ";
		p = p->next;
	}
	cout <<endl;
}

int main() {
	lifo list;
	list.push(5);
	list.push(6);
	list.push(7);
	list.print();
	cout << list.pop() <<endl;
	return 0;
}

