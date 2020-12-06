#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void* vp1, const void* vp2) {
  const card_t* const* cp1 = (const card_t* const*)vp1;
  const card_t* const* cp2 = (const card_t* const*)vp2;
  if ((*cp1)->value == (*cp2)->value){
    return (*cp2)->suit - (*cp1)->suit;
  }
  else {
    return (*cp2)->value - (*cp1)->value;
  }
}

suit_t flush_suit(deck_t* hand) {
  size_t c = 0;
  size_t d = 0;
  size_t h = 0;
  size_t s = 0;
  for (size_t i = 0; i < hand->n_cards; i++) {
    if (hand->cards[i]->suit == CLUBS) {
      c++;
      if (c >= 5) {
	return CLUBS;
      }
      continue;
    }
    if (hand->cards[i]->suit == DIAMONDS) {
      d++;
      if (d >= 5) {
	return DIAMONDS;
      }
      continue;
    }
    if (hand->cards[i]->suit == HEARTS) {
      h++;
      if (h >= 5) {
	return HEARTS;
      }
      continue;
    }
    if (hand->cards[i]->suit == SPADES) {
      s++;
      if (s >= 5) {
	return SPADES;
      }
      continue;
    }
  }
  return NUM_SUITS;
}

unsigned get_largest_element(unsigned* arr, size_t n) {
  unsigned largest = arr[0];
  for (size_t i = 1; i < n; i++) {
    if (arr[i] > largest) {
      largest = arr[i];
    }
  }
  return largest;
}

size_t get_match_index(unsigned* match_counts, size_t n, unsigned n_of_akind) {
  for (size_t i = 0; i < n; i++) {
    if (match_counts[i] == n_of_akind) {
      return i;
    }
  }
  exit(EXIT_FAILURE);
}

size_t find_secondary_pair(deck_t* hand, unsigned* match_counts, size_t match_idx) {
  for (size_t i = 0; i < hand->n_cards; i++) {
    if (i < match_idx) {
      if (match_counts[i] > 1) {
	return i;
      }
    }
    else if (i >= match_idx + match_counts[match_idx]) {
      if (match_counts[i] > 1) {
	return i;
      }
    }
    else {
      continue;
    }
  }
  return -1;
}

int is_n_length_straight_at(deck_t* hand, size_t index, suit_t fs, int n) {
  size_t counter = 1;
  size_t i = 1;
  size_t j = index;
  if (fs == NUM_SUITS) {
    while ((counter != n) && ((j+i) < hand->n_cards)) {
      if (hand->cards[j+i]->value == hand->cards[j]->value) {
	i++;
	continue;
      }
      if (hand->cards[j+i]->value != (hand->cards[j]->value - 1)) {
	return 0;
      }
      counter++;
      j = j + i;
      i = 1;
    }
  }
  else {
    if (hand->cards[index]->suit != fs) {
      return 0;
    }
    while ((counter != n) && ((j+i) < hand->n_cards)) {
      if ((hand->cards[j + i]->value == hand->cards[j]->value)
	                  ||
	  (hand->cards[j+i]->suit != fs)) {
	i++;
	continue;
      }
      if (hand->cards[j+i]->value != (hand->cards[j]->value - 1)) {
	return 0;
      }
      counter++;
      j = j + i;
      i = 1;
    }
  }
  if (counter == n) {
    return 1;
  }
  else {
    return 0;
  }
}

int is_ace_low_straight_at(deck_t* hand, size_t index, suit_t fs) {
  if (hand->cards[index]->value == VALUE_ACE) {
    int i = 1;
    while ((hand->cards[index + i]->value != 5) && ((index + i) < hand->n_cards-1)) {
      i++;
    }
    if (hand->cards[index+i]->value == 5) {
      return is_n_length_straight_at(hand, (index + i), fs, 4);
    }
  }
  return 0;
}

int is_straight_at(deck_t* hand, size_t index, suit_t fs) {
  if (is_n_length_straight_at(hand, index, fs, 5) == 1) {
    return 1;
  }
  if (is_ace_low_straight_at(hand, index, fs) == 1) {
    return -1;
  }
  return 0;
}

hand_eval_t build_hand_from_match(deck_t* hand, unsigned n, hand_ranking_t what, size_t idx) {
  hand_eval_t ans;
  ans.ranking = what;
  for (size_t i = 0; i < n; i++) {
    ans.cards[i] = hand->cards[idx+i];
  }
  size_t index1 = 0;
  size_t index2 = 0;
  for (size_t j = n; j < 5; j++) {
    if (idx > index1) {
      ans.cards[j] = hand->cards[index1];
      index1++;
    }
    else {
      ans.cards[j] = hand->cards[index1+n+index2];
      index2++;
    }
  }
  return ans;
}

void sortHands(card_t** array, size_t nelements) {
  qsort(array, nelements, sizeof(card_t*), card_ptr_comp);
}

int compare_hands(deck_t* hand1, deck_t* hand2) {
  sortHands(hand1->cards, hand1->n_cards);
  sortHands(hand2->cards, hand2->n_cards);
  hand_eval_t h1 = evaluate_hand(hand1);
  hand_eval_t h2 = evaluate_hand(hand2);
  if (h1.ranking != h2.ranking) {
    return h2.ranking - h1.ranking;
  }
  else {
    for (int i = 0; i < 5; i++) {
      if (h1.cards[i]->value != h2.cards[i]->value) {
	return h1.cards[i]->value - h2.cards[i]->value;
      }
    }
  }
  return 0;
}

unsigned* get_match_counts(deck_t* hand) {
  unsigned* counts = malloc(hand->n_cards * sizeof(*counts));
  unsigned last_value = 0;
  size_t counter = 1;
  for (size_t i = 0; i < hand->n_cards; i++) {
    if (hand->cards[i]->value == last_value) {
      counter++;
      for (size_t j = 1; j < counter; j++) {
	counts[i - j] ++;
      }
      counts[i] = counts[i - 1];
    }
    else {
      counts[i] = 1;
      counter = 1;
    }
    last_value = hand->cards[i]->value;
  }
  return counts;
}

void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}

int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) {
	// assert(hand->cards[i]->value == VALUE_ACE &&
	//       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}

hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { 
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) {
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) {
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {
      ans.cards[4] = hand->cards[2];
    }
    else {
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
