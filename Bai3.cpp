#include <stdio.h>
#include <conio.h>
typedef int ItemType; //khai bao du lieu moi co ten la ItemType
//dinh nghia cau truc nut
struct Node {
	ItemType Info;
	Node* Next;
};
//tao nut chua x(ham moi)
Node* createNode(ItemType x)
{
	Node* p = new Node;
	if (p == NULL)
	{
		printf("khong  du bao nho cap phat!");
		_getch();
		return NULL;
	}
	p->Info = x;
	p->Next = NULL;
	return p;
}
//ham chen phan tu vao ds sao cho van giu nguyen thu tu tang dan
void insertSorted(Node** HeadRef, ItemType x)
{
	Node* newNode = createNode(x);
	Node* current;
	if (*HeadRef == NULL || (*HeadRef)->Info >= x)
	{
		newNode->Next = *HeadRef;
		*HeadRef = newNode;
	}
	else
	{
		current = *HeadRef;
		while (current->Next != NULL && current->Next->Info < x)
		{
			current = current->Next;
		}
		newNode->Next = current->Next;
		current->Next = newNode;
	}
}
//ham in danh sach theo thứ tự giam dan
void printfReverse(Node* Head)
{
	if (Head == NULL)
		return;
	printfReverse(Head->Next);
	printf("%d", Head->Info);
}
//ham noi ds sl2 vao sau ptu x cuar ds sl1
void appendAfterValue(Node** HeadRef, ItemType x, Node* sl2)
{
	Node* current = *HeadRef;
	while (current != NULL && current->Info != x)
	{
		current = current->Next;
	}
	if (current == NULL)
	{
		printf("khong co phan tu %d\n", x);
		return;
	}
	Node* temp = current->Next;
	current->Next = sl2;
	while (current->Next != NULL)
	{
		current = current->Next;
	}
	current->Next = temp;
}
//am in ds
void printfList(Node* Head)
{
	while (Head != NULL)
	{
		printf("%d", Head->Info);
		Head = Head->Next;
	}
	printf("\n");
}
int main()
{
	Node* Head = NULL;
	// a. chen ptu vao ds sao cho van giu nguyen thu tu tang dan
	insertSorted(&Head, 1);
	insertSorted(&Head, 2);
	insertSorted(&Head, 3);
	insertSorted(&Head, 4);
	insertSorted(&Head, 5);
	printf("danh sach sau khi chen:\t");
	printfList(Head);
	//b.in ds theo thu tu giam dan
	printf("danh sach theo thu tu giam dan:\t");
	printfReverse(Head);
	printf("\n");
	//tao ds sl2
	Node* sl2 = createNode(6);
	insertSorted(&sl2, 7);
	//c.noi sl2 voi sl1
	int x = 3;
	appendAfterValue(&Head, x, sl2);
	printf("danh sach sau khi noi sl2 sau khi them vao sau %d la:", x);
	printfList(Head);
	return 0;
}