#include "pch.h"
#include "gtest/gtest.h"
#include "lab_A_1.cpp"

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(addTest, add_to_emptyList_returnTRUE) {
	XOR_list list;
	initial(&list);

	ASSERT_TRUE(add_element(&list, "one"));
	ASSERT_EQ(strcmp(list.first->data, "one"), 0);
	ASSERT_EQ((int)list.first->xor_address, 0);
	ASSERT_EQ((int)list.last->xor_address, 0);

	clear_list(&list);
}

TEST(addTest, add_to_with1ElemList_returnTRUE) {
	XOR_list list;
	initial(&list);
	element* a1, * a2;

	add_element(&list, "one");
	a1 = list.first;
	add_element(&list, "two");
	a2 = XOR_procedure(a1->xor_address, 0);

	ASSERT_EQ(strcmp(a2->data, "two"), 0);
	ASSERT_EQ(list.first->xor_address, a1->xor_address);
	ASSERT_EQ(list.last->xor_address, a2->xor_address);

	clear_list(&list);
}

TEST(addTest, add_to_moreElemList_returnTRUE) {
	XOR_list list;
	initial(&list);

	add_element(&list, "one");
	add_element(&list, "two");
	add_element(&list, "three");
	add_element(&list, "for");

	ASSERT_TRUE(add_element(&list, "five"));
	ASSERT_EQ(strcmp(list.last->data, "five"), 0);

	clear_list(&list);
}

TEST(FindElemByKey, find_in_emptyList) {
	XOR_list list;
	initial(&list);

	ASSERT_FALSE(find_element_key(&list, "one"));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	clear_list(&list);
}

XOR_list CreateList_1elem(void) {
	XOR_list list;
	initial(&list);

	// Сохраняем строку
	int len = strlen("one");  // определяем длину строки
	char* p = (char*)malloc(len + 1); // выделяем память под строку
	// Создаем элемент списка
	element* new_elem = (element*)malloc(sizeof(element));

	strcpy(p, "one"); // копирование строки
	p[len] = '\0'; // добавим терминальный ноль

	new_elem->data = p; // значение элемента (адрес строки)

	// Встраиваем элемент в конец списка
	new_elem->xor_address = XOR_procedure(0, 0);
	list.first = new_elem;

	list.last = new_elem;
	return list;
}

TEST(FindElemByKey, find_in_1ElemList) {
	XOR_list list = CreateList_1elem();
	
	ASSERT_TRUE(find_element_key(&list, "one"));
	ASSERT_EQ(find_element_key(&list, "one"), list.first);
	ASSERT_EQ(find_element_key(&list, "one"), list.last);

	clear_list(&list);
}

TEST(FindElemByKey, find_in_1ElemList_noExistElem) {
	XOR_list list = CreateList_1elem();
	
	ASSERT_TRUE(find_element_key(&list, "one"));
	ASSERT_EQ(find_element_key(&list, "one"), list.first);
	ASSERT_EQ(find_element_key(&list, "one"), list.last);

	ASSERT_FALSE(find_element_key(&list, "two"));

	clear_list(&list);
}

XOR_list CreateList_moreElem(void) {
	XOR_list list;
	initial(&list);

	//1 элемент
	// Сохраняем строку в ОП
	int len = strlen("one");  // определяем длину строки
	char* p = (char*)malloc(len + 1); // выделяем память под строку
	// Создаем элемент списка
	element* elem1 = (element*)malloc(sizeof(element));
	strcpy(p, "one"); // копирование строки
	p[len] = '\0'; // добавим терминальный ноль
	elem1->data = p; // значение элемента (адрес строки)
	// Встраиваем элемент в конец списка
	elem1->xor_address = XOR_procedure(0, 0);
	list.first = elem1;
	list.last = elem1;

	//2 элемент
	len = strlen("two");
	p = (char*)malloc(len + 1);
	element* elem2 = (element*)malloc(sizeof(element));
	strcpy(p, "two"); // копирование строки
	p[len] = '\0'; // добавим терминальный ноль
	elem2->data = p; // значение элемента (адрес строки)
	// уже есть больше одного элемента
	elem2->xor_address = XOR_procedure(list.last, 0);
	elem1 = XOR_procedure(list.last->xor_address, 0); // адрес предпоследнего элемента
	// обновление xor-адреса последнего элемента списка
	list.last->xor_address = XOR_procedure(elem1, elem2);
	list.last = elem2;

	//3 элемент
	len = strlen("three");
	p = (char*)malloc(len + 1);
	element* elem3 = (element*)malloc(sizeof(element));
	strcpy(p, "three"); // копирование строки
	p[len] = '\0'; // добавим терминальный ноль
	elem3->data = p; // значение элемента (адрес строки)
	// уже есть больше одного элемента
	elem3->xor_address = XOR_procedure(list.last, 0);
	elem2 = XOR_procedure(list.last->xor_address, 0); // адрес предпоследнего элемента
	// обновление xor-адреса последнего элемента списка
	list.last->xor_address = XOR_procedure(elem2, elem3);
	list.last = elem3;

	//4 элемент
	len = strlen("four");
	p = (char*)malloc(len + 1);
	element* elem4 = (element*)malloc(sizeof(element));
	strcpy(p, "four"); // копирование строки
	p[len] = '\0'; // добавим терминальный ноль
	elem4->data = p; // значение элемента (адрес строки)
	// уже есть больше одного элемента
	elem4->xor_address = XOR_procedure(list.last, 0);
	elem3 = XOR_procedure(list.last->xor_address, 0); // адрес предпоследнего элемента
	// обновление xor-адреса последнего элемента списка
	list.last->xor_address = XOR_procedure(elem3, elem4);
	list.last = elem4;

	return list;

}
TEST(FindElemByKey, find_in_moreElemList) {
	XOR_list list = CreateList_moreElem();

	ASSERT_TRUE(find_element_key(&list, "one"));
	ASSERT_TRUE(find_element_key(&list, "two"));
	ASSERT_TRUE(find_element_key(&list, "three"));
	ASSERT_TRUE(find_element_key(&list, "four"));
	ASSERT_EQ(find_element_key(&list, "one"), list.first);
	ASSERT_EQ(find_element_key(&list, "four"), list.last);


	clear_list(&list);
}

TEST(FindElemByKey, find_in_moreElemList_noExistElem) {
	XOR_list list = CreateList_moreElem();

	ASSERT_TRUE(find_element_key(&list, "one"));
	ASSERT_TRUE(find_element_key(&list, "two"));
	ASSERT_TRUE(find_element_key(&list, "three"));
	ASSERT_TRUE(find_element_key(&list, "four"));
	ASSERT_EQ(find_element_key(&list, "one"), list.first);
	ASSERT_EQ(find_element_key(&list, "four"), list.last);

	ASSERT_FALSE(find_element_key(&list, "six"));
	ASSERT_FALSE(find_element_key(&list, "seven"));

	clear_list(&list);
}

TEST(DeleteElemByKey, delete_in_emptyList) {
	XOR_list list;
	initial(&list);

	ASSERT_FALSE(delete_element_key(&list, "one"));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	clear_list(&list);
}

TEST(DeleteElemByKey, delete_in_1ElemList) {
	XOR_list list;
	initial(&list);

	add_element(&list, "one");
	ASSERT_TRUE(find_element_key(&list, "one"));
	ASSERT_EQ((int)list.first->xor_address, 0);
	ASSERT_EQ((int)list.last->xor_address, 0);

	ASSERT_TRUE(delete_element_key(&list, "one"));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	clear_list(&list);
}

TEST(DeleteElemByKey, delete_in_1ElemList_noExist) {
	XOR_list list;
	initial(&list);

	add_element(&list, "one");
	ASSERT_EQ((int)list.first->xor_address, 0);
	ASSERT_EQ((int)list.last->xor_address, 0);

	ASSERT_FALSE(delete_element_key(&list, "three"));

	clear_list(&list);
}

TEST(DeleteElemByKey, delete_in_moreElemList) {
	XOR_list list;
	initial(&list);

	add_element(&list, "one");
	add_element(&list, "two");
	add_element(&list, "three");
	add_element(&list, "for");

	ASSERT_TRUE(find_element_key(&list, "one"));
	ASSERT_TRUE(delete_element_key(&list, "one"));
	ASSERT_FALSE(find_element_key(&list, "one"));

	ASSERT_TRUE(find_element_key(&list, "three"));
	ASSERT_TRUE(delete_element_key(&list, "three"));
	ASSERT_EQ((int)find_element_key(&list, "three"), NULL);

	ASSERT_TRUE(find_element_key(&list, "two"));
	ASSERT_TRUE(delete_element_key(&list, "two"));
	ASSERT_EQ((int)find_element_key(&list, "two"), NULL);

	clear_list(&list);
}

TEST(DeleteElemByKey, delete_in_moreElemList_noExist) {
	XOR_list list;
	initial(&list);

	add_element(&list, "one");
	add_element(&list, "two");
	add_element(&list, "three");
	add_element(&list, "for");

	ASSERT_TRUE(find_element_key(&list, "three"));
	ASSERT_TRUE(delete_element_key(&list, "three"));
	ASSERT_EQ((int)find_element_key(&list, "three"), NULL);

	ASSERT_FALSE(find_element_key(&list, "hello"));
	ASSERT_FALSE(delete_element_key(&list, "hello"));
	ASSERT_EQ((int)find_element_key(&list, "hello"), NULL);

	clear_list(&list);
}

TEST(DeleteElemByAddress, delete_in_emptyList) {
	XOR_list list;
	initial(&list);

	ASSERT_FALSE(delete_element_key(&list, 0));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	clear_list(&list);
}

TEST(DeleteElemByAddress, delete_in_1ElemList) {
	XOR_list list;
	initial(&list);

	add_element(&list, "one");
	element* a = find_element_key(&list, "one");
	ASSERT_TRUE(delete_element_key(&list, a->data));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	ASSERT_FALSE(find_element_key(&list, "one"));

	clear_list(&list);
}

TEST(DeleteElemByAddress, delete_in_1ElemList_noExist) {
	XOR_list list;
	initial(&list);

	add_element(&list, "one");
	ASSERT_TRUE(find_element_key(&list, "one"));
	element* p = find_element_key(&list, "two");
	ASSERT_EQ((int)list.first->xor_address, 0);
	ASSERT_EQ((int)list.last->xor_address, 0);

	ASSERT_FALSE(delete_element_key(&list, p->data));

	clear_list(&list);
}

TEST(DeleteElemByAddress, delete_in_moreElemList) {
	XOR_list list;
	initial(&list);

	add_element(&list, "one");
	add_element(&list, "two");
	add_element(&list, "three");
	add_element(&list, "for");

	ASSERT_TRUE(find_element_key(&list, "one"));
	element* p1 = find_element_key(&list, "one");
	ASSERT_TRUE(delete_element_key(&list, p1->data));
	ASSERT_FALSE(find_element_key(&list, "one"));

	ASSERT_TRUE(find_element_key(&list, "three"));
	p1 = find_element_key(&list, "three");
	ASSERT_TRUE(delete_element_key(&list, p1->data));
	ASSERT_FALSE(find_element_key(&list, "three"));

	ASSERT_TRUE(find_element_key(&list, "two"));
	p1 = find_element_key(&list, "two");
	ASSERT_TRUE(delete_element_key(&list, p1->data));
	ASSERT_FALSE(find_element_key(&list, "two"));

	clear_list(&list);
}

TEST(DeleteElemByAddress, delete_in_moreElemList_noExist) {
	XOR_list list;
	initial(&list);

	add_element(&list, "one");
	add_element(&list, "two");
	add_element(&list, "three");
	add_element(&list, "for");

	ASSERT_TRUE(find_element_key(&list, "three"));
	ASSERT_TRUE(delete_element_key(&list, "three"));
	ASSERT_FALSE(find_element_key(&list, "three"));

	ASSERT_FALSE(find_element_key(&list, "hello"));
	element* p1 = find_element_key(&list, "hello");
	ASSERT_FALSE(delete_element_key(&list, p1->data));

	clear_list(&list);
}

TEST(Next, Next_in_emptyList) {
	XOR_list list;
	initial(&list);

	ASSERT_FALSE(next(&list, (element*)1));

	clear_list(&list);
}

TEST(Next, Next_in_1ElemList) {
	XOR_list list;
	initial(&list);

	add_element(&list, "one");
	ASSERT_FALSE(next(&list, find_element_key(&list, "one")));

	clear_list(&list);
}

TEST(Next, Next_lastElem_in_moreElemeList) {
	XOR_list list;
	initial(&list);

	add_element(&list, "one");
	add_element(&list, "two");
	add_element(&list, "three");
	ASSERT_FALSE(next(&list, find_element_key(&list, "three")));

	clear_list(&list);
}

TEST(Next, Next_in_moreElemeList) {
	XOR_list list;
	initial(&list);

	add_element(&list, "one");
	add_element(&list, "two");
	add_element(&list, "three");

	ASSERT_TRUE(next(&list, find_element_key(&list, "one")));
	ASSERT_TRUE(next(&list, find_element_key(&list, "two")));

	clear_list(&list);
}