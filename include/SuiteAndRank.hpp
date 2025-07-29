#ifndef SUITANDRANK_HPP
#define SUITANDRANK_HPP
#include <string>

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

struct CardHash{
    std::size_t operator()(const std::pair<MagyarRank,MagyarSuite> & card) const{
        return(static_cast<std::size_t>(card.first) << 4) | static_cast<std::size_t>(card.second);
    }
};

struct CardEqual {
    bool operator()(const std::pair<MagyarRank, MagyarSuite>& lhs, const std::pair<MagyarRank, MagyarSuite>& rhs) const{
        return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
    }
};

#endif