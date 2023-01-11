// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Card.h"
#include <string>
#include <vector>
#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <array>
#include <algorithm>



class Simple : public Player{
  private:
  std::string name;
  std::vector<Card>hand;

  public:
  Simple(const std::string &name_in):name(name_in){}

//EFFECTS returns player's name
  virtual const std::string & get_name() const{
    return name;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  virtual void add_card(const Card &c){
    if (hand.size()<MAX_HAND_SIZE){
      hand.push_back(c);
    }
    std::sort(hand.begin(), hand.end());
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  virtual bool make_trump(const Card &upcard, bool is_dealer,
      int round, std::string &order_up_suit) const{
      std::string Queen=Card::RANK_QUEEN;std::string King=Card::RANK_KING;
      std::string Ace=Card::RANK_ACE; std::string trump=upcard.get_suit();
      std::string same_color=Suit_next(trump);
      int good1=0;int good2=0;
     if (round==1){ 
      for(int i=0; i<MAX_HAND_SIZE; ++i){
        if((hand[i].is_left_bower(trump))||(hand[i].is_right_bower(trump))
        ||((hand[i].get_rank()==Queen)&&(hand[i].get_suit()==trump))|| 
          ((hand[i].get_rank()==King)&&(hand[i].get_suit()==trump))||
          ((hand[i].get_rank()==Ace)&&(hand[i].get_suit()==trump))){
            ++good1;}}
        if(good1>=2){
          order_up_suit=trump;return true;
        }else{return false;}}
      if (round==2){
        for (int i=0; i<MAX_HAND_SIZE; ++i){
        if((hand[i].is_left_bower(same_color))||
        (hand[i].is_right_bower(same_color))||
        ((hand[i].get_suit()==same_color)&&(hand[i].get_rank()==Queen))||
        ((hand[i].get_suit()==same_color)&&(hand[i].get_rank()==King))||
         ((hand[i].get_suit()==same_color)&& (hand[i].get_rank()==Ace))){
          ++good2;
        }}
     if((good2>=1)||(is_dealer)){
      order_up_suit=same_color;return true;}
      else{return false;
     }}return 1;}
    
    

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  virtual void add_and_discard(const Card &upcard){
      hand.push_back(upcard);
    std::string trump_suit=upcard.get_suit();
    int removal=0;
    for (int i=0; i<hand.size(); ++i){
      if(!(Card_less(hand[removal], hand[i], trump_suit))){
        removal=i;
      }
  }
      hand.erase(hand.begin()+removal);
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  virtual Card lead_card(const std::string &trump){
      int highest1=0;
      int highest2=0;
      Card removal1;
      Card removal2;
      int test=0;
      for(int i=0; i<hand.size(); ++i){
        if(hand[i].get_suit(trump)!=trump){
          test=1;
        }
      }
      
if(test==1){
    removal2=hand[0];
    for(int k=1; k<hand.size(); ++k){
      if((operator<(hand[highest2],hand[k])) && 
      (hand[k].get_suit(trump)!=trump)){
        highest2=k;
      }
}
    Card removal2=hand[highest2];
    hand.erase(hand.begin()+highest2);
    return(removal2);
  }else if(test==0){
    for(int j=0; j<hand.size(); ++j){
      if(Card_less(hand[highest1],hand[j],trump)){
        highest1=j;
      }
    }
    Card removal1=hand[highest1];
    hand.erase(hand.begin()+highest1);
    return(removal1);
}
        return removal1;
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  virtual Card play_card(const Card &led_card, const std::string &trump){
    std::string led_suit=led_card.get_suit(trump);
    Card removal1, removal2;
    int check=0; int case1=0;int case2=0;
    for(int i=0; i<hand.size(); ++i){
      if(hand[i].get_suit(trump)==led_suit){
        check=1;
        case1=i;
        break;
      }}
    for(int w=0; w<hand.size(); ++w){
      if(hand[w].get_suit(trump)!=led_suit){
        case2=w;
        break;
      }}
      if(check==1){
        for(int j=case1; j<hand.size(); ++j){
          if((hand[j].get_suit(trump)==led_suit)&&
          (Card_less(hand[case1],hand[j],led_card,trump))){
            case1=j;
        }
        }
    Card removal1=hand[case1];
    hand.erase(hand.begin()+case1);
    return(removal1);
      }
      if(check==0){
        for(int k=1; k<hand.size(); ++k){
          if(!(Card_less(hand[case2], hand[k],trump))){
            case2=k;
          }
        }
    Card removal2=hand[case2];
    hand.erase(hand.begin()+case2);
    return(removal2);
      }
      return led_card;
  }


/*       if(led_suit==trump){
          int case1=0;
        for(int i=0; i<hand.size()-1; ++i){
        if(Card_less(hand[i], hand[i+1],led_card, trump)){
        case1=i+1;
      }
        }
        Card led1=hand[case1];
        hand.erase(hand.begin()+case1);
        return led1;
        }else if(led_suit!=trump){
            int case2=0;
        for(int i=0; i<hand.size()-1; ++i){
          if(hand[i].get_suit()==led_suit){
            sub.push_back(hand[i]);
          }
        }
        for(int j=0; j<sub.size()-1; ++j){
          if(operator<(sub[j], sub[j+1])){
            case2=j+1;
          }
        Card led2=hand[case2];
        hand.erase(hand.begin()+case2);
        return led2;
        }
        }
      }*/
  };

  class Human : public Player{
  private:
  std::string name2;
  std::vector<Card>hand2;

  void print_hand() const {
  for (size_t i=0; i < hand2.size(); ++i)
    std::cout << "Human player " << name2 << "'s hand: "
         << "[" << i << "] " << hand2[i] << "\n";
}

  public:
  Human(const std::string &name_in2):name2(name_in2){}
    
  virtual const std::string & get_name() const{
    return name2;
  }


//REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  virtual void add_card(const Card &c){
      if (hand2.size()<MAX_HAND_SIZE){
      hand2.push_back(c);
    }
    std::sort(hand2.begin(), hand2.end());
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  virtual bool make_trump(const Card &upcard, bool is_dealer,
              int round, std::string &order_up_suit) const{ 
    std::vector<Card>copy;
    for(int i=0; i<hand2.size(); ++i){
      copy.push_back(hand2[i]);
    }               
  for (size_t i=0; i < copy.size(); ++i){
    std::cout << "Human player " << name2 << "'s hand: "
         << "[" << i << "] " << hand2[i] << "\n";
  }
std::cout << "Human player " << name2 
<< ", please enter a suit, or \"pass\":\n";
      std::string dec;
      std::cin>>dec;
      if (dec=="pass"){
        //std::cout<<name2<<" passes"<<std::endl;
        return false;
      }else if(dec=="Spades"||dec=="Hearts"||dec=="Clubs"||dec=="Diamonds"){
        //std::cout<<name2<<" orders up "<<dec<<std::endl;
        order_up_suit=dec;
        return true;
      }
      return 0;
}

                          

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  virtual void add_and_discard(const Card &upcard){
     std::sort(hand2.begin(), hand2.end());
    print_hand();
    std::cout << "Discard upcard: [-1]\n";
    std::cout << "Human player " << name2 
    << ", please select a card to discard:\n";
    int choice=0;
    hand2.push_back(upcard);
    std::cin>>choice;
      if (choice==-1){
        hand2.erase(hand2.begin()+5);
      }else if(choice>=0&&choice<hand2.size()){
         hand2.erase(hand2.begin()+choice);
      }
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  virtual Card lead_card(const std::string &trump){
     std::sort(hand2.begin(), hand2.end());
    print_hand();
    std::cout << "Human player " << name2 << ", please select a card:\n";
    int choice=0;
    std::cin>>choice;
    Card removal=hand2[choice];
    //std::cout<<removal<<" led by "<<name2<<std::endl;
    hand2.erase(hand2.begin()+choice);
    return removal;
    }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  virtual Card play_card(const Card &led_card, const std::string &trump){
     std::sort(hand2.begin(), hand2.end());
    print_hand();
    std::cout << "Human player " << name2 << ", please select a card:\n";
    int choice=0;
    std::cin>>choice;
    Card removal=hand2[choice];
    hand2.erase(hand2.begin()+choice);
    return removal;
    }
  };

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy){
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new Simple(name);
  }else if(strategy == "Human") {
     return new Human(name);
  }
    return nullptr;
  // Repeat for each other type of Player
}



//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p){
         return os<<p.get_name();
}