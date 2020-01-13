#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

/*Find the length of a string and output as an integer				*/
size_t Strlen(const char *string);
/*Compare two strings, returns 1 if str1 is larger, -1 if str2 or 0 if they	*/
/*are the same									*/
int Strcmp(const char *str1, const char *str2); 	 					
/*Copy st1 to str2								*/
char *Strcpy(char *str2, const char *str1);
/*Copy st1 to str2, up to n charcters						*/	
char *Strncpy(char *str2, const char *str1, size_t  n);
/*Convert all characters in a string to lower case				*/
char *StrLowerConvert(char *str);
/*Converts all strings to lower case and then performs a Strcmp			*/	
int Strcasecmp(char *str1, char *str2);
/*Create a pointer to the first instance of a character	in the string 		*/
char *Strchr(char *str, int ch);
/*Duplicate the pointer of the a string						*/	
char *Strdup(char *str);		
/*Append a string onto the destination string					*/
char Strcat(char *dest, const char *src);
/*Append a string onto the destination string up to n chatacers			*/	
char Strncat(char *dest, const char *src, size_t n);
/*Find the first instence of a string within a string and create a pointer to it*/
char *Strstr(char *hay, char *needle);	
/*Find the length of the first instence of a continuos set of characters and 	*/
/*return its length								*/		
size_t Strspn(const char *initial, const char *span);	
/*Separate a string by a deliniator and return the string upto the diliniator	*/
char *Strtok(char *str, const char *delin);
/*Check if a string is a Palindrome, return 1 for yes 0 for no			*/
int IsPalindrome (char *str);		
/*Play a game of Boom 7								*/
void Boom7(int from, int to);	
/*Swap the address of two intergers						*/
void Swap(int **num1, int **num2);	
/*Remove extra white space from a string					*/
void RmSpaces(char *str);		
/*Sum two numbers written as strings						*/
char *StringSum(char *num1, char *num2);	
#endif
