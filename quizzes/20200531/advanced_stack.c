/*Given a fully featured Stack data structure, write an AdvancedStack data structure. AdvancedStack supports all functionality of a regular Stack, with same complexities of O(1) for Insert(), Peek(), and Pop(), but it also supports the following operations:
GetMin() - O(1)
GetMax() - O(1)
GetMedian() - O(1) [You may read in the internet what median is]
GetSum() - O(1) - returns sum of all values currently in the stack.
Bonus: GetAverage() - O(1) - Returns current average of values in stack.*/


typedef struct advanced_stack
{
    int median;
    int sum;
    stack_t* min;
    stack_t* max;
    stack_t* stack;
}adv_stack_t;

int AdvPush(adv_stack_t* stack, int* data)
{
    StackPush(stack->stack, data);
    stack->sum += *data;
    if (StackPeek(stack->min) >= *data)
    {
        StackPush(stack->min, data);
    }
    if (StackPeek(stack->max) <= *data)
    {
        StackPush(stack->max, data);
    }
    stack->median = (StackPeek(stack->max)+StackPeek(stack->min))/2;
    return 0;
}

void AdvPop(adv_stack_t* stack)
{
    stack->sum -= StackPeek(stack->stack);
    if (StackPeek(stack->min) == StackPeek(stack->stack))
    {
        StackPop(stack->min);
    }
    if (StackPeek(stack->max) == StackPeek(stack->stack))
    {
        StackPop(stack->max);
    }
    StackPop(stack->stack);
    stack->median = (StackPeek(stack->max)+StackPeek(stack->min))/2;
}

int GetMin(adv_stack_t* stack)
{
    return StackPeek(stack->min);
}

int GetMax(adv_stack_t* stack)
{
    return StackPeek(stack->min);
}

int GetMedian(adv_stack_t* stack)
{
    return stack->median;
}

int GetSum(adv_stack_t* stack)
{
    return stack->sum;
}

int GetAverage(adv_stack_t* stack)
{
    return stack->sum / StackSize(stack->stack);
}