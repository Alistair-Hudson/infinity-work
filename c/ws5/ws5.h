#ifndef EDIT_FUNCTIONS_INCLUDED
#define EDIT_FUNCTIONS_INCLUDED

/*Function that opens a file (or creates if not availble), adds strings of 	*/
/*text (before or after another line of text)(from user input), counts the 	*/
/*number of lines used and deletes the file.								*/
/*User provides the name of the file they wish to work with					*/
/*Errors that are returned are; did not open, no string, no input, 			*/
/*not renamed, not removed													*/
int EditFile(char *filename);
#endif
