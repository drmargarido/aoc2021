#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "allocator.c"
#include "utils.c"
#include "list.c"

#define INPUT_FILE "day3_input.txt"
#define TOTAL_BITS 12

int main(){
  char * input = read_file(INPUT_FILE);
  char * cursor = input;

  IntList * list = create_ilist(1000);
  int ones_count[TOTAL_BITS] = {0};
  char number[TOTAL_BITS+1];
  while(*cursor != '\0'){
    consume_until_whitespace(number, &cursor);
    for(int i=0; i < TOTAL_BITS; i++){
      if(number[i] == '1') ones_count[i]++;
    }
    cursor++; // ignore \n
    ilist_add(list, strtol(number, NULL, 2));
  }

  int gama_rate = 0;
  int epsilon_rate = 0;
  int half_total = list->length / 2;
  for(int i=0; i < TOTAL_BITS; i++){
    if(ones_count[i] >= half_total) {
      gama_rate |= 1 << (TOTAL_BITS -1 - i);
    } else {
      epsilon_rate |= 1 << (TOTAL_BITS -1 - i);
    }
  }
  printf("Gama: %d, Epsilon: %d, Power: %d\n", gama_rate, epsilon_rate, (gama_rate * epsilon_rate));

  IntList * most_list = ilist_clone(list);
  for(int i=0; i < TOTAL_BITS; i++){
    int ones = 0;
    for(int n=0; n < most_list->length; n++){
      if(ilist_get(most_list, n) & (1 << (TOTAL_BITS-1-i))){
        ones++;
      }
    }
    int zeros = most_list->length - ones;
    for(int n=most_list->length - 1; n >= 0; n--){
      if(ilist_get(most_list, n) & (1 << (TOTAL_BITS-1-i))){ // 1
        if(ones < zeros) ilist_remove(most_list, n);
      } else { // 0
        if(zeros <= ones) ilist_remove(most_list, n);
      }
    }

    if(most_list->length == 1) break;
  }

  IntList * least_list = ilist_clone(list);
  for(int i=0; i < TOTAL_BITS; i++){
    int ones = 0;
    for(int n=0; n < least_list->length; n++){
      if(ilist_get(least_list, n) & (1 << (TOTAL_BITS-1-i))){
        ones++;
      }
    }
    int zeros = least_list->length - ones;
    for(int n=least_list->length - 1; n >= 0; n--){
      if(ilist_get(least_list, n) & (1 << (TOTAL_BITS-1-i))){ // 1
        if(ones >= zeros) ilist_remove(least_list, n);
      } else { // 0
        if(zeros > ones) ilist_remove(least_list, n);
      }
    }

    if(least_list->length == 1) break;
  }

  int oxigen_generator = ilist_get(most_list, 0);
  int co2_scrubber = ilist_get(least_list, 0);
  printf("Oxigen %d, CO2: %d, Life: %d\n", oxigen_generator, co2_scrubber, (oxigen_generator * co2_scrubber));
  return 0;
}
