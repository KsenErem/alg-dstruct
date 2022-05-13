#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#pragma warning (disable:4996)
const int size = 909091;

typedef struct
{
	char* str;
	int key;
} node;
node* table;
void hash_table()
{
	table = (node*)malloc(size * sizeof(node));
	if (table == NULL)
		return;
	for (int i = 0; i < size; i++)
	{
		table[i].str = NULL;
		table[i].key = 0;
	}
}

int make_hash(const char* str, int iter)
{
	int h = 21;
	int hash_1 = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++)
		hash_1 = h * hash_1 + str[i];
	hash_1 = hash_1 % size;
	int result = (int)(hash_1 + iter) % size;
	return result;
}

int Find(const char* str)
{
	int h = make_hash(str, 0);
	int i = 0;
	while (table[h].str != NULL && i < size)
	{
		if (!table[h].key && strcmp(table[h].str, str) == 0)
			return 1;
		i++;
		h = make_hash(str, i);
	}
	return 0;
}

void Add(const char* str)
{
	int i = 0;
	int h = make_hash(str, 0);
	int first_key = -1;
	while (table[h].str != NULL && i < size)
	{
		if (strcmp(table[h].str, str) == 0 && !table[h].key)
			return;

		if (table[h].key && first_key == -1)
			first_key = h;

		i++;
		h = make_hash(str, i);
	}

	if (first_key != -1)
	{
		table[first_key].str = (char*)malloc((strlen(str) + 1) * sizeof(char));
		strcpy(table[first_key].str, str);
		table[first_key].key = 0;
	}
	else
	{
		table[h].str = (char*)malloc((strlen(str) + 1) * sizeof(char));
		strcpy(table[h].str, str);
	}
}

void Remove(const char* str)
{
	int h = make_hash(str, 0);
	int i = 0;
	while (table[h].str != NULL && i < size)
	{
		if (strcmp(table[h].str, str) == 0 && !table[h].key)
		{
			table[h].key = 1;
			return;
		}
		i++;
		h = make_hash(str, i);
	}
}

void destroy_hash_table(void)
{
	if (table == NULL)
		return;

	for (int i = 0; i < size; i++)
		free(table[i].str);

	free(table);
	table = NULL;
}

int main() {
	hash_table();
	char command;
	char value[100000];
	while (scanf("%c", &command) > 0)
	{
		if (command == 'a')
		{
			scanf("%s", &value);
			Add(value);
		}
		if (command == 'f')
		{
			scanf("%s", &value);
			if (Find(value))
				printf("%s", "yes\n");
			else
				printf("%s", "no\n");
		}
		if (command == 'r')
		{
			scanf("%s", &value);
			Remove(value);
		}
	}
	destroy_hash_table();
	return 0;
}