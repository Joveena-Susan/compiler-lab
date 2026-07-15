#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *keywords[] = {
    "int", "float", "char", "double", "if", "else",
    "while", "for", "return", "void", "break",
    "continue", "do", "switch", "case", "default",
    "long", "short", "unsigned", "signed", "const"
};

int isKeyword(char str[])
{
    int n = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < n; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main()
{
    FILE *fp;
    char ch, buffer[100];
    int i;

    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("Cannot open input file.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        // Ignore white spaces
        if (isspace(ch))
            continue;

        // Skip comments
        if (ch == '/')
        {
            char next = fgetc(fp);

            // Single-line comment
            if (next == '/')
            {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
            }
            // Multi-line comment
            else if (next == '*')
            {
                while ((ch = fgetc(fp)) != EOF)
                {
                    if (ch == '*')
                    {
                        if ((ch = fgetc(fp)) == '/')
                            break;
                        else
                            ungetc(ch, fp);
                    }
                }
            }
            else
            {
                printf("/\t\tOperator\n");
                ungetc(next, fp);
            }
        }

        // Identifier or Keyword
        else if (isalpha(ch) || ch == '_')
        {
            i = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum(ch) || ch == '_'))
            {
                buffer[i++] = ch;
            }

            buffer[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            if (isKeyword(buffer))
                printf("%-12s Keyword\n", buffer);
            else
                printf("%-12s Identifier\n", buffer);
        }

        // Number
        else if (isdigit(ch))
        {
            i = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isdigit(ch) || ch == '.'))
            {
                buffer[i++] = ch;
            }

            buffer[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            printf("%-12s Number\n", buffer);
        }

        // Operators
        else if (strchr("+-*=<>!%", ch))
        {
            printf("%c\t\tOperator\n", ch);
        }

        // Delimiters
        else if (strchr("(){}[];,", ch))
        {
            printf("%c\t\tDelimiter\n", ch);
        }
    }

    fclose(fp);
    return 0;
}
