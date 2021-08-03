#ifndef MENSAGEM_H
#define MENSAGEM_H

using namespace std;

class Mensagem{
    private:
        string dataHora;
        int enviadaPor;
        string conteudo;
    public:
        void setDataHora(string _dataHora);
        string getDataHora();

        void setEnviadaPor(int _enviadaPor);
        int getEnviadaPor();
                
        void setConteudo(string _conteudo);
        string getConteudo();       
};

#endif