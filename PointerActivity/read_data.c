/*
 * Implementation of the read_data module.
 *
 * See read_data.h for a description of the read_data function's
 * specification.
 *
 * Note that the parameter declarations in this module must be
 * compatible with those in the read_data.h header file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "read_data.h"

// Reads the three fields from lines such as W$1349$1.414$ into
// local variables using getchar().
// Converts the two numeric fields to numbers using atoi for the
// integer fields and atof for the double.
// Using a correctly defined set of parameters (use pointers) pass
// those values back to the program that called this function.
void read_data(char *ch, int *num, double *num1) {
  int ch1;// for storing each character from the standard input
  int i=0;// for the index of the character array of integer and the double number
  char num2[25];// for storing the integer value
  int count=0;// for counting the number of $ signs
  char num3[25];// for storing the double value
  char ab=getchar();// taking the first character from the standard input
  *ch=ab;// deferencing and assigning the address to the character ab
  int ch_no_use=getchar();// character of no use. A $ sign that is of no use
  for(ch1=getchar();count!=1;ch1=getchar()){// for taking the input of integer from the standard input
    if(ch1=='$'){// if the given character is a $
      break;
    }
    num2[i]=ch1;// adding the characters in a character array 
    i+=1;// increasing the index of character array
  }
  int num4=atoi(num2);// converting the character array of number into an integer and storing it in a number
  *num=num4;// deferencing the num to the address of the number
  count=0;// initially count=0  
  i=0;// and the index of array is also 0
  for(ch1=getchar();count!=1;ch1=getchar()){// for taking the input of the double from the standard input
    num3[i]=ch1;// storing the double number in the character array
    i+=1;// increasing the index by 1
    if(ch1=='$'){// if the ch is a $
      break;
    }
  }
  double num5=atof(num3);// storing the double format characters into a new variable
  *num1=num5;// deferencing the num1 to the double number
  return ;
}
