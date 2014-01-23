//
//  Header.h
//  Circulation
//
//  Created by Med Ayoub on 12/01/2014.
//  Copyright (c) 2014 Med Ayoub. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nliste{
                 int val;
                 struct nliste *suiv;
                }nliste;

//fontion de creation d'une liste chainee a partir d'un variable
nliste *liste_creer(int val)
{
    nliste *l = malloc(sizeof(nliste));
    
    if(!l)
    {
        printf("Erreur d'allocation de mémoire\n");
        exit(1);
    }

    l->val = val;
    l->suiv = NULL;
    return l;
}

//fonctio qui affiche le contenu d'une liste chainee
void liste_afficher(nliste *liste)
{
    nliste *courant = liste;
    printf("[");
    while (courant)
    {
        printf("%d", courant->val);
        if (courant->suiv) printf("\t");
        courant = courant->suiv;
    }
    printf("]");
}

//fonction qui indique si une variable figure dans une liste ou non
int liste_recherche(int val, nliste *liste)
{
    if(!liste) return -1;
    nliste *courant = liste;
    int pos;
    for(pos = 0; courant; ++pos, courant = courant->suiv)
        if(courant->val == val)
            return pos;
    return -1;
} 

//fonction qui ajoute une variable a la fin d'une liste chainee
void liste_ajout_fin(nliste **liste, int val)
{
    nliste *courant = *liste;
    nliste *nouveau = &(*liste_creer(val));
    if(!(*liste)) *liste = nouveau;
    else
    {
        while(courant->suiv)  courant = courant->suiv;
        courant->suiv = nouveau;
    }
}

//fonction qui calcule le nombre de cellule dans une liste chainee
int longueur_liste(nliste *liste)
{
    int i=0;
    nliste *tmp = liste;
    while(tmp)
    {
        tmp = tmp->suiv;
        i++;
    }
    return i;
}

//fonction qui determine l'intersection entre deux listes chainee
nliste *liste_intersection(nliste *l1, nliste *l2)
{
    if(!l1 && !l2) return NULL;
    nliste *intersect = NULL;
    
    nliste *courant;
    
    if(longueur_liste(l1) > longueur_liste(l2))
    {
       for(courant = l1; courant; courant = courant->suiv )
       {
          if(liste_recherche(courant->val, l2) >= 0)
            liste_ajout_fin(&intersect, courant->val);
       }
    }
    else
    {
        for(courant = l2; courant; courant = courant->suiv )
        {
            if(liste_recherche(courant->val, l1) >= 0)
                liste_ajout_fin(&intersect, courant->val);
        }
    }
    return intersect;
}





