#include "pch.h"
#include "gtest/gtest.h"
#include "lab_A_1.c"

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

	free(list.first->data);
	free(list.last->data);
	free(list.first);
	free(list.last);
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

	free(a1);
	free(a2);
	free(list.first);
	free(list.last);
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

	free(&list);
}

TEST(FindElemByKey, find_in_emptyList) {
	XOR_list list;
	initial(&list);

	ASSERT_FALSE(find_element_key(&list, "one"));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	free(list.first);
	free(list.last);
}

TEST(FindElemByKey, find_in_1ElemList) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");  
	char* p = (char*)malloc(len + 1); 
	if (p == NULL) {
		printf("error");
		exit(1);
	}
	
	element* new_elem = (element*)malloc(sizeof(element));
	if (new_elem == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one"); 
	p[len] = '\0'; 

	new_elem->data = p; 

	new_elem->xor_address = XOR_procedure(0, 0);
	list.first = new_elem;
	list.last = new_elem;
	
	ASSERT_TRUE(find_element_key(&list, "one"));
	ASSERT_EQ(find_element_key(&list, "one"), list.first);
	ASSERT_EQ(find_element_key(&list, "one"), list.last);

	free(p);
	free(new_elem);
	free(list.first->data);
	free(list.first->xor_address);
	free(list.last->data);
	free(list.last->xor_address);
	free(list.first);
	free(list.last);
}

TEST(FindElemByKey, find_in_1ElemList_noExistElem) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");
	char* p = (char*)malloc(len + 1);
	if (p == NULL) {
		printf("error");
		exit(1);
	}

	element* new_elem = (element*)malloc(sizeof(element));
	if (new_elem == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one");
	p[len] = '\0';

	new_elem->data = p;

	new_elem->xor_address = XOR_procedure(0, 0);
	list.first = new_elem;
	list.last = new_elem;
	
	ASSERT_TRUE(find_element_key(&list, "one"));
	ASSERT_EQ(find_element_key(&list, "one"), list.first);
	ASSERT_EQ(find_element_key(&list, "one"), list.last);

	ASSERT_FALSE(find_element_key(&list, "two"));

	free(p);
	free(new_elem);
	free(list.first->data);
	free(list.first->xor_address);
	free(list.last->data);
	free(list.last->xor_address);
	free(list.first);
	free(list.last);
}


TEST(FindElemByKey, find_in_moreElemList) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");  
	char* p = (char*)malloc(len + 1); 
	if (p == NULL) {
		printf("error");
		exit(1);
	}
	element* elem1 = (element*)malloc(sizeof(element));
	if (elem1 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one"); 
	p[len] = '\0'; 
	elem1->data = p; 
	elem1->xor_address = XOR_procedure(0, 0);
	list.first = elem1;
	list.last = elem1;

	len = strlen("two");
	char* a = (char*)malloc(len + 1);
	if (a == NULL) {
		printf("error");
		exit(1);
	}
	element* elem2 = (element*)malloc(sizeof(element));
	if (elem2 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(a, "two"); 
	a[len] = '\0'; 
	elem2->data = a; 
	elem2->xor_address = XOR_procedure(list.last, 0);
	elem1 = XOR_procedure(list.last->xor_address, 0); 
	list.last->xor_address = XOR_procedure(elem1, elem2);
	list.last = elem2;

	len = strlen("three");
	char* b = (char*)malloc(len + 1);
	if (b == NULL) {
		printf("error");
		exit(1);
	}
	element* elem3 = (element*)malloc(sizeof(element));
	if (elem3 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(b, "three"); 
	b[len] = '\0'; 
	elem3->data = b; 
	elem3->xor_address = XOR_procedure(list.last, 0);
	elem2 = XOR_procedure(list.last->xor_address, 0); 
	list.last->xor_address = XOR_procedure(elem2, elem3);
	list.last = elem3;

	len = strlen("four");
	char* c = (char*)malloc(len + 1);
	if (c == NULL) {
		printf("error");
		exit(1);
	}
	element* elem4 = (element*)malloc(sizeof(element));
	if (elem4 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(c, "four"); 
	c[len] = '\0'; 
	elem4->data = c; 
	elem4->xor_address = XOR_procedure(list.last, 0);
	elem3 = XOR_procedure(list.last->xor_address, 0); 
	list.last->xor_address = XOR_procedure(elem3, elem4);
	list.last = elem4;

	ASSERT_TRUE(find_element_key(&list, "one"));
	ASSERT_TRUE(find_element_key(&list, "two"));
	ASSERT_TRUE(find_element_key(&list, "three"));
	ASSERT_TRUE(find_element_key(&list, "four"));
	ASSERT_EQ(find_element_key(&list, "one"), list.first);
	ASSERT_EQ(find_element_key(&list, "four"), list.last);

	free(p);
	free(a);
	free(b);
	free(c);
	free(&len);
	free(elem1->data);
	free(elem1->xor_address);
	free(elem2->data);
	free(elem2->xor_address);
	free(elem3->data);
	free(elem3->xor_address);
	free(elem4->data);
	free(elem4->xor_address);
	free(elem1);
	free(elem2);
	free(elem3);
	free(elem4);
	free(list.last->data);
	free(list.last->data);
	free(list.first->xor_address);
	free(list.last->xor_address);
	free(list.last);
	free(list.first);

}

TEST(FindElemByKey, find_in_moreElemList_noExistElem) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");
	char* p = (char*)malloc(len + 1);
	if (p == NULL) {
		printf("error");
		exit(1);
	}
	element* elem1 = (element*)malloc(sizeof(element));
	if (elem1 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one");
	p[len] = '\0';
	elem1->data = p;
	elem1->xor_address = XOR_procedure(0, 0);
	list.first = elem1;
	list.last = elem1;

	len = strlen("two");
	char* a = (char*)malloc(len + 1);
	if (a == NULL) {
		printf("error");
		exit(1);
	}
	element* elem2 = (element*)malloc(sizeof(element));
	if (elem2 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(a, "two");
	a[len] = '\0';
	elem2->data = a;
	elem2->xor_address = XOR_procedure(list.last, 0);
	elem1 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem1, elem2);
	list.last = elem2;

	len = strlen("three");
	char* b = (char*)malloc(len + 1);
	if (b == NULL) {
		printf("error");
		exit(1);
	}
	element* elem3 = (element*)malloc(sizeof(element));
	if (elem3 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(b, "three");
	b[len] = '\0';
	elem3->data = b;
	elem3->xor_address = XOR_procedure(list.last, 0);
	elem2 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem2, elem3);
	list.last = elem3;

	len = strlen("four");
	char* c = (char*)malloc(len + 1);
	if (c == NULL) {
		printf("error");
		exit(1);
	}
	element* elem4 = (element*)malloc(sizeof(element));
	if (elem4 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(c, "four");
	c[len] = '\0';
	elem4->data = c;
	elem4->xor_address = XOR_procedure(list.last, 0);
	elem3 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem3, elem4);
	list.last = elem4;

	ASSERT_TRUE(find_element_key(&list, "one"));
	ASSERT_TRUE(find_element_key(&list, "two"));
	ASSERT_TRUE(find_element_key(&list, "three"));
	ASSERT_TRUE(find_element_key(&list, "four"));
	ASSERT_EQ(find_element_key(&list, "one"), list.first);
	ASSERT_EQ(find_element_key(&list, "four"), list.last);

	ASSERT_FALSE(find_element_key(&list, "six"));
	ASSERT_FALSE(find_element_key(&list, "seven"));

	free(p);
	free(a);
	free(b);
	free(c);
	free(&len);
	free(elem1->data);
	free(elem1->xor_address);
	free(elem2->data);
	free(elem2->xor_address);
	free(elem3->data);
	free(elem3->xor_address);
	free(elem4->data);
	free(elem4->xor_address);
	free(elem1);
	free(elem2);
	free(elem3);
	free(elem4);
	free(list.last->data);
	free(list.last->data);
	free(list.first->xor_address);
	free(list.last->xor_address);
	free(list.last);
	free(list.first);
}

TEST(DeleteElemByKey, delete_in_emptyList) {
	XOR_list list;
	initial(&list);

	ASSERT_FALSE(delete_element_key(&list, "one"));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	free(list.first->data);
	free(list.first->xor_address);
	free(list.last->data);
	free(list.last->xor_address);
	free(list.last);
	free(list.first);
}

TEST(DeleteElemByKey, delete_in_1ElemList) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");
	char* p = (char*)malloc(len + 1);
	if (p == NULL) {
		printf("error");
		exit(1);
	}

	element* new_elem = (element*)malloc(sizeof(element));
	if (new_elem == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one");
	p[len] = '\0';

	new_elem->data = p;

	new_elem->xor_address = XOR_procedure(0, 0);
	list.first = new_elem;
	list.last = new_elem;

	ASSERT_TRUE(find_element_key(&list, "one"));
	ASSERT_EQ((int)list.first->xor_address, 0);
	ASSERT_EQ((int)list.last->xor_address, 0);

	ASSERT_TRUE(delete_element_key(&list, "one"));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	free(p);
	free(new_elem);
	free(list.first->data);
	free(list.first->xor_address);
	free(list.last->data);
	free(list.last->xor_address);
	free(list.first);
	free(list.last);
}

TEST(DeleteElemByKey, delete_in_1ElemList_noExist) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");
	char* p = (char*)malloc(len + 1);
	if (p == NULL) {
		printf("error");
		exit(1);
	}

	element* new_elem = (element*)malloc(sizeof(element));
	if (new_elem == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one");
	p[len] = '\0';

	new_elem->data = p;

	new_elem->xor_address = XOR_procedure(0, 0);
	list.first = new_elem;
	list.last = new_elem;

	ASSERT_EQ((int)list.first->xor_address, 0);
	ASSERT_EQ((int)list.last->xor_address, 0);

	ASSERT_FALSE(delete_element_key(&list, "three"));

	free(p);
	free(new_elem);
	free(list.first->data);
	free(list.first->xor_address);
	free(list.last->data);
	free(list.last->xor_address);
	free(list.first);
	free(list.last);
}

TEST(DeleteElemByKey, delete_in_moreElemList) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");
	char* p = (char*)malloc(len + 1);
	if (p == NULL) {
		printf("error");
		exit(1);
	}
	element* elem1 = (element*)malloc(sizeof(element));
	if (elem1 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one");
	p[len] = '\0';
	elem1->data = p;
	elem1->xor_address = XOR_procedure(0, 0);
	list.first = elem1;
	list.last = elem1;

	len = strlen("two");
	char* a = (char*)malloc(len + 1);
	if (a == NULL) {
		printf("error");
		exit(1);
	}
	element* elem2 = (element*)malloc(sizeof(element));
	if (elem2 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(a, "two");
	a[len] = '\0';
	elem2->data = a;
	elem2->xor_address = XOR_procedure(list.last, 0);
	elem1 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem1, elem2);
	list.last = elem2;

	len = strlen("three");
	char* b = (char*)malloc(len + 1);
	if (b == NULL) {
		printf("error");
		exit(1);
	}
	element* elem3 = (element*)malloc(sizeof(element));
	if (elem3 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(b, "three");
	b[len] = '\0';
	elem3->data = b;
	elem3->xor_address = XOR_procedure(list.last, 0);
	elem2 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem2, elem3);
	list.last = elem3;

	len = strlen("four");
	char* c = (char*)malloc(len + 1);
	if (c == NULL) {
		printf("error");
		exit(1);
	}
	element* elem4 = (element*)malloc(sizeof(element));
	if (elem4 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(c, "four");
	c[len] = '\0';
	elem4->data = c;
	elem4->xor_address = XOR_procedure(list.last, 0);
	elem3 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem3, elem4);
	list.last = elem4;

	ASSERT_TRUE(find_element_key(&list, "one"));
	ASSERT_TRUE(delete_element_key(&list, "one"));
	ASSERT_FALSE(find_element_key(&list, "one"));

	ASSERT_TRUE(find_element_key(&list, "three"));
	ASSERT_TRUE(delete_element_key(&list, "three"));
	ASSERT_EQ((int)find_element_key(&list, "three"), NULL);

	ASSERT_TRUE(find_element_key(&list, "two"));
	ASSERT_TRUE(delete_element_key(&list, "two"));
	ASSERT_EQ((int)find_element_key(&list, "two"), NULL);

	free(p);
	free(a);
	free(b);
	free(c);
	free(&len);
	free(elem1->data);
	free(elem1->xor_address);
	free(elem2->data);
	free(elem2->xor_address);
	free(elem3->data);
	free(elem3->xor_address);
	free(elem4->data);
	free(elem4->xor_address);
	free(elem1);
	free(elem2);
	free(elem3);
	free(elem4);
	free(list.last->data);
	free(list.last->data);
	free(list.first->xor_address);
	free(list.last->xor_address);
	free(list.last);
	free(list.first);
}

TEST(DeleteElemByKey, delete_in_moreElemList_noExist) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");
	char* p = (char*)malloc(len + 1);
	if (p == NULL) {
		printf("error");
		exit(1);
	}
	element* elem1 = (element*)malloc(sizeof(element));
	if (elem1 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one");
	p[len] = '\0';
	elem1->data = p;
	elem1->xor_address = XOR_procedure(0, 0);
	list.first = elem1;
	list.last = elem1;

	len = strlen("two");
	char* a = (char*)malloc(len + 1);
	if (a == NULL) {
		printf("error");
		exit(1);
	}
	element* elem2 = (element*)malloc(sizeof(element));
	if (elem2 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(a, "two");
	a[len] = '\0';
	elem2->data = a;
	elem2->xor_address = XOR_procedure(list.last, 0);
	elem1 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem1, elem2);
	list.last = elem2;

	len = strlen("three");
	char* b = (char*)malloc(len + 1);
	if (b == NULL) {
		printf("error");
		exit(1);
	}
	element* elem3 = (element*)malloc(sizeof(element));
	if (elem3 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(b, "three");
	b[len] = '\0';
	elem3->data = b;
	elem3->xor_address = XOR_procedure(list.last, 0);
	elem2 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem2, elem3);
	list.last = elem3;

	len = strlen("four");
	char* c = (char*)malloc(len + 1);
	if (c == NULL) {
		printf("error");
		exit(1);
	}
	element* elem4 = (element*)malloc(sizeof(element));
	if (elem4 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(c, "four");
	c[len] = '\0';
	elem4->data = c;
	elem4->xor_address = XOR_procedure(list.last, 0);
	elem3 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem3, elem4);
	list.last = elem4;

	ASSERT_TRUE(find_element_key(&list, "three"));
	ASSERT_TRUE(delete_element_key(&list, "three"));
	ASSERT_EQ((int)find_element_key(&list, "three"), NULL);

	ASSERT_FALSE(find_element_key(&list, "hello"));
	ASSERT_FALSE(delete_element_key(&list, "hello"));
	ASSERT_EQ((int)find_element_key(&list, "hello"), NULL);

	free(p);
	free(a);
	free(b);
	free(c);
	free(&len);
	free(elem1->data);
	free(elem1->xor_address);
	free(elem2->data);
	free(elem2->xor_address);
	free(elem3->data);
	free(elem3->xor_address);
	free(elem4->data);
	free(elem4->xor_address);
	free(elem1);
	free(elem2);
	free(elem3);
	free(elem4);
	free(list.last->data);
	free(list.last->data);
	free(list.first->xor_address);
	free(list.last->xor_address);
	free(list.last);
	free(list.first);
}

TEST(DeleteElemByAddress, delete_in_emptyList) {
	XOR_list list;
	initial(&list);

	ASSERT_FALSE(delete_element_key(&list, 0));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	free(list.first->data);
	free(list.last->data);
	free(list.first->xor_address);
	free(list.last->xor_address);
	free(list.first);
	free(list.last);
}

TEST(DeleteElemByAddress, delete_in_1ElemList) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");
	char* p = (char*)malloc(len + 1);
	if (p == NULL) {
		printf("error");
		exit(1);
	}

	element* new_elem = (element*)malloc(sizeof(element));
	if (new_elem == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one");
	p[len] = '\0';

	new_elem->data = p;

	new_elem->xor_address = XOR_procedure(0, 0);
	list.first = new_elem;
	list.last = new_elem;

	element* a = find_element_key(&list, "one");
	ASSERT_TRUE(delete_element_key(&list, a->data));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	ASSERT_FALSE(find_element_key(&list, "one"));

	free(p);
	free(new_elem);
	free(list.first->data);
	free(list.last->data);
	free(list.first->xor_address);
	free(list.last->xor_address);
	free(list.first);
	free(list.last);
	free(a->data);
	free(a->xor_address);
	free(a);
}

TEST(DeleteElemByAddress, delete_in_1ElemList_noExist) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");
	char* p = (char*)malloc(len + 1);
	if (p == NULL) {
		printf("error");
		exit(1);
	}

	element* new_elem = (element*)malloc(sizeof(element));
	if (new_elem == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one");
	p[len] = '\0';

	new_elem->data = p;

	new_elem->xor_address = XOR_procedure(0, 0);
	list.first = new_elem;
	list.last = new_elem;

	ASSERT_TRUE(find_element_key(&list, "one"));
	element* a = find_element_key(&list, "two");
	ASSERT_EQ((int)list.first->xor_address, 0);
	ASSERT_EQ((int)list.last->xor_address, 0);

	ASSERT_FALSE(delete_element_key(&list, a->data));

	free(list.first->data);
	free(list.last->data);
	free(list.first->xor_address);
	free(list.last->xor_address);
	free(list.first);
	free(list.last);
	free(a->data);
	free(a->xor_address);
	free(a);
}

TEST(DeleteElemByAddress, delete_in_moreElemList) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");
	char* p = (char*)malloc(len + 1);
	if (p == NULL) {
		printf("error");
		exit(1);
	}
	element* elem1 = (element*)malloc(sizeof(element));
	if (elem1 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one");
	p[len] = '\0';
	elem1->data = p;
	elem1->xor_address = XOR_procedure(0, 0);
	list.first = elem1;
	list.last = elem1;

	len = strlen("two");
	char* a = (char*)malloc(len + 1);
	if (a == NULL) {
		printf("error");
		exit(1);
	}
	element* elem2 = (element*)malloc(sizeof(element));
	if (elem2 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(a, "two");
	a[len] = '\0';
	elem2->data = a;
	elem2->xor_address = XOR_procedure(list.last, 0);
	elem1 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem1, elem2);
	list.last = elem2;

	len = strlen("three");
	char* b = (char*)malloc(len + 1);
	if (b == NULL) {
		printf("error");
		exit(1);
	}
	element* elem3 = (element*)malloc(sizeof(element));
	if (elem3 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(b, "three");
	b[len] = '\0';
	elem3->data = b;
	elem3->xor_address = XOR_procedure(list.last, 0);
	elem2 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem2, elem3);
	list.last = elem3;

	len = strlen("four");
	char* c = (char*)malloc(len + 1);
	if (c == NULL) {
		printf("error");
		exit(1);
	}
	element* elem4 = (element*)malloc(sizeof(element));
	if (elem4 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(c, "four");
	c[len] = '\0';
	elem4->data = c;
	elem4->xor_address = XOR_procedure(list.last, 0);
	elem3 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem3, elem4);
	list.last = elem4;

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

	free(p1->data);
	free(p1->xor_address);
	free(p1);
	free(p);
	free(a);
	free(b);
	free(c);
	free(&len);
	free(elem1->data);
	free(elem1->xor_address);
	free(elem2->data);
	free(elem2->xor_address);
	free(elem3->data);
	free(elem3->xor_address);
	free(elem4->data);
	free(elem4->xor_address);
	free(elem1);
	free(elem2);
	free(elem3);
	free(elem4);
	free(list.last->data);
	free(list.last->data);
	free(list.first->xor_address);
	free(list.last->xor_address);
	free(list.last);
	free(list.first);
}

TEST(DeleteElemByAddress, delete_in_moreElemList_noExist) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");
	char* p = (char*)malloc(len + 1);
	if (p == NULL) {
		printf("error");
		exit(1);
	}
	element* elem1 = (element*)malloc(sizeof(element));
	if (elem1 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one");
	p[len] = '\0';
	elem1->data = p;
	elem1->xor_address = XOR_procedure(0, 0);
	list.first = elem1;
	list.last = elem1;

	len = strlen("two");
	char* a = (char*)malloc(len + 1);
	if (a == NULL) {
		printf("error");
		exit(1);
	}
	element* elem2 = (element*)malloc(sizeof(element));
	if (elem2 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(a, "two");
	a[len] = '\0';
	elem2->data = a;
	elem2->xor_address = XOR_procedure(list.last, 0);
	elem1 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem1, elem2);
	list.last = elem2;

	len = strlen("three");
	char* b = (char*)malloc(len + 1);
	if (b == NULL) {
		printf("error");
		exit(1);
	}
	element* elem3 = (element*)malloc(sizeof(element));
	if (elem3 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(b, "three");
	b[len] = '\0';
	elem3->data = b;
	elem3->xor_address = XOR_procedure(list.last, 0);
	elem2 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem2, elem3);
	list.last = elem3;

	len = strlen("four");
	char* c = (char*)malloc(len + 1);
	if (c == NULL) {
		printf("error");
		exit(1);
	}
	element* elem4 = (element*)malloc(sizeof(element));
	if (elem4 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(c, "four");
	c[len] = '\0';
	elem4->data = c;
	elem4->xor_address = XOR_procedure(list.last, 0);
	elem3 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem3, elem4);
	list.last = elem4;

	ASSERT_TRUE(find_element_key(&list, "three"));
	ASSERT_TRUE(delete_element_key(&list, "three"));
	ASSERT_FALSE(find_element_key(&list, "three"));

	ASSERT_FALSE(find_element_key(&list, "hello"));
	element* p1 = find_element_key(&list, "hello");
	ASSERT_FALSE(delete_element_key(&list, p1->data));

	free(p1->data);
	free(p1->xor_address);
	free(p1);
	free(p);
	free(a);
	free(b);
	free(c);
	free(&len);
	free(elem1->data);
	free(elem1->xor_address);
	free(elem2->data);
	free(elem2->xor_address);
	free(elem3->data);
	free(elem3->xor_address);
	free(elem4->data);
	free(elem4->xor_address);
	free(elem1);
	free(elem2);
	free(elem3);
	free(elem4);
	free(list.last->data);
	free(list.last->data);
	free(list.first->xor_address);
	free(list.last->xor_address);
	free(list.last);
	free(list.first);
}

TEST(Next, Next_in_emptyList) {
	XOR_list list;
	initial(&list);

	ASSERT_FALSE(next(&list, (element*)1));

	free(list.first->data);
	free(list.first->xor_address);
	free(list.last->data);
	free(list.last->xor_address);
	free(list.first);
	free(list.last);
}

TEST(Next, Next_in_1ElemList) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");
	char* p = (char*)malloc(len + 1);
	if (p == NULL) {
		printf("error");
		exit(1);
	}

	element* new_elem = (element*)malloc(sizeof(element));
	if (new_elem == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one");
	p[len] = '\0';

	new_elem->data = p;

	new_elem->xor_address = XOR_procedure(0, 0);
	list.first = new_elem;
	list.last = new_elem;

	ASSERT_FALSE(next(&list, find_element_key(&list, "one")));

	free(p);
	free(new_elem);
	free(&len);
	free(list.first->data);
	free(list.last->data);
	free(list.first->xor_address);
	free(list.last->xor_address);
	free(list.first);
	free(list.last);
}

TEST(Next, Next_lastElem_in_moreElemeList) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");
	char* p = (char*)malloc(len + 1);
	if (p == NULL) {
		printf("error");
		exit(1);
	}
	element* elem1 = (element*)malloc(sizeof(element));
	if (elem1 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one");
	p[len] = '\0';
	elem1->data = p;
	elem1->xor_address = XOR_procedure(0, 0);
	list.first = elem1;
	list.last = elem1;

	len = strlen("two");
	char* a = (char*)malloc(len + 1);
	if (a == NULL) {
		printf("error");
		exit(1);
	}
	element* elem2 = (element*)malloc(sizeof(element));
	if (elem2 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(a, "two");
	a[len] = '\0';
	elem2->data = a;
	elem2->xor_address = XOR_procedure(list.last, 0);
	elem1 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem1, elem2);
	list.last = elem2;

	len = strlen("three");
	char* b = (char*)malloc(len + 1);
	if (b == NULL) {
		printf("error");
		exit(1);
	}
	element* elem3 = (element*)malloc(sizeof(element));
	if (elem3 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(b, "three");
	b[len] = '\0';
	elem3->data = b;
	elem3->xor_address = XOR_procedure(list.last, 0);
	elem2 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem2, elem3);
	list.last = elem3;

	ASSERT_FALSE(next(&list, find_element_key(&list, "three")));

	free(p);
	free(a);
	free(b);
	free(&len);
	free(elem1->data);
	free(elem1->xor_address);
	free(elem2->data);
	free(elem2->xor_address);
	free(elem3->data);
	free(elem3->xor_address);
	free(elem1);
	free(elem2);
	free(elem3);
	free(list.last->data);
	free(list.last->data);
	free(list.first->xor_address);
	free(list.last->xor_address);
	free(list.last);
	free(list.first);
}

TEST(Next, Next_in_moreElemeList) {
	XOR_list list;
	initial(&list);

	int len = strlen("one");
	char* p = (char*)malloc(len + 1);
	if (p == NULL) {
		printf("error");
		exit(1);
	}
	element* elem1 = (element*)malloc(sizeof(element));
	if (elem1 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(p, "one");
	p[len] = '\0';
	elem1->data = p;
	elem1->xor_address = XOR_procedure(0, 0);
	list.first = elem1;
	list.last = elem1;

	len = strlen("two");
	char* a = (char*)malloc(len + 1);
	if (a == NULL) {
		printf("error");
		exit(1);
	}
	element* elem2 = (element*)malloc(sizeof(element));
	if (elem2 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(a, "two");
	a[len] = '\0';
	elem2->data = a;
	elem2->xor_address = XOR_procedure(list.last, 0);
	elem1 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem1, elem2);
	list.last = elem2;

	len = strlen("three");
	char* b = (char*)malloc(len + 1);
	if (b == NULL) {
		printf("error");
		exit(1);
	}
	element* elem3 = (element*)malloc(sizeof(element));
	if (elem3 == NULL) {
		printf("error");
		exit(1);
	}
	strcpy(b, "three");
	b[len] = '\0';
	elem3->data = b;
	elem3->xor_address = XOR_procedure(list.last, 0);
	elem2 = XOR_procedure(list.last->xor_address, 0);
	list.last->xor_address = XOR_procedure(elem2, elem3);
	list.last = elem3;

	ASSERT_TRUE(next(&list, find_element_key(&list, "one")));
	ASSERT_TRUE(next(&list, find_element_key(&list, "two")));

	free(p);
	free(a);
	free(b);
	free(&len);
	free(elem1->data);
	free(elem1->xor_address);
	free(elem2->data);
	free(elem2->xor_address);
	free(elem3->data);
	free(elem3->xor_address);
	free(elem1);
	free(elem2);
	free(elem3);
	free(list.last->data);
	free(list.last->data);
	free(list.first->xor_address);
	free(list.last->xor_address);
	free(list.last);
	free(list.first);
}