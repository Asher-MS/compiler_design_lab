#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STATES 100
#define MAX_ALPHABET 100

int min(int a, int b)
{
    return (a < b) ? a : b;
}

typedef struct
{
    int transitions[MAX_STATES][MAX_ALPHABET];
    bool isFinal[MAX_STATES];
    int numStates;
    int alphabetSize;
} DFA;

void initializeDFA(DFA *dfa, int numStates, int alphabetSize)
{
    dfa->numStates = numStates;
    dfa->alphabetSize = alphabetSize;

    for (int i = 0; i < numStates; ++i)
    {
        dfa->isFinal[i] = false;
        for (int j = 0; j < alphabetSize; ++j)
        {
            dfa->transitions[i][j] = -1; // Initialize transitions to -1 (non-existent)
        }
    }
}

void addTransition(DFA *dfa, int fromState, int toState, int input)
{
    dfa->transitions[fromState][input] = toState;
}

void markFinalState(DFA *dfa, int state)
{
    dfa->isFinal[state] = true;
}

void minimizeDFA(DFA *dfa)
{
    int numStates = dfa->numStates;
    int partition[numStates];
    int prevPartition[numStates];
    bool changed = true;

    for (int i = 0; i < numStates; ++i)
    {
        partition[i] = dfa->isFinal[i] ? 1 : 0;
    }

    while (changed)
    {
        changed = false;

        for (int i = 0; i < numStates; ++i)
        {
            prevPartition[i] = partition[i];
        }

        for (int i = 0; i < numStates; ++i)
        {
            for (int j = i + 1; j < numStates; ++j)
            {
                if (dfa->isFinal[i] != dfa->isFinal[j])
                {
                    partition[i] = partition[j] = 2;
                    changed = true;
                }
                else
                {
                    bool equivalent = true;
                    for (int k = 0; k < dfa->alphabetSize; ++k)
                    {
                        if (dfa->transitions[i][k] != dfa->transitions[j][k])
                        {
                            equivalent = false;
                            break;
                        }
                    }
                    if (equivalent)
                    {
                        partition[i] = partition[j] = 3;
                        changed = true;
                    }
                }
            }
        }
    }

    int equivalenceClass = 0;
    int minPartitions = 4; // Start with a value greater than possible partition values

    for (int i = 0; i < numStates; ++i)
    {
        minPartitions = min(minPartitions, partition[i]);
    }

    equivalenceClass = minPartitions;

    printf("Equivalence Classes:\n");

    for (int i = 0; i < numStates; ++i)
    {
        if (partition[i] == equivalenceClass)
        {
            printf("State %d: Class %d\n", i, equivalenceClass);
        }
    }
}

int main()
{
    DFA dfa;
    int numStates, alphabetSize;

    printf("Enter the number of states in the DFA: ");
    scanf("%d", &numStates);

    printf("Enter the size of the alphabet: ");
    scanf("%d", &alphabetSize);

    initializeDFA(&dfa, numStates, alphabetSize);

    // Code to input transitions and mark final states goes here...
    addTransition(&dfa, 0, 1, 1);
    addTransition(&dfa, 0, 3, 0);
    addTransition(&dfa, 3, 0, 0);
    addTransition(&dfa, 3, 4, 1);
    addTransition(&dfa, 1, 2, 0);
    addTransition(&dfa, 1, 5, 1);
    addTransition(&dfa, 4, 5, 1);
    addTransition(&dfa, 4, 2, 0);
    addTransition(&dfa, 5, 5, 0);
    addTransition(&dfa, 5, 5, 1);
    addTransition(&dfa, 2, 5, 1);
    addTransition(&dfa, 2, 2, 0);

    markFinalState(&dfa, 1);
    markFinalState(&dfa, 2);
    markFinalState(&dfa, 4);

    minimizeDFA(&dfa);

    return 0;
}
