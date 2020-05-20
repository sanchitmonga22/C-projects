// Longest Line activity with limited unit tests
// Based on prior work by SE dept. faculty
// L. Kiser
// Oct. 18, 2015
// LLK updated Feb. 10, 2016 to make arrays MAXLINE + 1 for EOS.
//
// Adds a simple test function and a boolean assert function to
// allow basic unit test. This is intended as a starting point
// for more sophisticated unit testing in C in later activities
// and projects.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>		// LLK addition to support strstr function

#define MAXLINE 80   /* maximum input line size */

/* function declarations */
extern int readline( char line[], int max );
extern void copy( char to[], char from[] );
extern int test( void) ;		// LLK addition for unit testing

/*
 * main:
 *     Print longest input line
 * Note: You may have to declare additional variables.
 */

int main( int argc, char *argv[] ) {		// LLK addition for unit testing
	int len;	       /* current line length */
	char line[MAXLINE + 1];    /* current input line */
	int max=0;// storing the length of the largest line
	char longest_line[MAXLINE+1]="";// initializing an empty string
	//LLK additional if statement to execute unit tests if program
	// name contains "test".
	if ( strstr( argv[0], "test" ) )
		return test() ;
	while ( (len = readline( line, MAXLINE )) > 0 ) {
	  if(len>max){// checking whether the max len greatest or not
	    max=len;// if it is not then assign len to max
	    copy(longest_line,line);// Invoking the copy function to copy the current user input string into the longest_line which stores the string temporarily.
	  }
	}
        	/* Fill in with code to save the longest line using your copy function */	
       	printf("%s\n", longest_line);// printing the largest line
	//return 0; // return success code
}

/*
 * readline:
 *   Read a line into array <s> and return its length.
 *      * The string in <s> must be properly terminated.
 *      * At most <max_chars> are read; excessive characters are
 *        discarded.
 *      * The length returned is the length of the entire
 *        line, not just the piece that is copied.
 *      * A terminating newline ('\n') is *not* copied over.
 *      * If EOF is encountered, return (-1).
 * Note: You may have to declare additional variables.
 */
int readline( char s[], int max_chars ) {
	/* your code here */
  int ch;// for storing each character that user inputs
  int i=0;// for storing the index of the character array
  for(ch=getchar(); ch!=EOF && i<max_chars;ch=getchar()){// loop runs until the end of file
    if(ch=='\n'){// if user hits enter 
      s[i+1]='\0';// '\0' signifies the end of the line
      return i;// returning the length of the line 
    }//end of if
    else{// if the user enters the character
      s[i]=ch;//storing the characters in the array
      i++;// increasing the length by 1 each time a character is entered to the array
     }
    }
  if(ch==EOF){// if the user hits the end of the file command then return a negative number
     return -1;
    }
}

/* copy:
 *    Copy proper C string <from> into <to>
 *    Assume <to> has enough space to hold a copy of <from>.
 * Note: You may have to declare additional variables.
 */
void copy( char to[], char from[] ) {// copying each character to another array of characters
  //	Your code here: (LLK updated)
    int temp;// storing the character temporarily
    int i;// index of the character array
    for(i=0;from[i]!='\0';i++){//the loop runs until it reaches the end of the line
      temp=from[i];// copying each character into another array
      to[i]= temp;
    }
    to[i]='\0';// adding a null character at the end
    //}	//	You CANNOT use any of the string
	//	functions to implement this function.
	//	You MUST use the passed parameters as array.
	//	Do NOT use pointers.  
}

// LLK added simple boolean assert function for unit testing
int assert( int testresult, char error_message[] ) {
	static int test_number = 1 ;
	int result = 1 ;	// return 1 for test passed or 0 if failed
	
	if ( ! testresult ) {
		printf( "%d test failed: %s\n", test_number, error_message ) ;
		result = 0 ;
	}
	return result ;
}

// LLK added unit tests.
int test()
{
	char output_array[MAXLINE + 1] = "" ;	// initialize to empty line to be safe
	char testline1[] = "A" ;	// test single char line
	char testline2[] = "" ;		// test empty line
	char testline3[] = "Typical line to be copied." ;
	char testline4[] = "\n\n\n" ;
	int passcount = 0 ;
	int failcount = 0 ;
	int result ;
	
	printf("\nExecuting unit tests\n") ;
	// first unit test
       	copy( output_array, testline1 ) ;
	if ( assert( !strcmp( output_array, testline1 ), "Unit test for one character string" ) )
		passcount++ ;
	else
		failcount++ ;
	copy( output_array, testline2 ) ;
	if ( assert( !strcmp( output_array, testline2 ), "Unit test for copying empty string" ) )
		passcount++ ;
	else
		failcount++ ;
	copy( output_array, testline3 ) ;
	if ( assert( !strcmp( output_array, testline3 ), "Unit test for typical string" ) )
		passcount++ ;
	else
		failcount++ ;
	copy( output_array, testline4 ) ;
	if ( assert( !strcmp( output_array, testline4 ), "Unit test for string with only newlines" ) )
		passcount++ ;
	else
		failcount++ ;

	printf( "\nSummary of unit tests:\n%d tests passed\n%d tests failed\n\n", passcount, failcount ) ;
	
	return failcount ;
}
