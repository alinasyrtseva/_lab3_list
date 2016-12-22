#include "Arithmetic.h"
#include "Parser.h"

#include <cstdlib>


int main ()

{
	cout << "________________________________________________________________________________" << endl;
	cout << "           THE CONVERSION OF THE EXPRESSION FROM INFIX NOTATION" << endl;
	cout << "                     TO POSTFIX (REVERSE POLISH) NOTATION" << endl;
	cout << "________________________________________________________________________________" << endl;
	cout << endl;

	
	char exprassion [255];

	cout << "Enter the expression:" << endl;
	cin >> exprassion;

	cout << endl;

	int tok_numb = 0;
	Tokens * postfix_notation = ConversionToPostfixNotation (exprassion, tok_numb);


	cout << "The expression in the postfix form: " << endl;
	for (int i = 0; i < tok_numb; i ++)
		cout << postfix_notation [i].Token << ' ';

	cout << endl;

	cout << endl;

	double result = Calculation (postfix_notation, tok_numb);
	cout << "The result of the calculation: " << result << endl;
	cout << endl;

	return 0;
}