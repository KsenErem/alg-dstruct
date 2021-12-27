#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
	int key;
	int number;
	struct tree* left;
	struct tree* right;
}tree_t;

tree_t* CreateTree(int key) {
	tree_t* Tree = (tree_t*)malloc(sizeof(tree_t));
	if (!Tree)
		return NULL;
	Tree->key = key;
	Tree->left = Tree->right = NULL;
	Tree->number = 1;
	return Tree;
}

void DeleteTree(tree_t* Tree) {
	if (!Tree)
		return;
	DeleteTree(Tree->left);
	DeleteTree(Tree->right);
	free(Tree);
	return;
}

int AddElem(tree_t* Tree, int key) {
	int flag = 0;
	if (!Tree)
		return 0;
	if (key < Tree->key) {
		if (!Tree->left) {
			Tree->left = CreateTree(key);
			if (Tree->left) {
				Tree->number++;
				flag = 1;
			}
		}
		else {
			flag = AddElem(Tree->left, key);
			if (flag)
				Tree->number++;
		}
	}
	if (key > Tree->key) {
		if (!Tree->right) {
			Tree->right = CreateTree(key);
			if (Tree->right) {
				Tree->number++;
				flag = 1;
			}
		}
		else {
			flag = AddElem(Tree->right, key);
			if (flag)
				Tree->number++;
		}
	}
	return flag;
}

tree_t* kMin(tree_t* Tree, int k) {
	int r;
	if (!Tree)
		return NULL;
	if (Tree->left)
		r = Tree->left->number + 1;
	else
		r = 1;
	if (r != k) {
		if (r > k)
			Tree = kMin(Tree->left, k);
		else
			Tree = kMin(Tree->right, k - r);
	}
	return Tree;
}

void PrintLesser(tree_t* Tree, int key, FILE* file) {
	if (!Tree)
		return;
	PrintLesser(Tree->left, key, file);
	if (Tree->key < key) {
		fprintf(file, "%i ", Tree->key);
		PrintLesser(Tree->right, key, file);
	}
	return;
}

void PrintTree(tree_t* Tree) {
	if (!Tree)
		return;
	printf("%i ", Tree->key);
	if (Tree->left)
		PrintTree(Tree->left);
	if (Tree->right)
		PrintTree(Tree->right);
}

void PrintKMin(tree_t* Tree, int k, FILE* file) {
	tree_t* tmpTree = kMin(Tree, k);
	if (!tmpTree)
		return;
	if (tmpTree->key % 2 == 0) {
		PrintLesser(Tree, tmpTree->key, file);
	}
	else
		fprintf(file, "%i", tmpTree->key);
	return;
}

tree_t* ReadFile(FILE* file) {
	int key;
	tree_t* Tree = NULL;
	if (fscanf(file, "%i", &key) ==1) 
		Tree = CreateTree(key);
	if (!Tree)
		return NULL;
	while (fscanf(file, "%i", &key) != EOF)
		if (!AddElem(Tree, key))
			return Tree;
	return Tree;
}

int main(void)
{
	int k = 6;

	FILE* input = fopen("input.txt", "r");
	if (input == NULL)
	{
		printf("no file\n");
		fclose(input);
		return 1;
	}

	tree_t* Tree = ReadFile(input);
	if (Tree == NULL)
	{
		printf("error\n");
		DeleteTree(Tree);
		fclose(input);
		return 1;
	}

	FILE* output = fopen("output.txt", "w");
	PrintKMin(Tree, k, output);

	DeleteTree(Tree);
	fclose(output);
	fclose(input);
	return 0;
}