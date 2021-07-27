#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <vector>
#include <string>

using namespace std;

/*
Classe servidor CP1 ok
Usualmente os dados vem antes dos métodos
*/
class Servidor{
	public:
		void setDonoId(int _id);
		int getDonoId();

		void setNome(string _nome);
		string getNome();

		void setDescricao(string _descricao);
		string getDescricao();

		void setCodigo(string _codigo);
		string getCodigo();
	private:
		int usuarioDonoId;
		string nome;
		string descricao;
		string codigoConvite;
		//vector<CanalTexto> canaisTexto;
		//vector<int> participantesIDs;
};

#endif
