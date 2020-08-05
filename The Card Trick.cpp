/* File: Cardtrick.cpp
 * Programmer:
 * Date:
 * Course: COP 2931
 *
 * Purpose:
 * Write a program that performs a cardtrick. The program will create a
 * random deck of cards, deal them out, pick them up, and determine the
 * secret card.
 *
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdio>

using namespace std;

// Function prototypes
void BuildDeck( int deck[], const int size );
void PrintDeck( int deck[], const int size );
void PrintCard( int card );
void Deal( int deck[], int play[][3] );
void PickUp( int deck[], int play[][3], int column );
void SecretCard( int deck[] );

int main(void)
{
	int column = 0;
	int i = 0;
	const int size = 52;	//size of deck
	
	int deck[52] = {0}; 	//array of deck of cards
	int play[7][3] = {0}; 	//array holds portion of cards to be used for trick
	
	char response; 			//user response
	string name = ""; 		//user's name
	
	bool loop = false; 		//error checking


	cout << "Hello, I am a really tricky computer program and " << endl	//opeing text
		 << "I can even perform a card trick.  Here's how." << endl
		 << "To begin the card trick type in your name: ";
	
	cin >> name;
	name[0] = toupper(name[0]); //Capitalizes name

	cout << endl << "Thank you " << name << endl;

	do
	{
		BuildDeck(deck, size); //Builds deck

		cout << "Ok " + name + ", first things first.  Do you want to see what " << endl //user asks to see deck
			<< "the deck of cards looks like (y/n)? ";

		cin >> response;
		if(response == 'y') 
			{
				PrintDeck(deck, size);
			}
		
		cout << endl << name << " pick a card and remember it..." << endl;

		for(i = 0; i < 3; i++) 	//Starts card trick loop
		{
			Deal(deck, play); 	//deals first 21 cards
			do 					//Loop reads user column choice
			{
				cout << endl <<"Which column is your card in (0, 1, or 2)?: ";

				loop = false;			//resets input check
				if(!(cin >> column)) 	//checks if user inputs a number
				{   
					loop = true;		//forces do while to loop
					cout << "Please enter numbers only: ";
					cin.clear();
					cin.ignore(10000, '\n'); 
				}
			} 	
			while(column < 0 || column > 2 || loop);

			PickUp(deck, play, column); //Picks up dealt cards
		}

		SecretCard(deck); //Reveals user's card

		cout << name << ", would you like to play again (y/n)? ";
		cin >> response;
	} 
	while(response == 'y');

	cout << endl << endl << "Thank you for playing the card trick!" << endl;
	return 0;
}

void BuildDeck( int deck[], const int size)
{
	srand(time(0));		//sets pure random seed
  	int used[52] = {0}; //array holds position of every card to see if it has been selected
  	int card = 0;		//card in deck
	int i = 0;
  	
	while(i < size) 			//loop generates a unique number from 0-51 to represent card
	{

		card = rand() % 52;		//random number generator
		if(used[card] == 0)		//if card hasn't been generated, puts card in deck and marks card has been selected in used[]
		{
			deck[i] = card;
			used[card] = 1;
		}
		else						//if card has been generated, continually generates new cards until finds one that hasn't been generated
		{
			card = rand() % 52;
			while(used[card] == 1)
			{
                card = rand() % 52;
                if(used[card] == 0)
                {
                    deck[i] = card;
                    used[card] = 1;
                    break;
                }
			}
			deck[i] = card;
			used[card] = 1;
		}
        i++; //moves onto next card
	}
	return;
}

void PrintCard( int card )
{
	int rank = 0;
	int suit = 0;
        
		//breaks down deck into 4 sections of 13 cards: 0-12 spades, 13-25 diamonds, 26-38 hearts, 38-51 clubs
		//ACES:
		//first of each section is an Ace: 0, 13, 26, 38
		//FACES:
		//the last 3 of each section are the face cards: 10,23 = J| 11,24 = Q| 12,25 = K, etc.
		//NUMBERS:
		//all cards in between are offset by 1: 1 = rank 2, 2 = rank 3, 3 = rank 4
		//since cards are 2-10, subtracts value of card by their respective section's Ace position, so there distance from Ace is the rank
		//ex: 1 = 2 of Spades: 
			//2 is between 0 and 13 so it is a spade
			//rank = 1-0 => rank = 1, rank+1  = 2 offset is fixed in print statement 

        if(card <= 12)			
        {
            switch (card)
            {
                case 0:
                    suit = 0;
                    rank = 0;
                    break;
                case 10:
                    suit = 0;
                    rank = 10;
                    break;
                case 11:
                    suit = 0;
                    rank = 11;
                    break;
                case 12:
                    suit = 0;
                    rank = 12;
                    break; 
                default:
                    suit = 0;
                    rank = card;
                    break;
            }
        }
        else if(card >= 13 && card <= 25)
        {
            switch (card)
            {
                case 13:
                    suit = 1;
                    rank = 13;
                    break;
                case 23:
                    suit = 1;
                    rank = 23;
                    break;
                case 24:
                    suit = 1;
                    rank = 24;
                    break;
                case 25:
                    suit = 1;
                    rank = 25;
                    break; 
                default:
                    suit = 1;
                    rank = card - 13;
                    break;
            }
        }
        else if(card >= 26 && card <= 38)
        {    
            switch (card)
            {
                case 26:
                    suit = 2;
                    rank = 26;
                    break;
                case 36:
                    suit = 2;
                    rank = 10;
                    break;
                case 37:
                    suit = 2;
                    rank = 11;
                    break;
                case 38:
                    suit = 2;
                    rank = 12;
                    break; 
                default:
                    suit = 2;
                    rank = card - 26;
                    break;
            }
        }
        else if(card >= 39)
        {   
            switch (card)
            {
                case 39:
                    suit = 3;
                    rank = 39;
                    break;
                case 49:
                    suit = 3;
                    rank = 49;
                    break;
                case 50:
                    suit = 3;
                    rank = 50;
                    break;
                case 51:
                    suit = 3;
                    rank = 51;
                    break; 
                default:
                    suit = 3;
                    rank = card - 39;
                    break;
            }
        }

    // Determine the rank of the card and print it out i.e. Queen
        if(rank == 0 || rank == 13 || rank == 26 || rank == 39)
            cout << "Ace ";
        else if(rank == 10 || rank == 23 || rank == 36 || rank == 49)
            cout << "Jack ";
        else if(rank == 11 || rank == 24 || rank == 37 || rank == 50)
            cout << "Queen ";
        else if(rank == 12 || rank == 25 || rank == 38 || rank == 51)
            cout << "King ";
        else
            cout << rank+1 << " "; //fixes offset
	
	// Determine the suit of the card and print it out i.e. of Clubs
        if(suit ==  0)
            cout << "of Spades";
        else if(suit ==  1)
            cout << "of Diamonds";
        else if(suit ==  2)
            cout << "of Hearts";
        else if(suit ==  3)
            cout << "of Clubs";

	return;
}

void PrintDeck( int deck[], const int size )
{
	int i;
	for(i = 0; i < 52; i++) // prints every card in deck
		{
			//Prints cards as their number code
			//cout << deck[i] << " ";

			//Prints cards with their card name
			PrintCard(deck[i]);
			cout << ",  ";
		}
	cout << endl;
}

void Deal( int deck[], int play[][3] )
{
	cout << endl;
    int row = 0, col = 0, card = 0;
    for(int i = 0; i < 21; i+=3)	//loads play with first 21 cards
    {
        for(row = 0; row < 7; row++)
        {
            for(col = 0; col < 3; col++)
            {
                play[row][col] = deck[i];
                i++;
            }
        }
    }

	/* deal cards by passing addresses of cardvalues from
	   the deck array to the play array                   */
	cout << endl;
	cout << "   Column 0           Column 1           Column 2" << endl;
	cout << "======================================================="
		 << endl;
    
     for(int row = 0, col = 0; row < 7; row++, col+=3)			//prints cards out row by row
     {
        int col2 = 0;
        // play[row][col2] = deck[col];
        // play[row][col2+1] = deck[col+1];	
        // play[row][col2+2] = deck[col+2];	

        PrintCard(play[row][col2]);		cout << "           ";
        PrintCard(play[row][col2+1]);	cout << "           ";
        PrintCard(play[row][col2+2]);	cout << "           ";

        cout << endl; 
     }
	return;
}

void PickUp( int deck[], int play[][3], int column )
{
    int tempDeck[52];			//holds a copy of deck
    
    for(int i = 0; i < 52; i++)
    {
        tempDeck[i] = deck[i];	//copies deck into tempdeck[]
    }
        cout << endl;

    switch (column)				//switch contains stacking order based on user's selected column
    {
        case 0:
                for(int j = 0; j < 7; j++)		//puts the first column on deck
                {
                    deck[j] = play[j][1];
                }
      
                for(int j = 0; j < 7; j++)		//puts the selected column second on the deck
                {
                    deck[j+7] = play[j][0];
                }

                for(int j = 0; j < 7; j++) 		//puts the last column last on the deck
                {
                    deck[j+14] = play[j][2];
                }

                for(int g = 21; g < 52; g++)	//fills the rest of the deck with the rest of the cards
                {
                    deck[g] = tempDeck[g];
                }
            break;
        
        case 1:
                for(int j = 0; j < 7; j++)
                {
                    deck[j] = play[j][0];
                }
        
                for(int j = 0; j < 7; j++)
                {
                    deck[j+7] = play[j][1];
                }

                for(int j = 0; j < 7; j++)
                {
                    deck[j+14] = play[j][2];
                }

                for(int g = 21; g < 52; g++)
                {
                    deck[g] = tempDeck[g];
                }
            break;
        
        case 2:
                for(int j = 0; j < 7; j++)
                {
                    cout << play[j][1] << " ";
                    deck[j] = play[j][1];
                }
        
                for(int j = 0; j < 7; j++)
                {
                    cout << play[j][2] << " ";
                    deck[j+7] = play[j][2];
                }

                for(int j = 0; j < 7; j++)
                {
                    cout << play[j][0] << " ";
                    deck[j+14] = play[j][0];
                }

                for(int g = 21; g < 52; g++)
                {
                    deck[g] = tempDeck[g];
                }
            break;
        }
  
	return;
}

void SecretCard( int deck[] )
{
	int card = 0;

	cout << endl <<"Finding secret card..." << endl;
	for(card = 0; card < 10; card++)
	{
		PrintCard(deck[card]);
		cout << endl;
	}

	cout << endl <<"Your secret card is: ";
    PrintCard(deck[card]);
	cout << endl;
	return;
}
