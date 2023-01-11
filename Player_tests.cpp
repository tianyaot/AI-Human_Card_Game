// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;



TEST(test_player_get_name1) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}
// Add more tests here
TEST(test_player_insertion2) {
  // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}

TEST(test_player_get_name3) {
  // Create a player and verify that get_name() returns the player's name
  Player * alice = Player_factory("Alice", "Simple");
  ASSERT_EQUAL(alice->get_name(), "Alice");
  delete alice;
}

TEST(test_simple_player_make_trump4) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}


TEST(make_trump_round1_one_trump_leftbower) {
  Player * andy = Player_factory("Andy", "Simple");
  andy->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  andy->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  andy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  andy->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  andy->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));

  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = andy->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete andy;
}

TEST(make_trump_round1_one_trump_leftbower2) {
  Player * andy = Player_factory("Andy", "Simple");
  andy->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  andy->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  andy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  andy->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  andy->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));

  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = andy->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete andy;
}

TEST(make_trump_round1_only_one_trumpsuit) {
  Player * andy = Player_factory("Andy", "Simple");
  andy->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
  andy->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  andy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  andy->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  andy->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));

  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = andy->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump         // Suit ordered up (if any)
  );

  ASSERT_FALSE(orderup);

  delete andy;
}

TEST(make_trump_round2_no_same_color) {

  Player * andy = Player_factory("Andy", "Simple");
  andy->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
  andy->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  andy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  andy->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  andy->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));


  Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump;
  bool orderup = andy->make_trump(
    nine_hearts,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump         // Suit ordered up (if any)
  );

  ASSERT_FALSE(orderup);
  delete andy;
}

TEST(make_trump_round2_one_same_color) {

  Player * andy = Player_factory("Andy", "Simple");
  andy->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
  andy->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  andy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  andy->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  andy->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));


  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump;
  bool orderup = andy->make_trump(
    nine_diamonds,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump         // Suit ordered up (if any)
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_HEARTS);
  delete andy;
}

TEST(make_trump_round2_isdealer) {

  Player * andy = Player_factory("Andy", "Simple");
  andy->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
  andy->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  andy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  andy->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  andy->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));


  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump;
  bool orderup = andy->make_trump(
    nine_diamonds,    // Upcard
    true,           // Bob is also the dealer
    2,              // First round
    trump         // Suit ordered up (if any)
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_HEARTS);
  delete andy;
}

TEST(test_simple_player_lead_card5) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(lead_card_no_trump) {

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(card_led, ace_diamonds); //check led card

  delete bob;
}

TEST(lead9) {

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));

  bob->add_and_discard(
    Card(Card::RANK_JACK, Card::SUIT_HEARTS) // upcard
  );

  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  Card King_Diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(card_led, King_Diamonds); //check led card

  delete bob;
}

TEST(lead8) {

  Player * bob = Player_factory("Bob", "Simple");
 //bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  //bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));


  Card card_led = bob->lead_card(Card::SUIT_DIAMONDS);

  Card Jack_Hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_led, Jack_Hearts); //check led card
  delete bob;
}

TEST(lead_card_only_trump_leftbower2) {

  Player * bob = Player_factory("Bob", "Simple");
 //bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  //bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  Card Jack_diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(card_led, Jack_diamonds); //check led card
  delete bob;
}

TEST(lead_card_only_trump_leftbower3) {

  Player * bob = Player_factory("Bob", "Simple");
 //bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  //bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));


  Card card_led = bob->lead_card(Card::SUIT_DIAMONDS);

  Card Queen_Hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_led, Queen_Hearts); //check led card
  delete bob;
}

TEST(lead_card_only_trump_rightbower) {

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_led, jack_hearts); //check led card

  delete bob;
}

TEST(lead_card_only_trump_rightbower2) {

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  bob->add_and_discard(
    Card(Card::RANK_JACK, Card::SUIT_HEARTS) // upcard
  );

  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_led, jack_hearts); //check led card

  delete bob;
}


TEST(test_simple_player_play_card6) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

TEST(play_card_highest_ledsuit_card) {

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    king_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  delete bob;
}

TEST(play_card_nine_heart_ace_spade) {

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));

  Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
  Card card_played = bob->play_card(
    jack_spades,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_SPADES));
  delete bob;
}

TEST(play_card_led_jack_hearts_nine_diamonds) {

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));

  Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card card_played = bob->play_card(
    jack_hearts,  // Nine of Diamonds is led
    "Diamonds"        // Trump suit
  ); 

  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  delete bob;
}

TEST(play_card_led_jack_clubs_trump_spade) {

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
  Card card_played = bob->play_card(
    jack_clubs,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  delete bob;
}

TEST(play_card_highest_ledsuit_trump_card_leftbower) {

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    king_diamonds,  // Nine of Diamonds is led
    "Diamonds"        // Trump suit
  ); 

  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  delete bob;
}

TEST(play_card_highest_ledsuit_onlytrump_leftbower) {

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    king_diamonds,  // Nine of Diamonds is led
    "Diamonds"        // Trump suit
  ); 

  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  delete bob;
}

TEST(play_card_lowest_nonledsuit_rightbower) {

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));

  Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    king_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  delete bob;
}

TEST(play_card_lowest_nonledsuit_onlytrump_lowest) {

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    king_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  ASSERT_EQUAL(card_played, Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  delete bob;
}

TEST(play_card_lowest_nonledsuit_onlytrump_lowest23) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    king_diamonds,  // Nine of Diamonds is led
    "Diamonds"        // Trump suit
  ); 

  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  delete bob;
}

TEST(play_card_lowest_nonledsuit_onlytrump_lowest234) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  Card Jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
  Card card_played = bob->play_card(
    Jack_clubs,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  delete bob;
}

TEST(play_card5) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));

  Card Jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
  Card card_played = bob->play_card(
    Jack_spades,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_SPADES));
  delete bob;
}

TEST(play_card6) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));

  Card Jack_Hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card card_played = bob->play_card(
    Jack_Hearts,  // Nine of Diamonds is led
    "Diamonds"        // Trump suit
  ); 

  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

TEST(play_card7) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));

  Card Jack_Hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card card_played = bob->play_card(
    Jack_Hearts,  // Nine of Diamonds is led
    "Diamonds"        // Trump suit
  ); 

  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  delete bob;
}
TEST_MAIN()










