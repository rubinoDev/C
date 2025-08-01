#include <stdio.h>

int main()
{
    char texto[] = "Victor";
    char *ptr = texto;
    char comando;

    printf("String: %s\n", texto);
    printf("Use 'a' para voltar, 'd' para avançar, 'q' para sair.\n");

    while (1)
    {
        printf("Caractere atual: %c (endereço: %p)\n", *ptr, (void *)ptr);
        printf("Comando > ");
        scanf(" %c", &comando);

        if (comando == 'q')
        {
            printf("Encerrando...\n");
            break;
        }
        else if (comando == 'd')
        {
            if (*ptr != '\0')
            {
                ptr++;
            }
            else
            {
                printf("Chegou ao final da string!\n");
            }
        }
        else if (comando == 'a')
        {
            if (ptr > texto)
            {
                ptr--;
            }
            else
            {
                printf("Já está no início da string!\n");
            }
        }
        else
        {
            printf("Comando inválido! Use 'a', 'd' ou 'q'.\n");
        }
    }

    return 0;
}