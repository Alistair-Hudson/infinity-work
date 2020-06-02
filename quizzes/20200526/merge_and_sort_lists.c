list_t* MergeAndSortLists(list_t* list1, list_t* list2, is_b4_t* is_before)
{
    list_t* output = CreateSortedList(is_before)
    node_t* node1 = ListBegin(list1);
    node_t* node2 = ListBegin(list2);

    While (!IsSameNode(ListEnd(src), node1) && !IsSameNode(ListEnd(src), node2))
    {
        int data = GetData(node1);
        InsertData(ouput, data);
        data = GetData(node2);
        InsertData(ouput, data);
        node1 = NextNode(node1);
        node2 = NextNode(node2);
    }
    return output;
}