#include <stdio.h>
#include <string.h>

#define MAX 20

typedef struct
{
    char from[10];
    char symbol;
    char to[10];
} Transition;

Transition t[MAX];
char states[MAX][10];
char closure[MAX][10];
int transCount = 0, n;

int getIndex(char state[])
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (strcmp(states[i], state) == 0)
            return i;
    }
    return -1;
}


void eClosure(char state[], int visited[])
{
    int i;

    if (visited[getIndex(state)])
        return;

    visited[getIndex(state)] = 1;
    strcpy(closure[getIndex(state)], state);

    for (i = 0; i < transCount; i++)
    {
        if (strcmp(t[i].from, state) == 0 && t[i].symbol == 'e')
        {
            eClosure(t[i].to, visited);
        }
    }
}

int main()
{
    FILE *fp;
    int i, j;
    int visited[MAX];

    fp = fopen("input.dat", "r");

    if (fp == NULL)
    {
        printf("Cannot open file.\n");
        return 0;
    }


    fscanf(fp, "%d", &n);


    for (i = 0; i < n; i++)
        fscanf(fp, "%s", states[i]);

 
    while (fscanf(fp, "%s %c %s",
                  t[transCount].from,
                  &t[transCount].symbol,
                  t[transCount].to) != EOF)
    {
        transCount++;
    }

 
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < MAX; j++)
            visited[j] = 0;

        for (j = 0; j < MAX; j++)
            strcpy(closure[j], "");

        eClosure(states[i], visited);

        printf("E-Closure(%s) = { ", states[i]);

        for (j = 0; j < n; j++)
        {
            if (visited[j])
                printf("%s ", states[j]);
        }

        printf("}\n");
    }

    fclose(fp);
    return 0;
}

