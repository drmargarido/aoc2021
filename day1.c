#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include "allocator.c"
#include "utils.c"

#define INPUT_FILE "day1_input.txt"

int main(){
  char * cursor = read_file(INPUT_FILE);

  int larger_count = 0;
  int num1=-1, num2=-1, num3=-1;
  int last_num1=-1, last_num2=-1, last_num3=-1;
  while(*cursor != '\0'){
    num3 = num2;
    num2 = num1;
    consume_int(&num1, &cursor);
    bool is_window_ready = last_num1 != -1 && last_num2 != -1 && last_num3 != -1;
    int num_sum = num1 + num2 + num3;
    int last_num_sum = last_num1 + last_num2 + last_num3;
    if(is_window_ready && num_sum > last_num_sum){
      larger_count++;
    }

    last_num3 = num3;
    last_num2 = num2;
    last_num1 = num1;
    cursor++; // jump \n
  }

  printf("Larger Count: %d\n", larger_count);
  return 0;
}
