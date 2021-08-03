#include "canaltexto.h"

#include <iostream>

using namespace std;

void CanalTexto::setNome(string _nome){
    this->nome = _nome;
}
string CanalTexto::getNome(){
    return this->nome;
}