#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define INST 11
#define CONV 10
int error = 0;

/**************************************************************/
/* 
Créer le type pile_t
*/
 typedef struct pile
{
    int valeur;
    struct pile* precedent;
}pile_t;

/**************************************************************/
/* 
Permet d'afficher la pile
*/
void affi_pile(pile_t* element, int niveau)
{
    if ( element != NULL) 
    {
        affi_pile(element->precedent, niveau + 1);
        printf("%d", element->valeur);
        if ( niveau != 0){printf(" ");}
    }
}

/**************************************************************/
/* 
Permet de supprimer le premier élément de la pile
*/

pile_t* pop (pile_t* element)
{
    pile_t* new_element = NULL;
    if (element != NULL)
    {
        new_element = element->precedent;
        free(element);
    }
    return new_element;
}

/**************************************************************/
/* 
Permet de créer un nouvel élément
*/

pile_t* create (int valeur, pile_t* precedent)
{
    pile_t* element = (pile_t*)malloc(INST * sizeof(pile_t));
    if (element == NULL)
    {
      printf("Plus de mémoire");
      return 1;
    }
    element->valeur = valeur;
    element->precedent = precedent;
    return element;
}

/**************************************************************/
/* 
Permet d'ajouter le nouvel élément créé avec create à la pile
*/

pile_t* ajout (pile_t* pile, pile_t* element)
{
    if ( pile == NULL )
    {
        element->precedent = NULL;
        return element;
    }
    element->precedent = pile;
    return element;
}

/**************************************************************/
/* 
Transforme l'instruction en int
*/

int en_int (char instruction[INST])
{
    char *ptr;
    return strtol(instruction, &ptr, CONV);
}

/**************************************************************/
/* 
Vérifie si l'instruction est un int
*/

int est_int (char instruction[INST])
{
    int i;
    for ( i = 0; i < INST && instruction[i] != '\0'; i++ )
        if ( instruction[0] != '-' && !isdigit(instruction[i]) ) 
            return 0;
    return 1;
}

/**************************************************************/
/* 
Fait une addition sur les 2 élément du dessus de la pile
*/

pile_t* add (pile_t* element)
{
    if ( element == NULL)
        return NULL;
    if (element->precedent != NULL)
    {
        int element_1 = element->precedent->valeur;
        int element_2 = element->valeur;
        pile_t* element_precedent = element->precedent->precedent;
        free(element);
        free(element->precedent);
        return create(element_1+element_2, element_precedent);
    }
        else
    {
        error = 1;
        element = pop(element);
        return element;
    }
}

/**************************************************************/
/* 
Fait une soustraction sur les 2 élément du dessus de la pile
*/

pile_t* sub (pile_t* element)
{
    if ( element == NULL)
        return NULL;
    if (element->precedent != NULL)
    {
        int element_1 = element->precedent->valeur;
        int element_2 = element->valeur;
        pile_t* element_precedent = element->precedent->precedent;
        free(element);
        free(element->precedent);
        return create(element_1-element_2, element_precedent);
    }
        else
    {
        error = 1;
        element = pop(element);
        return element;
    }
}

/**************************************************************/
/* 
Fait une multiplication sur les 2 élément du dessus de la pile
*/

pile_t* mul (pile_t* element)
{
    if ( element == NULL)
        return NULL;
    if (element->precedent != NULL)
    {
        int element_1 = element->precedent->valeur;
        int element_2 = element->valeur;
        pile_t* element_precedent = element->precedent->precedent;
        free(element);
        free(element->precedent);
        return create(element_1*element_2, element_precedent);
    }
        else
    {
        error = 1;
        element = pop(element);
        return element;
    }
}

/**************************************************************/
/* 
Fait une division sur les 2 élément du dessus de la pile
*/

pile_t* division (pile_t* element)
{
    if ( element == NULL)
        return NULL;
    if (element->precedent != NULL)
    {
        int element_1 = element->precedent->valeur;
        int element_2 = element->valeur;
        if (element_2 == 0)
        {
            error = 1;
            element = pop(element);
            element = pop(element);
            return element;
        }
        else
        {
            pile_t* element_precedent = element->precedent->precedent;
            free(element);
            free(element->precedent);
            return create(element_1/element_2, element_precedent);
        }

    }
        else
    {
        error = 1;
        element = pop(element);
        return element;
    }
}

/**************************************************************/
/* 
Fait l'oppération modulo sur les 2 éléments du dessus de la pile
*/

pile_t* mod (pile_t* element)
{
    if ( element == NULL)
        return NULL;
    if (element->precedent != NULL)
    {
        int element_1 = element->precedent->valeur;
        int element_2 = element->valeur;
        pile_t* element_precedent = element->precedent->precedent;
        free(element);
        free(element->precedent);
        return create(element_1%element_2, element_precedent);
    }
        else
    {
        error = 1;
        element = pop(element);
        return element;
    }
}

/**************************************************************/
/* 
fais une duplication du dernier élément entrée dans la pile
*/

pile_t* dup (pile_t* element)
{
   if ( element == NULL )
        return NULL;
    return ajout(element, create(element->valeur, element));
}

/**************************************************************/
/* 
échange de position les deux dernier élément mis dans la pile
*/

pile_t* swp (pile_t* element)
{
    if (element == NULL)
        return NULL;
    
    if (element->precedent != NULL)
    {
        int element_temp = element->valeur;
        element->valeur = element->precedent->valeur;
        element->precedent->valeur = element_temp;
    }
    return element;
    
}

/**************************************************************/
/* 
Sélectionne l'élément i de la pile et le met en haut de la pile 
*/

pile_t* rol (pile_t* element_rol, pile_t* element_1, int i)
{
    if ( element_rol == NULL || element_1 == NULL )
    {
        error = 1;
        return 0;
    }
    if ( i == 1 )
    {
        pile_t* element_temp = element_1->precedent;
        int valeur = element_1->valeur;
        free(element_1);
        element_rol->precedent = element_temp;
        return valeur;
    }
    else
         return rol(element_1, element_1->precedent, i-1 );
}

/**************************************************************/

pile_t* op ( pile_t* pile, char instruction[INST] )
{
    if ( !strcmp("ROL", instruction) )
    {
        int n = pile->valeur;
        pile = pop(pile);
        n = rol(pile, pile->precedent, n-1);
        pile = ajout(pile, create(n, pile));
    }
    else if ( !strcmp("SWP", instruction))
        pile = swp(pile);
    else if ( !strcmp("DUP", instruction))
        pile = dup(pile);
    else if ( !strcmp("POP", instruction))
        pile = pop(pile);
    else if ( !strcmp("MOD", instruction))
        pile = mod(pile);
    else if ( !strcmp("DIV", instruction))
        pile = division(pile);
    else if ( !strcmp("MUL", instruction))
        pile = mul(pile);
    else if ( !strcmp("SUB", instruction))
        pile = sub(pile);
    else if ( !strcmp("ADD", instruction))
        pile = add(pile);
    else
        error = 1;
    return pile;
}

/**************************************************************/

int main()
{
    pile_t* pile=NULL;
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char instruction[INST];
        scanf("%s", instruction);
        if ( est_int(instruction) )
            pile = ajout(pile, create(en_int(instruction), pile));
        else
            pile = op(pile, instruction);
    }
    
    affi_pile(pile,0);
        if ( error == 1)
        {
            if (pile != NULL )
            {
                printf(" ");
            }
            printf("ERROR");
        }
    printf("\n");
    pop(pile);
    return 0;
}
