#include "Arithmetic.h"

#include <gtest.h>


TEST (Arithmetic, can_find_the_number_of_tokens_in_postfix_notation)
{
	int toknumb = 0;
	Tokens * pn = ConversionToPostfixNotation ("(1+3)*5", toknumb);

	EXPECT_EQ (5, toknumb);
}

TEST (Arithmetic, throws_when_an_empty_expression)
{
	int toknumb = 0;

	ASSERT_ANY_THROW (ConversionToPostfixNotation ("", toknumb));
}

TEST (Arithmetic, throws_when_there_is_an_unknown_token)
{
	int toknumb = 0;

	ASSERT_ANY_THROW (ConversionToPostfixNotation ("1+&", toknumb));
}

TEST (Arithmetic, throws_when_brackets_are_not_coordinated)
{
	int toknumb = 0;

	ASSERT_ANY_THROW (ConversionToPostfixNotation ("2+3)", toknumb));
}

TEST (Arithmetic, throws_when_brackets_are_not_coordinated_2)
{
	int toknumb = 0;

	ASSERT_ANY_THROW (ConversionToPostfixNotation ("(2+3", toknumb));
}