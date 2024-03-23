#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
typedef int ItemType;
struct Node
{
	ItemType Info;
	Node* Next;
};
struct List
{
	Node* Head;
	Node* Tail;
};
// khoi tao 1 ds moi
Node* createNode(ItemType x)
{
	Node* p = new Node;
	if (p == NULL)
	{
		printf("bo nho khong cap phat!");
		_getch();
		return NULL;
	}
	p->Info = x;
	p->Next = NULL;
	return p;
}
//khoi tao 1 ds rong
void initList(List& sl)
{
	sl.Head = NULL;
	sl.Tail = NULL;
}
//ham chen phan tu vao ds sao cho van giu nguyen thu tu tang dan
void insertSorted(Node** HeadRef, ItemType x)
{
	Node* newNode = createNode(x);
	Node* current = *HeadRef;
	Node* previous = NULL;
	while (current != NULL && current->Info < x)
	{
		previous = current;
		current = current->Next;
	}
	if (previous == NULL)
	{
		newNode->Next = *HeadRef;
		*HeadRef = newNode;
	}
	else
	{
		previous->Next = newNode;
		newNode = current;
	}
}
//ham in ds
void printList(Node* Head)
{
	while (Head != NULL)
	{
		printf("%d", Head->Info);
		Head = Head->Next;
	}
	printf("\n");
}
//a.tron 2 ds thanh 1 ds moi co thu tu tang dan
Node* mergeSortedListsAscending(Node* sl1, Node* sl2) {
	Node* mergedList = NULL;

	// Trong khi cả hai danh sách không rỗng
	while (sl1 != NULL && sl2 != NULL) {
		if (sl1->Info <= sl2->Info) {
			insertSorted(&mergedList, sl1->Info);
			sl1 = sl1->Next;
		}
		else {
			insertSorted(&mergedList, sl2->Info);
			sl2 = sl2->Next;
		}
	}

	// Nếu một trong hai danh sách còn phần tử
	while (sl1 != NULL) {
		insertSorted(&mergedList, sl1->Info);
		sl1 = sl1->Next;
	}

	while (sl2 != NULL) {
		insertSorted(&mergedList, sl2->Info);
		sl2 = sl2->Next;
	}

	return mergedList;
}

// b. Trộn 2 danh sách thành một danh sách mới có thứ tự giảm dần
Node* mergeSortedListsDescending(Node* sl1, Node* sl2) {
	Node* mergedList = NULL;

	// Trong khi cả hai danh sách không rỗng
	while (sl1 != NULL && sl2 != NULL) {
		if (sl1->Info >= sl2->Info) {
			insertSorted(&mergedList, sl1->Info);
			sl1 = sl1->Next;
		}
		else {
			insertSorted(&mergedList, sl2->Info);
			sl2 = sl2->Next;
		}
	}
	// Nếu một trong hai danh sách còn phần tử
	while (sl1 != NULL) {
		insertSorted(&mergedList, sl1->Info);
		sl1 = sl1->Next;
	}

	while (sl2 != NULL) {
		insertSorted(&mergedList, sl2->Info);
		sl2 = sl2->Next;
	}

	return mergedList;
}

// c. Trộn 2 danh sách thành một danh sách mới sao cho các phần tử có giá trị chẵn tăng dần, các phần tử có giá trị lẻ giảm dần
Node* mergeSortedListsEvenOdd(Node* sl1, Node* sl2) {
	Node* evenList = NULL;
	Node* oddList = NULL;

	// Tách các phần tử chẵn và lẻ từ hai danh sách
	while (sl1 != NULL) {
		if (sl1->Info % 2 == 0)
			insertSorted(&evenList, sl1->Info);
		else
			insertSorted(&oddList, sl1->Info);
		sl1 = sl1->Next;
	}

	while (sl2 != NULL) {
		if (sl2->Info % 2 == 0)
			insertSorted(&evenList, sl2->Info);
		else
			insertSorted(&oddList, sl2->Info);
		sl2 = sl2->Next;
	}

	// Sắp xếp các danh sách chẵn và lẻ
	Node* mergedList = mergeSortedListsAscending(evenList, oddList);
	return mergedList;
}

// d. Trộn 2 danh sách thành một danh sách mới sao cho các phần tử tại những vị trí chẵn tăng dần, các phần tử tại vị trí lẻ giảm dần
Node* mergeSortedListsPosition(Node* sl1, Node* sl2) {
	Node* evenPositionList1 = NULL;
	Node* oddPositionList1 = NULL;
	Node* evenPositionList2 = NULL;
	Node* oddPositionList2 = NULL;

	// Tách các phần tử tại vị trí chẵn và lẻ từ hai danh sách
	int index = 0;
	while (sl1 != NULL) {
		if (index % 2 == 0)
			insertSorted(&evenPositionList1, sl1->Info);
		else
			insertSorted(&oddPositionList1, sl1->Info);
		sl1 = sl1->Next;
		index++;
	}

	index = 0;
	while (sl2 != NULL) {
		if (index % 2 == 0)
			insertSorted(&evenPositionList2, sl2->Info);
		else
			insertSorted(&oddPositionList2, sl2->Info);
		sl2 = sl2->Next;
		index++;
	}

	// Sắp xếp các danh sách tại các vị trí chẵn và lẻ
	Node* mergedEvenPositionList = mergeSortedListsAscending(evenPositionList1, evenPositionList2);
	Node* mergedOddPositionList = mergeSortedListsDescending(oddPositionList1, oddPositionList2);

	// Ghép các danh sách kết quả
	Node* current = mergedEvenPositionList;
	if (current == NULL) {
		mergedEvenPositionList = mergedOddPositionList;
	}
	else {
		while (current->Next != NULL) {
			current = current->Next;
		}
		current->Next = mergedOddPositionList;
	}

	return mergedEvenPositionList;
}

int main() {
	// Tạo danh sách đơn sl1 và sl2 có thứ tự tăng dần
	Node* sl1 = NULL;
	Node* sl2 = NULL;
	insertSorted(&sl1, 1);
	insertSorted(&sl1, 3);
	insertSorted(&sl1, 5);
	insertSorted(&sl2, 2);
	insertSorted(&sl2, 4);
	insertSorted(&sl2, 6);

	// a. Trộn 2 danh sách thành một danh sách mới có thứ tự tăng dần
	printf("Danh sach sl1: ");
	printList(sl1);
	printf("Danh sach sl2: ");
	printList(sl2);
	Node* mergedListAscending = mergeSortedListsAscending(sl1, sl2);
	printf("Danh sach sau khi tron tang dan: ");
	printList(mergedListAscending);

	// b. Trộn 2 danh sách thành một danh sách mới có thứ tự giảm dần
	Node* mergedListDescending = mergeSortedListsDescending(sl1, sl2);
	printf("Danh sach sau khi tron giam dan: ");
	printList(mergedListDescending);

	// c. Trộn 2 danh sách thành một danh sách mới sao cho các phần tử có giá trị chẵn tăng dần, các phần tử có giá trị lẻ giảm dần
	Node* mergedListEvenOdd = mergeSortedListsEvenOdd(sl1, sl2);
	printf("Danh sach sau khi tron cac so chan tang dan, cac so le giam dan: ");
	printList(mergedListEvenOdd);

	// d. Trộn 2 danh sách thành một danh sách mới sao cho các phần tử tại những vị trí chẵn tăng dần, các phần tử tại vị trí lẻ giảm dần
	Node* mergedListPosition = mergeSortedListsPosition(sl1, sl2);
	printf("Danh sach sau khi tron cac phan tu o vi tri chan tang dan, cac phan tu o vi tri le giam dan: ");
	printList(mergedListPosition);

	return 0;
}
