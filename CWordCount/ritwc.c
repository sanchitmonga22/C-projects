#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define FALSE (0)
#define TRUE  (1)


int main() {
	int tot_chars = 0 ;	/* total characters */
	int tot_lines = 0 ;	/* total lines */
	int tot_words = 0 ;	/* total words */
	int ch;// for storing the current character in the user input
	int ch1;// for storing the character before to check whether it was a whitespace or not
	int extra=0;// to count the number of extra words that are counted because of whitespaces
	for(ch=getchar();ch!=EOF;ch=getchar()){// reading the input from the user
	  if((ch1==' ' || ch1=='\t' || ch1=='\n') && (ch==' ' || ch=='\t' || ch=='\n')){// checking whether the current character and the character before was a whitespace
	    extra+=1;// increasing the number of extra characters
	  }
	  if(ch=='\n'){// if the character entered is a new line 
	    tot_lines+=1;// increasing the total number of lines
	    tot_chars+=1;// increasing the total number of characters
	    tot_words+=1;// increasing the total number of words
	  }
	  else if(ch==' '){// if the character is a space
	    tot_words+=1;// increasing the number of words
	    tot_chars+=1;// increasing the number of characters
	  }
	  else{
	    tot_chars+=1;
	  }
	  ch1=ch;// storing the previous character to check for the whitespace
	} 
	printf("      %d      %d     %d\n", tot_lines, tot_words-extra, tot_chars);// printing the output in the required format
	/* REPLACE WITH ADDITIONAL VARIABLE DECLARATIONS YOU NEED */
	/* REPLACE WITH THE CODE FOR WORD COUNT */
	return FALSE;
}
