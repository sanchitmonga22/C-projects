// Document Analysis project functions for Part 2
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "analysis.h"
#include "unit_tests.h"

// First checks that p_list is not NULL. Returns 0 if p_list is a NULL pointer.
// Then checks that word pointer is not NULL and word is not any empty string.
// Returns 0 if either of the above tests on the passed word fails.
//
// Creates the list if starting a fresh list.
// Searches existing list for a match on the word. Increments word count
// if found. If not found adds the word in alphabetic order.
// Returns 1 if the word was added successfully.
// Returns 0 on failure.
// NOTE -- this function makes no assumption on upper or lower case. That is handled by read_file.
// For simplicity all words passed from the unit tests are all lower case only.
int process_word ( struct linked_list *p_list, char *word )
{
  if(p_list==NULL || word==NULL || *word=='\0'){// if the conditions are not satisfied
    return 0;
  }else{
    //printf("word is:%s:\n",word);
    if(p_list->p_head==NULL){// if the list is empty initially
      add_node_at_head(p_list,word);
      return 1;// success code of adding the word
    }
    int a=0;
    a=find_word(p_list,word);// finding the word if it already exists in the list
    if(a==1){
      p_list->p_current->one_word.word_count++;// if found then increasing the count 
       return 1;
    }
    else if(a==0){
      int s=add_node_after_current(p_list,word);// adding the word after the current node
      return s;// if the word was added or not
    }
    else{
      return 0;// if the word could not be found and added 
    }
  }
}

// Helper function for read_file to validate inputs.
static FILE *validate_read_file_parameters( struct linked_list *p_list, char *file_name )
{
        if ( p_list == NULL || file_name == NULL || *file_name == '\0' )        // if NULL list or if a bad or empty file name string return 0
                return 0 ;

        return fopen( file_name, "r" ) ;
}

// First checks that the passed string with the file name is not a NULL pointer and is not an empty string.
// Also checks that the passed pointer to the linked_list struct is not a NULL pointer.
// Returns 0 if any of the above tests fail.
// returns 0 if the file cannot be read or if the file does not contain any words as defined for this project.
// returns the number of words if the file was found, opened successfully, and it contained at least one valid word.
// NOTE -- this function MUST convert all words read to lower case only! e.g "First" becomes "first"
int read_file( struct linked_list *p_list, char *file_name )
{
        FILE *input_file = validate_read_file_parameters( p_list, file_name ) ;
        if ( input_file == NULL )
	  return 0 ;
          // Now read and process the entire file.
        char one_char ;// storing the char in the files
        char buffer[ MAX_WORD + 1 ] ;// storing each word in the array
        int i = 0 ;// the index of the array
        int word_count = 0 ;// counting the number of words
	int count=0;
	int extra=0;
	int prev;
        for ( one_char = fgetc( input_file ) ; one_char != EOF ; one_char = fgetc( input_file ) )// going over all the characters in the loop
        {
	  if(one_char==' ' || one_char=='\n' || one_char=='\t'){// if the character is a space, tab or a newline
	    count++;
	  }
	  if((prev==' ' || prev== '\n' || prev=='\t') && (one_char==' ' || one_char=='\t' || one_char=='\n')){
	    extra++;
	  }
	  if(one_char>=65 && one_char<=90){// if it is an Upper case letter
	    buffer[i]=one_char+32;
	    i++;
	  }
	  else if(one_char>=97 && one_char<=122){// if it a lower case letter
	    buffer[i]=one_char;
	    i++;
	  }
	  if(count-extra>0){// if the word is complete
	    count=0;
	    extra=0;
	    word_count++;// increasing the word count
	    buffer[i]='\0';// terminating character of the word
	    process_word(p_list,buffer);// adding the word in the list
	    i=0;
	  }
	  prev=one_char;
	}	  
        // Process all of the characters in the file one at a time.
        fclose( input_file ) ;
        return word_count ;
}

// Returns 0 in the word_count field if the p_list pointer is NULL.
// Returns 0 in the word_count field if no first word meaning p_head == NULL (empty list).
// Otherwise, returns a struct with the first unique word and its number of occurrences in the text file.
struct word_entry get_first_word( struct linked_list *p_list )
{
  struct word_entry entry ;// taking a new word_entry structure
  if(p_list==NULL || p_list->p_head==NULL || p_list->p_current==NULL){// if the list is null or the list is empty
    entry.word_count = 0 ;// then the word count is 0
    entry.unique_word=NULL;
  }
  else{
    entry=p_list->p_head->one_word;// storing the struct at which the head of the list is pointing
  }
  return entry ;// returning the entered node
}

// Returns 0 in the word_count field if p_list is NULL.
// Returns 0 in the word_count field if no next word (previously reached end of list or it is an empty list).
// Otherwise, returns a struct with the next unique word and its number of occurrences in the text file.
struct word_entry get_next_word( struct linked_list *p_list )// this is not working properly as it is not moving to the next word
{
  struct word_entry entry;
  if(p_list==NULL || p_list->p_head==NULL){// if the list is empty of ther is no word in the list
    entry.word_count = 0 ;// then the word count is 0 and unique word is null
    entry.unique_word=NULL;
  }
  else if(p_list->p_current==NULL){// if the next node is null
    entry.word_count=0;// then the word count is 0
    p_list->p_current=p_list->p_tail;// current element should not point to null but should point to the tail
  }
  else{
    entry=p_list->p_current->one_word;// storing the value of the current pointer
    p_list->p_current=p_list->p_current->p_next;// moving the pointer forward
  }
  return entry ;// returning the stored value
}

// Returns 0 in the word_count field if no previous word (was already at beginning of the list or it is an empty list).
// Otherwise, returns a struct with the previous unique word and its number of occurrences in the text file.
struct word_entry get_prev_word( struct linked_list *p_list )
{
  struct word_entry entry ;
  entry.unique_word="";
  if(p_list==NULL || p_list->p_current==p_list->p_head){// if the word is null or the current is at the start
    entry.word_count=0;
  }
  else{
    p_list->p_current=p_list->p_current->p_previous;// pointing to the previous element
    entry=p_list->p_current->one_word;// returnign the value of the previous element
  }
  return entry;
}
// Returns 0 in the word_count field if the p_list pointer is NULL.
// Returns 0 in the word_count field if no last word meaning p_tail == NULL (empty list).
// Otherwise, returns a struct with the last unique word and its number of occurrences in the text file.
struct word_entry get_last_word( struct linked_list *p_list )
{
  struct word_entry entry ;// for storing the value
  if(p_list==NULL || p_list->p_tail==NULL){// for checking the list if empty or not
    entry.word_count = 0 ;
  }
  else{
    entry=p_list->p_tail->one_word;// returning the word at the last element of the list
  }
  return entry ;
}

// First check the p_list is not NULL. Return 0 if it is NULL.
// Return 0 if the list is empty (e.g. p_head is NULL).
// Writes the sorted unique word list to a csv file.
// Receives the linked list pointer and the name of the file to be created.
// Returns 1 on a successful write of the file.
// Returns 0 on any failure.
// Test for a NULL or empty string in the file_name. Return 0 for failure if NULL or empty.
// Be sure to test for failure to open the file, failure to write to the file, and failure to close.
// You must have a header row exactly like this (without the quotes): "word,count"
// You must have one row for each unique word and its count (e.g. without quotes "student,5").
// It must be in sorted order and must be the complete list.
int write_unique_word_list_to_csv_file(  struct linked_list *p_list, char *file_name )
{
	int status = 0 ;
	int total=0;
	if ( p_list == NULL || p_list->p_head == NULL )
		return status ;
	if ( file_name == NULL || *file_name == '\0' )
		return status ;
	FILE *out_file = fopen( file_name, "w" ) ;
	if ( out_file )// if the file is not valid
	{
	  struct word_entry entry;// creating a new structure
	  p_list->p_current=p_list->p_head;// currently the first element is the head
	  while(p_list->p_current!=NULL){// till the end of the list
	    if(p_list->p_current->p_next!=NULL){// if approaching the end of the list
	      entry=get_next_word(p_list);// the next word
	      fprintf(out_file,"%s,%d\n",entry.unique_word,entry.word_count);// writing into the file
	      total+=entry.word_count;
	    }else{// if it is the end of the list
	      entry=get_last_word(p_list);// getting the last word
	      fprintf(out_file,"%s,%d\n",entry.unique_word,entry.word_count);// adding the last word to the list
	      total+=entry.word_count;
	    }
	    p_list->p_current=p_list->p_current->p_next;// moving to the next node
	  }
	  status=1;// status is 1 after adding the words successfully
	  fclose( out_file ) ;
	}
	return status ;
}
