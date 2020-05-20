/*
 * Skeleton implementation for the activity to parse and print
 * CSV formatted files read from standard input.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "csv.h"
#include "unit_tests.h"
/*
 * Returns true iff the character 'ch' ends a field. That is, ch is end of file,
 * a comma, or a newline.
 */
bool is_end_of_field(int ch) {
  return (ch == ',') || (ch == '\n') || (ch == EOF) ;// checking whether the given character is a comma, new line or end of file
}

/*
 * Return the minimum of two integers.
 */

int min(int x, int y) {
  return x < y ? x : y ;// returning the minimum of the two numbers
}

/*
 * Read the next field from standard input. Returns the value of getchar() that
 * stopped (terminated) the field.
 */

int get_field(f_string field) {
  int i;// for the index of character in standard input
  int j=0;// to keep track of the index in the field character array
  for(i=getchar();!is_end_of_field(i);i=getchar()){// for loop that take the standard input from the user
    field[j]=i;// storing the standard input in the field array
    j++;// increasing the index of character array by 1 each time a character is added
  }// end of loop
  field[j]='\0';// adding the null character at the end
  return i;// returning the end character of the array
}// end of the function

/*
 * Read in a CSV line. No error checking is done on the number of fields or
 * the size of any one field.
 * On return, the fields have been filled in (and properly NUL-terminated), and
 * nfields is the count of the number of valid fields.
 * nfields == 0 means end of file was encountered.
 */
csv_line get_line(){
  int k;// variable to keep track of the field array in the csv_line fields
  csv_line fields;// variable to store the data in the csv data structure
  fields.nfields=0; // initializing the intial number of nfields to 0 since there is no field
  for(k=get_field(fields.field[fields.nfields]); k!=EOF && k!='\n';k=get_field(fields.field[fields.nfields])){//runs the loop till the field array element is end of field or a newline
    fields.nfields+=1;// increasing the number of fields each time a new field is entered to the array 
  }// end of the for loop
  if(k=='\n')// if the for loop is terminated because of the new line then the field is not counted so include that field we have to add 1 to the number of fields
    fields.nfields+=1;// addding 1 to the number of the elements
  return fields;// returning the field which is a csv_line object
}

/*
 * Print a CSV line, associating the header fields with the
 * data line fields.
 * The minimum of the number of fields in the header and the data
 * determines how many fields are printed.
 */

void print_csv(csv_line header, csv_line data) {
  int minimum=min(header.nfields,data.nfields);// checking the minimum element from the given two integers
  int i;// integer to keep track of the index of the arrays
  for(i=0;i<minimum;i++){// for loop that goes from 0 to the minimum
    printf("%s = %s\n",header.field[i],data.field[i]);// prints the data in the given order.
  }
}

/*
 * Driver - read a CSV line for the header then read and print data lines
 * until end of file.
 */

int main( int argc, char *argv[] ) {
	csv_line header ;
	csv_line current ;

	// LLK additional if statement to execute unit tests if program
	// name contains "test".
	if ( strstr( argv[0], "test" ) )
		return test() ;

	header = get_line() ;
	current = get_line() ;

	while ( current.nfields > 0 ) {
		print_csv(header, current) ;
		current = get_line() ;
	}

	return 0 ;
}
