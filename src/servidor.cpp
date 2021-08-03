#include "servidor.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

void Servidor::setDonoId(int _id){
    this->usuarioDonoId = _id;
};
int Servidor::getDonoId(){
    return this->usuarioDonoId;
};

void Servidor::setNome(string _nome){
    this->nome = _nome;
};
string Servidor::getNome(){
    return this->nome;
};

void Servidor::setDescricao(string _descricao){
    this->descricao = _descricao;
};
string Servidor::getDescricao(){
    return this->descricao;
};

void Servidor::setCodigo(string _codigo){
    this->codigoConvite = _codigo;
};
string Servidor::getCodigo(){
    return this->codigoConvite;
};

void Servidor::addParticipante(int _id){
    participantesIDs.push_back(_id);
};
void Servidor::delParticipante(int _id){//Reformular método
    auto posicao = participantesIDs.begin();
    int i=0;
    for(auto itr=participantesIDs.begin(); itr!=participantesIDs.end(); ++itr){
        if(participantesIDs[i] == _id)
            posicao = itr;
        i++;
    }
    participantesIDs.erase(posicao);
};
