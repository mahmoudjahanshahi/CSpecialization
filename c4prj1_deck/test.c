#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"

int main(void) {
  printf("Hello\n");
  card_t* mycard1 = malloc(sizeof(*mycard1));
  mycard1->value = 14;
  mycard1->suit = HEARTS;
  printf("Card1: ");
  print_card(*mycard1);
  printf("\n");

  card_t* mycard2 = malloc(sizeof(*mycard2));
  mycard2->value = 14;
  mycard2->suit = SPADES;
  printf("Card2: ");
  print_card(*mycard2);
  printf("\n");

  card_t* mycard3 = malloc(sizeof(*mycard3));
  mycard3->value = 14;
  mycard3->suit = CLUBS;
  printf("Card3: ");
  print_card(*mycard3);
  printf("\n");

  deck_t* myhand1 = malloc(sizeof(*myhand1));
  myhand1->n_cards = 0;
  myhand1->cards = NULL;
  add_card_to(myhand1, *mycard1);
  printf("Hand1: ");
  print_hand(myhand1);
  printf("\n");

  deck_t* mydeck1 = make_deck_exclude(myhand1);
  printf("Deck1: ");
  print_hand(mydeck1);
  printf("\n");

  deck_t* myhand2 = malloc(sizeof(*myhand2));
  myhand2->n_cards = 0;
  myhand2->cards = NULL;
  add_card_to(myhand2, *mycard1);
  add_card_to(myhand2, *mycard2);
  add_card_to(myhand2, *mycard3);
  printf("Hand2: ");
  print_hand(myhand2);
  printf("\n");

  deck_t* hands[2];
  hands[0] = myhand1;
  hands[1] = myhand2;
  deck_t* mydeck2 = build_remaining_deck(hands, 2);
  printf("Deck2: ");
  print_hand(mydeck2);
  printf("\n");

  free_deck(mydeck2);
  free_deck(mydeck1);
  free(mycard1);
  free(mycard2);
  free(mycard3);
  free_deck(myhand1);
  free_deck(myhand2);
  return EXIT_SUCCESS;
}

