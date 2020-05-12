
enum stacks
{
    A = 0,
    B,
    C
};

stack_t stacks[3];

void InitStack()
{
    int i = 0;
    for (i = 1; i <= MAX_DISKS; ++i)
    {
        Push(stacks[A], i);
    }
}

void TowerOfHanoi(int stack)
{
    int move = 0;
    static int prev_is_empty = 0;
    int next_stack = stack == C ? A : stack + 1;
    int prev_stack = stack == A ? C : stack - 1;

    if(IsEmpty(stacks[stack]))
    {
        if (prev_is_empty)
        {
            return;
        }
        else
        {
            prev_is_empty = 1;
            TowerOfHanoi(next_stack);
        }
        
    }

    move = Peek(stacks[stack]);
    
    if (move < Peek(stacks[next_stack]))
    {
        Push(stacks[next_stack], move);
        Pop(stacks[stack]);
        printf("Disk %d moved from %d to %d", move, stack, next_stack);
        TowerOfHanoi(stack);
    }
    if(move < Peek(stacks[prev_stack]))
    {
        Push(stacks[prev_stack], move);
        Pop(stacks[stack]);
        printf("Disk %d moved from %d to %d", move, stack, prev_stack);
        TowerOfHanoi(stack);
    }
    TowerOfHanoi(next_stack);
}