#include "allocator.c"
#include "utils.c"
#include "vec2.c"

#define INPUT_FILE "day5_input.txt"

typedef enum {HORIZONTAL, VERTICAL, DIAGONAL} Orientation;
typedef struct Line {
  Vec2 start, end;
  Orientation orientation;
} Line;


int main(){
  char * input = read_file(INPUT_FILE);
  Line * lines = alloc(sizeof(Line) * 1000);

  int total_lines = 0;
  while(*input != '\0'){
    Line * l = &lines[total_lines];
    ignore_until_digit(&input);
    consume_int(&l->start.x, &input);
    ignore_until_digit(&input);
    consume_int(&l->start.y, &input);
    ignore_until_digit(&input);
    consume_int(&l->end.x, &input);
    ignore_until_digit(&input);
    consume_int(&l->end.y, &input);

    if(l->start.x == l->end.x){
      l->orientation = HORIZONTAL;
      total_lines++;
    }
    else if(l->start.y == l->end.y){
      l->orientation = VERTICAL;
      total_lines++;
    }
    else{
      l->orientation = DIAGONAL;
      total_lines++;
    }
  }

  int grid[1000][1000] = {0};
  for(int i=0; i < total_lines; i++){
    const Line l = lines[i];
    if(l.orientation == HORIZONTAL){
      int y1 = min(l.start.y, l.end.y);
      int y2 = max(l.start.y, l.end.y);
      for(int y=y1; y <= y2; y++){
        grid[l.start.x][y]++;
      }
    }
    else if(l.orientation == VERTICAL) {
      int x1 = min(l.start.x, l.end.x);
      int x2 = max(l.start.x, l.end.x);
      for(int x=x1; x <= x2; x++){
        grid[x][l.start.y]++;
      }
    }
    else if(l.orientation == DIAGONAL) {
      int inc_x = 1;
      int inc_y = 1;
      if(l.start.x > l.end.x) inc_x = -1;
      if(l.start.y > l.end.y) inc_y = -1;
      int distance = abs(l.end.x - l.start.x);
      int elapsed = 0;
      int x = l.start.x;
      int y = l.start.y;
      while(elapsed <= distance){
        grid[x][y]++;
        x += inc_x;
        y += inc_y;
        elapsed++;
      }
    }
  }

  int overlap_points = 0;
  for(int i=0; i < 1000; i++){
    for(int j=0; j < 1000; j++){
      if(grid[i][j] >= 2) overlap_points++;
    }
  }

  printf("Total lines %d\n", total_lines);
  printf("Overlapping points %d\n", overlap_points);
  return 0;
}
