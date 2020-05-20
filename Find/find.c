/*
 * Implementation of functions that find values in strings.
 *****
 * YOU MAY NOT USE ANY FUNCTIONS FROM <string.h>
 *****
 */

#include <stdlib.h>
#include <stdbool.h>

#include "find.h"

#define NOT_FOUND (-1)	// integer indicator for not found.

/*
 * Return the index of the first occurrence of <ch> in <string>,
 * or (-1) if the <ch> is not in <string>.
 */
int find_ch_index(char string[], char ch) {
  int i;// for the index of the characters in the given string
  for(i=0;string[i]!='\0';i++){// for going over all the characters in the given string
    if(string[i]==ch){// if the characters in the string is equal to the given string
      return i;// returning the index
    }
  }
  return NOT_FOUND ;// returning if not found
}

/*
 * Return a pointer to the first occurrence of <ch> in <string>,
 * or NULL if the <ch> is not in <string>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_ch_ptr(char *string, char ch) {
  int i;// for moving the pointer forward
  for(i=*string;i!='\0';i=*string){// for moving the pointer forward and accessing the next character
    if(i==ch){// if the string pointer is pointing to the same character
      return string;// returning the pointer
    }
    *string++;// pointing the pointer to the next character
  }
  return NULL ;// returning null if not found
}

/*
 * Return the index of the first occurrence of any character in <stop>
 * in the given <string>, or (-1) if the <string> contains no character
 * in <stop>.
 */
int find_any_index(char string[], char stop[]) {
  int i=0;// for the index of the stop array
  int j=0;// for the index of the string array
  if(stop[i]=='\0'){// if it is empty then returning not found
    return NOT_FOUND;
  }
  for(i=0;string[i]!='\0';i++){// for going over the characters of stop array
    for(j=0;stop[j]!='\0';j++){// for going over the characters of string array
      if(string[i]==stop[j]){// checking if there is any same character in both the arrays
	return i;// returning the index of the first matching character
      }
    }
  }
  return NOT_FOUND ;// if not found returning not found character
}

/*
 * Return a pointer to the first occurrence of any character in <stop>
 * in the given <string> or NULL if the <string> contains no characters
 * in <stop>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_any_ptr(char *string, char* stop) {
  int i=0;// for the stop pointer
  int j=0;// for the string pointer
  if(*stop=='\0'){// if empty then returing null
    return NULL;
  }
  char *oldstop=stop;// storing the initial pointer of the stop
  for(i=*string;i!='\0';i=*string){// for increasing the pointer to point to the next character in stop
    for(j=*stop;j!='\0';j=*stop){// for increasing the pointer to point to the next character in string
      if(i==j){// if the value they are pointing are same
	return string;// returning the pointer index for the string
      }
      *stop++;// moving the pointer to next character
    }
    stop=oldstop;// reinitialzing the character
    *string++;// moving the pointer to next character
  }
  return NULL ;// if not found
}

/*
 * Return a pointer to the first character of the first occurrence of
 * <substr> in the given <string> or NULL if <substr> is not a substring
 * of <string>.
 * Note: An empty <substr> ("") matches *any* <string> at the <string>'s
 * start.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_substr(char *string, char* substr) {
  if(*substr=='\0'){// if the substr is empty then returning the pointer of first character of the string
    return string;// returning the pointer of first character
  }
  char *old_substr=substr;// storing the initial pointer position of substr
  int i=0;// for the index of string
  int j=0;// for the index of substr
  int length=0;// length of the substr
  int count=0;// counting the number of characters in string
  for(j=*substr;j!='\0';j=*substr){// calculating the length of the substr
    length++;// increasing the length for every character
    *substr++;
  }
  substr=old_substr;// changing the pointer to the original position
  j=0;
  for(i=*string;i!='\0';i=*string){// loop for string
    char *old_string=string;// storing the initial pointer value of the string
    for(j=0;j<length;j++){// loop for going over the substr and string
      if(*string==*substr){// if the pointers are poiting towards the same value
	*substr++;// increasing the substr
	*string++;// increasing the string
	count++;// counting the matching characters
      }
    }
    string=old_string;// initialzing it back to the initial value
    substr=old_substr;// initializing to the initial value
    if(count==length){
      return string;
    }
    count=0;// initially count=0
    *string++;// increasing the string
  }
  return NULL ;	//if the substr does not exist in string
}
