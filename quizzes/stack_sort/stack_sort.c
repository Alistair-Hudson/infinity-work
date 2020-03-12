void StackSort(stack_t *stack)
{
	stack_t *stack_buffer = (stack*)malloc(StackSize(stack) * sizeof(size_t));
	int value1 = StackPeek(stack);
	int value2 = 0;
	int temp = 0;
	int sorted = 1;

	StackPop(stack);

	while (!sorted)
	{
		sorted = 1;	
		while(!StackIsEmpty(stack)
		{
			value2 = StackPeek(stack);
			if (value1 > value2)
			{
				temp = value1;
				value1 = value2;
				value2 = temp;	
				sorted = 0;	
			}
			StackPush(stack_buffer, value1);
			value1 = value2;
			StackPop(stack);
		}
		while (!StackIsEmpty(stack_buffer)
		{
			value1 = StackPeek(stack_buffer);
			StackPush(stack, value1);
			StackPop(stack_buffer);
		}		
	}
}
