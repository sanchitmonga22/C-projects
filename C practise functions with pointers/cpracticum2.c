// C pointers with malloc and free
// SWEN-250
// Larry Kiser October 30, 2015
// Larry Kiser updated to summer version July 11, 2017
// Larry Kiser (LLK) updated March 20, 2018
// Sanchit Monga

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cpracticum2.h"
#include "unit_tests.h"
int var=0;
// Determine if the p_unknown pointer points to one of the integers in the  array of integers.
// You need to use num_int_in_array -- this is the number of integers in the p_int_array array.
// return 1 if it does, return 0 otherwise.
// For example, if p_int_array has 3 entries then p_unknown points to one of the integers
// in the array if it points to the first, second, or third entry.
// Hint -- use pointer arithmetic to solve this.
int is_pointer_in_array( int *p_int_array, int *p_unknown, int num_int_in_array )
{
  int i;
  for(i=0;i<num_int_in_array;i++){
    if(p_unknown==p_int_array){
      return 1;
    }
    p_int_array++;
  }
    return 0 ;  // Fix this -- it is incorrect but allows the program to compile and run.
}

// The first time this is called return the first unsigned char in the mylist array.
// The second time this is called return the unsigned char in the mylist array.
// On subsequent calls return the next entry in mylist.
// HOWEVER, after you return the last item in the array the next call must return
// the first element in the array.
unsigned char my_random()
{
  unsigned char mylist[] = { 5, 9, 254, 129, 55, 32, 99, 207 } ;
  int index=var;
  var+=1;
  if (var<sizeof(mylist)){
    return(mylist[index]);
  }
  else{
    var=0;
    return(mylist[var]);
  }
  return 0; 
}

// Using malloc create an array that contains the product of the each element in *p_first with the
// corresponding element in *p_second and store that sum in the corresponding element in the
// returned array of integers.
// e.g. p_result[0] = p_first[0] * p_second[0]; p_result[1] = p_first[1] * p_second[1]
// Note -- this array must be the same size as the passed in arrays.
// Note that you can assume that the p_first and p_second arrays are the same size.
// The third parameter is the number of entries in each array.
// Return NULL if either array pointer is NULL.
// Return NULL if the number of entries is <= 0.
int *create_array_of_products( int *p_first, int *p_second, int number_of_entries )
{  if(p_first==NULL || p_second==NULL || number_of_entries<=0){
    return NULL;
  }
  int *ans=malloc((number_of_entries*4)+1);
  int i;
  int *o_ans=ans;
  for(i=0;i<number_of_entries;i++){
    *ans=(*p_first)*(*p_second);
    ans++;
    p_first++;
    p_second++;
  }
  ans=o_ans;
  return ans ;       
}

// Calculate the total of all of the entries in the passed array and return that total.
// Return a zero if the passed array (pointer) is NULL or the number of entries
// is less than or equal to 0.
// Only free the passed pointer if it is not NULL and the number of entries is greater than 0.
// hint: be sure to free the passed pointer only as described above!
int get_total_and_free( int *p_array, int number_of_entries )
{
  if(p_array==NULL || number_of_entries<=0){
    return 0;
  }
  int i;
  int sum=0;
  for(i=0;i<number_of_entries;i++){
    sum+=*p_array;
    if(p_array!=NULL){
      p_array++;
    }
  }
  return sum;     
}

// This function is implemented incorrectly. You need to correct it.
// When fixed it returns 1 if there are any digits (0 through 9) anywhere in the passed string.
// If there are no digits it returns 0.
// It also returns 0 if the passed string pointer is NULL or if the string points to an empty string.
// You can re-write this code completely if you prefer.
int fix_bad_code( char *pstring )
{
	int result = 0 ;	// is this a good choice for initialization?	
       	if ( ( ( pstring == NULL ) ) || *pstring == '\0'  )
	  return result;
	while (*pstring!='\0'){
	  if (isdigit(*pstring)){	// isdigit returns true if the passed character is a number 0 through 9
	    result=1; 	
	  }
	  pstring++;
	}	
	return result;
}
