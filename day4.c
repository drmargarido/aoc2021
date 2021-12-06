#include <stdbool.h>
#include "allocator.c"
#include "utils.c"
#include "list.c"

#define INPUT_FILE "day4_input.txt"
#define MAX_BINGO_CARDS 150

typedef struct BingoCard {
  int numbers[5][5];
  bool marked[5][5];
} BingoCard;

void consume_bingo_card(BingoCard * card, char ** stream){
  int num;
  for(int line=0; line < 5; line++){
    for(int col=0; col < 5; col++){
      ignore_until_digit(stream);
      consume_int(&num, stream);
      card->numbers[line][col] = num;
      card->marked[line][col] = false;
    }
  }
}

bool is_winner_card(BingoCard * card){
  // check lines
  for(int line=0; line < 5; line++){
    bool is_winner = true;
    for(int col=0; col < 5; col++){
      if(!card->marked[line][col]) is_winner = false;
    }
    if(is_winner) return true;
  }

  // check cols
  for(int col=0; col < 5; col++){
    bool is_winner = true;
    for(int line=0; line < 5; line++){
      if(!card->marked[line][col]) is_winner = false;
    }
    if(is_winner) return true;
  }

  return false;
}

void mark_marked_number(BingoCard * card, int number){
  for(int line=0; line < 5; line++){
    for(int col=0; col < 5; col++){
      if(card->numbers[line][col] == number) card->marked[line][col] = true;
    }
  }
}

int unmarked_numbers_sum(BingoCard * card){
  int sum = 0;
  for(int line=0; line < 5; line++){
    for(int col=0; col < 5; col++){
      if(!card->marked[line][col]) sum += card->numbers[line][col];
    }
  }
  return sum;
}

int main(){
  char * input = read_file(INPUT_FILE);

  IntList * numbers = create_ilist(100);
  while(*input != '\n'){
    if(*input == ',') input++;
    int num;
    consume_int(&num, &input);
    ilist_add(numbers, num);
  }
  input++;
  input++;

  int total_cards = 0;
  BingoCard * cards = alloc(sizeof(BingoCard) * MAX_BINGO_CARDS);
  while(*input != '\0'){
    consume_bingo_card(&cards[total_cards], &input);
    total_cards++;
  }

  printf("Total cards %d\n", total_cards);

  int winner = -1;
  int last_number = -1;
  for(int index=0; index < numbers->length; index++){
    int num = ilist_get(numbers, index);
    for(int i=0; i < total_cards; i++){
      mark_marked_number(&cards[i], num);
      if(is_winner_card(&cards[i])){
        winner = i;
        last_number = num;
        goto WINNER_FOUND;
      }
    }
  }

  WINNER_FOUND:
  printf("The winner is %d, with number %d\n", winner, last_number);
  int sum = unmarked_numbers_sum(&cards[winner]);
  printf("The result is %d\n", sum * last_number);


  IntList * not_won_cards = create_ilist(total_cards);
  for(int i=0; i < total_cards; i++){
    ilist_add(not_won_cards, i);
  }

  int last_winner = -1;
  for(int index=0; index < numbers->length; index++){
    int num = ilist_get(numbers, index);
    for(int i=not_won_cards->length - 1; i >= 0; i--){
      int card_index = ilist_get(not_won_cards, i);
      BingoCard * card = &cards[card_index];
      mark_marked_number(card, num);
      if(is_winner_card(card)){
        if(not_won_cards->length == 1){
          last_winner = card_index;
          last_number = num;
          goto LAST_WINNER_FOUND;
        } else {
          ilist_remove(not_won_cards, i);
        }
      }
    }
  }

  LAST_WINNER_FOUND:
  printf("The last winner is %d, with number %d\n", last_winner, last_number);
  sum = unmarked_numbers_sum(&cards[last_winner]);
  printf("The result is %d\n", sum * last_number);

  return 0;
}
