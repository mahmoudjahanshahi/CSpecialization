#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"

void assert_card_valid(card_t c) {
  assert(c.value>=2 && c.value<= VALUE_ACE);
  assert(c.suit >= SPADES && c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r){
  case STRAIGHT_FLUSH:
    return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND:
    return "FOUR_OF_A_KIND";
  case FULL_HOUSE:
    return "FULL_HOUSE";
  case FLUSH:
    return "FLUSH";
  case STRAIGHT:
    return "STRAIGHT";
  case THREE_OF_A_KIND:
    return "THREE_OF_A_KIND";
  case TWO_PAIR:
    return "TWO_PAIR";
  case PAIR:
    return "PAIR";
  case NOTHING:
    return "NOTHING";
  }
  return "";
}

char value_letter(card_t c) {
  assert_card_valid(c);
  for(int i = 2;i<10;i++){
    if(c.value == i){
      return i+48;
    }
  }
  switch(c.value){
  case 10:
    return '0';
  case VALUE_JACK:
    return 'J';
  case VALUE_QUEEN:
    return 'Q';
  case VALUE_KING:
    return 'K';
  case VALUE_ACE:
    return 'A';
  }
  return ' ';
}

char suit_letter(card_t c) {
  assert_card_valid(c);
  switch(c.suit){
  case SPADES:
    return 's';
  case HEARTS:
    return 'h';
  case DIAMONDS:
    return 'd';
  case CLUBS:
    return 'c';
  case NUM_SUITS:
    return ' ';
  }
  return ' ';
}

void print_card(card_t c) {
  assert_card_valid(c);
  char vl = value_letter(c);
  char sl = suit_letter(c);
  printf("%c%c",vl,sl);
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  for(int i=2; i<10; i++){
    if(value_let == 48+i){
      temp.value = i;
      break;
    }
  }
  if(value_let=='0'){
    temp.value = 10;
  }
  if(value_let=='J'){
    temp.value = VALUE_JACK;
  }
  if(value_let=='Q'){
    temp.value = VALUE_QUEEN;
  }
  if(value_let=='K'){
    temp.value = VALUE_KING;
  }
  if(value_let=='A'){
    temp.value = VALUE_ACE;
  }
  if(suit_let=='s'){
    temp.suit = SPADES;
  }
  if(suit_let=='h'){
    temp.suit = HEARTS;
  }
  if(suit_let=='d'){
    temp.suit = DIAMONDS;
  }
  if(suit_let=='c'){
    temp.suit = CLUBS;
  }
  assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  assert(c<52);
  temp.value = (c % 13)+2;
  temp.suit = (c / 13);
  assert_card_valid(temp);
  return temp;
}
