typedef struct array
{
    size_t size;
    int data[] : 1;
}array_t;

void setval(array_t* array, int indx, int val)
{
    if (array->size < indx || 0 > indx)
    {
        return;
    }
    array->data[indx] = val;
}

int getval(array_t* array, int indx)
{
    if (array->size < indx || 0 > indx)
    {
        return;
    }
    return array->data[indx];
}

void setall (array_t* array, int val)
{
    array->data[] = {val};
}