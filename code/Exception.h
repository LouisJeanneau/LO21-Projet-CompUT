//
// Created by Louis on 07/12/2020.
//

#ifndef PROJET_LO21_EXCEPTION_H
#define PROJET_LO21_EXCEPTION_H

#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

class ComputerException : public exception{
    string info;
    string resteCommande;
public:
    explicit ComputerException(string  i="", string  r="") noexcept :info(std::move(i)), resteCommande(std::move(r)){}
    virtual ~ComputerException() noexcept {}
    const char* what() const noexcept { return info.c_str(); }
    const char* reste() const noexcept { return resteCommande.c_str(); }
};

#endif //PROJET_LO21_EXCEPTION_H
