#include <stdio.h>
#include <string.h>

int Strlen(char *string)
{
	int length = 0;
	while (*(string + length) != 0x0)
	{
		++length;
	}

	return (length+1);
}

int Strcmp(char *str1, char *str2)
{
	int len1 = Strlen(str1);
	int len2 = Strlen(str2);
	int tot1 = 0;
	int tot2 = 0;
	int i = 0;
	int j = 0;
	while((i <= len1) || (j <= len2))
	{
		if ((i >= len1) && (j <= len2))
		{
			tot2 += *(str2+j);
		}else if ((i <= len1) && (j >= len2))
		{
			tot1 += *(str1+i);
		}else
		{
			tot1 += *(str1+i);
			tot2 += *(str2+j);
		}
		++i;
		++j;
	}
	if (tot1 > tot2)
	{
		return 1;
	}else if (tot1 < tot2)
	{
		return -1;
	}else if (tot1 == tot2)
	{
		return 0;
	}
}

char *Strcpy(char *str2, char *str1)
{
	str2 = str1;
	return str2;
}

void StrLowerConvert(char *str)
{
	int length = Strlen(str);
	for (int i = 0; i <= length; ++i)
	{
		if ((*(str+i) > 0x40) && (*(str+i) < 0x5b))
		{
			*(str+i) = *(str+i)+0x20;
		}
	
	}
}

int Strcasecmp(char *str1, char *str2)
{
	StrLowerConvert(str1);
	StrLowerConvert(str2);
	int result = Strcmp(str1, str2);

	return result;	
}

char *Strchr(char *str, char *ch)
{
	int length = Strlen(str);
	for (int i = 0; i <= length; ++i)
	{
		if (*(str+i) == *ch)
		{
			return (str+i);
			break;
		}
	}
}

char *Strdup(char *str)
{
	char *output = str;
	return output;
}

void Strcat(char *dest, char *src, int added)
{
	int length = Strlen(dest);
	printf("%d\n", length);
	for (int i = 0; i < added; ++i)
	{
		*(dest+length+i) = *(src+i);
	}
	printf("%s\n", dest);
}

char *Strstr(char *str1, char *str2)
{
	int length = Strlen(str1);
	int i = 0;
	int j = 0;
	while (i <= length;)
	{
		if (*(str1+i) == *(str2+j))
		{
			++j;
		}else
		{
 			j = 0;
		}
	}
}

void main()
{
	char string1[15] = {"QUICK"};
	char string2[] = {"Quick"};
	char *ret;
	
	Strcat(string1, string2, 6);
	//printf("%s %s\n", string1, string2);

}
