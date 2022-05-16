#include "marketplace.h"

using namespace std;

Marketplace::Marketplace(){}

/**
  * Cadastra um usuário no marketplace, retornando true ou false se o cadastro foi realizado com sucesso.
  * O e-mail deve ser único
  * @param nome Nome do usuário
  * @param email Email do usuário
  * @param senha Senha do usuário. Deve ser armazenada em forma criptografada.
  * @return True se o cadastro foi realizado com sucesso, false caso contrário.
  */
bool Marketplace::me_cadastrar(string nome, string email, string senha) {
  // TODO(opcional) Implementar
  // Buscando usuário com e-mail no cadastro
  auto it = usuarios.find(email);
  // Se não existir, cria um novo usuário
  if (it == usuarios.end()) {
    Usuario novo_usuario;
    novo_usuario.id = usuarios.size() + 1; //podemos fazer assim pois não existe remoção
    novo_usuario.email = email;
    novo_usuario.nome = nome;
    novo_usuario.senha_hash = geraHash(senha);
    usuarios.insert(make_pair(email, novo_usuario));
    return true;
  }
  return false;
}

/**
  * Tenta logar o usuário com esse e-mail / senha.
  * Caso bem sucessido o login, deve gerar aleatoriamente um token de acesso
  * e o par <token, usuario_id> deve ser armazenado em "acessos_liberados".
  * @param email Email do usuário
  * @param senha Senha do usuário.
  * @return  token de acesso caso o login seja bem sucedido. Caso contrário, retornar "invalid"
  */
string Marketplace::login(string email, string senha) {
    // TODO(opcional) Implementar
    // Buscando usuário com e-mail no cadastro
    auto it = usuarios.find(email);
    // Se não existir, retorna "invalid"
    if (it == usuarios.end()) {
      return "invalid";
    }
    // Se existir, verifica se a senha está correta
    string senha_hash = geraHash(senha);
    if (it->second.senha_hash == senha_hash) {
      // Se estiver correta, gera um token de acesso
      string token_de_acesso = genRandomString(32);
      // Armazena o token de acesso e o id do usuário
      acessos_liberados.insert(make_pair(token_de_acesso, it->second.id));
      return token_de_acesso;
    }
  return "invalid";
}

/**
  * Cria uma loja no marketplace com o nome especificado para o usuário que tem
  * um acesso com esse token.
  * @param token Token de acesso
  * @param nome Nome da loja
  * @return O id da loja, ou -1 caso o token não exista em acessos_liberados ou
  * uma loja com esse nome já exista no marketplace
  */
int Marketplace::criar_loja(string token, string nome) {
  Loja n_loja;
  Usuario n_usuario;
  int liberado = 0;

  for(auto it = acessos_liberados.begin(); it != acessos_liberados.end(); ++it){
    if(it -> first == token){
      liberado = 1;
    } 
  }
  if(liberado == 1){
    n_loja.id = lojas.size()+1;
    //cout << "tamanho loja: " << lojas.size() << endl;
    //cout << "n_loja.id: " << n_loja.id << endl;
    n_loja.nome = nome;
    for(auto it = usuarios.begin(); it != usuarios.end(); ++it){
      n_loja.proprietario = it->second;
      break;
    }
    lojas.insert(make_pair(n_loja.id, n_loja));
    return n_loja.id;
  }       
  return -1;
}

/**
  * Adicionando produtos em uma loja(pelo id) de um usuário(pelo token).
  * Não é permitido adicionar um produto em um loja caso seu proprietário não seja o usuário do token passado
  * A quantidade de um produto inserido é 0 (zero)
  * 
  * @return Um id do produto adicionado para ser usado em outras operações
  */
int Marketplace::adicionar_produto(string token, int loja_id, string nome, float preco) {
  Produto novo_produto;

  auto it = acessos_liberados.find(token);
  auto loja = lojas.find(loja_id);
  if(it->second == loja->second.proprietario.id){
    //cout << "proprietario.id: " << loja->second.proprietario.id << endl;
    
    //novo_produto.id = loja->second.produtos.size()+1;

    novo_produto.id = id_produtos;

    //cout << "tamanho size: " << loja->second.produtos.size() << endl;
    //cout << "novo_produto_id: " << novo_produto.id << endl;

    novo_produto.nome = nome;
    //cout << "novo_produto2: " << novo_produto.nome << endl; 
    novo_produto.preco = preco;
    //cout << "novo_produto_preco: " << novo_produto.preco << endl;

    novo_produto.quantidade = 0;

    id_produtos++;

    this->lojas.find(loja_id)->second.produtos.push_back(novo_produto);

    return novo_produto.id;
  }
return -1;
}

/**
  * Adiciona uma quantidade em um produto em uma loja(pelo id) de um usuário(pelo token).
  * 
  * @param token Token de acesso
  * @param loja_id Id da loja
  * @param produto_id Id do produto
  * @param quantidade Quantidade a ser adicionada
  * @return retornar novo estoque
  */
int Marketplace::adicionar_estoque(string token, int loja_id, int produto_id, int quantidade) {
  Produto produto_;
  auto it = acessos_liberados.find(token);
  auto loja = lojas.find(loja_id);

  cout << endl << endl << "ADICIONAR ESTOQUE:" << endl;

  if(it != acessos_liberados.end()){
    if(it->second == loja->second.proprietario.id){
      for(auto produto = loja->second.produtos.begin();produto != loja->second.produtos.end(); produto++ ){
        if(produto->id == produto_id){
          produto->quantidade += quantidade;
          cout << "Produto: " << produto->nome << " | Quantidade: " << produto->quantidade << endl;

          return produto->quantidade;
        }
      }
    }
  }
  return -1;
}

/**
  * Muda um produto da loja com o id loja_origem_id para loja_destino_id
  * Garantir que:
  *  - loja_origem_id e loja_destino_id são do usuário
  *  - O produto está originalmente na loja_origem
  *  - loja_origem_id != loja_destino_id
  * 
  * @param token Token de acesso
  * @param loja_origem_id Id da loja de origem
  * @param loja_destino_id Id da loja de destino
  * @param produto_id Id do produto
  * @return True se a operação foi bem sucedida, false caso contrário
  */
bool Marketplace::transferir_produto(string token, int loja_origem_id, int loja_destino_id, int produto_id) {

  auto it = acessos_liberados.find(token);
  auto loja_origem = lojas.find(loja_origem_id);
  auto loja_destino = lojas.find(loja_destino_id);

  if(it != acessos_liberados.end()){
    if(it->second == loja_origem->second.proprietario.id && it->second == loja_destino->second.proprietario.id ){
      for(auto produto = loja_origem->second.produtos.begin(); produto != loja_origem->second.produtos.end(); produto++){
        if(produto->id == produto_id){
          Produto produto_loja_final;

          //produto_loja_final.id = produto->id + loja_destino->second.produtos.size();//para tentar não ficr como o mesmo id

          produto_loja_final.id = produto->id;
          produto_loja_final.nome = produto-> nome;
          cout << produto_loja_final.nome << endl << endl;
          produto_loja_final.preco = produto->preco;
          produto_loja_final.quantidade = produto->quantidade;
          loja_destino->second.produtos.push_back(produto_loja_final);
          loja_origem->second.produtos.erase(produto);
          return true;
        }
      }
    }
  }
  return false;
}

/**
  * Lista de produtos do marketplace que tem a string nome_parcial no nome
  * 
  * @param nome_parcial String que deve aparecer no nome do produto
  * @return Lista de produtos que tem a string nome_parcial no nome
  */
vector<Produto> Marketplace::buscar_produtos(string nome_parcial) {
  vector<Produto> encontrados;

  for(auto par : this->lojas){
    auto loja_id = par.first;
    auto loja = par.second;
    for(auto produto : loja.produtos){
      if(produto.nome.find(nome_parcial) != std::string::npos){
        encontrados.push_back(produto);
        //cout << "teste produtos: " << produto.nome << endl;
      }
    }
  }
  if(encontrados.size() == 0){
    cout << "Produto não encontrado !" << endl;
  }
  return encontrados;
}

/**
  * Lista de produtos de uma loja específica do marketplace que tem a string nome_parcial no nome
  * 
  * @param nome_parcial String que deve aparecer no nome do produto
  * @param loja_id Id da loja
  * @return Lista de produtos que tem a string nome_parcial no nome e que pertencem a loja especificada
  */
vector<Produto> Marketplace::buscar_produtos(string nome_parcial, int loja_id) {
  vector<Produto> encontrados;
            
  for(auto par : this->lojas){
    if(par.first == loja_id){
      auto chave_loja = par.first;
      auto loja = par.second;
      for(auto produto : loja.produtos){
        if(produto.nome.find(nome_parcial) != std::string::npos){
          encontrados.push_back(produto);
          //cout << "teste produtos_id: " << produto.nome << endl;
        }
      }
    }
  }
  return encontrados;
}

/**
  * Lista de produtos - feita por maycon
  * OBJETIVO : teste
  */
vector<Produto> Marketplace::listar_produtos(){
  vector<Produto> encontrados;
  for(auto loja : this->lojas){
    auto loja_id = loja.first;
    auto _loja = loja.second;
    for(auto produto : _loja.produtos){
      encontrados.push_back(produto);
    }
  }
  return encontrados;
}

/**
  * Lista de lojas do marketplace que tem a string nome_parcial no nome
  * 
  * @param nome_parcial String que deve aparecer no nome da loja
  * @return Lista de lojas que tem a string nome_parcial no nome
  */
vector<Loja> Marketplace::buscar_lojas(string nome_parcial) {
  vector<Loja> encontradas; 
  for(auto loja : this->lojas){
    auto chave_id = loja.first;
    auto _loja = loja.second;

    if (_loja.nome.find(nome_parcial) != std::string::npos){
      encontradas.push_back(_loja);
    }
  }
  return encontradas;
}

/**
  * Lista de lojas do marketplace
  * 
  * @return Lista de lojas do marketplace
  */
vector<Loja> Marketplace::listar_lojas() {
  vector<Loja> encontradas;
  for(auto loja : this->lojas){
    auto chave_id = loja.first;
    auto _loja = loja.second;
    
    encontradas.push_back(_loja);
  }
  return encontradas;
}

/**
  * Cria uma nova Venda para o usuário com acesso com esse token,
  * para o produto especificado, para a loja desse produto e com a quantidade especificada.
  * 
  * @param token Token de acesso
  * @param produto_id Id do produto
  * @param quantidade Quantidade a ser vendida
  * @return Id da venda criada ou -1 caso não seja possível criar a venda
  */
int Marketplace::comprar_produto(string token, int produto_id, int quantidade) {
  Venda venda;

  cout << "COMPRAR_PRODUTO: ";

  auto it = acessos_liberados.find(token);
  if(it != acessos_liberados.end()){
    venda.id = vendas.size() + 1;
    //cout << "venda.id: " <<  venda.id << endl;

    venda.produto_id = produto_id;
    //cout << "venda.produto_id: " << venda.produto_id << endl;

    venda.quantidade = quantidade;
    //cout << "venda.quantidade: " << venda.quantidade << endl;

    for(auto loja = lojas.begin(); loja != lojas.end(); loja++){
      for(auto produto = loja->second.produtos.begin();produto != loja->second.produtos.end(); produto++ ){
        if(produto->id == produto_id && produto->quantidade > quantidade){
          //venda.loja_id = loja->second.id;
          cout << " | " << produto->nome << " | " << "R$ ";

          venda.preco_unitario = produto->preco;
          cout << venda.preco_unitario << endl;

          produto->quantidade -= quantidade;
          //cout << "produto->quantidade: " << produto->quantidade << endl;

          vendas.push_back(venda);

          return produto->quantidade;
        }
      }
    }
  }
  return venda.id;
}


// Métodos de debug (adicionar a vontade)
void Marketplace::show_usuarios() {
    for (auto it = usuarios.begin(); it != usuarios.end(); it++) {
        cout << it->first << " >>> " << it->second.senha_hash << endl;
    }
}
void Marketplace::show_tokens() {
    for (auto it = acessos_liberados.begin(); it != acessos_liberados.end(); it++) {
        cout << it->first << " >>> " << it->second << endl;
    }
}
