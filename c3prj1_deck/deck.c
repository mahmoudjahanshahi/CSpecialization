#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  for (int i=0;i<(*hand).n_cards;i++){
    print_card(*(*hand).cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for(int i=0;i<(*d).n_cards;i++){
    if((*(*d).cards[i]).value==c.value && (*(*d).cards[i]).suit==c.suit){
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  for (int i=0; i<200;i++){
    size_t a = rand()%(*d).n_cards;
    size_t b = rand()%(*d).n_cards;
    card_t* tmp = (*d).cards[a];
    (*d).cards[a]=(*d).cards[b];
    (*d).cards[b]=tmp;
  }
}

void assert_full_deck(deck_t * d) {
  int total = 0;
  for (int value = 2; value <= VALUE_ACE; value++){
    for (int suit = SPADES; suit < NUM_SUITS; suit++){
      card_t c;
      c.value = value;
      c.suit = (suit_t)suit;
      total += deck_contains(d,c);
    }
  }
  assert(total == 52);
}
