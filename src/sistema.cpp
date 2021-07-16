#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "usuario.h"
#include <map>

using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo do Concordo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
  for(int i=0; i<this->usuarios.size(); i++)
    if(this->usuarios[i].getEmail() == email)
      return "Usuário já existe!";

  Usuario temp;
  
  temp.setId(this->usuarios.size());
  temp.setNome(nome);
  temp.setEmail(email);
  temp.setSenha(senha);

  usuarios.push_back(temp);

  return "Criando usuário "+temp.getNome()+" ("+temp.getEmail()+")\nUsuário Criado";
}

string Sistema::login(const string email, const string senha) {
  for(int i=0; i<this->usuarios.size(); i++)
    if(this->usuarios[i].getEmail() == email &&
      this->usuarios[i].getSenha() == senha){
        this->usuariosLogados.insert(pair<int, pair<string,string>>(this->usuarios[i].getId(), {"",""}));
        return "Logado como "+this->usuarios[i].getEmail();
      }

  return "Senha ou usuário inválidos!";
}

string Sistema::disconnect(int id) {
  map< int, std::pair<std::string, std::string> >::iterator itr;
  for(itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      usuariosLogados.erase(id);
      return "Desconectando usuário "+this->usuarios[id].getEmail();       
    }

  return "Não está conectado";
}
//---------------------Fim Comandos Usuario----------------------

string Sistema::create_server(int id, const string nome) {
  return "create_server NÃO IMPLEMENTADO";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  return "set_server_desc NÃO IMPLEMENTADO";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  return "set_server_invite_code NÃO IMPLEMENTADO";
}

string Sistema::list_servers(int id) {
  return "list_servers NÃO IMPLEMENTADO";
}

string Sistema::remove_server(int id, const string nome) {
  return "remove_server NÃO IMPLEMENTADO";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  return "enter_server NÃO IMPLEMENTADO";
}

string Sistema::leave_server(int id, const string nome) {
  return "leave_server NÃO IMPLEMENTADO";
}

string Sistema::list_participants(int id) {
  return "list_participants NÃO IMPLEMENTADO";
}

string Sistema::list_channels(int id) {
  return "list_channels NÃO IMPLEMENTADO";
}
//---------------------Fim Comandos Servidor----------------------

string Sistema::create_channel(int id, const string nome) {
  return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
  return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
  return "list_messages NÃO IMPLEMENTADO";
}

/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */