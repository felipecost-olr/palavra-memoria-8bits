#include <stdio.h>
#include <stdint.h>
typedef uint8_t Palavra;

void exibir_bits(Palavra p, const char *label) {
    printf("%s: ", label);
    for (int i = 7; i >= 0; i--)
        printf("%d", (p >> i) & 1);
    printf(" (%u)\n", p);
}

Palavra ler_byte(const char *msg) {
    Palavra v;
    printf("%s", msg);
    scanf("%hhu", &v);
    exibir_bits(v, "  valor");
    return v;
}

int ler_int(const char *msg) {
    int v;
    printf("%s", msg);
    scanf("%d", &v);
    return v;
}

Palavra gerar_mascara(const char *operacao) {
    Palavra mascara = 0;
    int n, pos;

    printf("Quantos bits deseja %s? ", operacao);
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("  Posicao do bit %d (0=LSB, 7=MSB): ", i + 1);
        scanf("%d", &pos);
        if (pos >= 0 && pos <= 7)
            mascara |= (1 << pos);
        else
            printf("  Posicao invalida, ignorada.\n");
    }

    exibir_bits(mascara, "  mascara gerada");
    return mascara;
}

int main() {
    int op;
    do {
        printf("\n=== Operacoes com Palavra de Memoria (8 bits) ===\n"
               "1. Desligar bits (AND)\n2. Ligar bits (OR)\n"
               "3. Detectar diferencas (XOR)\n4. Shift Logico\n"
               "5. Shift Aritmetico\n6. Shift Circular\n0. Sair\nOpcao: ");
        scanf("%d", &op);
        if (op == 0) break;

        Palavra p = ler_byte("Digite a palavra (0-255): ");
        Palavra r, mascara;

        switch (op) {
            case 1:
                mascara = gerar_mascara("desligar");
                r = p & ~mascara;
                break;
            case 2:
                mascara = gerar_mascara("ligar");
                r = p | mascara;
                break;
            case 3:
                r = p ^ ler_byte("Segunda palavra (0-255): ");
                break;
            case 4: {
                int dir = ler_int("Direcao (0=esq, 1=dir): ");
                int n   = ler_int("Posicoes: ");
                r = dir ? (p >> n) : (p << n);
                break;
            }
            case 5: {
                int n = ler_int("Posicoes para direita: ");
                r = (Palavra)((int8_t)p >> n);
                break;
            }
            case 6: {
                int dir = ler_int("Direcao (0=esq, 1=dir): ");
                int n   = ler_int("Posicoes: ") % 8;
                r = dir ? ((p >> n) | (p << (8 - n)))
                        : ((p << n) | (p >> (8 - n)));
                break;
            }
            default: printf("Opcao invalida!\n"); continue;
        }

        printf("Resultado: ");
        for (int i = 7; i >= 0; i--)
            printf("%d", (r >> i) & 1);
        printf(" (%u)\n", r);

    } while (1);

    printf("Encerrando...\n");
    return 0;
}
