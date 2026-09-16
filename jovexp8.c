#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char op[2], arg1[20], arg2[20], result[20];

int main()
{
    FILE *fp1, *fp2;
    char f[100];

    printf("Enter input file name: ");
    scanf("%99s", f);

    fp1 = fopen(f, "r");
    if (fp1 == NULL)
    {
        printf("Unable to open input file.\n");
        return 1;
    }

    fp2 = fopen("output.txt", "w");
    if (fp2 == NULL)
    {
        printf("Unable to create output file.\n");
        fclose(fp1);
        return 1;
    }

    while (fscanf(fp1, "%s %s %s %s", op, arg1, arg2, result) == 4)
    {
        if (strcmp(op, "+") == 0)
        {
            fprintf(fp2, "\nMOV AX, %s", arg1);
            fprintf(fp2, "\nADD AX, %s", arg2);
            fprintf(fp2, "\nMOV %s, AX\n", result);
        }
        else if (strcmp(op, "*") == 0)
        {
            fprintf(fp2, "\nMOV AX, %s", arg1);
            fprintf(fp2, "\nMOV BX, %s", arg2);
            fprintf(fp2, "\nMUL BX");
            fprintf(fp2, "\nMOV %s, AX\n", result);
        }
        else if (strcmp(op, "-") == 0)
        {
            fprintf(fp2, "\nMOV AX, %s", arg1);
            fprintf(fp2, "\nSUB AX, %s", arg2);
            fprintf(fp2, "\nMOV %s, AX\n", result);
        }
        else if (strcmp(op, "/") == 0)
        {
            fprintf(fp2, "\nMOV AX, %s", arg1);
            fprintf(fp2, "\nXOR DX, DX");
            fprintf(fp2, "\nMOV BX, %s", arg2);
            fprintf(fp2, "\nDIV BX");
            fprintf(fp2, "\nMOV %s, AX\n", result);
        }
        else if (strcmp(op, "=") == 0)
        {
            fprintf(fp2, "\nMOV AX, %s", arg1);
            fprintf(fp2, "\nMOV %s, AX\n", result);
        }
    }

    fclose(fp1);
    fclose(fp2);

    printf("\nTarget code generated successfully in output.txt\n");

    return 0;
}
