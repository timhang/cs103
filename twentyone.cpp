/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Weihang Zhang
 * USC email: weihangz@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

//const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
    //Initializing the deck
    for(int i=0;i<52;i++)
        cards[i]=i;
    int temp,j;
    
    //Shuffling
    for(int i=51;i>0;i--){
        j = rand() %(i+1);
        temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
    
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  /******** You complete ****************/
    //Use remainders and integer division to get the cards
    int typei = ((id+1) % 13)-1;
    int index = ((id+1)/13);
    if ((id+1)%13==0)
        typei = 12;
    cout<<type[typei]<<"-"<<suit[index];

}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/
    int index = ((id+1) % 13)-1;
    if ((id+1)%13==0)
        index = 12;
    return value[index];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
    for(int i=0;i<numCards;i++){
        printCard(hand[i]);
        cout<<" ";
    }
    cout<<endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
    int ans=0,counter=0;
    for(int i=0;i<numCards;i++){
        ans = ans + cardValue(hand[i]);
        if (((hand[i])+1)%13==0)
            counter++; //Ace counter
    }
    
    //Subtracting score by tens if there are aces in hand
    while(counter>0){
        if(ans>21)
            ans = ans - 10;
        counter--;
    }
    return ans;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
    bool flag = true; 
    //Main Loop
    while(flag==true){
    
    //Dealing the first two cards to both people
    shuffle(cards);
    phand[0]=cards[0];
    dhand[0]=cards[1];
    phand[1]=cards[2];
    dhand[1]=cards[3];
    /*for(int i=0;i<25;i++)
        cout<<cards[i]<<" ";*/
    int dealnum = 2,dealscore;
    int playnum = 2,playscore;
    
    //Printing out the initial hands
    cout<<"Dealer: ? ";
    printCard(dhand[1]);
    cout<<endl<<"Player: ";
    printHand(phand,playnum);
    playscore = getBestScore(phand,playnum);
    bool win=true;
    
    //Player's turn
    if(playscore!=21){
    
    cout<<"Type 'h' to hit an 's' to stay:"<<endl;
    string playopt;
    cin>>playopt;
    
    while(playopt=="h"){
        //Dealing cards to player
        playnum++;
        phand[playnum-1]=cards[dealnum+playnum-1];
        playscore = getBestScore(phand,playnum);

        cout<<"Player: ";
        printHand(phand,playnum);
        if(playscore>21){ //Breaking out of loop when busted
            win = false;
            break;
        }
        if(playscore==21) //Breaking out of loop when 21 reached
            break;
        cout<<"Type 'h' to hit an 's' to stay:"<<endl;
        cin>>playopt;
        
    }
    }
    
    
    dealscore=getBestScore(dhand,dealnum);
    //if(dealscore>21)
    if (win==false){ //When player busts
        cout<<"Player busts"<<endl;
        cout<<"Lose "<<playscore<<" "<<dealscore<<endl;
    }
    else //When player score <=21
    {
        //Dealer's turn
        while(dealscore<17){
            dealnum++;
            dhand[dealnum-1]=cards[dealnum+playnum-1];
            dealscore = getBestScore(dhand,dealnum);
        }
        cout<<"Dealer: ";
        printHand(dhand,dealnum);
        
        //Determining the winner
        if(dealscore>21)
            cout<<"Dealer busts"<<endl<<"Win "<<playscore<<" "<<dealscore<<endl;
        if(dealscore<=21 && dealscore>playscore)
            cout<<"Lose "<<playscore<<" "<<dealscore<<endl;
        if(dealscore<=21 && dealscore<playscore)
            cout<<"Win "<<playscore<<" "<<dealscore<<endl;
        if(dealscore<=21 && dealscore==playscore)
            cout<<"Tie "<<playscore<<" "<<dealscore<<endl;
    }
    
    //Repeating
    cout<<endl<<"Play again? [y/n]"<<endl;
    string rep;
    cin>>rep;
    if(rep!="y")
        flag=false;
    
    }
    
    return 0;
}

