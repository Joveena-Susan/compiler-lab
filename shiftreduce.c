#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
char input[MAX];
int top = -1;
int ip = 0;

/* Display current parsing step */
void display(const char *action)
{
    int i;
    char stackStr[MAX];
    char inputStr[MAX];

    /* Convert stack to string */
    for (i = 0; i <= top; i++)
        stackStr[i] = stack[i];

    stackStr[top + 1] = '\0';

    /* Get remaining input */
    strcpy(inputStr, &input[ip]);

    printf("%-20s %-20s %-25s\n",
           stackStr, inputStr, action);
}

/* Shift operation */
void shift()
{
    char action[50];

    stack[++top] = input[ip++];

    sprintf(action, "SHIFT %c", stack[top]);

    display(action);
}

/* Reduction operation */
int reduce_once()
{
    char action[50];

    /* --------------------------------
       F -> id
       -------------------------------- */
    if (top >= 1 &&
        stack[top - 1] == 'i' &&
        stack[top] == 'd')
    {
        top -= 1;
        stack[top] = 'F';

        strcpy(action, "REDUCE F -> id");
        display(action);

        return 1;
    }

    /* --------------------------------
       F -> (E)
       -------------------------------- */
    if (top >= 2 &&
        stack[top - 2] == '(' &&
        stack[top - 1] == 'E' &&
        stack[top] == ')')
    {
        top -= 2;
        stack[top] = 'F';

        strcpy(action, "REDUCE F -> (E)");
        display(action);

        return 1;
    }

    /* --------------------------------
       T -> T*F
       -------------------------------- */
    if (top >= 2 &&
        stack[top - 2] == 'T' &&
        stack[top - 1] == '*' &&
        stack[top] == 'F')
    {
        top -= 2;
        stack[top] = 'T';

        strcpy(action, "REDUCE T -> T*F");
        display(action);

        return 1;
    }

    /* --------------------------------
       T -> F
       -------------------------------- */
    if (top >= 0 &&
        stack[top] == 'F')
    {
        stack[top] = 'T';

        strcpy(action, "REDUCE T -> F");
        display(action);

        return 1;
    }

    /* --------------------------------
       E -> E+T
       
       IMPORTANT:
       Do NOT reduce E+T if the next
       input symbol is '*'.
       This preserves multiplication
       precedence.
       -------------------------------- */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top] == 'T' &&
        input[ip] != '*')
    {
        top -= 2;
        stack[top] = 'E';

        strcpy(action, "REDUCE E -> E+T");
        display(action);

        return 1;
    }

    /* --------------------------------
       E -> T

       Do not reduce T to E when the
       next input symbol is '*'.
       -------------------------------- */
    if (top >= 0 &&
        stack[top] == 'T' &&
        input[ip] != '*')
    {
        stack[top] = 'E';

        strcpy(action, "REDUCE E -> T");
        display(action);

        return 1;
    }

    return 0;
}

int main()
{
    printf("\n");
    printf("============================================\n");
    printf("          SHIFT-REDUCE PARSER\n");
    printf("============================================\n");

    /* Display grammar */
    printf("\nGRAMMAR:\n");
    printf("E -> E + T | T\n");
    printf("T -> T * F | F\n");
    printf("F -> (E) | id\n");

    printf("\n============================================\n");

    /* Read input */
    printf("Enter the input string: ");
    scanf("%s", input);

    /* Add end marker */
    strcat(input, "$");

    /* Initialize stack */
    stack[++top] = '$';

    printf("\n");
    printf("============================================\n");
    printf("              PARSING TABLE\n");
    printf("============================================\n");

    printf("%-20s %-20s %-25s\n",
           "STACK", "INPUT", "ACTION");

    printf("-----------------------------------------------------------------\n");

    display("START");

    /* Main parsing loop */
    while (input[ip] != '$')
    {
        /* Shift */
        shift();

        /* Perform reductions */
        while (reduce_once())
        {
            /* Continue until no reduction is possible */
        }
    }

    /* Perform final reductions */
    while (reduce_once())
    {
        /* Continue until no reduction is possible */
    }

    printf("-----------------------------------------------------------------\n");

    /* Final acceptance check */
    if (top == 1 &&
        stack[0] == '$' &&
        stack[1] == 'E')
    {
        printf("\n");
        printf("============================================\n");
        printf("       SUCCESSFULLY STRING ACCEPTED\n");
        printf("============================================\n");
    }
    else
    {
        printf("\n");
        printf("============================================\n");
        printf("          STRING REJECTED\n");
        printf("============================================\n");
    }

    return 0;
}
