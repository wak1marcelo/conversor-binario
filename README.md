# Conversor Binario

## Objetivo

Este projeto converte um numero binario de 8 bits para decimal em C.

O programa:

- le uma entrada binaria
- valida se a entrada tem exatamente 8 bits
- valida se todos os caracteres sao `0` ou `1`
- converte o binario para decimal
- pergunta se o usuario quer fazer uma nova operacao

## Arquivo principal

- `conversor-bin-dec.c`

## O que foi construido

Durante o desenvolvimento, o programa evoluiu de uma leitura simples com `scanf` para uma versao mais organizada com funcoes separadas:

- `limparBuffer`
  - descarta o restante da linha quando a entrada e maior que o buffer
- `removerNewLine`
  - remove o `\n` quando ele foi armazenado por `fgets`
- `lerLinha`
  - centraliza a leitura com `fgets`
  - chama `removerNewLine` ou `limparBuffer` conforme o caso
- `validarBinario`
  - verifica tamanho da entrada
  - verifica se a string contem apenas `0` e `1`
  - retorna um status de validacao com `enum`
- `binarioParaDecimal`
  - faz a conversao de binario para decimal
- `perguntarRepetir`
  - le a resposta `S` ou `N`
  - usa `lerLinha` para tratar a entrada
  - converte a letra para maiuscula com `toupper`
  - repete a pergunta se a opcao for invalida

## Problemas que foram corrigidos

Ao longo da construcao, estes pontos foram ajustados:

- `printf` sem especificador de formato
- uso incorreto de `scanf` com `%s`
- tamanho de buffer insuficiente para strings com terminador `\0`
- comparacao de caractere com `1` em vez de `'1'`
- tentativa de converter os bits manualmente com pesos repetidos ou incorretos
- uso de variaveis nao inicializadas
- mistura de leitura com `scanf` e `fgets` sem tratar o `\n`
- validacao incompleta da entrada
- ausencia de repeticao quando o usuario digitava algo invalido
- funcao de conversao retornando tipo inadequado
- duplicacao de logica de tratamento de entrada
- refatoracao da validacao para `enum Validacao`
- substituicao da leitura espalhada por uma funcao unica de leitura segura
- separacao do tratamento de `\n` em funcoes menores

## Estrutura final do programa

### 1. Leitura do binario

O programa agora le a entrada com `lerLinha`:

```c
lerLinha(number, sizeof(number));
```

Essa funcao encapsula a leitura com `fgets` e o tratamento do buffer. Isso evita overflow e evita repetir a mesma logica em varios pontos.

### 2. Tratamento da entrada

O tratamento da entrada foi dividido em tres funcoes:

- `removerNewLine`
  - procura `\n` na string
  - troca esse caractere por `\0`
- `limparBuffer`
  - descarta o restante da entrada quando o texto digitado ultrapassa o tamanho do buffer
- `lerLinha`
  - decide qual das duas funcoes anteriores deve ser usada

Isso evita problemas na proxima leitura e deixa o codigo mais modular.

### 3. Validacao do binario

Foi criado um `enum` para representar os possiveis resultados:

```c
enum Validacao {
    VALIDO = 0,
    TAMANHO_INVALIDO = 1,
    BINARIO_INVALIDO = 2
};
```

A funcao `validarBinario` verifica:

- se a string tem 8 caracteres
- se cada caractere e `0` ou `1`

No `main`, o resultado dessa validacao e tratado por um `switch`, que decide qual mensagem mostrar para o usuario.

### 4. Conversao para decimal

A conversao final foi simplificada para esta formula:

```c
result = result * 2 + (number[i] - '0');
```

Logica:

- `number[i] - '0'` transforma `'0'` em `0` e `'1'` em `1`
- `result * 2` desloca o valor binario ja processado
- `+ ...` adiciona o bit atual

Exemplo para `10101100`:

- `1` -> 1
- `10` -> 2
- `101` -> 5
- `1010` -> 10
- `10101` -> 21
- `101011` -> 43
- `1010110` -> 86
- `10101100` -> 172

### 5. Repeticao da operacao

A funcao `perguntarRepetir` le a resposta do usuario usando um buffer maior:

```c
char buf[TAM_BUFFER];
```

Ela aceita apenas:

- `S`
- `N`

Se o usuario digitar mais de um caractere ou uma letra diferente, a funcao mostra erro e repete a pergunta.

## Fluxo do programa

1. Pede o codigo binario.
2. `lerLinha` faz a leitura e trata a entrada.
3. Valida o tamanho e o conteudo.
4. Se estiver invalido, mostra a mensagem e pede novamente.
5. Se estiver valido, converte para decimal.
6. Mostra o resultado.
7. `perguntarRepetir` pergunta se o usuario quer fazer nova operacao.
8. Se a resposta for `S`, repete.
9. Se a resposta for `N`, encerra.

## Como compilar

Dentro da pasta `conversorBinario`:

```bash
gcc -Wall -Wextra -Wpedantic conversor-bin-dec.c -o conversor-bin-dec
```

## Como executar

```bash
./conversor-bin-dec
```

## Exemplo de uso

Entrada:

```text
Digite o codigo binario: 10101100
resultado: 172
Quer fazer uma nova operacao(S/N): N
```

Outro exemplo:

```text
Digite o codigo binario: 11110000
resultado: 240
Quer fazer uma nova operacao(S/N): N
```

## Estado atual

A versao atual:

- compila com `gcc -Wall -Wextra -Wpedantic`
- valida corretamente a entrada
- converte corretamente binarios de 8 bits
- permite repeticao da operacao de forma segura
- usa `TAM_BINARIO` e `TAM_BUFFER` para evitar numeros magicos
- concentra a leitura de strings na funcao `lerLinha`
- separa melhor a responsabilidade entre leitura, validacao, conversao e repeticao
