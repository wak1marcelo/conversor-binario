#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAM_BINARIO 8
#define TAM_BUFFER 50

enum Validacao {
    VALIDO = 0,
    TAMANHO_INVALIDO = 1,
    BINARIO_INVALIDO = 2
};

void limparBuffer(void);
void removerNewLine(char *texto);
void lerLinha(char *buf, int tam);
char perguntarRepetir(void);
int binarioParaDecimal(const char number[]);
enum Validacao validarBinario(const char number[]);

int main(void){

    char number[TAM_BUFFER];
    enum Validacao status;
    
do
{   
    do
    {
        printf("Digite o codigo binario: ");
        lerLinha(number, sizeof(number));

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
        
    printf("resultado: %d\n", binarioParaDecimal(number));

} while (perguntarRepetir() == 'S');

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

void limparBuffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void removerNewLine(char *texto){
    char *p = strchr(texto, '\n');
    if(p) *p = '\0';
}

void lerLinha(char *buf, int tam){
    if (fgets(buf, tam, stdin) == NULL){
        buf[0] = '\0';
        return;
    }

    if (strchr(buf, '\n') == NULL){
        limparBuffer();
    } else {
        removerNewLine(buf);
    }
}

char perguntarRepetir(void){
    char buf[TAM_BUFFER];
    char opcao;

    for (;;) {
        printf("Quer fazer uma nova operacao (S/N): ");
        lerLinha(buf, sizeof(buf));
        
        if (strlen(buf) == 1) {
            opcao = (char) toupper((unsigned char) buf[0]);
            if (opcao == 'S' || opcao == 'N'){
                return opcao;
            }
        }

        printf("Opcao invalida, Digite S ou N.\n");
        
    }
    
}
