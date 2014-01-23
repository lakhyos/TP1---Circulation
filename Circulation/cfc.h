//
//  main.c
//  Circulation
//
//  Created by Med Ayoub on 09/12/2013.
//  Copyright (c) 2013 Med Ayoub. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listes.h"

typedef struct liste{
    int etiquette;
    nliste *succ;
    nliste *pred;
}liste;

//fonction de creation d'une liste chainee (plus ou moins double)
liste *liste_creert(int etiquette)
{
    liste *l = malloc(sizeof(liste));
    l->succ = NULL;
    l->pred = NULL;
    l->etiquette = etiquette;
    return l;
}

//fonction de remplissage d'un tableau de listes (les etiquettes)
void remplissage_tableau(liste *sommet[])
{
    int i,t;
    for(i=0;i<19;i++)
    {
        printf("donner le sommet %d: ",i);
        scanf("%d",&t);
        sommet[i]=&(*liste_creert(t));
    }
}

//fonction de remplissage des successeurs de chaqu'un des sommets
void remplissage_successeurs(liste *sommet[])
{
    int i,n,noeud;
    for(i=0;i<19;i++)
    {
        printf("le sommet %d a combient des successeurs ? : ", sommet[i]->etiquette);
        scanf("%d",&n);
        if(!n) sommet[i]->succ = NULL;
        else
        {
            do{
                printf("donner un successeur: ");
                scanf("%d",&noeud);
                liste_ajout_fin(&sommet[i]->succ, noeud);
                n--;
            }while(n!=0);
        }
    }
}

//fonction de remplissage des predecesseurs de chaqu'un des sommets
void remplissage_predecesseurs(liste *sommet[])
{
    printf("\n");
    int i,n,noeud;
    for(i=0;i<19;i++)
    {
        printf("le sommet %d a combient de predecesseurs ? : ", sommet[i]->etiquette);
        scanf("%d",&n);
        getchar();
        if(!n) sommet[i]->pred = NULL;
        else
        {
            do{
                printf("donner un predecesseur: ");
                scanf("%d",&noeud);
                liste_ajout_fin(&sommet[i]->pred, noeud);
                n--;
            }while(n!=0);
        }    }
}

//fonction qui determine le rang d'un sommet dans le tableau des sommets
int recherche_position(liste *sommet[], int etiquette)
{
    int i=0;
    while ((sommet[i]->etiquette) != etiquette) i++;
    return i;
}

//fonction de determination de tous les successeurs d'un sommet (GAMMA(+))
nliste *recherche_plus(int etiquette, liste *sommet[])
{
    nliste *X = &(*liste_creer(etiquette));
    nliste *tmp = X;
    while (tmp)
    {
      int i = recherche_position(sommet, tmp->val);
      if(sommet[i]->succ)
      {
        nliste *courant = sommet[i]->succ;
        while(courant)
        {
           if( liste_recherche(courant->val, X) == -1)
             {
                 liste_ajout_fin(&X, courant->val);
             }
           courant = courant->suiv;
        }
      }
      tmp = tmp->suiv;
    }
    return X;
}

//fonction de determination de tous les predecesseurs d'un sommet (GAMMA(-))
nliste *recherche_moin(int etiquette, liste *sommet[])
{
    nliste *X = &(*liste_creer(etiquette));
    nliste *tmp = X;
    while (tmp)
    {
        int i = recherche_position(sommet, tmp->val);
        if(sommet[i]->pred)
        {
            nliste *courant = sommet[i]->pred;
            while(courant)
            {
                if( liste_recherche(courant->val, X) == -1)
                {
                    liste_ajout_fin(&X, courant->val);
                }
                courant = courant->suiv;
            }
        }
        tmp = tmp->suiv;
    }
    return X;

}

//fonction de determination de la composante fortement connexe d'un sommet (CFC)
nliste *cfc(int etiquette, liste *sommet[])
{
    nliste *lp = recherche_moin(etiquette, sommet);
    nliste *ls = recherche_plus(etiquette, sommet);
    return liste_intersection(ls, lp);
}


/*fonction qui cherche la CFC d'un sommet, l'affiche et ajoute 
 ses elements dans l'ensemble C*/
void algo_som(int a, nliste *C, liste *sommet[])
{
    //afficher la composante fortement connexe de l'element
    nliste *CFC = cfc(a, sommet);
    //printf("CFC(%d) ", a);
    

    //ajouter les elements de la CFC dans l'ensemble C
    while(CFC)
    {
        if(liste_recherche(CFC->val, C) == -1)
        {
            printf("CFC(%d)", CFC->val);
            if(CFC->suiv) printf(" = ");
        }
        liste_ajout_fin(&C, CFC->val);
        CFC = CFC->suiv;
    }
    printf("\n");
}

//fonction qui cherche les CFC d'un graphe
void algo_soms(liste *sommet[])
{
    int i;
    //initialiser l'ensemble C au Vide
    nliste *C = NULL;
    
    //verifier tous les sommets
    for(i=0 ; i<19 ; i++)
    {
        //si le sommet n'existe pas dans l'ensemble C
        if(liste_recherche(sommet[i]->etiquette, C) == -1)
        {
             //chercher sa CFC, l'afficher et ajouter ses elements dans C
            nliste *CFC = cfc(sommet[i]->etiquette, sommet);
            
            //ajouter les elements de la CFC dans l'ensemble C
            while(CFC)
            {
                if(liste_recherche(CFC->val, C) == -1)
                {
                    printf("CFC(%d)", CFC->val);
                    if(CFC->suiv) printf(" = ");
                }
                liste_ajout_fin(&C, CFC->val);
                CFC = CFC->suiv;
            }
            printf(" = ");
            liste_afficher(cfc(sommet[i]->etiquette, sommet));
            printf("\n");
        }
    }
}

//fonction qui decide si un graphe est connexe ou non
void connexite(liste *sommet[])
{
    if (longueur_liste(cfc(sommet[0]->etiquette, sommet)) == 19)
    {
        printf("le graphe est connexe\n");
    }
    printf("le graphe n'est pas connexe, car il contient au moins deux CFC differentes\n");
}


