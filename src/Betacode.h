#pragma once

#include <string>

extern "C"
{
    // found in unibetacode lib
    int ub_beta2greek(char *beta, int max_beta, char *utf8gk, int max_utf8);
    int ub_greek2beta(char *, int, char *, int);
}

struct Betacode
{
  public:
    std::string beta{"lo/gos"};
    static std::string beta2greek(std::string &utf8);
    static std::string greek2beta(std::string &greek);
};