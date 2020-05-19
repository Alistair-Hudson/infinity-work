int CombinationToN(int* array_of_values, 
                    size_t index, 
                    size_t size_of_array, 
                    int N, 
                    int* combinations)
{
    if (index == size_of_array)
    {
        return 0;
    }
    if (N < total + array_of_values[index])
    {   
        return 0;
    }
    if(N == total + array_of_values[index])
    {
        *combinations += 1;
        return 1;
    }
    if (!CombinationToN(array_of_values, ++index, size_of_array, N, combinations))
    {
        return 0;
    }
    return 1;
}