#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ws3.c"

void JosephusTest(int soldiers, int survivour)
{
	int result = Josephus(soldiers);
	if (result == survivour)
	{
		printf("\nJosephus passed\n");
	}else
	{
		printf ("\nJosephus failed\n");
		printf("no. of soldiers = %d", soldiers);
		printf("survivour should be %d, reslut is %d\n", survivour, result);
	}
}

void DatatypeTest()
{
	printf("\nthe following is expected;\n");
	printf("char is size of %ld\n", sizeof(char));
	printf("int is size of %ld\n", sizeof(int));
	printf("float is size of %ld\n", sizeof(float));
	printf("double is size of %ld\n", sizeof(double));
	printf("void is size of non-existant\n");
	printf("the printout reads;\n");
	PrintDataTypeSizes( );
}

int main (int argc, char **argv, char **envp)
{		
	/*int result;
	double time_taken;
	clock_t t; 
	t = clock(); 
 	result =  Josephus(15);
	t = clock() - t; 
  	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Josephus took %f seconds to execute \n", time_taken); 

	t = clock(); 
 	result =  AliJosephus(15);
	t = clock() - t; 
  	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("AliJosephus took %f seconds to execute \n", time_taken);*/
	(void)argc;
	(void)argv;
	DatatypeTest();
	JosephusTest( 100, 73);
	printf("\n Enviroment read out\n");
	EnvExercise((const char **)envp);
	return 0;
}
