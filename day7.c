#include "allocator.c"
#include "utils.c"
#include <stdio.h>

int get_fuel_usage(int * crabs, int length, int pos){
  int fuel_usage = 0;
  for(int i=0; i < length; i++){
    fuel_usage += abs(crabs[i] - pos);
  }
  return fuel_usage;
}

int get_fuel_usage2(int * crabs, int length, int pos){
  int fuel_usage = 0;
  for(int i=0; i < length; i++){
    int dist = abs(crabs[i] - pos);
    int step = 1;
    for(int j=0; j < dist; j++){
      fuel_usage += step;
      step += 1;
    }
  }
  return fuel_usage;
}

int main(){
  char * input = read_file("day7_input.txt");
  int length = 0;
  int crabs[2000];
  while(*input != '\0'){
    consume_int(&crabs[length], &input);
    ignore_until_digit(&input);
    length++;
  }

  int max = arr_max(crabs, length);
  int min = arr_min(crabs, length);
  printf("Length: %d, Max: %d, Min: %d\n", length, max, min);

  int fuel_usages[2000] = {INT_MAX};
  for(int i=min; i <= max; i++){
    fuel_usages[i] = get_fuel_usage2(crabs, length, i);
  }

  int least_fuel = arr_min(fuel_usages, length);
  printf("The least fuel that can be used is %d\n", least_fuel);
  return 0;
}
