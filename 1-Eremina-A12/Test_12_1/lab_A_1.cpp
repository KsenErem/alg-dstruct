// вариант 12, Еремина, 5030102/00001

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

#define TRUE 1
#define FALSE 0



// создаем структуру, которая будет хранить элемент списка и результат операции над предыдущим и следующим указателями
struct element {
    char* data;    // строка в памяти
    struct element* xor_address;	 // xor адрес 
};

typedef struct element element;

// структура, которая хранит весь список
typedef struct XOR_list {
    element* first;
    element* last;
};

typedef struct XOR_list XOR_list;

// реализация операции XOR
element* XOR_procedure(element* x, element* y){
    return (element*)((unsigned long long)x ^ (unsigned long long)y);
}

//инициализация списка
void initial(XOR_list* list) {
    list->first = NULL;
    list->last = NULL;
}

// операция добавления элемента в список
int add_element(XOR_list* list, char* str) {
	
	// проверка
	if (list == NULL || str == NULL)
		return FALSE;

	// сохраняем строку 
	int lenght = strlen(str);  // определяем длину строки
	char* a = (char*)malloc(lenght + 1); // выделяем память под строку
	
	// Создаем элемент списка
	element* new_element = (element*)malloc(sizeof(element));

	if (a == NULL || new_element == NULL) {
		free(a);
		free(new_element);
		return FALSE;
	}

	strcpy(a, str); // происходит копирование строки
	a[lenght] = '\0'; // добавим терминальный ноль

	new_element->data = a; // значение элемента (адрес строки)

	// Встраиваем элемент в конец списка
	if (list->first == NULL) {// если список пуст 
		new_element->xor_address = XOR_procedure(0, 0);
		list->first = new_element;
	}
	else {// если есть больше одного элемента

		new_element->xor_address = XOR_procedure(list->last, 0);
		element* prev = XOR_procedure(list->last->xor_address, 0); // адрес предпоследнего элемента

		// обновление xor-адреса последнего элемента списка
		list->last->xor_address = XOR_procedure(prev, new_element);
	}
	list->last = new_element;

	return TRUE;
}


//операция нахождения элемента по ключу
element* find_element_key(XOR_list* list, char* key) {
	
	//в случае если список пуст
	if (list->first == NULL) {
		printf("Empty list\n");
		return NULL;
	}

	element* a1 = list->first;

	//в списке находиться один элемент
	if (list->first == list->last) {

		if (strcmp(a1->data, key) == 0) { // если это тот элемент, который нам нужен
			return a1;
		}
		else {
			printf("Don't have\n");  //нет такого элемента
			return NULL;
		}
	}

	//если в списке более одного эемента
	if (list->first != list->last) {

		element* a2 = XOR_procedure(a1->xor_address, 0); //указатель на второй элемент

		if (strcmp(a1->data, key) == 0) {

			return a1;
		}

		while (strcmp(a2->data, key) != 0) {

			element* next = XOR_procedure(a1, a2->xor_address);

			//если список не содержит элемента
			if ((a2 == list->last) && (strcmp(a2->data, key) != 0)) {
				printf("Don't have1\n");
				return NULL;
			}

			a1 = a2;
			a2 = next;
		}
		return a2;
	}
}

//операция удаления элемента из списка по ключу
int delete_element_key(XOR_list* list, char* key) {

	//если список пуст
	if (list->first == NULL) {
		printf("Empty list\n");
		return NULL;
	}

	element* a1 = list->first;

	//в списке находиться один элемент
	if (list->first == list->last) {

		if (strcmp(a1->data, key) == 0) {

			list->first = NULL;
			list->last = NULL;
			free(a1);
			return TRUE;
		}
		else
		{
			//нет такого элемента
			printf("There isn't such element in list\n");
			return NULL;
		}
	}

	//если в списке более одного эемента
	if (list->first != list->last) {
		//указатель на второй элемент
		element* a2 = XOR_procedure(a1->xor_address, 0);

		//если нужно удалить первый элемент списка
		if (strcmp(a1->data, key) == 0) {
			free(a1);

			element* a3 = XOR_procedure(a1, a2->xor_address);
			a2->xor_address = XOR_procedure(0, a3);
			list->first = a2;
			return TRUE;
		}

		while (strcmp(a2->data, key) != 0) {
			
			element* next = XOR_procedure(a1, a2->xor_address);
			a1 = a2;
			a2 = next;

			//если список не содержит элемента
			if (a2 == NULL) {
				printf("No element\n");
				return NULL;
			}
		}

		if (a2 == list->last) {
			a1->xor_address = XOR_procedure(XOR_procedure(a1->xor_address, a2), 0);
			list->last = a1;
		}
		else {
			// адрес следующего (3-его) элемента
			element* a3 = XOR_procedure(a1, a2->xor_address);
			a1->xor_address = XOR_procedure(XOR_procedure(a1->xor_address, a2), a3);

			if (a3 != NULL) {
				a3->xor_address = XOR_procedure(a1, XOR_procedure(a2, a3->xor_address));
			}

		}

		// удаление элемента a2
		printf("Removed element\n");
		free(a2);
		return TRUE;
	}
}

//операция удаления данного элемента списка (по адресу элемента)
int delete_element_address(XOR_list* list, element* p) {

	//если список пуст
	if (list->first == NULL) {
		printf("Empty list\n");
		return NULL;
	}

	element* a1 = list->first;

	//в списке находиться один элемент
	if (list->first == list->last) {

		if (a1 == p) {
			printf("Element removed\n");
			list->first = NULL;
			list->last = NULL;
			free(a1);
			return TRUE;
		}
		else {
			//нет такого элемента
			printf("There isn't such element in list\n");
			return NULL;
		}
	}

	//если в списке более одного эемента
	if (list->first != list->last) {
		//указатель на второй элемент
		element* a2 = XOR_procedure(a1->xor_address, 0);

		//если нужно удалить первый элемент списка
		if (a1 == p) {
			printf("Removed first element\n");
			free(a1);

			element* a3 = XOR_procedure(a1, a2->xor_address);
			a2->xor_address = XOR_procedure(0, a3);
			list->first = a2;
			return TRUE;
		}

		while (a2 != p) {
			// след = адрес_пред ^ xor_текущего
			element* next = XOR_procedure(a1, a2->xor_address);
			a1 = a2;
			a2 = next;

			//если список не содержит элемента
			if (a2 == NULL) {
				printf("No such element\n");
				return NULL;
			}
		}

		if (a2 == list->last) {
			a1->xor_address = XOR_procedure(XOR_procedure(a1->xor_address, a2), 0);
			list->last = a1;
		}
		else {
			// адрес следующего (3-его) элемента 
			element* a3 = XOR_procedure(a1, a2->xor_address);
			a1->xor_address = XOR_procedure(XOR_procedure(a1->xor_address, a2), a3);

			if (a3 != NULL) {
				a3->xor_address = XOR_procedure(a1, XOR_procedure(a2, a3->xor_address));
			}

		}

		// удаление элемента p2
		printf("Removed element\n");
		free(a2);
		return TRUE;
	}
}


//операция итерирование по списку

//функция возвращяет адрес первого элемента
element* first(XOR_list* list) {
	return list->first;
}

//функция возвращяет адрес последнего элемента
element* last(XOR_list* list) {
	return list->last;
}

//переход к следующему элементу
element* next(XOR_list* list, element* a) {

	if (list->first == NULL) {
		printf("Empty list\n");
		return NULL;
	}

	element* a1 = list->first;
	//в списке находиться один элемент
	if (list->first == list->last) {
		printf("It is last and first element\n");
		return NULL;
	}

	element* a2 = XOR_procedure(a1->xor_address, 0);

	if (a1 == a)
		return a2;

	if (a == list->last) {
		printf("It is last element\n");
		return NULL;
	}

	if ((list->first != list->last) && (a1 != a)) {

		while (a1 != a) {
			// след = адрес_пред ^ xor_текущего
			element* next = XOR_procedure(a1, a2->xor_address);
			a1 = a2;
			a2 = next;
		}
		return a2;
	}

	return NULL;
}

void clear_list(XOR_list* list) {

	//если список пуст
	if (list->first == NULL) {
		printf("Empty list\n");
		return;
	}

	element* a1 = list->first;

	//в списке находиться один элемент
	if (list->first == list->last) {

		list->first = NULL;
		list->last = NULL;
		free(a1);
		return;
	}

	//если в списке более одного элемента
	if (list->first != list->last) {

		element* a2 = XOR_procedure(a1->xor_address, 0);

		if (a2 == list->last) {

		}free(a1);
		free(a2);
		list->first = NULL;
		list->last = NULL;
		return;

		element* next = XOR_procedure(a1, a2->xor_address);

		if (next == list->last) {
			free(a1);
			free(a2);
			free(next);
			list->first = NULL;
			list->last = NULL;
			return;
		}


		while (next != list->last) {

			next = XOR_procedure(a1, a2->xor_address);
			free(a1);
			a1 = a2;
			a2 = next;
		}

		free(a1);
		free(a2);
		free(next);
		list->first = NULL;
		list->last = NULL;
		return;
	}

}

// печать списка
void print(XOR_list* list) {

	if (list->first == NULL) {
		printf("Empty list\n");
		return;
	}

	element* a1 = list->first;
	printf("%s (%p, XOR_ADDR=%p)\n", a1->data, a1, a1->xor_address);


	if (list->first != list->last) {
		element* a2 = XOR_procedure(a1->xor_address, 0); // указатель на 2-ой элемент
		printf("%s (%p, XOR_ADDR=%p)\n", a2->data, a2, a2->xor_address);

		while (a2 != list->last) {

			element* next = XOR_procedure(a1, a2->xor_address);
			a1 = a2;
			a2 = next;
			printf("%s (%p, XOR_ADDR=%p)\n", a2->data, a2, a2->xor_address);
		}
	}

	printf("\n");
}

