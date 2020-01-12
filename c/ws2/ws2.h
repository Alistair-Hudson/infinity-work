#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

int Strlen(char *string);		/*Find the length of a string and output as an integer	*/
int Strcmp(char *str1, char *str2); 	/*Compare two strings, 					*/
					/*returns 1 if str1 is larger, -1 if str2 or 0 if they	*/ 						/*are the same						*/
void *Strcpy(char *str2, char *str1);	/*Copy st1 to str2					*/
void *Strncpy(char *str2, char *str1, int n);
void StrLowerConvert(char *str);	/*Convert all characters in a string to lower case	*/
int Strcasecmp(char *str1, char *str2);	/*Compare strings in the same case			*/
char *Strchr(char *str, char *ch);	/*Create a pointer to the first instance of a character */
					/*inthe string						*/
char *Strdup(char *str);		/*Duplicate the pointer of the a string			*/
void Strcat(char *dest, char *src);	/*Append a string onto the destination string		*/
void Strncat(char *dest, char *src, int n);
char *Strstr(char *hay, char *needle);	/*Find the forst instence of a string within a string 	*/
					/*and create a pointer to it				*/
int Strspn(char *initial, char *span);	/*Find the length of the first instence of a continuos	*/
					/*set of characters and return its length		*/
void Strtok();
int IsPalindrome (char *str);		/*Check if a string is a Palindrome, return 1 for yes	*/
					/* 0 for no						*/
void Boom7(int *num1, int *num2);	/*Play a game of Boom 7					*/void Swap(int *num1, int *num2);	/*Swap the address of two intergers			*/
void RmSpaces(char *str);		/*Remove extra white space from a string		*/
nt StringSum(char *num1, char *num2, char *output);	/*Sum two numbers written as strings	*/

#endif
