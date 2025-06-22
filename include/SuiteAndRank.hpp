#ifndef SUITANDRANK_HPP
#define SUITANDRANK_HPP
#include <string>

enum class ClassicSuite{
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

enum class MagyarSuite{
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

inline std::string suiteToString(ClassicSuite suite)
{
    switch (suite)
    {
        case ClassicSuite::Hearts:
        {
            return " of Hearts";
            break;
        }
        case ClassicSuite::Diamonds:
        {
            return " of Diamonds";
            break;
        }
        case ClassicSuite::Clubs:
        {
            return " of Clubs";
            break;
        }
        case ClassicSuite::Spades:
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

inline std::string suiteToString(MagyarSuite suite)
{
    switch (suite)
    {
        case MagyarSuite::Rosu:
        {
            return " de Rosu";
            break;
        }
        case MagyarSuite::Ghinda:
        {
            return " de Ghinda";
            break;
        }
        case MagyarSuite::Bata:
        {
            return " de Bata";
            break;
        }
        case MagyarSuite::Verde:
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