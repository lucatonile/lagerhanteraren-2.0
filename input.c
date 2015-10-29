#define _GNU_SOURCE
#include "input.h"
#include "shelf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <ctype.h>


///NY INPUT-implementation



char * read_string_with_buffer(char *buf, size_t len,bool strip_newline){
 
 ssize_t read = getline(&buf, &len, stdin);

  if(read > 0 && strip_newline){
    buf[read-1] = '\0';
  }
  return buf;
}


char *read_string(bool strip_newline){
  return read_string_with_buffer(NULL, 0, true);
}


///VALIDATORS
bool valid_int(char *str){
  bool valid_int = true;
  for(char *c = str; *c && valid_int; ++c){
    valid_int = isdigit(*c);
  }
  return valid_int;
}


bool valid_shelf(char *input){
  return strlen(input) >= 2 && isalpha(input[0]) && valid_int(input+1);
}

bool valid_char(char *str){
  if(strlen(str) > 0) return true; 
  return false;
}


///CONVERTERS
result_t str_to_int(char *str){
  return (result_t) {.int_value = atoi(str)};
}
result_t str_to_str(char *str){
  return (result_t) {.ptr = str};
}

result_t str_to_char(char *str){
  return (result_t) {.char_value = str[0]};
}

result_t str_to_shelf(char *str){
	int amount = Ask_amount();
	return (result_t) {.ptr = shelf_create(str,amount)};
}




result_t ask_question(char *q, v_f validate, m_f convert, bool cleanup){
  char *input = NULL;
  do{
    printf("%s",q);
    if(input) free(input);
    input = read_string(true);
  }while(validate && validate(input) == false);


  result_t result = convert ? convert(input) : (result_t) {.ptr = input};

  if(cleanup) free(input);
  return result;

}



char ask_question_char_with_constraints(char *q,char *s){

	char input = '\0';
	bool ok = false;
	do{
		char input = Ask_char(q);

		for(int i = 0; i < strlen(s); i++ ){
			if(input == s[i]) ok = true;
		}
	}while(!ok);

	return input;
}



