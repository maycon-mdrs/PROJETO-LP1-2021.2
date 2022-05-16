#include <iostream>
#include <vector>
using namespace std;

int main() {
  int tam = 5;
  int x, y=0;

  vector<int> vet;

  cout << "Digite 5 valores para armazenar no vector: " << endl;

  for(int i=0; i<5;i++){
    cin>> x;
    vet.push_back(x);
  }

  //Imprimir vector
  cout << "vector = ["; 
  while(y<tam-1){
    if(vet[y] > -1){
      cout << vet[y] << ",";
    }
    y++;
  }
  if(vet[y] > -1){
    cout << vet[y];
  }
  cout << "] ";

  return 0;
} 