#include "Stack.h"

#include <gtest.h>

// Тестирование класса Стек

TEST (Stack, can_create_the_stack)
{
	ASSERT_NO_THROW (Stack <int> s);
}

TEST (Stack, can_push_the_element)
{
	Stack <int> s;
	s.Push (5);

	EXPECT_EQ (5, s.ViewTop ());
}

TEST (Stack, can_pop_the_element)
{
	Stack <int> s;
	s.Push (5);
	s.Push (7);
	s.Pop ();

	EXPECT_EQ (5, s.ViewTop ());
}

TEST(Stack, throws_if_pop_elem_from_empty_stack)
{
	Stack <int> s;

	ASSERT_ANY_THROW (int top = s.Pop ());
}

TEST (Stack, can_determine_that_the_stack_is_non_empty)
{
	Stack <int> s;
	s.Push (5);

	EXPECT_EQ (0, s.StackIsEmpty ());
}
