#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;




TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());

    Card c1(NINE, CLUBS);
    ASSERT_EQUAL(NINE, c1.get_rank());
    ASSERT_EQUAL(CLUBS, c1.get_suit());

    Card c2;
    ASSERT_EQUAL(TWO, c2.get_rank());
    ASSERT_EQUAL(SPADES, c2.get_suit());

    Card c3(JACK, HEARTS);
    ASSERT_EQUAL(JACK, c3.get_rank());
    ASSERT_EQUAL(DIAMONDS, c3.get_suit(DIAMONDS));
    ASSERT_EQUAL(HEARTS, c3.get_suit(CLUBS));
    ASSERT_EQUAL(HEARTS, c3.get_suit(HEARTS));
    ASSERT_EQUAL(HEARTS, c3.get_suit(SPADES));

    Card c4(TEN, SPADES);
    ASSERT_EQUAL(TEN, c4.get_rank());
    ASSERT_EQUAL(SPADES, c4.get_suit(SPADES));
    ASSERT_EQUAL(SPADES, c4.get_suit(CLUBS));
    ASSERT_EQUAL(SPADES, c4.get_suit(HEARTS));
    ASSERT_EQUAL(SPADES, c4.get_suit(DIAMONDS));

    Card c5(JACK, CLUBS);
    ASSERT_EQUAL(JACK, c5.get_rank());
    ASSERT_EQUAL(CLUBS, c5.get_suit(DIAMONDS));
    ASSERT_EQUAL(CLUBS, c5.get_suit(CLUBS));
    ASSERT_EQUAL(CLUBS, c5.get_suit(HEARTS));
    ASSERT_EQUAL(SPADES, c5.get_suit(SPADES));
}

TEST(test_card_self_comparison) {
    Card three_spades = Card(THREE, SPADES);
    Card four_spades = Card(FOUR, HEARTS);
    Card ace_clubs = Card(ACE, CLUBS);
    Card ace_hearts = Card(ACE, HEARTS);
    Card jack_clubs = Card(JACK, CLUBS);
    ASSERT_FALSE(four_spades < three_spades);
    ASSERT_TRUE(three_spades <= four_spades);
    ASSERT_FALSE(three_spades > four_spades);
    ASSERT_TRUE(four_spades >= three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades <= three_spades);
    ASSERT_TRUE(three_spades >= three_spades);
    ASSERT_FALSE(three_spades != three_spades);
    ASSERT_FALSE(jack_clubs == ace_clubs);
    ASSERT_TRUE(jack_clubs < ace_clubs);
    ASSERT_TRUE(jack_clubs <= ace_clubs);
    ASSERT_TRUE(jack_clubs != ace_clubs);
    ASSERT_FALSE(jack_clubs > ace_clubs);
    ASSERT_TRUE(ace_hearts != ace_clubs);
    ASSERT_FALSE(ace_hearts == ace_clubs);
    ASSERT_FALSE(ace_hearts > ace_clubs);
    ASSERT_TRUE(ace_hearts <= ace_clubs);
    ASSERT_TRUE(ace_hearts < ace_clubs);
    ASSERT_FALSE(ace_hearts >= ace_clubs);
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
}

TEST(test_Card_less_self) {
    Card three_spades = Card(THREE, SPADES);
    Card ten_spades = Card(TEN, SPADES);
    Card three_hearts = Card(THREE, HEARTS);
    Card four_hearts = Card(FOUR, HEARTS);
    Card nine_hearts = Card(NINE, HEARTS);
    Card ten_hearts = Card(TEN, HEARTS);
    Card ten_clubs = Card(TEN, CLUBS);
    Card ace_clubs = Card(ACE, CLUBS);
    Card ace_hearts = Card(ACE, HEARTS);
    Card jack_clubs = Card(JACK, CLUBS);
    Card jack_spades = Card(JACK, SPADES);
    ASSERT_FALSE(Card_less(three_spades, three_spades, CLUBS));
    ASSERT_TRUE(Card_less(three_spades, three_hearts, HEARTS));
    ASSERT_TRUE(Card_less(three_spades, four_hearts, CLUBS));
    ASSERT_FALSE(Card_less(jack_clubs, ace_clubs, CLUBS));
    ASSERT_FALSE(Card_less(jack_clubs, ace_clubs, SPADES));
    ASSERT_TRUE(Card_less(jack_clubs, ace_clubs, DIAMONDS));
    ASSERT_FALSE(Card_less(jack_clubs, ace_hearts, CLUBS));
    ASSERT_TRUE(Card_less(jack_clubs, ace_hearts, DIAMONDS));
    ASSERT_TRUE(Card_less(ace_clubs, ace_hearts, HEARTS));
    ASSERT_FALSE(Card_less(ace_clubs, ace_hearts, DIAMONDS));
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, SPADES));
    ASSERT_FALSE(Card_less(jack_clubs, jack_spades, CLUBS));
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, SPADES));

    ASSERT_FALSE(Card_less(three_spades, three_spades, three_spades,CLUBS));
    ASSERT_TRUE(Card_less(ace_hearts, jack_clubs, ace_clubs, DIAMONDS));
    ASSERT_FALSE(Card_less(ace_clubs, ace_hearts, ten_spades, DIAMONDS));
    ASSERT_FALSE(Card_less(ten_hearts, jack_clubs, ace_clubs, HEARTS));
    ASSERT_FALSE(Card_less(jack_clubs, jack_spades, ace_clubs, CLUBS));
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, ace_clubs, SPADES));
    ASSERT_TRUE(Card_less(ten_clubs, ten_hearts, nine_hearts, SPADES));
    ASSERT_FALSE(Card_less(ten_clubs, ten_hearts, nine_hearts, CLUBS));
    ASSERT_FALSE(Card_less(ten_clubs, ten_hearts, ace_clubs, DIAMONDS));
    ASSERT_FALSE(Card_less(ten_clubs, ten_hearts, ace_clubs, DIAMONDS));
}


TEST(test_card_insertion) {
    Card three_spades = Card(THREE, SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}

TEST(test_card_extraction) {
    istringstream iss("Three of Spades");
    Card c;
    iss >> c;
    ASSERT_EQUAL(c, Card(THREE, SPADES));
}
// Add more test cases here

TEST_MAIN()
