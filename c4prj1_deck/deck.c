#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_hand(deck_t* hand) {
  for (size_t i=0; i < (*hand).n_cards; i++) {
    print_card(*(*hand).cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t* d, card_t c) {
  for (size_t i=0;i<(*d).n_cards;i++) {
    if ((*(*d).cards[i]).value==c.value && (*(*d).cards[i]).suit==c.suit) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t* d) {
  for (size_t i=0; i<(*d).n_cards/2;i++) {
    size_t a = rand()%(*d).n_cards;
    size_t b = rand()%(*d).n_cards;
    card_t* tmp = (*d).cards[a];
    (*d).cards[a]=(*d).cards[b];
    (*d).cards[b]=tmp;
  }
}

void assert_full_deck(deck_t* d) {
  int total = 0;
  for (int value = 2; value <= VALUE_ACE; value++) {
    for (int suit = SPADES; suit < NUM_SUITS; suit++) {
      card_t c;
      c.value = value;
      c.suit = (suit_t)suit;
      total += deck_contains(d,c);
    }
  }
  assert(total == 52);
}

void add_card_to(deck_t* d, card_t c) {
  d->cards = realloc(d->cards, (d->n_cards + 1) * sizeof(*d->cards));
  d->cards[d->n_cards] = &c;
  d->n_cards++;
}

card_t* add_empty_card(deck_t* d) {
  card_t* empty = malloc(sizeof(*empty));
  empty->value = 0;
  empty->suit = 0;
  add_card_to(d, *empty);
  return d->cards[d->n_cards - 1];
}

deck_t* make_deck_exclude(deck_t* excluded_cards) {
  deck_t* d = malloc(sizeof(*d));
  d->cards = NULL;
  d->n_cards = 0;
  for (unsigned i = 0 ; i < 52 ; i++ ) {
    card_t* c = malloc(sizeof(*c));
    *c = card_from_num(i);
    if (deck_contains(excluded_cards, *c) == 1) {
      free(c);
      continue;
    }
    add_card_to(d, *c);
  }
  return d;
}

deck_t* build_remaining_deck(deck_t** hands, size_t n_hands) {
  deck_t excluded_cards;
  excluded_cards.cards = NULL;
  excluded_cards.n_cards = 0;
  for (size_t i = 0; i < n_hands; i++) {
    for (size_t j = 0; j < hands[i]->n_cards; j++) {
      add_card_to(&excluded_cards, *hands[i]->cards[j]);
    }
  }
  deck_t* d = make_deck_exclude(&excluded_cards);
  free(excluded_cards.cards);
  return d;
}

void free_deck(deck_t* d) {
  for (size_t i = 0; i < d->n_cards; i++) {
    free(d->cards[i]);
  }
  free(d->cards);
  free(d);
}
