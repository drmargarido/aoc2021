#include "allocator.c"
#include "utils.c"
#include <stddef.h>

#define INPUT_FILE "day6_input.txt"

typedef struct FishGroup {
  int days;
  int64_t size;
} FishGroup;

void process_day(FishGroup * list, int * total_groups){
  int64_t fishes_to_add = 0;
  for(int i=0; i < *total_groups; i++){
    if(list[i].days == 0){
      fishes_to_add += list[i].size;
      list[i].days = 6;
    } else {
      list[i].days--;
    }
  }
  list[*total_groups].size = fishes_to_add;
  list[*total_groups].days = 8;
  (*total_groups)++;
}

int main(){
  char * input = read_file(INPUT_FILE);
  FishGroup * list = alloc(sizeof(FishGroup) * 1000);
  int total_groups = 0;
  while(*input != '\0'){
    consume_int(&list[total_groups].days, &input);
    list[total_groups].size = 1;
    total_groups++;
    ignore_until_digit(&input);
  }

  const int total_days = 256;
  for(int i=0; i < total_days; i++){
    process_day(list, &total_groups);
  }

  int64_t total_fishes = 0;
  for(int i=0; i < total_groups; i++){
    total_fishes += list[i].size;
  }
  printf("Total Fishes %ld\n", total_fishes);
  return 0;
}
