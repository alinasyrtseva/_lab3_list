#ifndef __STACK_H__
#define __STACK_H__

#include "List.h"

// Класс Стек

template <class ValType>
class Stack 
{
protected:
	List <ValType> Mem;
public:
	Stack ();
	int StackIsEmpty ()
	{
		return Mem.IsEmpty ();
	}
	void Push (const ValType _data);
	ValType Pop ();
	ValType ViewTop ();
	void PrintStack ();
};


template <class ValType> 
Stack <ValType> :: Stack () 
{
}

template <class ValType> 
void Stack <ValType> :: Push (const ValType _data)
{
	Mem.InsertInTheHead (_data);
};

template <class ValType> 
ValType Stack <ValType> :: Pop ()
{
	ValType top = Mem.RemoveFromTheHead ();
	return top;
};

template <class ValType> 
void Stack <ValType> :: PrintStack ()
{
	Mem.PrintList ();
}

template <class ValType> 
ValType Stack <ValType> :: ViewTop ()
{
	ValType top = Mem.ViewHeadData ();
	return top;
};

#endif