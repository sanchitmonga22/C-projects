
/*
 * Implementation of functions that filter values in strings.
 *****
 * YOU MAY NOT USE ANY FUNCTIONS FROM <string.h> OTHER THAN
 * strcpy() and strlen()
 *****
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "filter.h"

#define NUL ('\0')

/*
 * YOU MAY FIND THIS FUNCTION USEFUL.
 * Return true if and only if character <c> is in string <s>.
 */
static bool includes(char c, char *s) {
	while( *s && c != *s ) {
		s++ ;
	}
	return c == *s ;
  }

/*
 * YOU MAY ALSO FIND THIS FUNCTION USEFUL.
 * Return true if and only if string <pre> is a prefix of string <s>.
 */
static bool prefix(char *s, char *pre) {
	while( *pre && *s == *pre ) {
		s++ ;
		pre++ ;
	}
	return *pre == NUL ;
}

/*
 * Copy <string> to <result> while removing all occurrences of <ch>.
 */
void filter_ch_index(char string[], char result[], char ch) {
  int i=0;// for the index of the string array
  int j=0;// for the index of the result array
  if(string[0]==NUL){// fi the string is empty
    result[0]=NUL;// result is null
  } 
  else{
    for(i=0;string[i]!=NUL;i++){// loop to go over all the characters of the string array
      if(ch!=string[i]){// if the character at that index is equal to ch
	result[j]=string[i];// then copying the character from string into result
	j++;// increasing the index by one after oen character is added
      }
    }
    result[i]=NUL;// null at the end
  }
}

/*
 * Return a pointer to a string that is a copy of <string> with
 * all occurrences of <ch> removed. The returned string must occupy
 * the least possible dynamically allocated space.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *filter_ch_ptr(char *string, char ch) {  
  int i=0;// for the index of string pointer 
  int count=0;// for counting the number of characters needed for the new array
  char *old_string=string;// for storing the intiial position of the pointer
  for(i=*string;i!='\0';i=*string){// going over all the characters of pointer string
    if(i!=ch){// if string is not pointing to same value as ch
      count++;// increasing the count
    }
    *string++;//going to the next value of the pointer
  }
  string=old_string;// initializing back to the original string
  char *result=malloc(count+1);// assigning the dynamic memory to the result
  if(*string==NUL){// if the string isppoitning to null
    *result=NUL;// then the result will point to null
    return result;
  }
  i=0;
  char *old_result=result;// storing the initial position of the pointer
  for(i=*string;i!=NUL;i=*string){// going over the characters
    if(ch!=i){// if not equal to the given character
      *result=*string;// pointing to the same value
      *result++;// moving the pointer to next value
    }
    *string++;// moving the pointer to next value
  }
  result=old_result;// initializing back to the initial position
  return result;// returning the pointer to the first character of the copied string
}

/*
 * Copy <string> to <result> while removing all occurrences of
 * any characters in <remove>.
 */
void filter_any_index(char string[], char result[], char remove[]) {
  int i=0;// pointer for the updatea array
  int j=0;// pointer for the result array
  int k=0;// pointer for the remove array
  int temp;// for storing the character temporarily
  char update[strlen(string)+1];// for storing the result temporarily
  char empty[strlen(string)+1];// for assigning an empty array to the result
  empty[0]=NUL;// assigning the null character to the empty array
  if(string[0]==NUL){// if the string is null then assigning nul to the result
    result[0]=NUL;
  }
  else if(remove[0]==NUL){// if the empty string is an empty array
    strcpy(result,string);// result will be same as the string
  }
  else{
    strcpy(update,string);// initial value of the update will be the original string
    for(k=0;remove[k]!=NUL;k++){// for going over the characters of the remove array
      j=0;// initializing j to 0
      temp=remove[k];
      strcpy(result,empty);// emptying the result everytime to update it
      for(i=0;update[i]!=NUL;i++){// for going over the update string
	if(temp!=update[i]){// if the character is not in the update
	  result[j]=update[i];// updating result
	  j++;// incereasing the index of the result
	}
      }
      result[j]=NUL;
      strcpy(update,result);// assinging the resultant string to the update
    }
  }
}

/*
 * Return a pointer to a copy of <string> after removing all
 * occurrrences of any characters in <remove>.
 * The returned string must occupy the least possible dynamically
 * allocated space.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *filter_any_ptr(char *string, char* remove){
  int size_of_string=strlen(string);// storing the size of the string
  int i=0;// used for index of temp
  int count=0;// counting the number of characters in the new string
  int k=0;// for index of the remove
  char *final=malloc(size_of_string+1);// temporatily using the final pointer to store the value of the final answer
  char *temp=malloc(size_of_string+1);// temporarily storing the value of the string and going over the string again
  char *old_final=final;// storing the initial value of the pointer final 
  char *old_string=string;// storing the initial value of the pointer string
  char *old_remove=remove;// storing the initial value of the pointer remove
  char *old_temp=temp;// storing the initial value of the pointer temp
  strcpy(temp,string);// copying the string into temp for temporarily user
  for(k=*remove;k!=NUL;k=*remove){// for going over the remove pointer
    memset(final,0,size_of_string+1);// initializing all the values of final pointer to null
    old_final=final;// storing the initial value of the pointer in the old_final
    count=0;// count is 0
    for(i=*temp;i!=NUL;i=*temp){// for going over the character in the temp
      if(k!=i){// checking if the characters are equal or not
	*final=i;// storing the value of characters in the final
	count++;// counting the number of elements
	*final++;// moving the pointer to the next value
      }
      *temp++;// moving to the next pointer in temp
    }
    if(*remove++ !=NUL){// if remove is null 
      final=old_final;// initializing final back to the final
      strcpy(temp,final);// copying and storing the value of final in temp and updating temp everytime
    }
    else if(*remove++==NUL){
      *final=NUL;// adding NUL at the end
      final=old_final;
    }
  }
  remove=old_remove;// initialzing the remove back to its original value
  temp=old_temp;// reinitialzing temp to its original position
  char *result=malloc(count+1);// final result is created
  if(*string==NUL){
    *result=NUL;
    free(final);// freeing the dynamic memory before returning
    free(temp);
    return result;
  }
  if(*remove==NUL){
    strcpy(result,string);// if remove is empty then the copy of string is returned
    free(final);// freeing the dynamic memory before returning
    free(temp);
    return result;
  }
  strcpy(result,final);//copying the final into result 
  free(final);// freeing the dynamic memory before returning the result
  free(temp);
  return result;
}

/*
 * Return a pointer to a copy of <string> after removing all
 * occurrrences of the substring <substr>.
 * The returned string must occupy the least possible dynamically
 * allocated space.
 *****
 * YOU MAY *NOT* USE ARRAY INDEXING.
 *****
 */
char *filter_substr(char *string, char* substr) {
 char *old_substr=substr;// storing the initial pointer position of substr
  int i=0;// for the index of string
  int j=0;// for the index of substr
  int length=strlen(substr);// length of the substr
  int size_of_string=strlen(string);
  int count=0;// counting the number of characters in string
  int num=0;// to count the number of substrings in the string
  char *old_string=string;// storing the initial value of the string
  /*
    Calculating the number of substring in the given string and then creating the variable with dynamic memory according to that
   */
  for(i=*string;i!=NUL;i=*string){// loop for string
    char *old_string1=string;// storing the initial pointer value of the string
    for(j=0;j<length;j++){// loop for going over the substr and string
      if(*string==*substr){// if the pointers are poiting towards the same value
	*substr++;// increasing the substr
	*string++;// increasing the string
	count++;// counting the matching characters
      }
    }
    string=old_string1;// initialzing it back to the initial value
    substr=old_substr;// initializing to the initial value
    if(count==length){// if they have the same length
      num++;// counting the number of substrings
    }
    count=0;// initially count=0
    *string++;// increasing the string
  }
  char *result=malloc(size_of_string-length*num+1);// creating the variable with dynamic memory
  char *final=malloc(size_of_string+1);// a temporary variable for storing the value of the final answer
  char *temp=malloc(size_of_string+1);// a temporary variable for storing the value of the string
  char *old_final=final;// storing the initial value of the pointer
  char *old_temp=temp;// initial pointer of temp
  string=old_string;// initializing the string back to its original value
  strcpy(temp,string);// making a copy of string and storing it in temp
  if(*temp==NUL){// if the string is null
    *result=NUL;// then the result is null
    return result;
  }
  /*
    Now extracting and removing the substr from string and creating a new string without the occurences of substr
   */
  for(i=*temp;i!=NUL;i=*temp){// going over the string characters
    if(i!=*substr){// if the character does not match the character of a substr
      *final=*temp;// if the characters are not equal then adding it to the final string
      *temp++;//moving the temp pointer to the next point
      *final++;// moving the final pointer to the next point
    }else if(strlen(temp)>=length){// if the length of the temp is greater than length then the pointer will go out of bounds
      char *old_temp=temp;// storing the initial value of the temp
      count=0;// count is zero for every new iteration
      for(j=0;j<length;j++){// going over the length of the substr 
	if(*temp==*substr){// if temp elements are equal to the substr elements
	  *substr++;// moving the substr pointer to the next element
	  *temp++;// moving the temp pointer to the next element
	  count++;// moving the count pointer to the next element
	}
      }
      substr=old_substr;// reinitializing the substr to its initial value
      if(count!=length){// if the count is not equal to the length then there is on substr in the string till that point
	temp=old_temp;// reinitializing the value of temp back to the original value
	*final=*temp;
	*final++;// moving the final to next pointer
	*temp++;// moving the temp to the next pointer
      }
    }
    else{
      *final=*temp;
      *final++;
      *temp++;
    }
  }
  *final=NUL;// adding the nul element at the end
  final=old_final;// initializing back to its original value
  strcpy(result,final);// copying the elements of the final into the result
  free(final);
  temp=old_temp;// initialzing back to its original value
  free(temp);// freeing the dynamic memory before returning
  return result;
}
