#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <vector>
#include <string>

using namespace std;

class Servidor{		 
	private:
		int usuarioDonoId;
		string nome;
		string descricao;
		string codigoConvite;
		//vector<CanalTexto> canaisTexto;
		vector<int> participantesIDs;

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
};

#endif
