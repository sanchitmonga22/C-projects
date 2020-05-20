// C language self test// SWEN-563
// Larry Kiser Jan. 30, 2017
//Sanchit Monga

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "c_language_test.h"
#include "unit_tests.h"

int r=-1;
// return a pointer to the character that is at the passed position.
// return a null if the requested position is past the end of the string.
char *get_pointer_at_position( char *pstring, int position )
{    
  if(position>=strlen(pstring)){
    return NULL;
  }
	return pstring+position ;
}


// Convert array of integer x values into an array of y values using y = mx + b where m and b are constants
// passed to the function. The x values will be replaced by the y values (the x values are overwritten).
// The constants can be positive, negative or zero.
// Return the sum of the y values.
// Return 0 if the passed in px pointer is NULL.
int convert_and_sum( int *px, int m, int b, int number_of_x_values )
{
  if(px==NULL){
    return 0;
  } 
  int sum=0;
  int i;
  for(i=0;i<number_of_x_values;i++){
    *px=(*px*m)+b;
    sum=sum+*px;
    px++;
  }
  return sum ;	
}

// Determine if two pointers point to the same array of numbers
// return 1 if they do, return 0 otherwise.
// return 0 if either pointer is NULL.
int same_array( int *pfirst, int *psecond )
{
  if(pfirst==NULL || psecond==NULL)
    return 0;
  if(sizeof(pfirst)!=sizeof(psecond))
    return 0;
  int i=0;
  while(sizeof(pfirst)>i){
   if(&pfirst[i]!=&psecond[i]){
    return 0;
   }
   i++;
  }
  return 1;
}

// The first time this is called return 1.
// The second time this is called return 0.
// Continue this pattern returning 1, then 0, then 1 and so on.
int bool_flip_flop()
{
  r+=1;
  if(r%2==0){
    return 1;
  }
  return 0;
}

// This function is implemented incorrectly. You need to correct it.
// When fixed it changes the last character in the passed string to 'Z'.
// It returns returns 1 on success.
// It returns 0 on if the passed string is NULL or an empty string.
int fix_bad_code( char *pstring )
{
  if ( &pstring[0]=="" || ! pstring )
    return 0 ; 
  while ( *pstring != '\0' )
    pstring++;
  pstring--;
  *pstring = 'Z' ;
  return 1 ;
}

// value contains a value from a hardware register that has many bit settings.
// bit_position is the value we want selected from value.
// bit_position 0 means get the lowest bit.
// bit_position 1 means get the next lowest bit.
// This function returns 0 if the selected bit is a 0
// It returns 1 if the selected bit is a 1
int get_bit_value( int value, int bit_position )
{
  value=value >> bit_position;
  value &= 1;
  if ( value == 0 ){
    return 0;
  }
  else{
    return 1;
  }
}
