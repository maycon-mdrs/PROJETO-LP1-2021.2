#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class usuario{
  public:
    string nome;

    usuario(string nome){
      this->nome = nome;
    }
};

int main() {
  vector <usuario> cadastro;

  int num = 0;
 
  string nome_tmp;
  bool can_add = false;

  while(num != 2){
    can_add = true;
    cout << "DIGITE NOME DO USUARIO PARA CADASTRAR:" << endl; 
    getline(cin>>ws, nome_tmp);
    //cout << "nome:" << nome_tmp << endl;

    for (auto it = cadastro.begin(); it != cadastro.end(); ++it){
        if (nome_tmp.compare(it->nome) == 0){
            cout << "Usuário já foi cadastrado anteriomente!" << endl;
            can_add = false;
            break;
        }
    }

    if (can_add){
        cadastro.push_back(usuario(nome_tmp));
        cout << "Cadastro realizado com sucesso" << endl;
    }

    //Repetir loop
    cout << "Deseja realizar novo cadastro? [1: sim, 2: finalizar]: " << endl;
    cin >> num;
  }
  
  //mostrar todos os usuarios cadastrados
  cout << "    [CADASTRADOS]  " << endl;
  for(int i=0; i<cadastro.size(); i++){
    cout<< "-> nome: " << cadastro[i].nome << endl;
  }

  return 0;
} 