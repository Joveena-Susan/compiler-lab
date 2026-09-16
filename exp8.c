#include<stdio.h>
#include<string.h>
char op[2], arg1[5], arg2[5], result[5];

int main()
{
FILE *fp1, *fp2;
char f[100];

printf("Enter input file name: ");
scanf("%99s", f);

fp1 = fopen(f, "r");
fp2 = fopen("output.txt", "w");

if (fp1 == NULL)
{
printf("Cannot open input file.\n");
return 1;
}

if (fp2 == NULL)
{
printf("Cannot create output file.\n");
fclose(fp1);
return 1;
}

while (fscanf(fp1, "%1s %4s %4s %4s",
op, arg1, arg2, result) == 4)
{
if (strcmp(op, "+") == 0)
{
fprintf(fp2, "\nMOV AX,%s", arg1);
fprintf(fp2, "\nADD AX,%s", arg2);
fprintf(fp2, "\nMOV %s,AX", result);
}
else if (strcmp(op, "*") == 0)
{
fprintf(fp2, "\nMOV AX,%s", arg1);
fprintf(fp2, "\nMUL %s", arg2);
fprintf(fp2, "\nMOV %s,AX", result);
}
else if (strcmp(op, "-") == 0)
{
fprintf(fp2, "\nMOV AX,%s", arg1);
fprintf(fp2, "\nSUB AX,%s", arg2);
fprintf(fp2, "\nMOV %s,AX", result);
}
else if (strcmp(op, "/") == 0)
{
fprintf(fp2, "\nMOV AX,%s", arg1);
fprintf(fp2, "\nMOV BX,%s", arg2);
fprintf(fp2, "\nDIV BX");
fprintf(fp2, "\nMOV %s,AX", result);
}
else if (strcmp(op, "=") == 0)
{
fprintf(fp2, "\nMOV AX,%s", arg1);
fprintf(fp2, "\nMOV %s,AX", result);
}
}

fclose(fp1);
fclose(fp2);

printf("Target code generated successfully.\n");

return 0;
}
