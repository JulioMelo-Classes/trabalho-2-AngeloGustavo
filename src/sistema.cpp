#include "sistema.h"
#include "usuario.h"
#include "servidor.h"

#include <iostream>
#include <iterator>
#include <map>
#include <vector>

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
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      usuariosLogados.erase(id);
      return "Desconectando usuário "+this->usuarios[id].getEmail();       
    }
  return "Não está conectado";
}

string Sistema::create_server(int id, const string nome) {
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      for(int i=0; i<this->servidores.size(); i++)
        if(this->servidores[i].getNome() == nome)
          return "Servidor com esse nome já existe";
      
      Servidor temp;
      temp.setDonoId(id);
      temp.setNome(nome);
      servidores.push_back(temp);

      return "Servidor criado"; 
    }
  return "Usuário não conectado";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      for(int i=0; i<servidores.size(); i++)
        if(servidores[i].getNome() == nome){
          if(servidores[i].getDonoId() == id){
            servidores[i].setDescricao(descricao);
            return "Descrição do servidor ‘"+nome+"’ modificada!";
          }else
            return "Você não pode alterar a descrição de um servidor que não foi criado por você";
        }
      return "Servidor ‘"+nome+"’ não existe";
    }
  return "Usuário não conectado";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){  
      for(int i=0; i<servidores.size(); i++)
        if(servidores[i].getNome() == nome){
          if(servidores[i].getDonoId() == id){
            servidores[i].setCodigo(codigo);
            if(codigo != "")
              return "Código de convite do servidor ‘"+nome+"’ modificado!";
            else
              return "Código de convite do servidor ‘"+nome+"’ removido!";
          }else
            return "Você não pode alterar o codigo de convite de um servidor que não foi criado por você";
        }
      return "Servidor ‘"+nome+"’ não existe";
    }
  return "Usuário não conectado";
}

string Sistema::list_servers(int id) {
  string saida;
  for(int i=0; i<servidores.size(); i++)
    if(servidores[i].getDonoId() == id){
      if(saida != "")
        saida += "\n";
      saida += servidores[i].getNome();
    }
  return saida;
}

string Sistema::remove_server(int id, const string nome) {
  int cont;

  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      cont=0;
      for(auto itr2=servidores.begin(); itr2!=servidores.end(); ++itr2){
        if(nome == servidores[cont].getNome()){
          if(servidores[cont].getDonoId() == id){
            servidores.erase(itr2);
            return "Servidor ‘"+nome+"’ removido";
          }else
            return "Você não é o dono do servidor ‘"+nome+"’";
        }cont++;
      }
      return "Servidor ‘"+nome+"’ não encontrado";
    }
  return "Usuário não logado";
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