#ifndef MARKETPLACE_H
#define MARKETPLACE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "utils.h"

using namespace std;

class Usuario {
    public:
    int id; // número incremental
    string email;
    string nome;
    string senha_hash; // Senha em hash
};

class Produto {
    public:
    int id; // número incremental
    string nome;
    float preco;
    int quantidade;
};

class Loja {
    public:
    int id; // número incremental
    string nome;
    Usuario proprietario;
    vector<Produto> produtos;
};

class Venda {
    public:
    int id; // número incremental
    int comprador_id; // Id do Usuário que fez a compra
    int loja_id; // Id da Loja que o produto foi comprado
    int produto_id; // Id do produto comprado
    int quantidade; // Quantos produtos foram comprados
    float preco_unitario; // Qual era o preço do produto no momento da venda
};

class Marketplace {
    private:
    
    map<string, Usuario> usuarios; // Chave: email, Valor: Usuario
    map<string, int> acessos_liberados; // Chave: token_de_acesso, Valor: id_do_usuario
    map<int, Loja> lojas; // Chave: id da loja, Valor: Loja
    vector<Venda> vendas;

    public:

    Marketplace();
    bool me_cadastrar(string nome, string email, string senha);
    string login(string email, string senha);
    int criar_loja(string token, string nome);
    int adicionar_produto(string token, int loja_id, string nome, float preco);
    int adicionar_estoque(string token, int loja_id, int produto_id, int quantidade);
    bool transferir_produto(string token, int loja_origem_id, int loja_destino_id, int produto_id);
    vector<Produto> buscar_produtos(string nome_parcial);
    vector<Produto> buscar_produtos(string nome_parcial, int loja_id);
    vector<Loja> buscar_lojas(string nome_parcial);
    vector<Loja> listar_lojas();
    int comprar_produto(string token, int produto_id, int quantidade);
    // Métodos de debug (adicionar a vontade)
    void show_usuarios();
    void show_tokens();
    vector<Produto> listar_produtos();
    int id_produtos = 1;
};

#endif