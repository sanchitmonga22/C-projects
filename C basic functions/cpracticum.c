//
// SWEN-250
// Larry Kiser Feb. 13, 2018
// Sanchit Monga

#include <stdlib.h>
#include <stdio.h>
#include "cpracticum.h"
#include "unit_tests.h"

// Create a loop that goes to the end of the passed string that
// counts the number of numeric characters in that string.
// Return that count from this function.
// Numeric characters are all of the characters from 0 through 9.
//
// Return 0 if there are no numeric characters in the string.
// Return 0 if the passed string is an empty string.
// Otherwise, return the number of numeric characters in the string.
//
// You are NOT allowed to use any library functions. You must write
// C code that determines whether or not each character is a numeric character.
// If you wish you can create your own function that determines whether
// or not a character is a numeric character. You could then call that function
// in your loop that searches the string.
int count_number_of_numeric_characters( char mystring[] )
{
  char digits[]={'0','1','2','3','4','5','6','7','8','9'};// creating an array of digits
  int i;// index of the mystring array
  int j;// index of the digits array
  int count=0;// initial count is 0
  for(i=0;mystring[i]!='\0';i++){// loop that goes through each character of mystring
    for(j=0;j<9;j++){// to go through all the digits
      if(mystring[i]!=digits[j] && mystring[i]>=48 && mystring[i]<=57){ // checking whether the given character is a digit or not
	count++;// increasing the count
	break;
      }
    }
  }
  return count;// returning the number of digits
}

// For the passed string you must convert all lower case letters to upper case letters.
// Do no change make any other changes to the array.
// For example a string "ab132 CD==" would become "AB123 CD==".
// The string may be an empty string. If it is empty do nothing.
// Note that this means you are directly changing the characters in the passed string.
// Hint -- per the ASCII code chart an 'a' is 97 decimal and an 'A' is 65 decimal.
//         You can use that difference to convert from lower case to upper case.
void convert_to_upper_case( char mystring[] ){
  int i;// for the index of mystring
  for(i=0;mystring[i]!=EOF;i++){// going through each character of mystring
    if(mystring[i]>= 97 && mystring[i]<=122){// checking whether the character is a lowercase letter 
      mystring[i]=mystring[i]-32;// converting it to the uppercase
    }
  }
}

// This function returns the letter 'L' if the value is < the lower_limit.
// It returns the letter 'M' if the value is >= the lower limit and <= the upper_limit.
// It returns 'H' if the value is > the upper limit.
// You can assume that upper_limit is always > lower_limit.
char range_test( int value, int lower_limit, int upper_limit )
{
  if(value<lower_limit){
    return 'L';
  }
  else if(value>=lower_limit && value<=upper_limit){
    return 'M';
  }
  else// if value is not in the above ranges than it has to be greater thatn the upper_limit as upper_limit is always greater than the lower_limit
    return 'H';
}

// This function is implemented incorrectly. You need to correct it.
// It is supposed to total up the integers in the array.
// The number of entries to add up is the second parameter.
// It returns that sum.
// NOTE -- you are required to correct this code. You are not allowed to completely rewrite it.
//         There are 5 errors in this routine. You must fix all errors. It is possible that the
//         unit tests may pass without all errors being corrected. Be sure that your corrected
//         code does not produce any warnings.
int fix_bad_code( int numbers[], int number_to_add )
{
        int i ;
	int total=0;
	for ( i = 0 ; i<number_to_add ; i++ ) 
		total +=numbers[i] ;
	return  total;
}


// Only runs the unit tests.
int main( int argc, char *argv[] ) {

	// Execute unit tests
	return test() ;
}
