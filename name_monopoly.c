#include "dbg.h"
#include "monopoly.h"
#include <stdio.h>

char *take_input(char *string, size_t size, FILE *c) 
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
