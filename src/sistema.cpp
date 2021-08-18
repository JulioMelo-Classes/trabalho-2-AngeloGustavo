#include "sistema.h"
#include "usuario.h"
#include "servidor.h"
#include "mensagem.h"
#include "canaltexto.h"

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

  Usuario temp(this->usuarios.size(), nome, senha, email);
  usuarios.push_back(temp);

  return "Criando usuário "+temp.getNome()+" ("+temp.getEmail()+")\nUsuário Criado";
}

string Sistema::login(const string email, const string senha) {
  for(int i=0; i<this->usuarios.size(); i++)
    if(usuarios[i].checkLogin(email, senha) == true){
      this->usuariosLogados.insert({this->usuarios[i].getId(), {"",""}});
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
      
      Servidor temp(id, nome);
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
            return "Descrição do servidor '"+nome+"' modificada!";
          }else
            return "Você não pode alterar a descrição de um servidor que não foi criado por você";
        }
      return "Servidor '"+nome+"' não existe";
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
              return "Código de convite do servidor '"+nome+"' modificado!";
            else
              return "Código de convite do servidor '"+nome+"' removido!";
          }else
            return "Você não pode alterar o codigo de convite de um servidor que não foi criado por você";
        }
      return "Servidor '"+nome+"' não existe";
    }
  return "Usuário não conectado";
}

string Sistema::list_servers(int id) {
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      if(servidores.size() == 0)
        return "Não há servidores no sistema";
      for(int i=0; i<servidores.size(); i++){
        if(i>0)
          cout<<endl;
        cout<<servidores[i].getNome();
      }
      return "";
    }
  return "Usuário não conectado";
}

string Sistema::remove_server(int id, const string nome) {
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      for(int i=0; i<servidores.size(); i++)
        if(nome == servidores[i].getNome()){
          if(servidores[i].getDonoId() == id){
            for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
              if((itr->second).first == nome)
                itr->second = {"",""};
            servidores.erase(servidores.begin() + i);
            return "Servidor '"+nome+"' removido";
          }else
            return "Você não é o dono do servidor '"+nome+"'";
        }
      return "Servidor '"+nome+"' não encontrado";
    }
  return "Usuário não logado";
}

/*
A2.7 0,8
*/
string Sistema::enter_server(int id, const string nome, const string codigo) {
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      //esse aqui não é um caso de erro, quando o enter server é chamado 2 vezes o sistema deve mudar o servidor que o usuário visualiza
      //da forma como está aqui o usuário só consegue entrar em um servidor, vou tirar 20% por isso
      if((itr->second).first != "") 
        return "Usuário ja está em um servidor";
      for(int i=0; i<servidores.size(); i++)
        if(servidores[i].getNome() == nome){
          if(servidores[i].getDonoId() == id || servidores[i].getCodigo() == "" || servidores[i].getCodigo() == codigo){
            servidores[i].addParticipante(id);
            itr->second = {servidores[i].getNome(),""};
            return "Entrou no servidor com sucesso";
          }else if(codigo == "")
            return "Servidor requer código de convite";
          else 
            return "Código de convite errado";
        }
      return "Servidor '"+nome+"' não encontrado";
    }
  return "Usuário não conectado";
}

/*
A2.8 0,8
*/
string Sistema::leave_server(int id, const string nome) {
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      for(int i=0; i<servidores.size(); i++)
        if(servidores[i].getNome() == nome){
          if(nome == (itr->second).first){
            servidores[i].delParticipante(id);
            itr->second = {"",""};
            return "Saindo do servidor '"+nome+"'";
          }else if((itr->second).first == "") 
            //esse aqui também não é um caso de teste, leave server deve sair do servidor dado pelo usuário
            //mesmo que ele não esteja visualizando qualquer. Nesse caso vou remover 20% uma vez que o usuário não
            //consegue sair de servidores que ele não está visualizando
            return "Você não está visualizando nenhum servidor";
          else
            return "Você não está nesse servidor";
        }
      return "Servidor '"+nome+"' não encontrado";
    }
  return "Usuário não conectado";
}

/*
A.9 0,3
*/
string Sistema::list_participants(int id) {
  bool primeiro = true;
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      if((itr->second).first == "")
        return "Você não está em um servidor";
      for(auto itr2=usuariosLogados.begin(); itr2!=usuariosLogados.end(); ++itr2)
        if((itr->second).first == (itr2->second).first){
          if(primeiro == true)
            primeiro = false;
          else
            cout<<endl;
          /*essa não é a forma como esse método deve funcionar
          o que você faz aqui é mostrar quais usuários estão visualizando
          o servidor ao mesmo tempo que o usuário que chamou o comando,
          na verdade esse comando deveria mostrar quais participantes fizeram
          "enter-server" no servidor específico
          vou considerar 30%*/
          for(int i=0; i<usuarios.size(); i++)
            if(usuarios[i].getId() == itr2->first)
              cout<<usuarios[i].getNome();
        }
      return "";
    }
  return "Usuário não conectado";
}

/*
B1.1 ok
*/
string Sistema::list_channels(int id) {
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id)
      for(int i=0; i<servidores.size(); i++)
        if(servidores[i].getNome() == (itr->second).first){
          servidores[i].printCanais();
          return "";
        }
  return "Usuário não conectado";
}

/*
B1.2 ok
*/
string Sistema::create_channel(int id, const string nome) {
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      if((itr->second).first == "")
        return "Você não está em um servidor";
      for(int i=0; i<servidores.size(); i++)
        if(servidores[i].getNome() == (itr->second).first){
          bool bol = servidores[i].checkCanal(nome);
          if(bol == true)//podia usar direto if(servidores[i].checkCanal(nome))
            return "Canal de texto '"+nome+"' já existe!";
          servidores[i].addCanal(nome);
          return "Canal de texto '"+nome+"' criado";
        }
    }
  return "Usuário não conectado";
}

/*
B1.3 ok
*/
string Sistema::enter_channel(int id, const string nome) {
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id)
      for(int i=0; i<servidores.size(); i++)
        if(servidores[i].getNome() == (itr->second).first){
          bool bol = servidores[i].checkCanal(nome);
          if(bol == false)
            return "Canal '"+nome+"' não existe";
          (itr->second).second = nome;
          return "Entrou no canal '"+nome+"'";         
        }
  return "Usuário não conectado";
}

/*
B1.4 ok
*/
string Sistema::leave_channel(int id) {
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      (itr->second).second = "";
      return "Saindo do canal";
    }
  return "Usuário não conectado";
}

/*
B2.1 ok
*/
string Sistema::send_message(int id, const string mensagem) {
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      if((itr->second).second == "")
        return "Você não está em um canal";
      for(int i=0; i<servidores.size(); i++)
        if(servidores[i].getNome() == (itr->second).first)
          servidores[i].addMensagem_Server(id, mensagem, (itr->second).second);
      return "Mensagem enviada";
    }
  return "Usuário não conectado";
}

/*
B2.2 ok
*/
string Sistema::list_messages(int id) {
  for(auto itr=usuariosLogados.begin(); itr!=usuariosLogados.end(); ++itr)
    if(itr->first == id){
      if((itr->second).second == "")
        return "Você não está em um canal";
      for(int i=0; i<servidores.size(); i++)
        if(servidores[i].getNome() == (itr->second).first)
          servidores[i].printMensagens_Server((itr->second).second, &usuarios); //aqui vc poderia usar uma referencia de C++ ao invés de um ponteiro
      return "";
    }   
  return "Usuário não conectado";
}

/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
