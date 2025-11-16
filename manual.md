#  *AutoTrack - Sistema de Gerenciamento de Veículos*

<img width="392" height="344" alt="image" src="https://github.com/user-attachments/assets/47734088-fb7a-41f4-85b3-a54ce387a4ec" />


---

## **Visão geral**

AutoTrack é um sistema simples de cadastro e controle de veículos desenvolvido em linguagem C.  
Ele permite criar, buscar, editar e remover registros de veículos (carros, motos e caminhões) de forma prática, usando um arquivo binário como base de dados.

Os dados são armazenados no arquivo `veiculos.dat` e organizados de forma eficiente, permitindo operações como **remoção lógica** e **compactação física** do arquivo.

---

##  **Funcionalidades principais**

| Função | Descrição |
|--------|------------|
| **Cadastrar veículo** | Adiciona um novo veículo à base de dados. |
| **Listar veículos** | Exibe todos os veículos ativos cadastrados. |
| **Buscar por ID** | Encontra um veículo específico através do número de identificação. |
| **Buscar por nome** | Localiza veículos cujo nome contém uma determinada palavra. |
| **Editar** | Atualiza o nome de um veículo existente. |
| **Remover (lógico)** | Marca o veículo como removido, sem excluí-lo fisicamente. |
| **Compactar base** | Remove permanentemente os veículos marcados como removidos. |

---

##  **Menu principal**

Ao iniciar o programa, o usuário verá o menu abaixo:

<img width="273" height="189" alt="image" src="https://github.com/user-attachments/assets/f4e58f72-31a1-47c5-9d74-56a236d4804f" />


---

## **1. Cadastrar novo veículo**

Permite inserir um novo veículo no sistema.

**Fluxo:**
1. O usuário escolhe o tipo:  
   - 1 = Carro  
   - 2 = Moto  
   - 3 = Caminhão  
2. Informa o nome do veículo.  
3. Preenche os dados específicos (número de portas, cilindradas ou carga).  

**Exemplo de tela:**

<img width="363" height="246" alt="image" src="https://github.com/user-attachments/assets/34f718a0-25d7-4aa3-acce-5a7b311fd527" />


O veículo é salvo no arquivo `veiculos.dat`.

---

##  **2. Listar todos os veículos**

Exibe todos os veículos **ativos** (não removidos).

 **Exemplo de saída:**
 
<img width="326" height="289" alt="image" src="https://github.com/user-attachments/assets/e2bd9ddc-ce43-41cb-b3bd-a7f8b2944d25" />

---

##  **3. Buscar por ID**

Localiza um veículo específico informando seu número de identificação.

**Exemplo:**

<img width="273" height="260" alt="image" src="https://github.com/user-attachments/assets/04e10805-6860-4fd6-958f-5ba3485b774e" />


Se o ID não existir:

<img width="235" height="164" alt="image" src="https://github.com/user-attachments/assets/ac8a8f8b-fcea-48c8-aab5-ef6e6370f2f1" />


---

##  **4. Buscar por nome**

Procura veículos cujo nome contém uma determinada parte do texto.

 **Exemplo:**

<img width="284" height="234" alt="image" src="https://github.com/user-attachments/assets/d2a5ebb1-ca49-40f6-88f9-f6db15f0bb0e" />



---

##  **5. Editar veículo**

Permite alterar o **nome** de um veículo existente.

 **Exemplo:**

<img width="297" height="145" alt="image" src="https://github.com/user-attachments/assets/e16b8901-12b1-43de-b916-c73ce4056c0d" />




---

## **6. Remover (Lógico)**

Marca o veículo como **removido**, mas o registro ainda existe fisicamente no arquivo.

 **Exemplo:**

<img width="277" height="116" alt="image" src="https://github.com/user-attachments/assets/492a7fa5-8a2f-4064-8edb-262b31ce3aed" />




 O veículo não aparecerá mais nas listagens, mas continuará armazenado até a compactação.

---

##  **7. Compactar base**

Executa a **remoção física** dos veículos marcados como removidos.  
Cria um novo arquivo (`temp.dat`), copia apenas os veículos ativos e substitui o arquivo original.

**Exemplo:**


<img width="480" height="83" alt="image" src="https://github.com/user-attachments/assets/e5e4b807-e7aa-4ef9-98f7-963d5bd982d7" />


---

## **Arquivos Utilizados**

| Arquivo | Função |
|----------|--------|
| veiculos.dat | Base principal dos veículos cadastrados. |
| temp.dat | Usado temporariamente durante a compactação. |
| veiculos.h | Cabeçalho com definições da estrutura `Veiculo` e enumeração `Tipo`. |
| main.c | Arquivo principal contendo as funções e o menu do sistema. |

---

##  **Estrutura de Dados**

### Estrutura do Tipo `Veiculo`
```c
typedef struct {
  int id;
  int removido;
  Tipo tipo;
  char nome[40];
  union {
    struct { int portas; int manut[3][2]; } carro;
    struct { int cilindradas; } moto;
    struct { float carga; } caminhao;
  } info;
} Veiculo;


typedef enum { CARRO=1, MOTO, CAMINHAO } Tipo;
