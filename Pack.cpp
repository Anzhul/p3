#include "Pack.hpp"
#include <cassert>
#include <array>

using namespace std;



Pack::Pack()
{
    for (int i = SPADES; i <= DIAMONDS; i++){
        for (int j = NINE; j <= ACE; j++){
            Card card(static_cast<Rank>(j),static_cast<Suit>(i));
            //cout << i << " " << j << " " << (i*6)+(j-7) << endl;
            this->cards[(i*6)+(j-7)] = card;
        }
    }
    this->next = 0;
}

Pack::Pack(std::istream& pack_input)
{
    int count = 0;
    string discard;
    Rank rank;
    Suit suit;
    while (pack_input >>rank >> discard >> suit){
        Card card(rank, suit);
        this -> cards[count] = card; 
        count ++;
    }
    this->next = 0;
}

Card Pack::deal_one(){
    this->next++;
    //delete this
    this->count1++;
    cout<< this->count1<< endl;
    //delete this
    return this->cards[next-1];

}

void Pack::reset() {
    this->next = 0;
}

void Pack::shuffle(){
    for (int i = 0; i<7; i++){
        std::array<Card, PACK_SIZE/2> shuffled_top;
        std::array<Card, PACK_SIZE/2> shuffled_bottom;
        for (int j = 0; j < PACK_SIZE/2; j++){
            shuffled_bottom[j] = this -> cards[j];
            shuffled_top[j] = this -> cards[j+12];
        }
        for (int k = 0; k < PACK_SIZE; k+=2){
            this->cards[k] = shuffled_top[k/2];
            this->cards[k+1] = shuffled_bottom[k/2];
            //cout << cards[k] << endl;
            //cout << cards[k+1] << endl;
        }
    }
}

bool Pack::empty() const{
    return this->next == PACK_SIZE;
}
