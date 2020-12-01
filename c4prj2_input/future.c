#include <stdlib.h>
#include <stdio.h>
#include "future.h"

void add_future_card(future_cards_t* fc, size_t index, card_t* ptr) {
  fc->decks[index].cards = realloc(fc->decks[index].cards, (fc->decks[index].n_cards + 1) * sizeof(*fc->decks[index].cards));
  fc->decks[index].cards[fc->decks[index].n_cards] = ptr;
  fc->decks[index].n_cards++;
}

void future_cards_from_deck(deck_t* deck, future_cards_t* fc) {
  for (size_t i = 0; i < fc->n_decks; i++) {
    for (size_t j = 0; j < fc->decks[i].n_cards; j++) {
      fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
      fc->decks[i].cards[j]->value = deck->cards[i]->value;
    }
  }
}
