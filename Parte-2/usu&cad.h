#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

//CLASS
class Usuario{
  private:
    std::string nome;
    int cpf;
    int creditos;

  public:
  //Construtor - Usuario
    Usuario(string _nome, int _cpf);

  //MÉTODOS
    string getNome();
    void setNome(string _nome);
    int getCPF();
    int getCreditos();

  //MÉTODOS EXTRAS
    bool adicionarCreditos(int valor);
    bool removerCreditos(int valor);

  //operator
    Usuario& operator++();
    Usuario& operator--();
};

//CLASS
class Cadastro{
  private:
    map <int, Usuario> usuarios;

  public:
  //Construtor - Cadastro
    Cadastro(){}

  //MÉTODOS
    void adicionarUsuario(Usuario usuario);
    
    void getUsuarios();
    //
    bool getUsuarioPorCPF(int _cpf);
    //
    void getUsuariosPorNome(string _nome);
    //
    bool delUsuarioPorCPF(int _cpf);
    //
    void getUsuariosOrdenado();
    //
    bool testarRepeticaoCPF(int _cpf);
};