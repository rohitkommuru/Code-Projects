/*
Name : Rohit Kommuru
ID: 117999570
Directory ID: rkommuru
*/





#include <stdio.h>
#include <string.h>
#include "document.h"

/* Initializes the given document, gives it the given name */
int init_document(Document * doc, const char *name) {
   
  if (!doc || !name || strlen(name) > MAX_STR_SIZE) {
    return FAILURE;
  }
    
  strcpy(doc->name, name);
  doc->number_of_paragraphs = 0;
  return SUCCESS;
}

 /* Empties the document of all lines and paragraph */
int reset_document(Document * doc) {
  if (!doc) {  
    return FAILURE;   
  }

  doc->number_of_paragraphs = 0;
  return SUCCESS;
}

 /* prints out the document */
int print_document(Document * doc) {
    
  int i = 0, j = 0;
  if(!doc) {
    return FAILURE;
  }
  
  printf("Document name: \"%s\"\n", doc->name); 
  printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);
    
  for (i = 0; i < doc->number_of_paragraphs; i++) {
    Paragraph * para_ptr = &doc->paragraphs[i]; 
    for (j = 0; j < para_ptr->number_of_lines; j++) {    
      if (j == 0) {       
	      printf("%s\n", para_ptr->lines[j]);   
      } else {      
	      printf("%s\n", para_ptr->lines[j]);  
      }   
      if (j == para_ptr->number_of_lines - 1 &&
                 i < doc->number_of_paragraphs - 1) {
     	  printf("\n"); 
      } 
    }
  }
  return SUCCESS;
}

 
 /* adds a paragraph after the given paragraph number */
int add_paragraph_after(Document * doc, int paragraph_number) {

  int i = 0;
  Paragraph para = {0, {"\0"}};
    
  if (!doc || doc->number_of_paragraphs >= MAX_PARAGRAPHS
      || paragraph_number > doc->number_of_paragraphs) {    
    return FAILURE;  
  }
    
 
  if (paragraph_number != doc->number_of_paragraphs) {   
    for(i = doc->number_of_paragraphs; i > paragraph_number; i--) {       
       doc->paragraphs[i] = doc->paragraphs[i - 1];
        }
    }
    
  doc->paragraphs[paragraph_number] = para;   
  doc->number_of_paragraphs++;
  
  return SUCCESS;
}

 /* Adds a line after the specified line number, 
  specified by the given paragraph number in the given document */
int add_line_after(Document * doc, int paragraph_number, int line_number,
                      const char *new_line) {
    
  if (!doc || doc->number_of_paragraphs >= MAX_PARAGRAPHS ||
      doc->paragraphs[paragraph_number - 1].number_of_lines >=
      MAX_PARAGRAPH_LINES || paragraph_number > doc->number_of_paragraphs
      || line_number > doc->paragraphs[paragraph_number - 1].number_of_lines
      || new_line == NULL) {
    return FAILURE;   
  }
    
  if (line_number != doc->paragraphs[paragraph_number - 1].number_of_lines) {     
    int i = 0;   
    Paragraph para_ptr = doc->paragraphs[paragraph_number - 1];  
    
      for (i = para_ptr.number_of_lines; i > line_number; i--) {  
        strcpy(para_ptr.lines[i - 1], para_ptr.lines[i]);
        }
  }
    
  strcpy(doc->paragraphs[paragraph_number - 1].lines[line_number], new_line);
  doc->paragraphs[paragraph_number - 1].number_of_lines++;
    
 
  return SUCCESS;
}

 /* Returns the number of lines in the specified paragraph in the
 given document */
int get_number_of_lines_paragraph(Document * doc, int paragraph_number,
                                     int *number_of_lines) {
    
  if (!doc || number_of_lines == NULL || 
      doc->number_of_paragraphs > MAX_PARAGRAPHS || 
      paragraph_number > doc->number_of_paragraphs) {
      return FAILURE; 
  }
    
  *number_of_lines = doc->paragraphs[paragraph_number - 1].number_of_lines;
    
  return SUCCESS;
}

 
/* appends the given line to the specified paragraph in the given document */
int append_line(Document * doc, int paragraph_number, const char *new_line) {
  int line_num = 0;
  if (!doc || doc->number_of_paragraphs > MAX_PARAGRAPHS ||
      line_num >= MAX_PARAGRAPH_LINES || 
      paragraph_number > doc->number_of_paragraphs || new_line == NULL) {
  return FAILURE;
  }
    
  if (!paragraph_number) {     
    paragraph_number = 1;  
  }
  line_num = doc->paragraphs[paragraph_number - 1].number_of_lines;
 
  strcpy(doc->paragraphs[paragraph_number - 1].lines[line_num], new_line);  
  doc->paragraphs[paragraph_number - 1].number_of_lines++;   
  return SUCCESS;
}

 /* removes the given line specified by the line number from the given 
 document */
int remove_line(Document * doc, int paragraph_number, int line_number) { 

  int i = 0;
  if (!doc || doc->number_of_paragraphs > MAX_PARAGRAPHS || 
      paragraph_number > doc->number_of_paragraphs || 
      doc->paragraphs[paragraph_number - 1].number_of_lines>= 
      MAX_PARAGRAPH_LINES || line_number > 
      doc->paragraphs[paragraph_number - 1].number_of_lines) {
    return FAILURE;
  }
    
  for (i = line_number - 1;
       i < doc->paragraphs[paragraph_number - 1].number_of_lines - 1; i++) {
       
      strcpy(doc->paragraphs[paragraph_number - 1].lines[i],
             doc->paragraphs[paragraph_number - 1].lines[i + 1]);
  }
  strcpy(doc->paragraphs[paragraph_number - 1].lines[
         doc->paragraphs[paragraph_number - 1].number_of_lines - 1],"\0");
  doc->paragraphs[paragraph_number - 1].number_of_lines--; 
  return SUCCESS;
}

 
 /* Adds the number, specified in data_lines, of lines from 
   the data array to the given doc */
int load_document(Document * doc, char data[][MAX_STR_SIZE + 1],
                   int data_lines) {
    
  int j = 0;  
  char *new_line_ptr = NULL;    
  Paragraph * para_ptr = NULL;   
  int new_paragraph_num = doc->number_of_paragraphs;
    
  if (!doc || !data || data_lines == 0) {
    return FAILURE; 
  }
  
  add_paragraph_after(doc, new_paragraph_num);
  para_ptr = &doc->paragraphs[new_paragraph_num];
      
  for (j = 0; j < data_lines; j++) {      
    if (strlen(data[j]) == 0) {
      if(new_paragraph_num >= MAX_PARAGRAPHS) {
        return FAILURE;
      }      
      new_paragraph_num++; 
      add_paragraph_after(doc, new_paragraph_num);       
      para_ptr = &doc->paragraphs[new_paragraph_num]; 
      
    } else {
      new_line_ptr = para_ptr->lines[para_ptr->number_of_lines]; 
      strcpy(new_line_ptr, data[j]);
      para_ptr->number_of_lines++;
        
    }
  }
  return SUCCESS;
}

 
 /* Replaces all instances of the given char
   with the given replacement char in the given document */
int replace_text(Document * doc, const char *target,
                      const char *replacement) {
    
  int i = 0, j = 0, copy_len = 0, target_len = 0;
    
  if (!doc || !target || !replacement) {      
    return FAILURE;  
  }
    
  copy_len = strlen(replacement); 
  target_len = strlen(target);
  if(copy_len > MAX_STR_SIZE || target_len > MAX_STR_SIZE) {
    return FAILURE;
  }
    
  for (i = 0; i < doc->number_of_paragraphs; i++) {   
    Paragraph * para_ptr = &doc->paragraphs[i]; 
    for (j = 0; j < para_ptr->number_of_lines; j++) {  
     
      const char *start = para_ptr->lines[j];    
      const char *ret = start;
      ret = strstr(start, target);
            
      while (ret) {
        char before[MAX_STR_SIZE + 1] = "\0";
        memcpy((void *) before, (void *) start, ret - start);  
        strcpy(para_ptr->lines[j],
               strcat(strcat(before, replacement), ret + target_len));    
        ret += copy_len;      
        ret = strstr(ret, target);
      } 
    } 
  } 
  return SUCCESS;

}

 /* puts the HIGHLIGHT_START_STR and HIGHLIGHT_END_STR around all instances
 of the given document */
int highlight_text(Document * doc, const char *target) {
    
  int i = 0, j = 0, copy_len = 0, target_len = 0;
  if (!doc || !target) {   
    return FAILURE; 
  }
  target_len = strlen(target);
  copy_len =
        target_len + strlen(HIGHLIGHT_START_STR) + strlen(HIGHLIGHT_END_STR);
  if(target_len > MAX_STR_SIZE) {
    return FAILURE;
  }
  for (i = 0; i < doc->number_of_paragraphs; i++) {
    Paragraph * para_ptr = &doc->paragraphs[i];
    
      for (j = 0; j < para_ptr->number_of_lines; j++) {
        const char *start = para_ptr->lines[j];
        const char *ret = start;
        ret = strstr(start, target);
        
        while (ret) {
          char before[MAX_STR_SIZE + 1] = "\0";
          memcpy((void *) before, (void *) start, ret - start);
          strcpy(para_ptr->lines[j],
                 strcat(strcat(strcat(strcat(before, HIGHLIGHT_START_STR),
                 target),HIGHLIGHT_END_STR), ret + target_len));
          ret += copy_len;
          ret = strstr(ret, target);
        } 
      } 
    } 
 return SUCCESS;
}

 /* Removes all instances of the target char from the given document */
int remove_text(Document * doc, const char *target) {
    
  int i = 0, j = 0, target_len = 0;
    
  if (!doc || !target) {
    return FAILURE; 
  }
    
  target_len = strlen(target);
  if(target_len > MAX_STR_SIZE) {
    return FAILURE;
  }
    
  for (i = 0; i < doc->number_of_paragraphs; i++) {
    Paragraph * para_ptr = &doc->paragraphs[i];
    
      for (j = 0; j < para_ptr->number_of_lines; j++) {
        const char *start = para_ptr->lines[j];
        const char *ret = start;
        ret = strstr(start, target);
            
        while (ret) {
          char before[MAX_STR_SIZE + 1] = "\0";
          memcpy((void *) before, (void *) start, ret - start);
          strcpy(para_ptr->lines[j], strcat(before, ret + target_len));
          ret = strstr(start, target);
        } 
      } 
    } 
  return SUCCESS;
}
/* Loads the specified file into the given document */
int load_file(Document *doc, const char *filename) {
  FILE *input;
  char line[MAX_STR_SIZE + 1];
  char *new_line_ptr = NULL;    
  Paragraph * para_ptr = NULL;
  int new_paragraph_num = 0;
  
  if(doc == NULL || filename == NULL || 
     doc->number_of_paragraphs >= MAX_PARAGRAPHS) {
    return FAILURE;
  }
  add_paragraph_after(doc, new_paragraph_num);
  para_ptr = &doc->paragraphs[new_paragraph_num];

  
  if ((input = fopen(filename, "r")) == NULL) {
      return FAILURE;
   } else {
      while (fgets(line, MAX_STR_SIZE + 1, input) != NULL) {    
          int size = strlen(line);
          if(line[size - 1] == '\n'){
             line[size - 1] = '\0';
             size--;
          }     
          if((size == 0 || strspn(line," ") == size)) {
             if(doc->number_of_paragraphs + new_paragraph_num >=
                MAX_PARAGRAPHS) {
                 return FAILURE;
                }  
             new_paragraph_num++;     
             add_paragraph_after(doc, new_paragraph_num);       
             para_ptr = &doc->paragraphs[new_paragraph_num]; 
          } else {
             new_line_ptr = para_ptr->lines[para_ptr->number_of_lines]; 
             strcpy(new_line_ptr, line);
             para_ptr->number_of_lines++;
          }
    
     }
  }
 fclose(input);
 return SUCCESS;
}
 
 
 /* Writes contents of given document into given file */
int save_document(Document *doc, const char *filename) { 
  FILE *output;
  int i = 0, j = 0;
  if(filename == NULL || doc == NULL) {
    return FAILURE;
   }
   
  if ((output = fopen(filename, "w")) == NULL) {
      return FAILURE;
   }
   
  for(i = 0; i < doc->number_of_paragraphs; i++) {
    for(j = 0; j < doc->paragraphs[i].number_of_lines; j++) {
       fputs(doc->paragraphs[i].lines[j], output);
       fputs("\n", output);
    }
    if(i != doc->number_of_paragraphs - 1) {
       fputs("\n", output);
    }
  }
  
  fclose(output);
  return SUCCESS;
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
