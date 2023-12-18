#include <stdio.h>
int ep, flag[10];
int tt[10][10];
int clos[10][10];
int news[10][10], arr[2][10];
int ind = -1;
int n, in, i, j, l, k, num, c;
int input[10], temp[2][10];
int states[10];
int M[10][10];
int eqclass[10][10];

// void closure(int val)
// {
//     int i;
//     for (i = 0; tt[val][ep][i] != -1; i++)
//     {
//         if (flag[tt[val][ep][i]] == 0)
//         {
//             flag[tt[val][ep][i]] = 1;
//             closure(tt[val][ep][i]);
//         }
//     }
// }
int f, final[10];
int isFinal(int da)
{
    for (int l = 0; l < f; l++)
    {
        if (da == final[l])
            return 1;
    }
    return 0;
}
void main()
{

    printf("Enter number of states\n");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            M[i][j] = -1;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            eqclass[i][j] = -1;
    }
    for (i = 0; i < n; i++)
    {
        states[i] = i;
    }
    states[i] = -1;
    printf("Enter number of input symbols\n");
    scanf("%d", &in);
    printf("Enter input symbols(Enter 0 for epsilon)\n");
    for (i = 0; i < in; i++)
    {
        scanf(" %d", &input[i]);
        if (input[i] == 0)
        {
            ep = i;
        }
    }

    printf("Enter the number of final states\n");
    scanf("%d", &f);
    printf("Enter the final states\n");
    for (i = 0; i < f; i++)
    {
        scanf("%d", &final[i]);
    }

    printf("Enter the transition table\n");
    for (i = 0; i < n; i++)
    {

        for (j = 0; j < in; j++)
        {
            printf("\n\nQ%d %d ", i, input[j]);

            printf(": ");

            scanf("%d", &tt[i][j]);
        }
    }
    printf("The transition table is\n");
    for (i = 0; i < n; i++)
    {

        for (j = 0; j < in; j++)
        {
            printf("Q%d %d ", i, input[j]);

            printf("Q%d", tt[i][j]);

            printf("\n");
        }
    }
    printf("\nfinal states ");
    for (i = 0; i < f; i++)
    {
        printf("\tQ%d", final[i]);
    }
    // Intial Mark
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {

            if ((isFinal(i) && !isFinal(j)) || (isFinal(j) && !isFinal(i)))
            {
                // printf("\nmarking\n  %d %d", i, j);
                M[i][j] = 1;
            }
        }
    }
    int flag = 1;
    while (flag)
    {
        flag = 0;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < i; j++)
            {

                // printf("\nmarking\n");

                if (M[i][j] != 1)
                {

                    for (k = 0; k < in; k++)
                    {

                        int t1 = tt[i][k];
                        int t2 = tt[j][k];

                        if (M[t1][t2] == 1)
                        {
                            // printf("\nmarking\n");

                            M[i][j] = 1;
                            flag = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    printf("\n Eq classes are :");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (M[i][j] != 1)
            {
                eqclass[i][j] = 1;
                printf("\tQ%d,Q%d", i, j);
                states[i] = states[j];
                states[j] = states[j];
            }
        }
    }

    int flagr[10];
    for (i = 0; i < 10; i++)
    {
        flagr[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        // if (flagr[i] == 1)
        printf("\nQ%d =");
        for (j = 0; j < n; j++)
        {
            if (states[i] == states[j] && flagr[j] != -1)
            {
                printf("Q%d ");
                flagr[j] = 1;
            }
        }
    }

    printf("\n states");
    for (i = 0; i < n; i++)
    {
        printf("\t%d", states[i]);
    }

    printf("\n\nNew TT");
    for (i = 0; i < n; i++)
    {
        flagr[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < in; j++)
        {
            if (flagr[states[i]] < 2)
            {
                printf("\nQ%d %d Q%d", states[i], input[j], states[tt[i][j]]);
                flagr[states[i]]++;
            }
        }
    }
}
