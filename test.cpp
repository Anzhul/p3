#include "Card.hpp"
#include "Pack.hpp"
#include <iostream>
using namespace std;

int main() {
    Card card(NINE, SPADES);
    cout << card.get_rank() << endl;
    return 0;
}