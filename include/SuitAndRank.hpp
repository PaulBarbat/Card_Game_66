#ifndef SUITANDRANK_HPP
#define SUITANDRANK_HPP
#include <string>

enum class ClassicSuit{
    Hearts = 1,
    Diamonds,
    Clubs,
    Spades
};

enum class ClassicRank{
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

inline std::string rankToString(ClassicRank rank){
    switch (rank)
    {
        case ClassicRank::Two:
        {
            return "Two";
            break;
        }
        case ClassicRank::Three:
        {
            return "Three";
            break;
        }
        case ClassicRank::Four:
        {
            return "Four";
            break;
        }
        case ClassicRank::Ten:
        {
            return "Ten";
            break;
        }
        case ClassicRank::Ace:
        {
            return "Ace";
            break;
        }
        default:
            return "Unknown";
            break;
    }
    return "Unknown";
}

inline std::string rankToString(MagyarRank rank){
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
            return "Unknown";
            break;
    }
    return "Unknown";
}

inline std::string suitToString(ClassicSuit suit)
{
    switch (suit)
    {
        case ClassicSuit::Hearts:
        {
            return " of Hearts";
            break;
        }
        case ClassicSuit::Diamonds:
        {
            return " of Diamonds";
            break;
        }
        case ClassicSuit::Clubs:
        {
            return " of Clubs";
            break;
        }
        case ClassicSuit::Spades:
        {
            return " of Spades";
            break;
        }
        default:
            return "Unknown";
            break;
    }
    return "Unknown";
}

inline std::string suitToString(MagyarSuit suit)
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
            return "Unknown";
            break;
    }
    return "Unknown";
}

#endif