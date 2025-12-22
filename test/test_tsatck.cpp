#include <gtest.h>
#include "stack.h"

TEST(TStack, can_create_stack_with_positive_size)
{
    ASSERT_NO_THROW(TStack<int> s(5));
}

TEST(TStack, throws_when_create_stack_with_negative_size)
{
    ASSERT_ANY_THROW(TStack<int> s(-5));
}

TEST(TStack, can_create_stack_with_default_size)
{
    ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, can_create_copied_stack)
{
    TStack<int> s(5);

    ASSERT_NO_THROW(TStack<int> s1(s));
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
    TStack<int> s(5);
    s.push(10);
    s.push(20);

    TStack<int> s1(s);

    ASSERT_EQ(s1.pop(), 20);
    ASSERT_EQ(s1.pop(), 10);
    ASSERT_TRUE(s1.IsEmpty());
}


TEST(TStack, copied_stack_has_its_own_memory)
{
    TStack<int> s(5);
    s.push(10);

    TStack<int> s1(s);
    s1.push(20); 

    ASSERT_EQ(s.pop(), 10);
    ASSERT_TRUE(s.IsEmpty());

    ASSERT_EQ(s1.pop(), 20);
    ASSERT_EQ(s1.pop(), 10);
}

TEST(TStack, can_check_if_stack_is_empty)
{
    TStack<int> s(5);

    ASSERT_TRUE(s.IsEmpty());

    s.push(10);
    ASSERT_FALSE(s.IsEmpty());

    s.pop();
    ASSERT_TRUE(s.IsEmpty());
}

TEST(TStack, can_push_and_pop_element)
{
    TStack<int> s(5);

    ASSERT_NO_THROW(s.push(42));
    ASSERT_NO_THROW(s.push(42));
    ASSERT_NO_THROW(s.pop());
    ASSERT_EQ(s.pop(), 42);
}

TEST(TStack, top_returns_element_without_removing)
{
    TStack<int> s(5);
    s.push(10);
    s.push(20);

    ASSERT_EQ(s.top(), 20);
    ASSERT_EQ(s.top(), 20);  
    ASSERT_EQ(s.pop(), 20);  
}

TEST(TStack, can_assign_stack_to_itself)
{
    TStack<int> s(5);
    s.push(10);
    s.push(20);

    ASSERT_NO_THROW(s = s);

    ASSERT_EQ(s.pop(), 20);
    ASSERT_EQ(s.pop(), 10);
    ASSERT_TRUE(s.IsEmpty());
}

TEST(TStack, can_assign_stacks_of_equal_size)
{
    TStack<int> s1(5);
    s1.push(10);
    s1.push(20);

    TStack<int> s2(5);

    ASSERT_NO_THROW(s2 = s1);

    ASSERT_EQ(s2.pop(), 20);
    ASSERT_EQ(s2.pop(), 10);
    ASSERT_TRUE(s2.IsEmpty());
}

TEST(TStack, assign_operator_change_stack_size)
{
    TStack<int> s1(5);
    TStack<int> s2(10);

   
    s1 = s2;

 
    for (int i = 0; i < 10; i++) {
        s1.push(i);
    }


    ASSERT_THROW(s1.push(10), std::out_of_range);
}

TEST(TStack, throws_when_pop_from_empty_stack)
{
    TStack<int> s(5);

    ASSERT_TRUE(s.IsEmpty());
    ASSERT_THROW(s.pop(), std::out_of_range);
}

TEST(TStack, throws_when_top_from_empty_stack)
{
    TStack<int> s(5);

    ASSERT_TRUE(s.IsEmpty());
    ASSERT_THROW(s.top(), std::out_of_range);
}

TEST(TStack, throws_when_push_to_full_stack)
{
    TStack<int> s(3);

    s.push(1);
    s.push(2);
    s.push(3);

    ASSERT_THROW(s.push(4), std::out_of_range);
}

TEST(TStack, follows_LIFO_principle)
{
    TStack<int> s(5);

    s.push(1);
    s.push(2);
    s.push(3);

    ASSERT_EQ(s.pop(), 3);
    ASSERT_EQ(s.pop(), 2);
    ASSERT_EQ(s.pop(), 1);
    ASSERT_TRUE(s.IsEmpty());
}

TEST(TStack, can_work_with_different_data_types)
{
  
    TStack<int> s1(5);
    s1.push(42);
    ASSERT_EQ(s1.pop(), 42);

   
    TStack<double> s2(5);
    s2.push(3.14);
    ASSERT_DOUBLE_EQ(s2.pop(), 3.14);

   
    TStack<std::string> s3(5);
    s3.push("test");
    ASSERT_EQ(s3.pop(), "test");
}

TEST(TStack, compare_equal_stacks_works_correctly)
{
    TStack<int> s1(5);
    s1.push(10);
    s1.push(20);

    TStack<int> s2(s1); 

   
    while (!s1.IsEmpty()) s1.pop();
    while (!s2.IsEmpty()) s2.pop();

    ASSERT_TRUE(s1.IsEmpty());
    ASSERT_TRUE(s2.IsEmpty());
}