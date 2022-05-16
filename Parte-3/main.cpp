#include "marketplace.h"
#include "utils.h"

int main() {
  Marketplace marketplace;

  bool cadastro1_ok, cadastro2_ok;

  cadastro1_ok = marketplace.me_cadastrar("João", "joao@gmail.com", "123456");
  testa(cadastro1_ok, "Cadastro de usuário 1");
  cadastro2_ok = marketplace.me_cadastrar("Maria", "maria@gmail.com", "654321");
  testa(cadastro2_ok, "Cadastro de usuário 2");

  marketplace.show_usuarios();

  if ( !cadastro1_ok || !cadastro2_ok) {
      cout << "Cadastro de João ou Maria nao realizado" << endl;
      return -1;
  }

  string invalid_token = marketplace.login("inexistente@hotmail.com", "senha qualquer");
  testa(invalid_token == "invalid", "login de usuario inexistente");
  
  string joao_token = marketplace.login("joao@gmail.com", "123456");
  testa(joao_token != "invalid", "login de usuario valido");
  cout << "Token de acesso recebido para João: " << joao_token << endl;

  if (joao_token != "invalid") {
      cout << "Usuário logado com sucesso" << endl;

      // João cria duas lojas com o seu token de acesso
      int bodega_do_joao_id = marketplace.criar_loja(joao_token, "Bodega do João");
      testa(bodega_do_joao_id != -1, "Cadastro de loja");
      int acougue_do_joao_id = marketplace.criar_loja(joao_token, "Açougue do João");
      testa(acougue_do_joao_id != -1, "Cadastro de loja");
      
      // João adiciona produtos na loja e altera o seu estoque
      int leite_id = marketplace.adicionar_produto(joao_token, bodega_do_joao_id, "Leite em pó", 8.40);
      testa(leite_id != -1, "Cadastro de produto");
      marketplace.adicionar_estoque(joao_token, bodega_do_joao_id, leite_id, 10);
      
      int novo_estoque_leite = marketplace.adicionar_estoque(joao_token, bodega_do_joao_id, leite_id, 5);
      testa(novo_estoque_leite == 15, "Adicionando estoque");
      
      int arroz_id = marketplace.adicionar_produto(joao_token, bodega_do_joao_id, "Arroz", 3.50);
      marketplace.adicionar_estoque(joao_token, bodega_do_joao_id, arroz_id, 40);
      
      int coca_id = marketplace.adicionar_produto(joao_token, bodega_do_joao_id, "Coca cola 250ml", 2.40);
      marketplace.adicionar_estoque(joao_token, bodega_do_joao_id, coca_id, 15);
      
      // João adicionou um produto na loja que não deveria... Aff João...
      int picanha_id = marketplace.adicionar_produto(joao_token, bodega_do_joao_id, "Picanha Maturada", 58.40);
      marketplace.adicionar_estoque(joao_token, bodega_do_joao_id, picanha_id, 5);
      
      int pic_suina_id = marketplace.adicionar_produto(joao_token, acougue_do_joao_id, "Picanha Suína", 78.40);
      marketplace.adicionar_estoque(joao_token, acougue_do_joao_id, pic_suina_id, 8);
      
      // Transferindo um produto de uma loja para outrao (do mesmo usuário)
      cout << endl << "Transferindo: ";
      marketplace.transferir_produto(joao_token, bodega_do_joao_id, acougue_do_joao_id, picanha_id);

      // Logar como Maria
      string maria_token = marketplace.login("maria@gmail.com", "654321");

      marketplace.show_tokens(); // opcional. debug
      cout << endl;

      //testando
      vector<Produto> teste = marketplace.listar_produtos();
      for(Produto prod : teste){
        cout << "id: " << prod.id << " | Produto: " << prod.nome << " | R$ " << prod.preco <<  endl;
      }

      cout << endl;

      marketplace.comprar_produto(maria_token, pic_suina_id, 2);

      // Maria buscando picanha:
      vector<Produto> picanhas = marketplace.buscar_produtos("Picanha");
      
      // verificando se achou picanhas e comprando a primeira
      if (picanhas.size() > 0) {
          marketplace.comprar_produto(maria_token, picanhas[0].id, 1);
      }

      // Maria buscando uma loja qualquer com o nome Bodega
      vector<Loja> bodegas = marketplace.buscar_lojas("Bodega");
      //Retornando se achou a loja
        for (Loja loja : bodegas) {
          cout << "LOJA encontrada: " << loja.nome << endl;
        }
      // vendo se existe alguma bodega, se existir, comprando o primeiro produto com o nome Coca
      if (bodegas.size() > 0) {
          vector<Produto> produtos = marketplace.buscar_produtos("Coca", bodegas[0].id);
          if (produtos.size() > 0) {
              marketplace.comprar_produto(maria_token, produtos[0].id, 1);
          }
      }
      
      // mostrando todas as lojas do marketplace
      vector<Loja> lojas = marketplace.listar_lojas();
      cout << endl << "Lista de lojas do marketplace com os seus produtos" << endl;
      for (Loja loja : lojas) {
          cout << loja.nome << endl;
          for (Produto produto : loja.produtos) {
              cout << "\t" << produto.id << "-" << produto.nome << endl;
          }
      }
  } else {
      cout << "Usuário não pode se logar" << endl;
  }
}