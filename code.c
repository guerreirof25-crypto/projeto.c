#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ARQ "veiculos.dat"
#define ARQ_TEMP "temp.dat"

typedef enum{CARRO=1,MOTO,CAMINHAO} Tipo;

typedef struct{
  int id;
  int removido;
  Tipo tipo;
  char nome[40];
  union{
    struct{int portas;int manut[3][2];} carro;
    struct{int cilindradas;} moto;
    struct{float carga;} caminhao;
  }info;
}Veiculo;

//////////////////////////////////////////////////////////////////////FUNÇÕES AUXILIARES/////////////////////////////////////////////////////////////////////////////

int lerInt(const char *msg) {
    int n;
    printf("%s", msg);
    while (scanf("%d", &n) != 1) {
        printf("Valor inválido, digite novamente: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return n;
}

float lerFloat(const char *msg) {
    float n;
    printf("%s", msg);
    while (scanf("%f", &n) != 1) {
        printf("Valor inválido, digite novamente: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return n;
}

void lerString(const char *msg, char *dest, size_t tam) {
    printf("%s", msg);
    fgets(dest, tam, stdin);
    dest[strcspn(dest, "\n")] = 0;
}

//////////////////////////////////////////////////////////////////////////EDITAR O VEÍCULO//////////////////////////////////////////////////////////////////////////////////////

void editar() {
    int id = lerInt("ID do veículo a editar: ");
    FILE *f = fopen(ARQ, "rb+");
    if (!f) {
        puts("Arquivo não encontrado.");
        return;
    }
 Veiculo v;
    long pos = 0;
    int achou = 0;

    while (fread(&v, sizeof(Veiculo), 1, f)) {
        if (v.id == id && !v.removido) {
            pos = ftell(f) - sizeof(Veiculo);
            achou = 1;
            break;
        }
    }

    if (!achou) {
        puts("Veículo não encontrado.");
        fclose(f);
        return;
    }
  
    lerString("Novo nome: ", v.nome, sizeof(v.nome));
    fseek(f, pos, SEEK_SET);
    fwrite(&v, sizeof(Veiculo), 1, f);
    fclose(f);
    puts("Veículo atualizado com sucesso!");
}

///////////////////////////////////////////////////////////////////////////REMOVER LÓGICO//////////////////////////////////////////////////////////////////////////

void remover() {
    int id = lerInt("ID do veículo a remover: ");
    FILE *f = fopen(ARQ, "rb+");
    if (!f) {
        puts("Arquivo não encontrado.");
        return;
    }

    Veiculo v;
    int achou = 0;
    while (fread(&v, sizeof(Veiculo), 1, f)) {
        if (v.id == id && !v.removido) {
            v.removido = 1;
            fseek(f, ftell(f) - sizeof(Veiculo), SEEK_SET);
            fwrite(&v, sizeof(Veiculo), 1, f);
            achou = 1;
            break;
        }
    }
    fclose(f);
    puts(achou ? "Veículo removido com sucesso!" : "Veículo não encontrado.");
}

//////////////////////////////////////////////////////////////////////////// COMPACTAR(REMOÇÃO FÍSICA)//////////////////////////////////////////////////////////////////////////

void compactar() {
    FILE *f = fopen(ARQ, "rb");
    if (!f) {
        puts("Arquivo não encontrado.");
        return;
    }

    FILE *tmp = fopen(ARQ_TEMP, "wb");
    if (!tmp) {
        perror("Erro ao criar arquivo temporário");
        fclose(f);
        return;
    }

    Veiculo v;
    int ativos = 0;
    while (fread(&v, sizeof(Veiculo), 1, f))
        if (!v.removido) {
            fwrite(&v, sizeof(Veiculo), 1, tmp);
            ativos++;
        }

    fclose(f);
    fclose(tmp);
    remove(ARQ);
    rename(ARQ_TEMP, ARQ);
    printf("Compactação concluída. %d veículos permanecem ativos.\n", ativos);
}

//////////////////////////////////////////////////////////////////////////PROXIMO ID/////////////////////////////////////////////////////////////////////////////////////

int proximoID() {
    FILE *f = fopen(ARQ, "rb");
    if (!f) return 1;
    Veiculo v;
    int max = 0;
    while (fread(&v, sizeof(Veiculo), 1, f))
        if (v.id > max) max = v.id;
    fclose(f);
    return max + 1;
}

//////////////////////////////////////////////////////////////////////////PRA EXIBIR O VEICULO/////////////////////////////////////////////////////////////////////////////

void mostrarVeiculo(Veiculo v) {
    printf("\n--- Detalhes do veículo ---\n");
    printf("ID: %d\n", v.id);
    printf("Nome: %s\n", v.nome);
    printf("Tipo: ");
    switch (v.tipo) {
        case CARRO:
            printf("Carro\nPortas: %d\n", v.info.carro.portas);
            break;
        case MOTO:
            printf("Moto\nCilindradas: %d\n", v.info.moto.cilindradas);
            break;
        case CAMINHAO:
            printf("Caminhão\nCapacidade de carga: %.1f toneladas\n", v.info.caminhao.carga);
            break;
    }
    printf("---------------------------\n");
}

////////////////////////////////////////////////////////////////////////// CRIAR VEÍCULO/////////////////////////////////////////////////////////////////////////////

void criar(){
    Veiculo v= {0};
    v.id= proximoID();
    v.removido= 0;
    v.tipo= lerInt("Tipo (1= Carro, 2= Moto, 3= Caminhão): ");
    lerString("Nome do veículo: ", v.nome, sizeof(v.nome));

    if (v.tipo== CARRO){
        V.info.carro.portas= lerInt("Quantidade de portas: ");
        memset(v.info.carro.manut, 0, sizeof(v.info.carro.manut));
    } else if (v.tipo== MOTO){
        v.info.moto.cilindradas= lerINT("Cilindradas: ");
    } else{
        v.info.caminhao.carga= lerFloat("Capacidade de carga (toneladas): ");
    }

    FILE *f= fopen (ARQ, "ab");
    if (!f){
        perror("Erro ao abrir o arquivo");
        return;
    }
    fwrite(&v, sizeof(Veiculo), 1, f);
    fclose(f);

    printf("Veículo cadastrado com sucesso! ID: %d\n, v.id);
}

//////////////////////////////////////////////////////////////////////////LISTAR VEÍCULO/////////////////////////////////////////////////////////////////////////////

void listar() {
    FILE *f = fopen(ARQ, "rb");
    if (!f) {
        puts("Nenhum veículo cadastrado ainda.");
        return;
    }
    Veiculo v;
    int cont = 0;
    while (fread(&v, sizeof(Veiculo), 1, f))
        if (!v.removido) {
            mostrarVeiculo(v);
            cont++;
        }
    if (!cont) puts("Nenhum veículo ativo encontrado.");
    fclose(f);
}

//////////////////////////////////////////////////////////////////////////BUSCAR POR ID////////////////////////////////////////////////////////////////////////////

void buscar ID(){
    int id= lerInt("Digite o ID: ");
    FILE *f= fopen(ARQ, "rb");
    if (!f) {
        puts("Arquivo não encontrado.");
        return;
    }
    Veiculo v;
    int achou= 0;
    while (fread(&v, sizeof(Veiculo), 1, f)) {
        if (v.id == id && !v.removido) {
            mostrarVeiculo(v);
            achou = 1;
            break;
        }
    }
    if (!achou) puts("Veículo não encontrado.");
    fclose(f);
}

////////////////////////////////////////////////////////////////////////// BUSCAR POR NOME////////////////////////////////////////////////////////////////////////////

void buscarNome() {
    char termo[40];
    lerString("Digite parte do nome: ", termo, sizeof(termo));
    FILE *f=  fopen(ARQ, "rb");
    if (!f) {
        puts("Arquivo não encontrado.");
        return;
    }
    Veiculo v;
    int achou= 0;
    while (fread(&v, sizeof(Veiculo), 1, f))
        if (!v.removido && strstr(v.nome, termo)){
            mostrarVeiculo(v);
            achou= 1;
        }
        if (!achou) puts("Nenhum veículo com esse nome foi encontrado.");
        fclose(f);
}

////////////////////////////////////////////////////////////////////////////MENU////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int op;
    do {
        printf("\n===== MENU DE VEÍCULOS =====\n"
               "1 - Cadastrar novo veículo\n"
               "2 - Listar todos\n"
               "3 - Buscar por ID\n"
               "4 - Buscar por nome\n"
               "5 - Editar\n"
               "6 - Remover (lógico)\n"
               "7 - Compactar base\n"
               "0 - Sair\n");
        op = lerInt("Escolha uma opção: ");
        switch (op) {
            case 1: criar(); break;
            case 2: listar(); break;
            case 3: buscarID(); break;
            case 4: buscarNome(); break;
            case 5: editar(); break;
            case 6: remover(); break;
            case 7: compactar(); break;
            case 0: puts("Encerrando o programa. Até logo!"); break;
            default: puts("Opção inválida, tente novamente.");
        }
    } while (op != 0);
}
