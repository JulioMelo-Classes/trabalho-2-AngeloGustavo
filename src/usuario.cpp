#include "usuario.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

void Usuario::setId(int _id){
    this->id = _id;
};
int Usuario::getId(){
    return this->id;
};

void Usuario::setNome(string _nome){
    this->nome = _nome;
};
string Usuario::getNome(){
    return this->nome;
};

void Usuario::setSenha(string _senha){
    this->senha = _senha;
};
string Usuario::getSenha(){
    return this->senha;
};

void Usuario::setEmail(string _email){
    this->email = _email;
};
string Usuario::getEmail(){
    return this->email;
};