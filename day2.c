#include <stdlib.h>
#include <stddef.h>
#include "allocator.c"
#include "utils.c"

#define INPUT_FILE "day2_input.txt"

int main(){
  char * input = read_file(INPUT_FILE);
  char operation[8];
  int operation_distance;

  int depth = 0;
  int distance = 0;
  int aim = 0;
  while(*input != '\0'){
    consume_until_whitespace(operation, &input);
    input++;
    consume_int(&operation_distance, &input);
    input++;

    if(strcmp(operation, "forward") == 0){
      distance += operation_distance;
      depth += (aim * operation_distance);
    }
    else if(strcmp(operation, "up") == 0){
      aim -= operation_distance;
    }
    else if(strcmp(operation, "down") == 0){
      aim += operation_distance;
    }
  }

  printf("Distance %d, Depth %d: Result %d\n", distance, depth, distance * depth);
  return 0;
}
