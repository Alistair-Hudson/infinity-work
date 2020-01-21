#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

/*Function that opens a file (or creates if not availble), adds strings of 	*/
/*text (before or after another line of text)(from user input), counts the 	*/
/*number of lines used and deletes the file.								*/
/*Errors that are returned are; 404 file not found, permission denied,		*/
/**/
int EditFile(char *filename);
#endif
