#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "input.h"
#include "deck.h"
#include "future.h"
#include "cards.h"

deck_t* hand_from_string(const char* str, future_cards_t* fc) {
  deck_t* hand = malloc(sizeof(*hand));
  hand->cards = NULL;
  hand->n_cards = 0;
  const char* ptr = str;
  while (*ptr != '\n') {
    char* space = strchr(ptr, ' ');
    if (space == NULL) {
      space = strchr(ptr, '\n');
    }
    if (*ptr == '?') {
      card_t* empty = add_empty_card(hand);
      int index;
      if ((space - ptr) == 2) {
	index = *(ptr + 1) - 48;
      }
      else {
	index = ((*(ptr + 1) - 48) * 10) + (*(ptr + 2) - 48);
      }
      add_future_card(fc, index, empty);
    }
    else {
      card_t c = card_from_letters(*ptr, *(ptr + 1));
      add_card_to(hand, c);
    }
    ptr = space + 1;
  }
  if (hand->n_cards < 5) {
    perror("Less than 5 cards in hand!");
    exit(EXIT_FAILURE);
  }
  return hand;
}

deck_t** read_input(FILE* f, size_t* n_hands, future_cards_t* fc) {
  deck_t** inputs = NULL;
  *n_hands = 0;
  char* line = NULL;
  size_t sz;
  while (getline(&line, &sz, f) >= 0) {
    inputs = realloc(inputs, (*n_hands + 1) * sizeof(*inputs));
    inputs[*n_hands] = hand_from_string(line, fc);
    (*n_hands)++;
    free(line);
    line = NULL;
  }
  free(line);
  return inputs;
}
