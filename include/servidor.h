#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "canaltexto.h"

#include <vector>
#include <string>

using namespace std;

class Servidor{		 
	private:
		int usuarioDonoId;
		string nome;
		string descricao;
		string codigoConvite;
		vector<int> participantesIDs;
		vector<CanalTexto> canaisTexto;

	public:
		void setDonoId(int _id);
		int getDonoId();

		void setNome(string _nome);
		string getNome();

		void setDescricao(string _descricao);
		string getDescricao();

		void setCodigo(string _codigo);
		string getCodigo();

		void addParticipante(int _id);
		void delParticipante(int _id);

		vector<string> getCanais();

		void addCanal(string nome);
};

#endif
