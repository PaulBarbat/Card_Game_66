#include "Card.hpp"

Card::Card(Suit suit, Rank rank): suit(suit), rank(rank) {}

std::string Card::toString()
{
    std::string card="";
    switch (this->rank)
    {
        case Rank::Two:
        {
            card +="Two";
            break;
        }
        case Rank::Three:
        {
            card +="Three";
            break;
        }
        case Rank::Four:
        {
            card +="Four";
            break;
        }
        case Rank::Ten:
        {
            card +="Ten";
            break;
        }
        case Rank::Ace:
        {
            card +="Ace";
            break;
        }
        default:
            break;
    }
    switch (this->suit)
    {
        case Suit::Hearts:
        {
            card+=" of Hearts";
            break;
        }
        case Suit::Diamonds:
        {
            card+="of Diamonds";
            break;
        }
        case Suit::Clubs:
        {
            card+="of Clubs";
            break;
        }
        case Suit::Spades:
        {
            card+="of Spades";
            break;
        }
        default:
            break;
    }
    return card;
}