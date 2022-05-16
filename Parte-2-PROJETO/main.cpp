#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include "usu&cad.h"

using namespace std;

int main() {
  int id_cpf, add_c, N_pesquisa; 
  int valor;
  int exit1=0, exit2=0, exit_total=0;
  
  string name;
  Cadastro cad;
  
  // MENU CADASTROS

  while(exit_total != 2){
    while(exit1 != 2){
      cout << " [SISTEMA DE CADASTRO] " << endl;
      cout << endl;
      string nome;
      
      cout << "Digite o nome:" << endl;
      getline(cin, nome);
      if(nome[0]=='\0'){
        cout << "Nome em branco é inválido no sistema!" << endl <<endl;
        continue;
      }

      cout << endl << endl;

      cout << "Digite o CPF:" <<endl;
      cin >> id_cpf;

      if(cad.testarRepeticaoCPF(id_cpf)==false){}
      else{
        
        cout << endl << endl;
      
        Usuario u1(nome, id_cpf);

        //ADD CRÉDITOS
        cout<<"Adicionar ou Remover créditos?"<<endl;
        cout<<"1 - Adicionar: 1 crédito"<<endl;
        cout<<"2 - Remover: 1 crédito"<<endl;
        cout<<"3 - Adicionar quantidade desejada de créditos"<<endl;
        cout<<"4 - Remover quantidade desejada de créditos"<<endl;
        cout<<"5 - Não mudar"<<endl;

        cin >> add_c;

        switch(add_c){
          case(1):
            u1.operator++(); break;

          case(2):
            u1.operator--(); break;

          case(3):
            do{
              cout << "Qual a quantia a ser adicionada? " << endl;
              cin >> valor;
              if(valor >= 0){
                u1.adicionarCreditos(valor);
                break;
              }
              cout << "Valor negativo não permitido" << endl;
            }
            while(true); break;

          case(4):
            do{
              cout << "Qual a quantia a ser removida? " << endl;
              cin >> valor;
              if(u1.removerCreditos(valor) == true){
                //remove quantidade
                break;
              }
              cout << "Valor maior que o saldo do casdastrado" << endl;
            }
            while(true); break;

          case(5):
            cout << "Nada removido" << endl; break;
        
        }

        cad.adicionarUsuario(u1);
      }
      cout << endl;
      
      cout << "Deseja contiuar o cadastro? [1: Sim, 2: finalizar]" << endl;

      cin >> exit1;
      cout << endl;

      cin.ignore();
    }
    exit1=0;
  
    // MENU PESQUISAS
    cout << " [BUSCA NO SISTEMA DOS CADASTRADOS] " << endl;
    cout << endl;
    
    while(exit2 != 2){
      
      cout << "Digite o número correspondente para o que deseja: " << endl << endl;
      
      cout<<"1 - Lista de Cadastrados;"<<endl;
      cout<<"2 - Buscar por CPF;"<<endl;
      cout<<"3 - Buscar por Nome;"<<endl;
      cout<<"4 - Deletar por CPF;"<<endl;
      cout<<"5 - Lista Ordenada por créditos;"<<endl;

      cin >> N_pesquisa;
      cin.ignore();

      cout << endl << endl;

      switch(N_pesquisa){
        case(1):
          cout << " [LISTA DE CADASTRADOS] " << endl << endl;
          cad.getUsuarios(); break;

        case(2):
          cout << "Digite o CPF que deseja buscar: " << endl;
          cin >> id_cpf;
          cin.ignore();
          if(cad.getUsuarioPorCPF(id_cpf)==true){
            //encontrou por cpf
          }else{
            cout<<"Esse CPF não foi cadastrado no sistema!"<<endl;
          }
          break;

        case(3):
          cout << "Digite o Nome que deseja buscar: " << endl;
          getline(cin, name);
          cad.getUsuariosPorNome(name); break;

        case(4):
          cout << "Digite o CPF que deseja deletar: " << endl;
          cin >> id_cpf;
          cin.ignore();
          if(cad.delUsuarioPorCPF(id_cpf)==true){
            //deletou por cpf
          }
          else{
            cout << "Esse CPF não foi cadastrado sistema!" << endl;
          }
          break;

        case(5):
          cad.getUsuariosOrdenado(); 
          break;
      }
      
      cout << "Deseja continuar a pesquisa? [1: Sim, 2: finalizar]" << endl;
      cin >> exit2;
      cin.ignore();
    }
    exit2 = 0;

    cout << "Deseja continuar toda operação? [1: Sim, 2: finalizar]" << endl;
    cin >> exit_total;
    cin.ignore();

    cout << endl << endl;
  }
  exit_total =0;

  cout << " [PROCESSO FINALIZADO] ";

  return 0;
} 