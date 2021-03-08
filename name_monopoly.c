#include "dbg.h"
#include "monopoly.h"
#include <stdio.h>
#include <stdarg.h>


char prompt_yn (const char *question, const char first_choice, const char second_choice, ...)
{
    va_list args;
    va_start(args, second_choice);
    int third_choice = va_arg(args, int);
    va_end(args);  

       
    if (!third_choice)
        fprintf(stdout, "%s [%c/%c]: ", question, first_choice, second_choice);
    else 
        fprintf(stdout, "%s [%c/%c/%c]: ", question, first_choice, second_choice, third_choice);

    char answer[2];
    user_input(answer, sizeof(answer), stdin);
    if (answer == NULL) return 1;
    
    while (answer[0] != first_choice  && answer[0] != second_choice && answer[0] != third_choice) {
        printf("Incorrect answer, type [%c/%c/%c]: ", first_choice, second_choice, third_choice);
        user_input(answer, sizeof(answer), stdin);
    }
    
    return answer[0];
}


char *user_input (char *string, size_t size, FILE *c) 
{ 
  char junkBuffer[128];
  size_t length; 

  // fgets() always returns a null-terminated string
  // As a result, it's useless to call it with a junkBuffer size less than 2
  if (size < 2) return NULL;
 
  // Call fgets()
  if (fgets(string, size, c) == NULL) return NULL;
  
  while (string[0] == '\n' || string[0] == '\0') {  //avoid empty entry
       printf("Put at least one character: ");
       if (fgets(string, size, c) == NULL) return NULL;
  }

  length = strlen(string);
  
  if (length < 1) return NULL;

  // Whole point of this wrapper is to go line-by-line, even
  // if it means disregarding the rest of a given line.
  
   if (string[length - 1] == '\n')
       string[length - 1]  = '\0';
   else {
      fgets(junkBuffer, 128, c);
      length = strlen(junkBuffer);
      while((length > 0) && (junkBuffer[length - 1] != '\n')) {
          fgets(junkBuffer, 128, c);
          length = strlen(junkBuffer);
      }
   }

    return string;
}
