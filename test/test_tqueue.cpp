#include <gtest.h>
#include "queue.h"

TEST(TQueue, can_create_queue_with_positive_size)
{
    ASSERT_NO_THROW(TQueue<int> q(5));
}


TEST(TQueue, can_create_queue_with_default_size)
{
    ASSERT_NO_THROW(TQueue<int> q);
}

TEST(TQueue, throws_when_create_queue_with_negative_size)
{
    ASSERT_ANY_THROW(TQueue<int> q(-5));
}

TEST(TQueue, can_create_copied_queue)
{
    TQueue<int> q(5);
    q.push(10);

    ASSERT_NO_THROW(TQueue<int> q1(q));
}

TEST(TQueue, copied_queue_is_equal_to_source_one)
{
    TQueue<int> q(5);
    q.push(10);
    q.push(20);
    q.push(30);

    TQueue<int> q1(q);

    ASSERT_EQ(q1.pop(), 10);
    ASSERT_EQ(q1.pop(), 20);
    ASSERT_EQ(q1.pop(), 30);
    ASSERT_TRUE(q1.IsEmpty());
}

TEST(TQueue, copied_queue_has_its_own_memory)
{
    TQueue<int> q(5);
    q.push(10);

    TQueue<int> q1(q);
    q1.push(20);  

 
    ASSERT_EQ(q.pop(), 10);
    ASSERT_TRUE(q.IsEmpty());


    ASSERT_EQ(q1.pop(), 10);
    ASSERT_EQ(q1.pop(), 20);
    ASSERT_TRUE(q1.IsEmpty());
}
TEST(TQueue, can_check_if_queue_is_empty)
{
    TQueue<int> q(5);

    ASSERT_TRUE(q.IsEmpty());

    q.push(10);
    ASSERT_FALSE(q.IsEmpty());

    q.pop();
    ASSERT_TRUE(q.IsEmpty());
}

TEST(TQueue, can_check_if_queue_is_full)
{
    TQueue<int> q(3);

    ASSERT_FALSE(q.IsFull());

    q.push(1);
    q.push(2);
    q.push(3);

    ASSERT_TRUE(q.IsFull());
}

TEST(TQueue, can_push_and_pop_element)
{
    TQueue<int> q(5);

    ASSERT_NO_THROW(q.push(42));
    ASSERT_EQ(q.pop(), 42);
    ASSERT_TRUE(q.IsEmpty());
}

TEST(TQueue, follows_FIFO_principle)
{
    TQueue<int> q(5);

    q.push(1);
    q.push(2);
    q.push(3);

    ASSERT_EQ(q.pop(), 1);
    ASSERT_EQ(q.pop(), 2);
    ASSERT_EQ(q.pop(), 3);
    ASSERT_TRUE(q.IsEmpty());
}

TEST(TQueue, throws_when_pop_from_empty_queue)
{
    TQueue<int> q(5);

    ASSERT_TRUE(q.IsEmpty());
    ASSERT_THROW(q.pop(), std::out_of_range);
}

TEST(TQueue, throws_when_push_to_full_queue)
{
    TQueue<int> q(3);

    q.push(1);
    q.push(2);
    q.push(3);

    ASSERT_TRUE(q.IsFull());
    ASSERT_THROW(q.push(4), std::out_of_range);
}

TEST(TQueue, can_assign_queue_to_itself)
{
    TQueue<int> q(5);
    q.push(10);
    q.push(20);

    ASSERT_NO_THROW(q = q);

    ASSERT_EQ(q.pop(), 10);
    ASSERT_EQ(q.pop(), 20);
    ASSERT_TRUE(q.IsEmpty());
}

TEST(TQueue, can_assign_queues_of_equal_size)
{
    TQueue<int> q1(5);
    q1.push(10);
    q1.push(20);
    q1.push(30);

    TQueue<int> q2(5);

    ASSERT_NO_THROW(q2 = q1);

    ASSERT_EQ(q2.pop(), 10);
    ASSERT_EQ(q2.pop(), 20);
    ASSERT_EQ(q2.pop(), 30);
    ASSERT_TRUE(q2.IsEmpty());
}

TEST(TQueue, assign_operator_change_queue_size)
{
    TQueue<int> q1(5);
    q1.push(1);
    q1.push(2);

    TQueue<int> q2(3); 

    q2 = q1; 

    ASSERT_EQ(q2.pop(), 1);
    ASSERT_EQ(q2.pop(), 2);
    ASSERT_TRUE(q2.IsEmpty());

    for (int i = 0; i < 5; i++) {
        q2.push(i);
    }

    ASSERT_THROW(q2.push(5), std::out_of_range);
}

TEST(TQueue, circular_buffer_works_correctly)
{
    TQueue<int> q(3);


    q.push(1);
    q.push(2);

    ASSERT_EQ(q.pop(), 1);  

    q.push(3);  
    q.push(4);  

    ASSERT_TRUE(q.IsFull());

 
    ASSERT_EQ(q.pop(), 2);
    ASSERT_EQ(q.pop(), 3);
    ASSERT_EQ(q.pop(), 4);
    ASSERT_TRUE(q.IsEmpty());
}

TEST(TQueue, can_work_with_different_data_types)
{

    TQueue<int> q1(5);
    q1.push(42);
    ASSERT_EQ(q1.pop(), 42);

  
    TQueue<double> q2(5);
    q2.push(3.14);
    ASSERT_DOUBLE_EQ(q2.pop(), 3.14);

   
    TQueue<std::string> q3(5);
    q3.push("test");
    ASSERT_EQ(q3.pop(), "test");
}


TEST(TQueue, IsEmpty_and_IsFull_behavior)
{
    TQueue<int> q(3);

    ASSERT_TRUE(q.IsEmpty());
    ASSERT_FALSE(q.IsFull());

    q.push(1);
    ASSERT_FALSE(q.IsEmpty());
    ASSERT_FALSE(q.IsFull());

    q.push(2);
    ASSERT_FALSE(q.IsEmpty());
    ASSERT_FALSE(q.IsFull());

    q.push(3);
    ASSERT_FALSE(q.IsEmpty());
    ASSERT_TRUE(q.IsFull());

    q.pop();
    ASSERT_FALSE(q.IsEmpty());
    ASSERT_FALSE(q.IsFull());

    q.pop();
    q.pop();
    ASSERT_TRUE(q.IsEmpty());
    ASSERT_FALSE(q.IsFull());
}


TEST(TQueue, queue_size_one)
{
    TQueue<int> q(1);

    ASSERT_TRUE(q.IsEmpty());
    ASSERT_FALSE(q.IsFull());

    q.push(42);
    ASSERT_FALSE(q.IsEmpty());
    ASSERT_TRUE(q.IsFull());

    ASSERT_THROW(q.push(43), std::out_of_range);  

    ASSERT_EQ(q.pop(), 42);
    ASSERT_TRUE(q.IsEmpty());
    ASSERT_FALSE(q.IsFull());

    ASSERT_THROW(q.pop(), std::out_of_range);  
}