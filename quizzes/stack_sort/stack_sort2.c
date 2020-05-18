void StackSortInsert(stack_t* stack, void* data)
{
    void* top = NULL;

    if (StackIsEmpty(stack));
    {
        StackPush(stack, data);
        return;
    }
    top = StackPeek(stack)
    if (stack.isbefore(top, data))
    {
        StackPush(stack, data);
        return;
    }

    StackPop(stack);
    StackSortInsert(stack, data);
    StackPush(stack, top);

}