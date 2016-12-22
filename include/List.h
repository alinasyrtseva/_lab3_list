#ifndef __LIST_H__
#define __LIST_H__


#include <cstdlib>
#include <iostream>

using namespace std;


// ����� ������

template <class ValType>
struct Node {
	ValType Data; // �������������� ����
	Node <ValType> * Next; // ��������� �����
};

template <class ValType>
class List
{
protected:
	Node <ValType> * Head;
	int Size;
public:

	List (int s = 0) // ����������� �� ���������
	{
		if (s >= 0)
		{
			Size = s;
			Head = NULL;
		}
		else
			throw 1;
	};

	~ List (); // ����������

	int GetSize () const // �������� ������ ������
	{
		return Size;
	}

	int IsEmpty () const // �������� �� �������
	{ 
		if (Head) 
			return 0; 
		return 1; 
	}

	void InsertInTheHead  (ValType _data); // ������� ����� � �������� ������ � ������ ������
	void InsertInTheTail (ValType _data); // ������� ����� � �������� ������ � ����� ������
	void InsertAfterPointer (ValType _data, Node <ValType> * ptr); // ������� ����� � �������� ������ ����� ���������

	ValType RemoveFromTheHead (); // �������� ����� �� ������ ������
	void RemoveFromTheTail (); // �������� ����� �� ����� ������
	void RemoveAfterPointer (Node <ValType> * ptr); // �������� ����� ����� ���������

	Node <ValType> * SearchByKey (ValType _data); // ����� ����� �� �����

	ValType ViewPointerData (Node <ValType> * ptr) // �������� ������ �����
	{
		return (ptr -> Data); 
	}	

	ValType ViewHeadData () // �������� ������ ������ ������
	{
		return (Head -> Data); 
	}	

	ValType ViewTailData () // �������� ������ ������ ������
	{
		Node <ValType> * tmp = Head;
		while (tmp -> Next != NULL) 
			tmp = tmp -> Next;
		return tmp -> Data; 
	}

	void PrintList (); // ������ ������
};

template <class ValType>
List <ValType> :: ~ List ()
{
	Node <ValType> * tmp;
	while (Head)
	{
		tmp = Head -> Next;
		delete Head;
		Head = tmp;
	}
}

template <class ValType>
void List <ValType> :: InsertInTheHead (ValType _data)
{
	Node <ValType> * tmp = new Node <ValType>;

	tmp -> Data = _data;
	tmp -> Next = Head;


	Head = tmp;
	Size ++;
}

template <class ValType>
void List <ValType> :: InsertInTheTail (ValType _data)
{
	if (IsEmpty ()) 
	{ 
		InsertInTheHead (_data); 
		return;
	}
	Node <ValType> * tmp = new Node <ValType>;

	tmp -> Data = _data;
	tmp -> Next = NULL;

	Node <ValType> * ptr = Head;
	while (ptr -> Next != NULL) 
		ptr = ptr -> Next;
	ptr -> Next = tmp;
	Size ++;
}

template <class ValType> 
void List <ValType> :: InsertAfterPointer (ValType _data, Node <ValType> * ptr)
{
	if (ptr)
	{
		Node <ValType> * tmp = new Node <ValType>;

		tmp -> Data = _data;
		tmp -> Next = ptr -> Next;

		ptr -> Next = tmp;
		Size ++;
	}
	else
	{
		Node <ValType> * tmp = new Node <ValType>;

		tmp -> Data = _data;
		tmp -> Next = NULL;


		Head = tmp;
		Size ++;
	}
}

template <class ValType> 
ValType List <ValType> :: RemoveFromTheHead ()
{
	if (Head != NULL) 
	{
		ValType top = Head -> Data;
		Node <ValType> * tmp = Head -> Next;
		delete Head;
		Head = tmp;
		Size --;
		return top;
	}
	else
		throw 1;
}

template <class ValType> 
void List <ValType> :: RemoveFromTheTail ()
{
	if (Size == 1)
	{
		delete Head;
		Head = NULL;
		Size --;
	}
	else if (Size > 0)
	{

		Node <ValType> * tmp = Head;
		while (tmp -> Next -> Next)
		{
			tmp = tmp -> Next;
		}
		delete tmp -> Next;
		tmp -> Next = NULL;
		Size --;
	}
	else
		throw 1;
}

template <class ValType>
void List <ValType> :: RemoveAfterPointer (Node <ValType> * ptr)
{
	if (Size == 1)
	{
		delete Head;
		Head = NULL;
		Size --;
	}
	else if (Size > 0)
	{
		Node <ValType> * tmp = ptr -> Next -> Next;
		delete ptr -> Next;
		ptr -> Next = tmp;
		Size --;
	}
	else
		throw 1;
}

template <class ValType> 
Node <ValType> * List <ValType> :: SearchByKey (ValType _data)
{
	if (Size > 0)
	{
		Node <ValType> * tmp = Head;
		while (tmp != NULL)
		{
			if (tmp -> Data == _data)
				break;	
			else
				tmp = tmp -> Next;
		}
		return tmp;
	 }
	else
		throw 1;
}

template <class ValType> 
void List <ValType> :: PrintList ()
{
	Node <ValType> * tmp = Head;
	while (tmp)
	{
		cout << tmp -> Data << endl;
		tmp = tmp -> Next;
	} 
}

#endif

