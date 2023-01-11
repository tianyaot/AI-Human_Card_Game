// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Card.h"
#include <array>
#include <string>
#include "Pack.h"

  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack(){
  int num=0;
    for(int i=0; i<NUM_SUITS; i++){
      for(int j=7;j<NUM_RANKS; j++){
      cards[num]=Card(RANK_NAMES_BY_WEIGHT[j],SUIT_NAMES_BY_WEIGHT[i]);
      ++num;
      }
    }
   next=0;
}

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream& pack_input){
    std::string rank;
    std::string suit;
    std::string garbage;
    next=0;
    for(int i=0; i<PACK_SIZE; ++i){
      pack_input>>rank>>garbage>>suit;  
      cards[i]=Card(rank,suit);
    }
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one(){
    int num=next;
    ++next;
    return cards[num];
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset(){
    next=0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle(){
    int round=0;
    int zero=0;
    int half=12;
    std::array<Card, PACK_SIZE> card_copy;
    while(round<7){
    for(int i=0; i<24; ++i){
      card_copy[i]=cards[i];
    }
    for(int j=0; j<24; ++j){
      if (j%2==0){
        cards[j]=card_copy[half];
        ++half;
    }else if(j%2==1){
      cards[j]=card_copy[zero];
      ++zero;
    }
    }
    half=12;
    zero=0;
    ++round;
  }
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
    if (next>=24){
      return true;
    }
    return false;
  }
  
