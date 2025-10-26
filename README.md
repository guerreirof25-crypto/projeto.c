## Domínio do projeto
Este sistema pertence ao domínio de **gerenciamento de frotas e veículos**.  
Ele é útil para empresas ou pessoas que precisam manter o controle de veículos de forma organizada, como oficinas, locadoras, transportadoras ou pequenas frotas corporativas.  
O sistema permite registrar, consultar, atualizar e remover veículos, armazenando informações gerais e específicas de cada tipo (carros, motos e caminhões).

## O que o programa faz

O sistema permite:
- Cadastrar novos veículos  
- Listar todos os veículos já cadastrados  
- Remover um veículo do arquivo  
- Atualizar informações quando necessário  

Cada tipo de veículo tem seus próprios dados:
- **Carro:** número de portas e registros de manutenção  
- **Moto:** cilindradas  
- **Caminhão:** capacidade de carga  

## Estrutura do código

O projeto usa:
- Um `enum` pra definir os tipos de veículo (`CARRO`, `MOTO`, `CAMINHAO`)  
- Uma `struct` principal pra guardar o ID, tipo, nome e os dados específicos de cada veículo  
- Um `union` pra armazenar só as informações do tipo correspondente (economiza memória)  

O programa trabalha com dois arquivos:
- `veiculos.dat` → onde ficam todos os dados  
- `temp.dat` → usado como auxiliar pra exclusões e atualizações  
  
- Ideal pra quem quer praticar arquivos, structs e unions em C de um jeito direto.
