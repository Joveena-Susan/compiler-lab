#include <stdio.h>
#include <ctype.h>

#define MAX 20
#define SIZE 100

char production[MAX][MAX];
char first[MAX][SIZE];
char follow[MAX][SIZE];

int n;

/* Check whether character already exists */
int exists(char set[], int size, char ch)
{
    int i;

    for (i = 0; i < size; i++)
    {
        if (set[i] == ch)
            return 1;
    }

    return 0;
}

/* Add character to a set */
void add(char set[], int *size, char ch)
{
    if (!exists(set, *size, ch))
    {
        set[*size] = ch;
        (*size)++;
    }
}

/* Find FIRST of a symbol */
void findFirst(char result[], int *size, char symbol)
{
    int i, j;
    int allEpsilon;

    /* Terminal */
    if (!isupper((unsigned char)symbol))
    {
        add(result, size, symbol);
        return;
    }

    /* Find all productions of the non-terminal */
    for (i = 0; i < n; i++)
    {
        if (production[i][0] == symbol)
        {
            /* A -> # */
            if (production[i][2] == '#')
            {
                add(result, size, '#');
                continue;
            }

            allEpsilon = 1;

            /* Process RHS symbols */
            for (j = 2; production[i][j] != '\0'; j++)
            {
                char temp[SIZE];
                int tempSize = 0;
                int k;

                findFirst(temp, &tempSize, production[i][j]);

                /* Add FIRST(symbol) except epsilon */
                for (k = 0; k < tempSize; k++)
                {
                    if (temp[k] != '#')
                        add(result, size, temp[k]);
                }

                /* If epsilon is not present, stop */
                if (!exists(temp, tempSize, '#'))
                {
                    allEpsilon = 0;
                    break;
                }
            }

            /* Entire RHS can produce epsilon */
            if (allEpsilon)
                add(result, size, '#');
        }
    }
}

/* Find FOLLOW of a non-terminal */
void findFollow(char symbol, char result[], int *size)
{
    int i, j, k;

    /* Start symbol gets $ */
    if (production[0][0] == symbol)
        add(result, size, '$');

    for (i = 0; i < n; i++)
    {
        for (j = 2; production[i][j] != '\0'; j++)
        {
            if (production[i][j] == symbol)
            {
                /* Symbol is followed by another symbol */
                if (production[i][j + 1] != '\0')
                {
                    char temp[SIZE];
                    int tempSize = 0;
                    int next = j + 1;

                    findFirst(temp, &tempSize, production[i][next]);

                    /* Add FIRST of next symbol except # */
                    for (k = 0; k < tempSize; k++)
                    {
                        if (temp[k] != '#')
                            add(result, size, temp[k]);
                    }

                    /*
                     * If next symbol can produce epsilon,
                     * add FOLLOW of LHS.
                     */
                    if (exists(temp, tempSize, '#') &&
                        production[i][0] != symbol)
                    {
                        char tempFollow[SIZE];
                        int tempFollowSize = 0;

                        findFollow(
                            production[i][0],
                            tempFollow,
                            &tempFollowSize
                        );

                        for (k = 0; k < tempFollowSize; k++)
                            add(result, size, tempFollow[k]);
                    }
                }
                else
                {
                    /*
                     * Symbol is at the end of RHS.
                     * Add FOLLOW of LHS.
                     */
                    if (production[i][0] != symbol)
                    {
                        char tempFollow[SIZE];
                        int tempFollowSize = 0;

                        findFollow(
                            production[i][0],
                            tempFollow,
                            &tempFollowSize
                        );

                        for (k = 0; k < tempFollowSize; k++)
                            add(result, size, tempFollow[k]);
                    }
                }
            }
        }
    }
}

int main()
{
    int i, j;
    char firstSet[SIZE];
    char followSet[SIZE];
    int firstSize;
    int followSize;

    printf("Enter no. of production rules: ");
    scanf("%d", &n);

    printf("\nEnter the production rules:\n");
    printf("Use # for epsilon\n\n");

    for (i = 0; i < n; i++)
    {
        printf("Production %d: ", i + 1);
        scanf("%19s", production[i]);
    }

    printf("\n========================================\n");
    printf("             FIRST SETS\n");
    printf("========================================\n");

    /*
     * Print FIRST sets
     */
    for (i = 0; i < n; i++)
    {
        int alreadyPrinted = 0;

        for (j = 0; j < i; j++)
        {
            if (production[j][0] == production[i][0])
            {
                alreadyPrinted = 1;
                break;
            }
        }

        if (alreadyPrinted)
            continue;

        firstSize = 0;

        findFirst(
            firstSet,
            &firstSize,
            production[i][0]
        );

        printf("FIRST(%c) = { ", production[i][0]);

        for (j = 0; j < firstSize; j++)
        {
            printf("%c", firstSet[j]);

            if (j < firstSize - 1)
                printf(", ");
        }

        printf(" }\n");
    }

    printf("\n========================================\n");
    printf("             FOLLOW SETS\n");
    printf("========================================\n");

    /*
     * Print FOLLOW sets
     */
    for (i = 0; i < n; i++)
    {
        int alreadyPrinted = 0;

        for (j = 0; j < i; j++)
        {
            if (production[j][0] == production[i][0])
            {
                alreadyPrinted = 1;
                break;
            }
        }

        if (alreadyPrinted)
            continue;

        followSize = 0;

        findFollow(
            production[i][0],
            followSet,
            &followSize
        );

        printf("FOLLOW(%c) = { ", production[i][0]);

        for (j = 0; j < followSize; j++)
        {
            printf("%c", followSet[j]);

            if (j < followSize - 1)
                printf(", ");
        }

        printf(" }\n");
    }

    printf("========================================\n");

    return 0;
}
