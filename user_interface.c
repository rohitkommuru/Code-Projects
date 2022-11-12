#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document.h"
#include <ctype.h>
#include <sysexits.h>

#define QUIT -3
#define INVALID -4

/* Name: Rohit Kommuru
  ID Number: 117999570
  Directory ID: rkommuru
*/

/* Checks if the given line is made up of whitespaces
Returns false if there exists a char that is not a whitespace,
otherwise true */
static int check_blank(char* str) {
  int i = 0, size = strlen(str);
  
  for(i = 0; i < size; i++){
    if(!isspace(str[i]) && str[i] != '\n'){
      return 0;
    }
  }
  return 1;
}
/* parses a string and returns an integer. Returns 
INVALID if there exists a char that is not a number or whitespace,
otherwise returns the integer */
static int parse_int(char* str) {
  int i = 0, size = strlen(str), chr = 0;
  
  sscanf(str," %s",str);
  for(i = 0; i < size; i++) {
    chr = (int)(str[i]);
    if(chr < 48 || chr > 57) {
      return INVALID;
    }
  } 
  return atoi(str);
}

/*Checks if a given line is a valid command. If it is not a valid command, 
the method returns INVALID. If it is valid, the method executes the command.
Returns SUCCESS or FAILURE depending on whether the command was successfully
executed */
static int is_command(Document *doc, char *line, char *cmd, char args[][1024]){
   int first_arg = 0, second_arg = 0, i = 0, arg_num = 0,
   size = 0, spaces_num = 0;
   char read_value[1024];
  
   size = strlen(line);
   strcpy(cmd, "\0");
   if(line[size - 1] == '\n'){
      line[size - 1] = '\0';
      size--;
   }
  /* reads each string in command line until end of string is reached */
  while(sscanf(line + i, " %n%s ", &spaces_num, read_value) != EOF
        && i <= size) {
    if(arg_num == 0){
       strcpy(cmd, read_value);
    } else {
      /* Gets line in add_line_after command */
      if(arg_num == 2 && !strcmp(cmd, "add_line_after")) {
         strcpy(args[arg_num - 1], read_value);
         i += spaces_num + strlen(read_value);
         sscanf(line + i, " %n%s", &spaces_num, read_value);
         strncpy(args[2], line + i + spaces_num, size - (i + spaces_num));
         args[2][size - (i + spaces_num)] = '\0';
         arg_num = 4;
         break;
        /* Gets line in append_line command */
    } else if(arg_num == 1 && !strcmp(cmd, "append_line")) {
         strcpy(args[arg_num - 1], read_value);
         i += spaces_num + strlen(read_value);
         sscanf(line + i, " %n%s", &spaces_num, read_value);
         strncpy(args[1], line + i + spaces_num, size - (i + spaces_num));
         args[1][size - (i + spaces_num)] = '\0';
         arg_num = 3;
         break;
      /* Gets "TARGET" in remove_text command and highlight_text command */
    } else if(arg_num == 1 && (!strcmp(cmd, "remove_text")
              || !strcmp(cmd, "highlight_text"))) {
         char *first_quote = 0, *second_quote = 0;
         
         first_quote = strstr(line + i, "\"");
         if(first_quote != NULL) {
            second_quote = strstr(first_quote + 1, "\"");
            if(second_quote != NULL) {
               strncpy(args[0], first_quote + 1, second_quote - first_quote);
               args[0][second_quote - first_quote - 1] = '\0';
               arg_num = 2;
               break;
            }
         }
         return INVALID;
      /* Gets "TARGET" and "REPLACEMENT" strings in replace_text command */
    } else if(arg_num == 1 && !strcmp(cmd, "replace_text")) {
         char *first_quote = 0, *second_quote = 0, *third_quote = 0,
              *fourth_quote = 0;
        
         first_quote = strstr(line + i, "\"");
         if(first_quote != NULL) {
            second_quote = strstr(first_quote + 1, "\"");
            if(second_quote != NULL) {
               third_quote = strstr(second_quote + 1, "\"");
               if(third_quote != NULL) {
                  fourth_quote = strstr(third_quote + 1, "\"");
                  if(fourth_quote != NULL) {
                     strncpy(args[0], second_quote + 1, 
                             third_quote - second_quote);
                     args[0][third_quote - second_quote - 1] = '\0';
                     if(!check_blank(args[0])) {
                        return INVALID;
                     }
                     strncpy(args[0], first_quote + 1, 
                             second_quote - first_quote);
                     args[0][second_quote - first_quote - 1] = '\0';
                     strncpy(args[1], third_quote + 1,
                             fourth_quote - third_quote);
                     args[1][fourth_quote - third_quote - 1] = '\0';
                     arg_num = 3;
                     break;
                  }
               }
            }
         }
         return INVALID;
    }
    
    if(arg_num > 4){ 
       return INVALID;
    }
    strcpy(args[arg_num - 1], read_value);
    }
    arg_num++;
    i += spaces_num + strlen(read_value);
  }
    /* Checks if all the arguments given for the appropriate command
     are valid and appropriate number of args were given for command.
    If conditions are met,command is executed */
  if(arg_num == 1) {
    if(!strcmp(cmd, "exit") || !strcmp(cmd, "quit")) {
      return QUIT;
    } else if(!strcmp(cmd, "print_document")) {
      return print_document(doc);
    } else if(!strcmp(cmd, "reset_document")) {
      return reset_document(doc);
    }
    
  } else if(arg_num == 2) {
      if(!strcmp(cmd, "add_paragraph_after")) {
        first_arg = parse_int(args[0]);
        if(first_arg >= 0) {
          return add_paragraph_after(doc, first_arg);
        }
      } else if(!strcmp(cmd, "load_file")) {
         return load_file(doc, args[0]);
        
      } else if(!strcmp(cmd, "highlight_text")) {
         return highlight_text(doc, args[0]);
        
      } else if(!strcmp(cmd, "remove_text")) {
         return remove_text(doc, args[0]);
        
      } else if(!strcmp(cmd, "save_document")) {
         return save_document(doc, args[0]); 
      }  
      
  } else if(arg_num == 3) {
      if(!strcmp(cmd, "remove_line")) {
        first_arg = parse_int(args[0]);
        second_arg = parse_int(args[1]);
        if(first_arg > 0 && second_arg > 0) {
           return remove_line(doc, first_arg, second_arg);
        }
      } else if(!strcmp(cmd, "replace_text")) {
          return replace_text(doc, args[0], args[1]);
        
      } else if(!strcmp(cmd, "append_line")) {
          first_arg = parse_int(args[0]);
          if(first_arg > 0 && args[1][0] == '*') {
            return append_line(doc, first_arg, args[1] + 1);
          }
      }
      
  } else if(arg_num == 4) {
      if(!strcmp(cmd, "add_line_after") && args[2][0] == '*') {
        first_arg = parse_int(args[0]);
        second_arg = parse_int(args[1]);
        if(first_arg > 0 && second_arg  >= 0) {
           return add_line_after(doc, first_arg, second_arg, args[2] + 1);
        }
      }
  }
  return INVALID;
}



int main(int argc, char* argv[]) {
  Document doc;
  FILE *input = stdin;
  const char *name = "main_document";
  char filename[1024] = {"\0"}, cmd[1024] = {"\0"}, line[1024] = {"\0"},
        args[5][1024] = {{"\0"}, {"\0"}, {"\0"}, {"\0"}};
  int output = 0, spaces_num = 0;
  
  init_document(&doc, name);
  if(argc == 1) {
     /* If no file was specified in command line, input is set to stdin */
     input = stdin;   
     fprintf(stdout, "> ");
     while(fgets(line, 1024 + 1, input) != NULL) {
        output = 0;
        sscanf(line, " %n%s", &spaces_num, filename);
      
        if(line[spaces_num] != '#' && !check_blank(line)) {
           output = is_command(&doc, line, cmd, args);
        }
      
        if(output == QUIT) {
          break;
        } else if(output == FAILURE) {
          fprintf(stdout, "%s failed\n", cmd);
        } else if (output == INVALID) {
           fprintf(stdout, "Invalid Command\n");
        }
         fprintf(stdout, "> ");
     }
     
   } else if(argc == 2) { 
      /* If file provided, input is set to the file*/
      input = fopen(argv[1], "r");
      if(input == NULL) {
         fprintf(stderr, "%s cannot be opened.\n", argv[1]);
         exit(EX_OSERR);
            
      } else {
          while (fgets(line, 1024 + 1, input) != NULL) {
            output = 0;
            sscanf(line, " %n%s", &spaces_num, filename);
            if(line[spaces_num] != '#' && !check_blank(line)) {
               output = is_command(&doc, line, cmd, args);
              }
              if(output == QUIT) {
                 break;
              } else if(output == FAILURE) {
                  fprintf(stdout, "%s failed\n", cmd);
              } else if (output == INVALID) {
                  fprintf(stdout, "Invalid Command\n");
              } 
         } 
       fclose(input);
       exit(EXIT_SUCCESS);
      }
      
     /* If too many args were given in the command line, outputs 
       the following error message */
   } else {
      fprintf(stderr, "Usage: user_interface\n");
      fprintf(stderr, "Usage: user_interface <filename>\n");
      exit(EX_USAGE);      
   }
  return 0;
}

