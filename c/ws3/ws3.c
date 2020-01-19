#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ws3.h"
#include <time.h>

unsigned int AliJosephus(unsigned int number_of_soldiers)
{
	int *regiment = malloc(number_of_soldiers);
	unsigned int survivour = 0;
	unsigned int i = 0;
	int kill = 2;
	int lucky;
	do
	{
		regiment[i] = survivour;
		if ( i == survivour)
		{
			survivour = 1;
		}else
		{
			survivour += kill;
		}
		++i;
	}while(i <= number_of_soldiers);
	lucky = regiment[number_of_soldiers];
	free(regiment);
	return lucky;
}

unsigned int Josephus(unsigned int number_of_soldiers)
{
	unsigned int *regiment = malloc(sizeof(number_of_soldiers)*number_of_soldiers);
	unsigned int i = 0;
	unsigned int next;
	while(i < number_of_soldiers)
	{
		if(i == (number_of_soldiers -1))
		{
			regiment[i] = 0;
		}else
		{
			regiment[i] = i+1;
		}
		++i;
	}
	i = 0;
	do
	{
		next = regiment[i];
		regiment[i] = regiment[next];
		i = regiment[next];
		if(i == next)
		{
			free(regiment);
			return (next+1);
		}

	}while (1);
	free(regiment);
	regiment = NULL;
	return 0;
}
		

void PrintDataTypeSizes()
{
	printf("char is size of %ld\n", sizeof(char));
	printf("int is size of %ld\n", sizeof(int));
	printf("float is size of %ld\n", sizeof(float));
	printf("double is size of %ld\n", sizeof(double));
	printf("void is size of non-existant\n");
}

char *Copy(char *dest, const char *src)
{
	strcpy(dest, src);
	while(*dest)
	{	
		*dest = (char)tolower(*dest);
		++dest;
	}
	return 0;
}

void Print (char *string)
{
	printf("%s \n", string);
}

void EnvExercise(const char **evp)
{
	char **env = (char **)evp;
	char *buffer;
	while(*env)
	{	

		buffer = (char *)malloc(strlen(*env)+1);
		Copy(buffer, *env);		
		Print(buffer);		
		free(buffer);
		buffer = NULL;
		++env;
	}			
}




