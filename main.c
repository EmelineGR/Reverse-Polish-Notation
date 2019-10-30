#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define inst 11

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 typedef struct pile
{
    int valeur;
    struct pile* precedent;
}pile_t;

pile_t* suppr (pile_t* element)
{
    pile_t* new_element = element->precedent;
    free(element);
    return new_element;
}

pile_t* create (int valeur, pile_t* precedent)
{
    pile_t* element = (pile_t*)malloc(inst * sizeof(pile_t));
    if (element == NULL)
    {
      printf("Plus de mémoire");
      return 1;
    }
    element->valeur = valeur;
    element->precedent = precedent;
    return element;
}

pile_t* division (pile_t* element)
{
    if ( element == NULL)
        return NULL;
    if (element->precedent != NULL)
        return ;
}



int main()
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char instruction[11];
        scanf("%s", instruction);
    }

    // Write an action using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");
    

    printf("answer\n");

    return 0;
}
