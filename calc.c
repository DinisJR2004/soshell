#include "shell.h"

// math.h
// atof() -> converter string em double
// pow() -> Elevado
//
// SOSHELL: prompt> calc 2.0 + 3.0
// Resultado calc 2.000 + 3.000 = 5.000
//
// op -> +, -, *, /, ^
void calc(char *value1, char *op, char *value2)
{
    double val1 = atof(value1);
    double val2 = atof(value2);

    if (strcmp(op, "+") == 0)
    {
        printf("Resultado: %.3lf\n", val1 + val2);
    }
    else if (strcmp(op, "-") == 0)
    {
        printf("Resultado: %.3lf\n", val1 - val2);
    }
    else if (strcmp(op, "*") == 0)
    {
        printf("Resultado: %.3lf\n", val1 * val2);
    }
    else if (strcmp(op, "/") == 0)
    {
        if (val2 == 0.0)
        {
            printf("Erro: Divisão por zero\n");
        }
        else
        {
            printf("Resultado: %.3lf\n", val1 / val2);
        }
    }
    else if (strcmp(op, "^") == 0)
    {
        printf("Resultado: %.3lf\n", pow(val1, val2));
    }
    else
    {
        printf("Erro: Operador inválido\n");
    }
}

//
// SOSHELL: prompt> bits 11 & 14
// Resultado bits 11 & 14 = 10
//
// string to integer -> atoi()
//
// & binary bitwise AND
// ^ binary bitwise exclusive OR
// | binary bitwise inclusive OR
// ~ negação
// << e >> shifts
void bits(char *op1, char *op, char *op2)
{
    int num1 = atoi(op1);
    int num2 = atoi(op2);
    int resultado;

    // AND (&) - Retorna 1 apenas se ambos os bits forem 1
    if (strcmp(op, "&") == 0)
    {
        resultado = num1 & num2;
    }
    // XOR (^) - Retorna 1 se os bits forem diferentes
    else if (strcmp(op, "^") == 0)
    {
        resultado = num1 ^ num2;
    }
    // OR (|) - Retorna 1 se pelo menos um dos bits for 1
    else if (strcmp(op, "|") == 0)
    {
        resultado = num1 | num2;
    }
    // NOT (~) - Inverte todos os bits do número (complemento de dois)
    else if (strcmp(op, "~") == 0)
    {
        resultado = ~num1; // Aplica a negação apenas ao primeiro operando
        printf("~%d = %d\n", num1, resultado);
        return;
    }
    // Shift à esquerda (<<) - Multiplica por potências de 2 deslocando bits à esquerda
    else if (strcmp(op, "<<") == 0)
    {
        resultado = num1 << num2;
    }
    // Shift à direita (>>) - Divide por potências de 2 deslocando bits à direita
    else if (strcmp(op, ">>") == 0)
    {
        resultado = num1 >> num2;
    }
    else
    {
        printf("Operador inválido!\n");
        return;
    }

    printf("Resultado %d %s %d = %d\n", num1, op, num2, resultado);
}