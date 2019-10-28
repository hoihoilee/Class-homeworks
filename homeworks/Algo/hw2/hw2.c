#include <stdio.h>
#include <stdlib.h>

typedef struct rbnode {
	int key;
	int size;
	int color; //black : 0, red : 1
	struct rbnode *left, *right, *parent;
} rbnode;

typedef struct rbtree {
	rbnode *root;
	rbnode *nil;
} rbtree;

/*void print_tree(rbtree* T, rbnode *X) {
	char *color[2] = {"black", "red  "};
	if (X == T->nil) return;
	print_tree(T, X->left);
	if (X == T->root) printf("key : %d, size : %d, color : %s, parent : NULL\n", X->key, X->size, color[X->color]);
	else printf("key : %d, size : %d, color : %s, parent : %d\n", X->key, X->size, color[X->color], X->parent->key);
	print_tree(T, X->right);
	return;
}*/

void switch_node(rbtree *T, rbnode *X, rbnode *Y) { //Y node get the position of X node
	if (X->parent == T->nil) T->root = Y;
	else if (X == X->parent->left) X->parent->left = Y;
	else X->parent->right = Y;

	Y->parent = X->parent;
	return;
}

void rotate_tree(rbtree *T, rbnode *X, int r) { //right : 0, left : 1
	int tmp_size = 0;
	rbnode *tmp;
	if (r == 0) {
		tmp = X->left;
		X->left = tmp->right;

		if (tmp->right != T->nil) {
			tmp->right->parent = X;
			tmp_size = tmp->right->size;
		}

		tmp->parent = X->parent;

		if (X->parent == T->nil) T->root = tmp;
		else if (X == X->parent->left) X->parent->left = tmp;
		else X->parent->right = tmp;

		tmp->right = X;
		X->parent = tmp;

		tmp_size += X->size - tmp->size;  //maintaining the size
		tmp->size = X->size;
		X->size = tmp_size;
	}
	else {
		tmp = X->right;
		X->right = tmp->left;

		if (tmp->left != T->nil) {
			tmp->left->parent = X;
			tmp_size = tmp->left->size;
		}

		tmp->parent = X->parent;

		if (X->parent == T->nil) T->root = tmp;
		else if (X == X->parent->left) X->parent->left = tmp;
		else X->parent->right = tmp;

		tmp->left = X;
		X->parent = tmp;

		tmp_size += X->size - tmp->size;
		tmp->size = X->size;
		X->size = tmp_size;
	}
	return;
}

int OS_Insert(rbtree* T, int x) {
        rbnode *leaf = (rbnode*)malloc(sizeof(rbnode));
        rbnode *tmp = T->root;
	rbnode *par = T->nil;

	leaf->key = x;
        leaf->size = 1;
        leaf->color = 1;
        leaf->left = T->nil;
        leaf->right = T->nil;
	
	while(tmp != T->nil) { //searching the position of given key
		par = tmp;
		if (x > tmp->key) tmp = tmp->right;
		else if (x < tmp->key) tmp = tmp->left;
		else { //already has the key
			free(leaf);
			return 0;
		}
	}
	leaf->parent = par;

	if (par == T->nil) T->root = leaf;
	else if (x > par->key) par->right = leaf;
	else par->left = leaf;

	tmp = leaf;
	while(tmp != T->root) { //get size by 1
		tmp = tmp->parent;
		tmp->size++;
	}

	while(leaf->parent->color == 1) { //maintaining the property of red-black tree
		if (leaf->parent == leaf->parent->parent->left) {
			tmp = leaf->parent->parent->right;

			if (tmp->color == 1) {
				leaf->parent->color = 0;
				tmp->color = 0;
				leaf->parent->parent->color = 1;
				leaf = leaf->parent->parent;
			}
			else {
				if (leaf == leaf->parent->right) {
					leaf = leaf->parent;
					rotate_tree(T, leaf, 1);
				}
				leaf->parent->color = 0;
				leaf->parent->parent->color = 1;
				rotate_tree(T, leaf->parent->parent, 0);
			}
		}
		else {
			tmp = leaf->parent->parent->left;

			if (tmp->color == 1) {
				leaf->parent->color = 0;
				tmp->color = 0;
				leaf->parent->parent->color = 1;
				leaf = leaf->parent->parent;
			}
			else {
				if (leaf == leaf->parent->left) {
					leaf = leaf->parent;
					rotate_tree(T, leaf, 0);
				}
				leaf->parent->color = 0;
				leaf->parent->parent->color = 1;
				rotate_tree(T, leaf->parent->parent, 1);
			}
		}
	}
	T->root->color = 0;
	return x;
}

int OS_Delete(rbtree* T, int x) {
	rbnode *node = T->root;
	rbnode *tmp;
	rbnode *pos;
	int color;

	while(node != T->nil) { //searching the key
		if (node->key > x) node = node->left;
		else if (node->key < x) node = node->right;
		else break;
	}
	if (node == T->nil) return 0; //has no key

	color = node->color;

	if (node->left == T->nil) { //there's no or only one child
		pos = node->right;
		switch_node(T, node, node->right);
	}
	else if (node->right == T->nil) {
		pos = node->left;
		switch_node(T, node, node->left);
	}
	else { //there are 2 children
		tmp = node->right;
		while(tmp->left != T->nil) {
			tmp = tmp->left;
		}
		color = tmp->color;
		pos = tmp->right;

		switch_node(T, tmp, tmp->right);
		tmp->right = node->right;
		tmp->right->parent = tmp;
		tmp->size = node->size;
		switch_node(T, node, tmp);
		tmp->left = node->left;
		tmp->left->parent = tmp;
		tmp->color = node->color;
	}
	tmp = pos;
        while(tmp != T->root) { //lose size by 1
                tmp = tmp->parent;
                tmp->size--;
        }

	if (color == 0) { //maintaining the property of red-black tree
		while((pos->color == 0) && (pos != T->root)) {
			if (pos == pos->parent->left) {
				tmp = pos->parent->right;
				if (tmp->color == 1) {
					tmp->color = 0;
					pos->parent->color = 1;
					rotate_tree(T, pos->parent, 1);
					tmp = pos->parent->right;
				}
				if ((tmp->left->color == 0) && (tmp->right->color == 0)) {
					tmp->color = 1;
					pos = pos->parent;
				}
				else {
					if((tmp->left->color == 1) && (tmp->right->color == 0)) {
						tmp->color = 1;
						tmp->left->color = 0;
						rotate_tree(T, tmp, 0);
						tmp = pos->parent->right;
					}
				}
				if (tmp->right->color == 1) {
					tmp->color = pos->parent->color;
					tmp->right->color = 0;
					pos->parent->color = 0;
					rotate_tree(T, pos->parent, 1);
					pos = T->root;
				}
			}
			else {
				tmp = pos->parent->left;
				if (tmp->color == 1) {
					tmp->color = 0;
					pos->parent->color = 1;
					rotate_tree(T, pos->parent, 0);
					tmp = pos->parent->left;
				}
				if ((tmp->left->color == 0) && (tmp->right->color == 0)) {
					tmp->color = 1;
					pos = pos->parent;
				}
				else {
					if((tmp->right->color == 1) && (tmp->left->color == 0)) {
						tmp->color = 1;
						tmp->right->color = 0;
						rotate_tree(T, tmp, 1);
						tmp = pos->parent->left;
					}
				}
				if (tmp->left->color == 1) {
					tmp->color = pos->parent->color;
					tmp->left->color = 0;
					pos->parent->color = 0;
					rotate_tree(T, pos->parent, 0);
					pos = T->root;
				}
			}
		}
		pos->color = 0;
	}
	return x;			
}

int OS_Select(rbtree* T, int i) {
	if ((T->root->size < i) || (i <= 0)) return 0;

	rbnode *tmp = T->root;
	int r;

	while(tmp != T->nil) {
		r = tmp->left->size + 1;

		if (i == r) return tmp->key;
		if (i < r) tmp = tmp->left;
		else {
			tmp = tmp->right;
			i = i - r;
		}
	}
	return 0;
}

int OS_Rank(rbtree* T, int x) {
	rbnode *tmp = T->root;
	int r = 1;

        while(tmp != T->nil) { //searching the key
                if (tmp->key > x) tmp = tmp->left;
                else if (tmp->key < x) {
			r += tmp->left->size + 1;
			tmp = tmp->right;
		}
                else {
			r += tmp->left->size;
			break;
		}
        }
        if (tmp == T->nil) return 0; //has no key
	return r;
}

void main(int argc, char *argv[]) {
        if (argc != 2) return;

        FILE *file = fopen(argv[1], "r");
        if (file == NULL) return;

        FILE *outfile = fopen("hw2_output.txt", "w");

        char line[10];
        rbtree *T = (rbtree*)malloc(sizeof(rbtree));
	T->nil = (rbnode*)malloc(sizeof(rbnode));
	T->nil->color = 0;
	T->nil->size = 0;
	T->root = T->nil;

        while (fgets(line, sizeof(line), file) != NULL) {
                char inst = line[0];
		int N = atoi(line + 2);
		if (inst == 'I') {
			fprintf(outfile, "I %d : %d\n", N, OS_Insert(T, N));
		}
		else if (inst == 'D') {
			fprintf(outfile, "D %d : %d\n", N, OS_Delete(T, N));
		}
		else if (inst == 'S') {
			fprintf(outfile, "S %d : %d\n", N, OS_Select(T, N));
		}
		else {
			fprintf(outfile, "R %d : %d\n", N, OS_Rank(T, N));
		}
        }
	//print_tree(T, T->root);
	free(T);
       	fclose(file);
	fclose(outfile);
        return;
}
