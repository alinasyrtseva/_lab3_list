#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include "Stack.h"
#include "Parser.h"
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;

int OperationPriority (char op) // ����������� ���������� ��������
{
	int prior;
	switch (op)
	{
	case '^': { prior = 4; break; }
	case '*': { prior = 3; break; }
	case '/': { prior = 3; break; }
	case '+': { prior = 2; break; }
	case '-': { prior = 2; break; }
	case '(': { prior = 1; break; }
	case ')': { prior = 1; break; }
	default: throw 1;
	}
	return prior;
}


Tokens * ConversionToPostfixNotation (char * expr, int & toknumb) // �������������� � ��� (�������� �������� �������)
{

	Tokens * toks = Tokenization (expr); // ��������� ��������� �� �������
	Tokens top;

	int len = strlen (expr);
	int i = 0;
	int j = 0;

	Stack <Tokens> OperationStack;

	Tokens Postfix [255]; 

	while (i < len)
	{
		// ������ ��������� �������

		// ���� ������� �������� ������, ��������� �� � �������� ������
		if (strcmp (toks [i].TokenType, "Number") == 0)
		{
			Postfix [j] = toks [i];
			j ++;
		}

		// ���� ������� �������� ����������� �������, �������� �� � ���� 
		else if (strcmp (toks [i].TokenType, "Opening bracket") == 0)
			OperationStack.Push (toks [i]);

		// ���� ������ �������� ����������� �������: 
		//   �� ��� ���, ���� ������� ��������� ����� �� ������ ����������� ������, ����������� �������� �� ����� � �������� ������
		//   ��� ���� ����������� ������ ��������� �� �����, �� � �������� ������ �� �����������
		// ? ���� ���� ���������� ������, ��� �� ��������� ����������� ������, �� � ��������� ���� ������� ��������� �����������, ���� �� ����������� ������
		
		else if (strcmp (toks [i].TokenType, "Closing bracket") == 0)
		{
		    int flag = 0;

			while (! OperationStack.StackIsEmpty ())
			{
				if (strcmp (OperationStack.ViewTop ().TokenType, "Opening bracket") != 0)
				{
					top = OperationStack.Pop ();
					Postfix [j] = top;
				    j ++;
				}
				else
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0)
				throw 1;

			top = OperationStack.Pop ();
		}

	
		
		// ���� ��������� ��������� ������ ���������� ���������, ������������ �� ������� �����,
		//   ����������� ������� ������� ����� � �������� ������
		// � �������� �������� � ����
		else if (strcmp (toks [i].TokenType, "Operator") == 0)
		{
			Tokens _t;
			if (OperationStack.StackIsEmpty ())
				OperationStack.Push (toks [i]);
			else
			{
				top = OperationStack.ViewTop ();
				if (OperationPriority (toks[i].Token [0]) > OperationPriority (top.Token [0]))
					OperationStack.Push (toks [i]);

				else
				{
					while (! OperationStack.StackIsEmpty ())
					{
						top = OperationStack.ViewTop ();
						if (OperationPriority (toks[i].Token [0]) <= OperationPriority (top.Token [0]))
						{
							_t = OperationStack.Pop ();
						    Postfix [j] = _t;
						    j ++;
						}
						else
							break;
					}
					OperationStack.Push (toks [i]);
				}
			}
		}

		i ++;
	}

	Tokens _t;

	// ����� ������� ������ �����������, ����������� ��� ������� �� ����� � �������� ������. 
	// � ����� ������ ���� �������� ������ ������� ����������; ���� ��� �� ���, ������ � ��������� �� ����������� ������.

	while (! (OperationStack.StackIsEmpty ()))
	{
		_t = OperationStack.Pop ();
		if (strcmp (_t.TokenType, "Operator") == 0)
		{
		    Postfix [j] = _t;
		    j ++;
		}
		else
			throw 1;
	}
	
	 toknumb = j;

	return Postfix;
}


double Operation (double a, double b, char op) // ���������� ��������
{
	switch (op)
	{
	case '+': { return a + b; break; }
	case '-': { return a - b; break; }
	case '*': { return a * b; break; }
	case '/': { return a / b; break; }
	case '^':
		{
			double res = a;
		    for (int i = 1 ; i < b ; i++)
			res = res * a;
			return res;
			break;
		}

		default: throw 1;
    }
}

double Calculation (Tokens * pn, int toknumb) // ������������� ������� �������� ���������
{
	double res;
	Stack <double> _Stack;
	for (int i = 0; i < toknumb; i ++)
	{
		if (strcmp (pn [i].TokenType , "Number") == 0)
			_Stack.Push (atof (pn [i].Token));
		else
		{
			double b = _Stack.Pop ();
			double a = _Stack.Pop ();
			res = Operation (a, b, pn [i].Token [0]);
			_Stack.Push (res);
		}
	}

	return res;
}

#endif