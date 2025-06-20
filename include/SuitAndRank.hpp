#ifndef SUITANDRANK_HPP
#define SUITANDRANK_HPP
#include <string>

enum class ClasicSuit{
    Hearts = 1,
    Diamonds,
    Clubs,
    Spades
};

enum class ClasicRank{
    Two = 2,
    Three,
    Four,
    Ten = 10,
    Ace
};

enum class MagyarSuit{
    Rosu = 1,
    Ghinda,
    Bata,
    Verde
};

enum class MagyarRank{
    Doi = 2,
    Trei,
    Cal,
    Craita = 10,
    Tuz
};

std::string rankToString(ClasicRank rank){
    switch (rank)
    {
        case ClasicRank::Two:
        {
            return "Two";
            break;
        }
        case ClasicRank::Three:
        {
            return "Three";
            break;
        }
        case ClasicRank::Four:
        {
            return "Four";
            break;
        }
        case ClasicRank::Ten:
        {
            return "Ten";
            break;
        }
        case ClasicRank::Ace:
        {
            return "Ace";
            break;
        }
        default:
            break;
    }
}

std::string rankToString(MagyarRank rank){
    switch (rank)
    {
        case MagyarRank::Doi:
        {
            return "Doi";
            break;
        }
        case MagyarRank::Trei:
        {
            return "Trei";
            break;
        }
        case MagyarRank::Cal:
        {
            return "Cal";
            break;
        }
        case MagyarRank::Craita:
        {
            return "Craita";
            break;
        }
        case MagyarRank::Tuz:
        {
            return "Tuz";
            break;
        }
        default:
            break;
    }
}

std::string suitToString(ClasicSuit suit)
{
    switch (suit)
    {
        case ClasicSuit::Hearts:
        {
            return " of Hearts";
            break;
        }
        case ClasicSuit::Diamonds:
        {
            return " of Diamonds";
            break;
        }
        case ClasicSuit::Clubs:
        {
            return " of Clubs";
            break;
        }
        case ClasicSuit::Spades:
        {
            return " of Spades";
            break;
        }
        default:
            break;
    }
}

std::string suitToString(MagyarSuit suit)
{
    switch (suit)
    {
        case MagyarSuit::Rosu:
        {
            return " de Rosu";
            break;
        }
        case MagyarSuit::Ghinda:
        {
            return " de Ghinda";
            break;
        }
        case MagyarSuit::Bata:
        {
            return " de Bata";
            break;
        }
        case MagyarSuit::Verde:
        {
            return " de Verde";
            break;
        }
        default:
            break;
    }
}

#endif