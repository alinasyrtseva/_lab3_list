#ifndef __PARSER_H__
#define __PARSER_H__

#include <cstring>
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct Tokens
{
	char Token [255]; // лексема
	char TokenType [20]; // тип лексемы
};

Tokens * Tokenization (char * expr) // разбиение исходного арифметического выражения на лексемы 
{
	int len = strlen (expr);
	Tokens toks [255];
	int i = 0;
	int j = 0;

	if (expr [i] == 0)
		throw 1;

    while (isspace (expr [i])) // Пропустить разделительные символы
		i ++; 
	
	if (expr [i] == '-')
	{
		int k = 1;

		toks [j].Token [0] = expr [i];
        while ((isdigit (expr [i + 1])) || (expr [i + 1] == '.'))
		{
			toks [j].Token [k] = expr [i + 1];
			k ++;
			i ++;
		}
		toks [j].Token [k] = '\0';
		
		strcpy_s (toks [j].TokenType, "Number");

		j ++;
	}


    else if (strchr ("+-*/^", expr [i]))
    {
		toks [j].Token [0] = expr [i];
		toks [j].Token [1] = '\0';

		strcpy_s (toks [j].TokenType, "Operator");

		j ++;
    }

	else if (expr [i] == '(')
	{
		toks [j].Token [0] = expr [i];
		toks [j].Token [1] = '\0';

		strcpy_s (toks [j].TokenType, "Opening bracket");

		j ++;
	}

	else if (expr [i] == ')')
	{
		toks [j].Token [0] = expr [i];
		toks [j].Token [1] = '\0';

		strcpy_s (toks [j].TokenType, "Closing bracket");

		j ++;

	}

    else if (isalpha (expr [i]))
    {
		char numb [255];
		cout << "Enter the value of the variable " << expr [i] << ": " << endl;
		cin >> numb;
		cout << endl;

		unsigned  int k = 0;
		while (k < strlen (numb))
		{
			toks [j].Token [k] = numb [k];
			k ++;
		}
		toks [j].Token [k] = '\0';

		strcpy_s (toks [j].TokenType, "Number");

		j ++;
    }

    else if (isdigit (expr [i]))
    {
		int k = 1;
		toks [j].Token [0] = expr [i];
        while ((isdigit (expr [i + 1])) || (expr [i + 1] == '.'))
		{
			toks [j].Token [k] = expr [i + 1];
			k ++;
			i ++;
		}
		toks [j].Token [k] = '\0';

		strcpy_s (toks [j].TokenType, "Number");

		j ++;

    }

	else
		throw 1;

	i ++; 

    for (; i < len; i ++)
	{

	while (isspace (expr [i])) // Пропустить разделительные символы
		i ++; 

	if ((expr [i] == '-') && (expr [i - 1] == '('))
	{
		int k = 1;

		toks [j].Token [0] = expr [i];
        while ((isdigit (expr [i + 1])) || (expr [i + 1] == '.'))
		{
			toks [j].Token [k] = expr [i + 1];
			k ++;
			i ++;
		}
		toks [j].Token [k] = '\0';

		strcpy_s (toks [j].TokenType, "Number");

		j ++;
	}


    else if (strchr ("+-*/^", expr [i]))
    {
		toks [j].Token [0] = expr [i];
		toks [j].Token [1] = '\0';

		strcpy_s (toks [j].TokenType, "Operator");

		j ++;
    }

	else if (expr [i] == '(')
	{
		toks [j].Token [0] = expr [i];
		toks [j].Token [1] = '\0';

		strcpy_s (toks [j].TokenType, "Opening bracket");

		j ++;
	}

	else if (expr [i] == ')')
	{
		toks [j].Token [0] = expr [i];
		toks [j].Token [1] = '\0';


		strcpy_s (toks [j].TokenType, "Closing bracket");

		j ++;

	}


	else if (isalpha (expr [i]))
    {
		char numb [255];
		cout << "Enter the value of the variable " << expr [i] << ": " << endl;
		cin >> numb;
		cout << endl;

		unsigned int k = 0;
		while (k < strlen (numb))
		{
			toks [j].Token [k] = numb [k];
			k ++;
		}
		toks [j].Token [k] = '\0';

		strcpy_s (toks [j].TokenType, "Number");

		j ++;
    }



    else if (isdigit (expr [i]))
    {
		int k = 1;

		toks [j].Token [0] = expr [i];
        while ((isdigit (expr [i + 1])) || (expr [i + 1] == '.'))
		{
			toks [j].Token [k] = expr [i + 1];
			k ++;
			i ++;
		}
		toks [j].Token [k] = '\0';

		strcpy_s (toks [j].TokenType, "Number");

		j++;

    }

	else
		throw 1;
	}

	return toks; 
}


#endif