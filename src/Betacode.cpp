#include "Betacode.h"
#include <cstring>

std::string Betacode::beta2greek(const std::string &beta)
{
    char cstr[150]{0};
    strncpy(cstr, beta.c_str(), beta.length());
    char gkstr[150]{0};
    ub_beta2greek(cstr, 150, gkstr, 150);
    return std::string(gkstr);
}
std::string Betacode::greek2beta(const std::string &greek)
{
    char gkstr[150]{0};
    strncpy(gkstr, greek.c_str(), greek.length());
    char cstr[150]{0};
    ub_beta2greek(cstr, 150, gkstr, 150);
    return std::string(cstr);
}
