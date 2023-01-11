// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cassert>
#include <string>
#include <array>
#include <vector>
#include "Card.h"
#include "Pack.h"
#include "Player.h"
#include <algorithm>
using namespace std;



class Game {
  private:
  vector<Player*> players;
  string shuffle_choice;
  int points_win;
  Pack pack;
  Card upcard;
  string trump_suit;
  int trump=0;
  int score_team1=0;
  int score_team2=0;
  Card highest;
  int trick1=0;
  int trick2=0;
  int game_hand=0;
  int dealer=0;
  int first=(dealer+1)%4;
  int second=(dealer+2)%4;
  int third=(dealer+3)%4;
  int fourth=(dealer+4)%4;
    vector<Player*>group1;
    vector<Player*>group2;
  // ...
  //shuffle cards

  //3_2_3_2 2_3_2_3 deal cards
  void three_cards(int num){
    for(int i=0; i<3; ++i){
    players[num]->add_card(pack.deal_one());
    }
  }
  void two_cards(int num){
    for(int i=0; i<2; ++i){
    players[num]->add_card(pack.deal_one());
    }
  }
  
  void print_hand(){
    int copy=game_hand;
    game_hand++;
    cout<<"Hand " <<copy<<endl;
  }
  
  int hand(){
    return game_hand;
  }

  void deal(){
    cout<<*players[fourth]<<" deals"<<endl;
    pack.reset();
    if(shuffle_choice=="shuffle"){
      pack.shuffle();
    }
    three_cards(first);
    two_cards(second);
    three_cards(third);
    two_cards(fourth);
    two_cards(first);
    three_cards(second);
    two_cards(third);
    three_cards(fourth);
    }

  Card decide_upcard(){
    upcard=pack.deal_one();
    cout<<upcard<<" turned up"<<endl;
    return upcard;
  }


  string upcard_as_trump(Card &upcard){
    trump_suit=upcard.get_suit();
    return trump_suit;
  }
  
  void trump_who(Player *players){
    for(int i=0; i<2; ++i){
        if(group1[i]==players){
          trump=1;         
           }else if(group2[i]==players){
            trump=2;
          }}
  }
 

  void make_trump(Card &upcard, string &trump_suit){
    for(int i=1; i<3; ++i){
      if(players[first]->make_trump(upcard,false,i,trump_suit)){
        cout<<*players[first]<<" orders up "<<trump_suit<<endl<<endl;
        trump_who(players[first]);
        if(i==1){players[fourth]->add_and_discard(upcard);}
        break;}else{cout<<*players[first]<<" passes"<<endl;}   
      if(players[second]->make_trump(upcard,false,i,trump_suit)){
        cout<<*players[second]<<" orders up "<<trump_suit<<endl<<endl;
        trump_who(players[second]);
        if(i==1){players[fourth]->add_and_discard(upcard);}
        break;}else{cout<<*players[second]<<" passes"<<endl;}
      if(players[third]->make_trump(upcard,false,i,trump_suit)){
        cout<<*players[third]<<" orders up "<<trump_suit<<endl<<endl;
        trump_who(players[third]);
        if(i==1){players[fourth]->add_and_discard(upcard);}
        break;
      }else{cout<<*players[third]<<" passes"<<endl;}
      if(players[fourth]->make_trump(upcard,true,i,trump_suit)){
        cout<<*players[fourth]<<" orders up "<<trump_suit<<endl<<endl;
        trump_who(players[fourth]);
        if(i==1){
        players[fourth]->add_and_discard(upcard);
        }break;}else{cout<<*players[fourth]<<" passes"<<endl;}}}

  void decide_team(){
    group1.push_back(players[first]);
    group1.push_back(players[third]);
    group2.push_back(players[fourth]);
    group2.push_back(players[second]);
  }
 
  void reset_player(){
    first=(dealer+1)%4; second=(dealer+2)%4; third=(dealer+3)%4;
     fourth=(dealer+4)%4;
  }

  void decide_handcard(Card led_card,Card play_1,Card play_2,Card play_3){
    vector<Card>handcard;
    handcard.push_back(led_card); handcard.push_back(play_1);
    handcard.push_back(play_2); handcard.push_back(play_3);
    highest=handcard[0];
    for(int i=1; i<handcard.size(); ++i){
      if(Card_less(highest, handcard[i], led_card, trump_suit)){
        highest=handcard[i];}}
  }
   
  void plus_score(Player *players){
    for(int i=0; i<2; ++i){
        if(group1[i]==players){score_team1++;}
        else if(group2[i]==players){score_team2++;}}
        cout<<*players<<" takes the trick"<<endl<<endl;
  }




   void play_hand(){
    reset_player();
    vector<Card>handcard;
    Card led_card=players[first]->lead_card(trump_suit);
    cout<<led_card<<" led by "<<*players[first]<<endl;
    Card play_1=players[second]->play_card(led_card,trump_suit);
    cout<<play_1<<" played by "<<*players[second]<<endl;
    Card play_2=players[third]->play_card(led_card,trump_suit);
    cout<<play_2<<" played by "<<*players[third]<<endl;
    Card play_3=players[fourth]->play_card(led_card,trump_suit);
    cout<<play_3<<" played by "<<*players[fourth]<<endl;
    decide_handcard(led_card,play_1,play_2,play_3);
    if (highest==led_card){
      plus_score(players[first]);
      dealer=fourth;
    }else if(highest==play_1){plus_score(players[second]);
      dealer=first;
    }else if(highest==play_2){plus_score(players[third]);
      dealer=second;
    }else if(highest==play_3){plus_score(players[fourth]);
      dealer=third;
    }handcard.clear();}

  void win_hand(int trump){
    score_team1=0;
    score_team2=0;
    for(int i=0; i<5; ++i){
          play_hand();
        }
     if (score_team1>score_team2){
      cout<<*players[1]<<" and "<<*players[3]<<" win the hand"<<endl;
      if((trump==1)&&(score_team1==5)){
        trick1+=2;
        cout<<"march!"<<endl;
      }else if(trump==1){
        trick1++;
      }else{
        trick1+=2;
        cout<<"euchred!"<<endl;
      }
     }else if(score_team2>score_team1){
      cout<<*players[0]<<" and "<<*players[2]<<" win the hand"<<endl;
      if((trump==2)&&(score_team1==5)){
        trick2+=2;
        cout<<"march!"<<endl;
     }else if(trump==2){
      trick2++;
     }else{
      trick2+=2;
      cout<<"euchred!"<<endl;
     }
  }
   cout<<*players[0]<<" and "<<*players[2]
   <<" have "<<trick2<<" points"<<endl;
   cout<<*players[1]<<" and "<<*players[3]
   <<" have "<<trick1<<" points"<<endl<<endl;
  }
  
  void final_winner(int trick1, int trick2){
     if(trick2>=points_win){
      cout<<*players[0]<<" and "<<*players[2]<<" win!"<<endl;
     }else if(trick1>=points_win){
      cout<<*players[1]<<" and "<<*players[3]<<" win!"<<endl;
     }
  }

 void delete_players(){
  for (size_t i = 0; i < players.size(); ++i) {
  delete players[i];
}
 }
 

 public:
  Game(vector<Player*> player,int points,Pack pack_in, string s):
  players(player),shuffle_choice(s),points_win(points),pack(pack_in){}


void play(){
  decide_team();
  while((trick1<points_win)&&(trick2<points_win)){
  print_hand();
  deal();
  upcard=decide_upcard();
  trump_suit=upcard_as_trump(upcard);
  make_trump(upcard,trump_suit);
  win_hand(trump);
  dealer=hand();
  first=(dealer+1)%4;
  second=(dealer+2)%4;
  third=(dealer+3)%4;
  fourth=(dealer+4)%4;
  }
  final_winner(trick1,trick2);
  delete_players();
}
};




int main(int argc, char **argv) {
  // Read command line args and check for errors
  string pack_filename=argv[1];
  ifstream fin;
  fin.open(pack_filename);
  if(!fin.is_open()){
        cout << "Error opening " << pack_filename << endl;
        return 1;
    }
  int arguments=12;
  string shuf=argv[2];
  int pts=atoi(argv[3]);
  string p0=argv[5];
  string p1=argv[7];
  string p2=argv[9];
  string p3=argv[11];


  if((argc==arguments)&&(pts>=1 && pts<=100)
  &&(shuf=="shuffle"||shuf=="noshuffle")&&(p0=="Simple"||p0=="Human")
  &&(p1=="Simple"||p1=="Human")&&(p2=="Simple"||p2=="Human")
  &&(p3=="Simple"||p3=="Human")){
    cout<<argv[0]<<" "<<argv[1]<<" "<<argv[2]<<" "<<atoi(argv[3])<<" "<<argv[4]
    <<" "<<argv[5]<<" "<<argv[6]<<" "<<argv[7]<<" "<<argv[8]<<" "<<argv[9]<<" "
    <<argv[10]<<" "<<argv[11]<<" "<<endl;
  vector<Player*> player;
  Pack pack;
  Player *d = Player_factory(argv[4],argv[5]);
  Player *l = Player_factory(argv[6],argv[7]);
  Player *u = Player_factory(argv[8],argv[9]);
  Player *r= Player_factory(argv[10],argv[11]);
  player.push_back(d);
  player.push_back(l);
  player.push_back(u);
  player.push_back(r);
  pack=Pack(fin);
  Game game(player,pts,pack,shuf);
  game.play();
 }else{
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
  }
}