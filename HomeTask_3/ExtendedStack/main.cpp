#include <gtest/gtest.h>
#include "Stack.h"

// Тест на перевірку функціональності push та min
TEST(StackTest, PushAndMin) {
    StackPtr stack = StackInit();

    StackPush(stack, 10);
    StackPush(stack, 5);
    StackPush(stack, 20);

    // Перевіряємо, чи мінімум правильний
    EXPECT_EQ(StackMin(stack), 5);

    StackDestroy(stack);
}

// Тест на перевірку функціональності pop
TEST(StackTest, Pop) {
    StackPtr stack = StackInit();

    StackPush(stack, 10);
    StackPush(stack, 5);
    StackPush(stack, 20);

    // Після видалення елемента перевіряємо мінімум
    StackPop(stack);
    EXPECT_EQ(StackMin(stack), 5);

    StackPop(stack);
    EXPECT_EQ(StackMin(stack), 10);

    StackDestroy(stack);
}

// Тест на перевірку порожнього стека
TEST(StackTest, EmptyStack) {
    StackPtr stack = StackInit();
    
    // Перевіряємо, чи порожній стек
    EXPECT_TRUE(StackEmpty(stack));

    // Додаємо елементи і перевіряємо
    StackPush(stack, 5);
    EXPECT_FALSE(StackEmpty(stack));

    StackDestroy(stack);
}