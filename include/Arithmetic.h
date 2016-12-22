#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include "Stack.h"
#include "Parser.h"
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;

int OperationPriority (char op) // определение приоритета операции
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


Tokens * ConversionToPostfixNotation (char * expr, int & toknumb) // преобразование к ќѕЌ (обратной польской нотации)
{

	Tokens * toks = Tokenization (expr); // раздел€ем выражение на лексемы
	Tokens top;

	int len = strlen (expr);
	int i = 0;
	int j = 0;

	Stack <Tokens> OperationStack;

	Tokens Postfix [255]; 

	while (i < len)
	{
		// „итаем очередную лексему

		// ≈сли лексема €вл€етс€ числом, добавл€ем ее в выходную строку
		if (strcmp (toks [i].TokenType, "Number") == 0)
		{
			Postfix [j] = toks [i];
			j ++;
		}

		// ≈сли лексема €вл€етс€ открывающей скобкой, помещаем ее в стек 
		else if (strcmp (toks [i].TokenType, "Opening bracket") == 0)
			OperationStack.Push (toks [i]);

		// ≈сли символ €вл€етс€ закрывающей скобкой: 
		//   до тех пор, пока верхним элементом стека не станет открывающа€ скобка, выталкиваем элементы из стека в выходную строку
		//   при этом открывающа€ скобка удал€етс€ из стека, но в выходную строку не добавл€етс€
		// ? ≈сли стек закончилс€ раньше, чем мы встретили открывающую скобку, то в выражении либо неверно поставлен разделитель, либо не согласованы скобки
		
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

	
		
		// ѕока приоритет оператора меньше приоритета оператора, наход€щегос€ на вершине стека,
		//   выталкиваем верхний элемент стека в выходную строку
		// и помещаем оператор в стек
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

	//  огда входна€ строка закончилась, выталкиваем все символы из стека в выходную строку. 
	// ¬ стеке должны были остатьс€ только символы операторов; если это не так, значит в выражении не согласованы скобки.

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


double Operation (double a, double b, char op) // совершение операции
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

double Calculation (Tokens * pn, int toknumb) // окончательный подсчет значени€ выражени€
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