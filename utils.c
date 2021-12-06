#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

int INDEX(int line, int col, int width){
  return line * width + col;
}

size_t get_file_size(const char * name){
  FILE * f = fopen(name, "r");
  fseek(f, 0, SEEK_END); // seek to end of file
  size_t size = ftell(f); // get current file pointer
  fclose(f);
  return size;
}

char * read_file(const char * name){
  size_t size = get_file_size(name);
  char * buffer = alloc(size+1);

  FILE * f = fopen(name, "r");
  fread(buffer, size, 1, f);
  fclose(f);

  return buffer;
}

bool is_digit(char l){
  return l >= '0' && l <= '9';
}

bool is_hexadecimal(char l){
  return is_digit(l) || l >= 'a' && l <= 'f' || l >= 'A' && l <= 'F';
}

void consume_until(char l, char * buffer, char ** stream){
  while(**stream != l && **stream != '\0'){
    *buffer = **stream;
    buffer++;
    (*stream)++;
  }
  *buffer = '\0';
}

/* Includes tabs and end of line */
void consume_until_whitespace(char * buffer, char ** stream){
  while(**stream != ' ' && **stream != '\t' && **stream != '\n' && **stream != '\0'){
    *buffer = **stream;
    buffer++;
    (*stream)++;
  }
  *buffer = '\0';
}

#define consume_until_cond_m(buffer, stream, cond) do { \
  char * buffer_ptr = buffer; \
  while(*stream != '\0' && (cond)){ \
    *buffer_ptr = *stream; \
    buffer_ptr++; \
    stream++; \
  } \
  *buffer_ptr = '\0'; \
} while(false);

void ignore_until(char l, char ** stream){
  while(**stream != l && **stream != '\0'){
    (*stream)++;
  }
}

/* Includes tabs and end of line */
void ignore_until_whitespace(char ** stream){
  while(**stream != ' ' && **stream != '\t' && **stream != '\n' && **stream != '\0'){
    (*stream)++;
  }
}

void ignore_until_digit(char ** stream){
  while(!is_digit(**stream) && **stream != '\0') {
    (*stream)++;
  }
}

size_t get_file_lines(char * input){
  size_t lines = 0;
  while(*input != '\0'){
    ignore_until('\n', &input);
    if(*input == '\n')  input++;
    lines++;
  }
  return lines;
}

size_t get_file_cols(char * input){
  size_t columns = 0;
  while(*input != '\n' && *input != '\0'){
    input++;
    columns++;
  }
  return columns;
}

typedef struct match_pair {
  char * key;
  int value;
} match_pair;

int match(char * field, match_pair * pairs, int len){
  for(int i=0; i < len; i++){
    if(strcmp(field, pairs[i].key) == 0){
      return pairs[i].value;
    }
  }

  printf("Unknown field read %s\n", field);
  return -1;
}

bool is_one_of(char * field, char * possible[], int len){
  for(int i=0; i < len; i++){
    if(strcmp(field, possible[i]) == 0){
      return true;
    }
  }
  return false;
}

unsigned int count_set_bits(int num){
  unsigned int count = 0;
  while (num) {
    count += num & 1;
    num = num >> 1;
  }
  return count;
}

bool in_array(int v, int * arr, int len){
  for(int i=0; i < len; i++){
    if(v == arr[i]){
      return true;
    }
  }
  return false;
}

void switch_values(int * i, int val1, int val2){
  if(*i == val1){
    *i = val2;
  }
  else if(*i == val2){
    *i = val1;
  }
  else {
    printf("The received value is not one of the two %d\n", *i);
  }
}

void consume_int(int * num, char ** input){
  char number_text[12] = "";
  int idx = 0;
  if(**input == '-' || **input == '+'){
    number_text[0] = **input;
    idx++;
    (*input)++;
  }

  while(**input != '\0' && is_digit(**input)){
    number_text[idx] = **input;
    (*input)++;
    idx++;
  }
  number_text[idx] = '\0';
  *num = atoi(number_text);
}

void consume_int64(int64_t * num, char ** input){
  char number_text[20] = "";
  int idx = 0;
  if(**input == '-' || **input == '+'){
    number_text[0] = **input;
    idx++;
    (*input)++;
  }

  while(**input != '\0' && is_digit(**input)){
    number_text[idx] = **input;
    (*input)++;
    idx++;
  }
  number_text[idx] = '\0';
  *num = atoll(number_text);
}

int arr_max(int * arr, int len){
  int max = INT_MIN;
  for(int i=0; i < len; i++){
    if(arr[i] > max){
      max = arr[i];
    }
  }
  return max;
}

int arr_min(int * arr, int len){
  int min = INT_MAX;
  for(int i=0; i < len; i++){
    if(arr[i] < min){
      min = arr[i];
    }
  }
  return min;
}

void swap(int *a, int *b){
  int tmp = *b;
  *b = *a;
  *a = tmp;
}

void sort_int_array(int * arr, int len){
  bool all_sorted = false;
  while(!all_sorted){
    all_sorted = true;
    for(int i=0; i < len - 1; i++){
      if(arr[i] > arr[i+1]){
        swap(&arr[i], &arr[i+1]);
        all_sorted = false;
      }
    }
  }
}

int max(int a, int b){
  return a > b ? a : b;
}

int min(int a, int b){
  return a < b ? a : b;
}

int abs(int a){
  if(a < 0)  a *= -1;
  return a;
}

float radians_to_degrees(float rad){
  return rad * 180 / M_PI;
}

float degrees_to_radians(float deg){
  return deg * M_PI / 180;
}

void print_bits(uint64_t num)
{
   for(int bit=0;bit<(sizeof(uint64_t) * 8); bit++)
   {
      printf("%li", num & 0x01);
      num = num >> 1;
   }
}
