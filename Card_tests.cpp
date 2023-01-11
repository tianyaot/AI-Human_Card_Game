// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor1) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_card_suit_and_rank1) {
    Card two_spades = Card();
    ASSERT_EQUAL(two_spades.get_rank(), Card::RANK_TWO);
    ASSERT_EQUAL(two_spades.get_suit(), Card::SUIT_SPADES);

    Card Jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Jack_clubs.get_suit(Card::SUIT_SPADES), Card::SUIT_SPADES);
}

TEST(test_card_type1) {
    Card Jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(Jack_clubs.is_face_or_ace());
    ASSERT_TRUE(Jack_clubs.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(Jack_clubs.is_left_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(Jack_clubs.is_trump(Card::SUIT_CLUBS));
}

TEST(test_card_self_comparison1) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_TRUE(three_spades <= three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades >= three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades != three_spades);
}

TEST(test_card_self_comparison2) {
    Card Jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card Queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card King_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card King_clubs = Card(Card::RANK_KING, Card::SUIT_CLUBS);
    ASSERT_FALSE(King_diamonds < King_clubs);
    ASSERT_TRUE(King_diamonds > King_clubs);
    ASSERT_TRUE(King_diamonds >= King_clubs);
    ASSERT_TRUE(King_diamonds != King_clubs);
}

TEST(test_Suit_next1) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
}

TEST(test_Card_less_self1) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(three_spades, three_spades, Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(three_spades, three_spades, three_spades,
                           Card::SUIT_CLUBS));
}

TEST(test_Card_less_self2) {
    Card Jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card Jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card Queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card King_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(Jack_spades, Jack_clubs, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(Queen_diamonds, King_diamonds, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(King_diamonds, Jack_clubs, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(Queen_diamonds, Jack_spades, King_diamonds,
                           Card::SUIT_CLUBS));
}

TEST(test_card_insertion1) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}

TEST_MAIN()
