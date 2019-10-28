#include "std_lab_facilities.h"

struct node {
	int x;
	node *left;
	node *right;
};

class tree {
	private:
		node *root;
		//void deleteTree(node *p);
		void insert(node *p, int val);
		void inorder(node *p);
		void postorder(node *p);
		void preorder(node *p);
	public:
		tree(void);
		~tree(void);
		void insert(int val);
		void print();
};

void tree::inorder(node *p) {
	if (p == NULL) return;
	
	if (p->left != NULL) tree::inorder(p->left);
	cout << p->x << " ";
	if (p->right != NULL) tree::inorder(p->right);
}

void tree::postorder(node *p) {
	if (p == NULL) return;

        if (p->left != NULL) tree::postorder(p->left);
        if (p->right != NULL) tree::postorder(p->right);
	cout << p->x << " ";
}

void tree::preorder(node *p) {
	if (p == NULL) return;

        cout << p->x << " ";
	if (p->left != NULL) tree::preorder(p->left);
        if (p->right != NULL) tree::preorder(p->right);
}

void tree::insert(node *p, int val) {
	/*if (p == NULL) {
		node *p2 = new node;
		p2->x = val;
		p2->left = NULL;
		p2->right = NULL;

		p = p2;
	}
	else {*/
		if ((p->x) > val) {
			if (p->left == NULL) {
				node *p2 = new node;
				p2->x = val;
				p2->left = NULL;
				p2->right = NULL;

				p->left = p2;
			}
			else tree::insert(p->left, val);
		}
		else {
			if (p->right == NULL) {
				node *p2 = new node;
				p2->x = val;
				p2->left = NULL;
				p2->right = NULL;
	
				p->right = p2;
			}
			else tree::insert(p->right, val);
		}
	//}
}

tree::tree(void) {
	root = NULL;
}

tree::~tree(void) {
	delete root;
}

void tree::insert(int val) {
	if(root == NULL)
	{
		node *p = new node;
		p-> x= val;
		p-> left = NULL; p->right = NULL;
		root = p;
	}
	else tree::insert (root, val);
}

void tree::print() {
	cout<<"preorder : ";
	tree::preorder(root);
	cout<<endl;
	cout << "inorder : ";
	tree::inorder(root);
	cout<<endl;
	cout << "postorder : ";
	tree::postorder(root);
	cout << endl;
}

int main() {
	tree list;
	list.insert(8);
	list.insert(3);
	list.insert(1);
	list.insert(6);
	list.insert(4);
	list.insert(7);
	list.insert(10);
	list.insert(14);
	list.insert(13);
	list.print();

	return 0;
}
