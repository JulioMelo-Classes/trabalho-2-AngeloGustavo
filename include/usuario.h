#ifndef USUARIO_H
#define USUARIO_H
#include <string>
using namespace std;

class Usuario{
	private:
		int id;
		string nome;
		string senha;
		string email;
		
	public:
		void setId(int _id);
		int getId();

		void setNome(string _nome);
		string getNome();

		void setSenha(string _senha);
		string getSenha();

		void setEmail(string _email);
		string getEmail();
};

#endif
