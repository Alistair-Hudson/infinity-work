#include <stdio.h>
#include <stdlib.h>

int *Bursa(int *stock_price, size_t array_size)
{
	int result[3];
	int *resptr = result;
	unsigned int buy = 0;
	unsigned int sell = 1;
	int min_price = stock_price[buy];
	int max_price = stock_price[sell];
	int profit = max_price - min_price;
	int index_to_buy = buy;
	int index_to_sell = sell;
	int buy_at_buf = buy;
	int sell_at_buf = sell ;
	++buy;
	++sell;
	for(; sell < array_size; ++sell, ++buy)
	{
		if(stock_price[buy] < min_price)
		{
			min_price = stock_price[buy];
			max_price = stock_price[sell];
			buy_at_buf = buy;
			sell_at_buf = sell;

		}
		else if (stock_price[sell] > max_price)
		{
			max_price = stock_price[sell];
			sell_at_buf = sell;
		}
		if(profit < (max_price - min_price))
		{
			profit = max_price - min_price;
			index_to_buy = buy_at_buf;
			index_to_sell = sell_at_buf;
		}
	}
	result[0] = profit;
	result[1] = index_to_buy;
	result[2] = index_to_sell;
	return resptr;
}


int main ()
{	
	int stock[] = {6,12,3,5,1,4,9,2};
	size_t size = sizeof(stock)/sizeof(int);
	int *profit = Bursa(stock, size);
	printf("profit is %d, buy @ %d, sell @ %d\n", *profit, profit[1], profit[2]);
 	return 0;
}
	
