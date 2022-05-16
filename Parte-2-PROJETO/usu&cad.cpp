#include "usu&cad.h"

using namespace std;

////* USUARIO *////
//Construtor - Usuario
Usuario::Usuario(string _nome, int _cpf){
  this->nome = _nome;
  this->cpf = _cpf;

  creditos = 10;
}

//MÉTODOS
string Usuario::getNome(){
  return this->nome;
}

void Usuario::setNome(string _nome){
  if(_nome[0]=='\0'){
    cout << " Nome em branco inválido! " << endl;
  }else{
    this->nome = _nome;
  }
}

int Usuario::getCPF(){
  return this->cpf;
}

int Usuario::getCreditos(){
  return this->creditos;
}

bool Usuario::adicionarCreditos(int valor){
  if(valor >= 0){
    this->creditos += valor;
    return true;
  }
  else{
    return false;
  }
}

bool Usuario::removerCreditos(int valor){
  if(creditos >= valor){
    this->creditos -= valor;
    return true;
  }
  else{
    return false;
  }
}

//OPERADOR 
Usuario& Usuario::operator++(){
  this->adicionarCreditos(1);
  return *this;
}

Usuario& Usuario::operator--(){
  this->removerCreditos(1);
  return *this;
}


////* CADRASTRO *////
//MÉTODOS
void Cadastro::adicionarUsuario(Usuario _usuario){
  if (usuarios.count(_usuario.getCPF())>0){
    return;
  }
  else{
    usuarios.insert(pair<int, Usuario>(_usuario.getCPF(), _usuario));
  }
}

void Cadastro::getUsuarios(){
 for (auto uso: this->usuarios) {
    auto cpf = uso.first;
    auto _usuario = uso.second;

    cout<<"[ Nome: " << _usuario.getNome();

    cout<<" | CPF: " << _usuario.getCPF();

    cout<<" | Créditos: " << _usuario.getCreditos() << " ]" << endl;

    cout << endl;
  }
}

bool Cadastro::getUsuarioPorCPF(int _cpf){
  for (auto uso: this->usuarios) {
    auto cpf = uso.first;
    auto _usuario = uso.second;

    if(cpf == _cpf){
      cout<<"[ Nome: " << _usuario.getNome();

      cout<<" | CPF: " << _usuario.getCPF();

      cout<<" | Créditos: " << _usuario.getCreditos() << " ]" << endl;

      cout << endl;
      
      return true;
    }
  }

  return false;
}

 void Cadastro::getUsuariosPorNome(string _nome){
    for (auto uso : this->usuarios) {
      auto cpf = uso.first;
      auto _usuario = uso.second;

      if(_usuario.getNome() == _nome){
        cout<<"[ Nome: " << _usuario.getNome();

        cout<<" | CPF: " << _usuario.getCPF();

        cout<<" | Créditos: " << _usuario.getCreditos() << " ]" << endl;

        cout << endl;
      }
    } 
 }

bool Cadastro::delUsuarioPorCPF(int _cpf){
  this->usuarios.erase(_cpf);
  cout << "Usuário deletado com sucesso!" << endl << endl;
  return true;
}

void Cadastro::getUsuariosOrdenado(){
  for(int i=0; i<1000; i++){
    for (auto uso : this->usuarios){
      auto cpf = uso.first;
      auto _usuario = uso.second;

      if(_usuario.getCreditos() == i){
        cout<<"[ Nome: " << _usuario.getNome();

        cout<<" | CPF: " << _usuario.getCPF();

        cout<<" | Créditos: " << _usuario.getCreditos() << " ]" << endl;

        cout << endl;
      }
    }
  }
}

//TESTAR CPF
bool Cadastro::testarRepeticaoCPF(int id_cpf){
  for (auto chave_cpf: this->usuarios) {
    auto cpf = chave_cpf.first;
    if(cpf==id_cpf){
      cout<<"CPF já cadastrado!"<<endl; 
      return false;    
    }
  }
  return true;
}