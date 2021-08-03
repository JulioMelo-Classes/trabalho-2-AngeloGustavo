#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include "mensagem.h"

#include <vector>

using namespace std;

class CanalTexto{
	private:
		string nome;
		vector<Mensagem> mensagens;
	public:
		void setNome(string _nome);
		string getNome();

		//void listMensagens(int id);
		//void addMensagem(int id, string mensagem);
};

#endif
