# Parte 2)
Faça um novo programa, também de cadastro de usuários, porém com as seguintes
restrições:
1) Classe Usuario com os atributos privados: ```nome (string)```, ```cpf (int)```, ```creditos (int)```
2) Um construtor para Usuario que recebe por parâmetro o ```nome``` e ```cpf```. Os ```créditos``` devem ser iniciados com o valor 10
3) Métodos públicos para obter e setar valores aos atributos de Usuario:

    - a) ```getNome```: Retorna o nome atual do usuário
    - b) ```setNome```: Altera o nome do usuário. Não deve aceitar nomes em branco. Podem haver repetições de nome.
    - c) ```getCPF```: Retorna o CPF do usuário.
    - d) ```setCPF``` não deve existir, já que esse dado é somente leitura
    - e) ```getCreditos```: Retorna os créditos atuais do usuário
    
4) Métodos extras para usuário (também públicos):
    - a) ```adicionarCreditos```: Deve ter uma quantidade de créditos passadas por parâmetro, que devem ser adicionadas aos créditos do usuário. Garanta que devem ser adicionados somente valores positivos.
    - b) ```removerCreditos```: Deve ter uma quantidade de créditos passadas por parâmetro, que devem ser removidos dos créditos do usuário. Garanta que os créditos não possam ficar negativos.
    - c) Em casos de erro, esses métodos devem retornar o boleano "falso", e "verdade" em caso de execução com sucesso.

5) Sobrecarregar o ```operador ++``` em Usuario de modo que ele adicione 1 crédito ao usuário
6) Sobrecarregar o ```operador --``` em Usuario de modo que ele remova 1 crédito do usuário, caso isso não deixe o crédito negativo.
7) Crie uma classe chamada Cadastro com:
    - a) Um atributo privado chamado "usuarios", que guardará a coleção de usuários do cadastro, e que deve ser map<int, Usuario>, ou seja, uma coleção de usuários indexados por um inteiro que será uma analogia ao seu CPF. Isso significa que o mesmo CPF dentro de cada usuário será usado como a chave desse map.
    - b) Um método público chamado adicionarUsuario(Usuario usuario) que irá adicionar esse usuário no cadastro, indexado pelo seu CPF que já está no objeto. Isso significa que um ```pair <cpf, usuario>``` deverá ser adicionado na variável "usuarios". Não é possível adicionar usuários com CPFs já no cadastro
    - c) É possível ter usuários com mesmo nome no cadastro, porém não com mesmo CPF (chave do map)
    - d) Adicione as seguintes ações (métodos) no cadastro:
      - i) getUsuarios: Retornar todos os usuários cadastrados
      - ii) getUsuarioPorCPF: Buscar e retornar um usuário por CPF
      - iii) getUsuariosPorNome: Buscar e retornar usuários por nome (pode existir mais de um com o mesmo nome)
      - iv) delUsuarioPorCPF: Remover um usuário por CPF
      - v) getUsuariosOrdenado: Retornar todos os usuários ordenados por crédito (de quem tem menos para quem tem mais)
    - e) Escolha e implemente uma forma para que os retornos dos métodos de busca que fracassam representem esse fracasso (que quem o chamou saiba que nada retornou)
   
8) Crie um programa que testa todas as funcionalidades que você implementou.
