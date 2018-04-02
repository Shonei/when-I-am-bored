//
// Assessment include for Coursework 1.
//
// DO NOT ALTER OR REWRITE ANY OF THESE ROUTINES.
//

// Use an enumerated type for the four suits.
typedef enum { Spades, Diamonds, Clubs, Hearts } cardSuit;

// The items added to the stack are all of type 'card'.
typedef struct {
  cardSuit suit;
  int value;
} card;

// The deck itself.
#define MAX_DECK_SIZE 52
card deck[MAX_DECK_SIZE];

// The current deck size (location of the top card plus one).
int deckSize = 0;

//
// Functions for deck management excluding push, pop and swap.
//

// Print the entire deck.
void printDeck() {
  int i;

  printf("---TOP----\n");
  for (i = deckSize - 1; i >= 0; i--) {
    // Each card output in the format 'value of suit'.
    switch (deck[i].value) {
      case 1:
        printf("Ace");
        break;
      case 11:
        printf("Jack");
        break;
      case 12:
        printf("Queen");
        break;
      case 13:
        printf("King");
        break;
      default:
        printf("%d", deck[i].value);
    }
    printf(" of ");
    switch (deck[i].suit) {
      case Spades:
        printf("spades");
        break;
      case Diamonds:
        printf("diamonds");
        break;
      case Hearts:
        printf("hearts");
        break;
      case Clubs:
        printf("clubs");
        break;
    }
    printf("\n");
  }
  printf("--BOTTOM--\n");

  printf("Total number of items in deck: %d\n", deckSize);
}

// Call just before quitting the program.
// DO NOT MODIFY: Will be altered as part of the assessment and therefore MUST
// BE CALLED.
void finaliseDeck() {
  // Code will be added here for the assessment.
}
