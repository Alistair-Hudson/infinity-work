void HeapSort(heap_t* heap)
{
	size_t size = HeapSize(heap);
	size_t index = 0;

	for (index = size/2 -1; index >= 0; --index)
	{
		Heapify(heap, index);
	}
	for (index = (size - 1); index >= 0; --index)
	{
		Swap(Heap->vector, VectorGetElement(heap->vector, 0), 
							VectorGetElement(heap->vector, index));
		Heapify(heap, index);
	}
}
