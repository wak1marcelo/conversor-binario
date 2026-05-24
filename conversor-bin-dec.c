#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAM_BINARIO 8

enum Validacao {
    VALIDO = 0,
    TAMANHO_INVALIDO = 1,
    BINARIO_INVALIDO = 2
};

char validarNovaOperacao (void);
void tratarEntrada(char texto[]);
int binarioParaDecimal(const char number[]);
enum Validacao validarBinario(const char number[]);

int main(){

    char number[TAM_BINARIO + 1];
    int result;
    enum Validacao status;
    char novaOperacao;
    
do
{   
    do
    {
        printf("Digite o codigo binario: ");
        if (fgets(number, sizeof(number), stdin) == NULL){
            return 1;
        }
        
        tratarEntrada(number);

        status = validarBinario(number);

        switch (status)
        {
        case TAMANHO_INVALIDO:
            printf("Digite exatamente %d bits\n", TAM_BINARIO);
            break;
        case BINARIO_INVALIDO:
            printf("Codigo binario invalido\n");
            break;
        case VALIDO:
            break;
        default:
            printf("Erro desconhecido\n");
            break;
        }

    } while (status != VALIDO);
    
    result = binarioParaDecimal(number);
    
    printf("resultado: %d\n", result);
    
    novaOperacao = validarNovaOperacao();

} while (novaOperacao == 'S');

return 0;

}

enum Validacao validarBinario(const char number[]){
    if(strlen(number) != TAM_BINARIO){
        return TAMANHO_INVALIDO;
    }
         
    for (int i = 0; i < TAM_BINARIO; i++){
        if(number[i] != '0' && number[i] != '1'){
            return BINARIO_INVALIDO;
        }
    }

    return VALIDO;
}

int binarioParaDecimal(const char number[]){
    int result = 0;
    for (int i = 0; i < TAM_BINARIO; i++)
    {
        result = result * 2 + (number[i] - '0');
    }

    return result;
}

char validarNovaOperacao (void){
    char novaOperacao[2];

       do
        {
            printf("Quer fazer uma nova operacao(S/N): ");
            if (fgets(novaOperacao, sizeof(novaOperacao), stdin) == NULL){
                return 'N';
            }
            
            tratarEntrada(novaOperacao);
            novaOperacao[0] = toupper(novaOperacao[0]);

            if (novaOperacao[0] != 'S' && novaOperacao[0] != 'N') {
                printf("Opcao invalida. Digite S ou N.\n");
        }
        } while (novaOperacao[0] != 'S' && novaOperacao[0] != 'N');

        return novaOperacao[0];
}

void tratarEntrada(char texto[]){
    if (strchr(texto, '\n') == NULL){
        int c;
        while ((c = getchar()) != '\n' && c != EOF){
        }
    } else {
        texto[strcspn(texto, "\n")] = '\0';
    }
}