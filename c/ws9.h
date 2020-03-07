#ifndef __WS_9_H__
#define __WS_9_H__

/*Takes int two string locations dest and src								*/
/*size bytes of the src are copied to the dest								*/
void *Memcpy(void *dest, const void *src, size_t size);

/*As with Memcpy but checks to see if there is overlap between the dest and	*/
/*src, to prevent corruption												*/
void *Memmove(void *dest, const void *src, size_t size);

/*Takes a character and copies it size times to dest.						*/
void *Memset(void  *dest, int character, size_t size);

/*Converts an integer to a string, according to the base input				*/
char *Itoa(int value, char *str, int base);

/*Takes an input string and converts to an integer							*/
/*First checks to see if the first character is a '-'						*/
/*Will return 0 if a character other than those from 0-9 are entered else 	*/
/*will return an integer of base 10											*/
int Atoi(const char *str);

/*Checks to see if the computer is Little Endian, returns 1 if true			*/
int IsLittleEndian();

/*Prints the letters that appear in both arr1 and arr2, but do not appear*/ 
/*in arr3																	*/
void PrintLettersofArrays(	const char *arr1, size_t size1, 
							const char *arr2, size_t size2,
							const char *arr3, size_t size3);
#endif
