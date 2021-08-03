#include "mensagem.h"

#include <iostream>

using namespace std;

void Mensagem::setDataHora(string _dataHora){
    this->dataHora = _dataHora;
}
string Mensagem::getDataHora(){
    return this->dataHora;
}

void Mensagem::setEnviadaPor(int _enviadaPor){
    this->enviadaPor = _enviadaPor;
}
int Mensagem::getEnviadaPor(){
    return this->enviadaPor;
}
        
void Mensagem::setConteudo(string _conteudo){
    this->conteudo = _conteudo;
}
string Mensagem::getConteudo(){
    return this->conteudo;
}