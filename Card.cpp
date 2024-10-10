#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
//EFFECTS returns the Rank corresponding to str, for example "Two" -> TWO
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
//EFFECTS returns the Suit corresponding to str, for example "Clubs" -> CLUBS
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}


//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////

//Default initilize
Card::Card()
  : rank(TWO), suit(SPADES)
  {}


//Initializes Card to specified rank and suit
Card::Card(Rank rank_in, Suit suit_in)
  : rank(rank_in), suit(suit_in)
  {}

//Returns the rank
Rank Card::get_rank() const{
  return(rank);
}

Suit Card::get_suit() const{
  return(suit);
}

//Left bower = second jack
Suit Card::get_suit(Suit trump) const{
  if(rank == JACK && ( trump == suit + 2 || trump == suit - 2)){
    return trump;
  }
  else{
    return suit;
  }
}

bool Card::is_face_or_ace() const{
  return rank == JACK || rank == QUEEN || rank == KING || rank == ACE;
}

bool Card::is_right_bower(Suit trump) const{
  return rank == JACK && suit == trump;
}

bool Card::is_left_bower(Suit trump) const{
  return rank == JACK && (suit == trump + 2 || suit == trump -2);
}

bool Card::is_trump(Suit trump) const{
  return suit == trump || (rank == JACK && (suit == trump + 2 || suit == trump -2));
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card){
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

std::istream & operator>>(std::istream &is, Card &card){
  string discard;
  is >> card.rank >> discard >> card.suit;
  return is;
}


bool operator<(const Card &lhs, const Card &rhs) {
  if(lhs.get_rank() == rhs.get_rank()){
    return lhs.get_suit() < rhs.get_suit();
  }
  else{
      return lhs.get_rank() < rhs.get_rank();
  }
}

bool operator==(const Card &lhs, const Card &rhs) {
  if(lhs.get_rank() == rhs.get_rank()){
    return lhs.get_suit() == rhs.get_suit();
  }
  else{
      return lhs.get_rank() == rhs.get_rank();
  }
}

bool operator>(const Card &lhs, const Card &rhs) {
  if(lhs.get_rank() == rhs.get_rank()){
    return lhs.get_suit() > rhs.get_suit();
  }
  else{
      return lhs.get_rank() > rhs.get_rank();
  }
}

bool operator<=(const Card &lhs, const Card &rhs) {
  if(lhs.get_rank() == rhs.get_rank()){
    return lhs.get_suit() <= rhs.get_suit();
  }
  else{
      return lhs.get_rank() <= rhs.get_rank();
  }
}

bool operator>=(const Card &lhs, const Card &rhs) {
  if(lhs.get_rank() == rhs.get_rank()){
    return lhs.get_suit() >= rhs.get_suit();
  }
  else{
      return lhs.get_rank() >= rhs.get_rank();
  }
}

bool operator!=(const Card &lhs, const Card &rhs) {
  if(lhs.get_rank() == rhs.get_rank()){
    return lhs.get_suit() != rhs.get_suit();
  }
  else{
      return lhs.get_rank() != rhs.get_rank();
  }
}

Suit Suit_next(Suit suit){
  if (suit == SPADES){
    return CLUBS;
  }
  else if (suit == HEARTS){
    return DIAMONDS;
  }
  else if (suit == CLUBS){
    return SPADES;
  }
  else{
    return HEARTS;
  }

}

bool Card_less(const Card &a, const Card &b, Suit trump){
  if (b.is_right_bower(trump)){
      return true;
  }
  else if (a.is_right_bower(trump)){
    return false;
  }
  else if (b.is_left_bower(trump)){
    return true;
  }
  else if (a.is_left_bower(trump)){
    return false;
  }
  else if (a.get_suit() == b.get_suit()){
      return a < b;
  }
  else if (a.is_trump(trump) == false && b.is_trump(trump) == true){
    return true;
  }
  else if (a.is_trump(trump) == true && b.is_trump(trump) == false){
    return false;
  }
  else{
    if (a.get_rank() == b.get_rank()){
      return a.get_suit() < b.get_suit();
    }
    else{
      return a.get_rank() < b.get_rank();
    }
  }

}

bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump){
  if (b.is_right_bower(trump)){
      return true;
  }
  else if (a.is_right_bower(trump)){
    return false;
  }
  else if (b.is_left_bower(trump)){
    return true;
  }
  else if (a.is_left_bower(trump)){
    return false;
  }
  if (a.get_suit() == b.get_suit()){
      return a < b;
  }
  else if (a.is_trump(trump) == false && b.is_trump(trump) == true){
    return true;
  }
  else if (a.is_trump(trump) == true && b.is_trump(trump) == false){
    return false;
  }
  else if (a.get_suit() != led_card.get_suit() && b.get_suit() == led_card.get_suit()){
    return true;
  }
  else if (a.get_suit() == led_card.get_suit() && b.get_suit() != led_card.get_suit()){
    return false;
  }
  else{
    return a.get_suit() < b.get_suit();
  }
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
