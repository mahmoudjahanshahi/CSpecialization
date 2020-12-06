#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int main(int argc, char** argv) {
  if (argc < 2 || argc > 3) {
    perror("Usage: poker inputfile [trials]!");
    return EXIT_FAILURE;
  }
  int trials = 10000;
  if (argc == 3) {
    trials = atoi(argv[2]);
  }
  FILE* f = fopen(argv[1],"r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  size_t n_hands = 0;
  future_cards_t* fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  deck_t** input_hands = read_input(f, &n_hands, fc);
  deck_t* remaining_deck = build_remaining_deck(input_hands, n_hands);
  size_t* win_counts = malloc((n_hands + 1) * sizeof(*win_counts));
  for (size_t i = 0; i < n_hands + 1 ; i++) {
    win_counts[i] = 0;
  }
  for (int i = 0; i < trials; i++) {
    shuffle(remaining_deck);
    future_cards_from_deck(remaining_deck, fc);
    int winner = 0;
    int tie = 0;
    for (size_t j = 1; j < n_hands; j++) {
      if (compare_hands(input_hands[j], input_hands[winner]) > 0) {
	winner = j;
	tie = 0;
      }
      else {
	if (compare_hands(input_hands[j], input_hands[winner]) == 0) {
	  tie = 1;
	}
      }
    }
    if (tie == 1) {
      win_counts[n_hands]++;
    }
    else {
      win_counts[winner]++;
    }
  }
  for (size_t i = 0; i < n_hands; i++) {
    double percent = (double)win_counts[i]/trials * 100;
    printf("Hand %zu won %zu / %d times (%.2f%%)\n", i, win_counts[i], trials, percent);
  }
  printf("And there were %zu ties\n",win_counts[n_hands]);
  for (size_t i = 0 ; i < fc->n_decks ; i++) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);
  for (size_t i = 0; i < n_hands; i++) {
    free_deck(input_hands[i]);
  }
  free(input_hands);
  free_deck(remaining_deck);
  free(win_counts);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
