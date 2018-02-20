//
// Starting code for coursework. Requires "cwk1_extra.h", which should be placed in the same directory.
//
// Compile with (on the school machines):
// gcc -fopenmp -Wall -o cwk1 cwk1.c
// where '-fopenmp' is redundant until OpenMP functionality has been added.
// Alternatively, use the provided makefile (type 'make').
//
// There is an optional command line argument for the number of cards to remove, 'numToRemove'
// (which defaults to zero). See coursework guidance for what needs to be done with this. 
//


//
// Includes
//

// Standard includes.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declarations and functions specific to this coursework.
#include "cwk1_extra.h"
//
// Feel free to read (but not modify) "cwk1_extra.h"; the important parts are:
//
// - An enumerated type for Suits:
// typedef enum { Spades, Diamonds, Clubs, Hearts } cardSuit;
//
// - The structure for a single card:
// typedef struct {
// 	  cardSuit suit;
// 	  int value;
// } card;
//
// - The deck itself as a global array.
// #define MAX_DECK_SIZE 52
// card deck[MAX_DECK_SIZE];
//
// - The current deck size (location of the top card plus one).
// int deckSize;
//
// Routines:
// void printDeck();         // Prints the current deck.
// void finaliseDeck();      // Will be replaced for assessment.
//


//
// Functions for stack management.
//

// Pushes the item to the top of the deck.
void pushCardToDeck( cardSuit suit, int value )
{
	// Make sure we don't already have the maximum number of cards.
	if( deckSize == MAX_DECK_SIZE )
	{
		printf( "Cannot add any more cards - the deck is full!\n" );
		return;
	}

	#pragma omp critical
	{
		// Copy the data over to the card one beyond the current deck size.
		deck[deckSize].suit  = suit;
		deck[deckSize].value = value;

		// Increment the stack counter.
		deckSize++;
	}
}

// Copy one card to another, field by field.
// To copy from i to j call as: copyCard( &deck[i], &deck[j] )
void copyCard( const card *source, card *dest )
{
	dest->value = source->value;
	dest->suit  = source->suit;
}

void swap( card *first, card *second )
{
	card temp = { .value = 0, .suit = Hearts };
	copyCard( first, &temp );
	copyCard( second, first );
	copyCard( &temp, second );
}

void pop()
{
	// deck[deckSize] = NULL;

	// Increment the stack counter.
	#pragma omp atomic
	deckSize--;
}

void shuffle(int iterations)
{
	srand(3);
	int x = rand() % (MAX_DECK_SIZE + 1 - 0) + 0;
	int y = 0;
	int i;
	for(i = 0; i < iterations; i++)
	{
		printf("%d - %d\n", x, y);
		swap(&deck[y], &deck[x]);
		y = x;
		x = rand() % (MAX_DECK_SIZE + 1 - 0) + 0;
	}
}

//
// Main
//
int main( int argc, char** argv )
{
	int i;

	// Optional command line argument; the number of cards to removed (defaults to 0).
	int numToRemove = (argc>=2 ? atoi(argv[1]) : 0 );
	if( numToRemove<0 )
	{
		printf( "Number of cards to remove cannot be negative.\n" );
		return EXIT_FAILURE;
	}

	//
	// Generate a full deck. You need to make pushCardToDeck() thread safe, and make this loop parallel.
	//
	#pragma omp parallel for
	for( i=1; i<=13; i++ )
	{
		pushCardToDeck( Hearts  , i );
		pushCardToDeck( Diamonds, i );
		pushCardToDeck( Spades  , i );
		pushCardToDeck( Clubs   , i );
	}
	printf( "Initial deck:\n" );
	printDeck();
	
	shuffle(60);

	//
	// Remove cards from the deck.
	//
	if( numToRemove>0 )
	{
		// ... (add code to pop numToRemove cards from the deck)
		int i;
		#pragma omp parallel for
		for(i = numToRemove; i > 0; i--)
		{
			pop();
		}
		// Print the deck after the removal. You do not need to parallelise this.
		printf( "\nAfter removal of %d cards:\n", numToRemove );
		printDeck();
	}

	//
	// Clean up and quit.
	//
	finaliseDeck();					// MUST BE CALLED; DO NOT MODIFY OR REPLACE.
	return EXIT_SUCCESS;
}


