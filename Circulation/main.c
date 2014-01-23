//
//  main.c
//  Circulation
//
//  Created by Med Ayoub on 12/01/2014.
//  Copyright (c) 2014 Med Ayoub. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cfc.h"

int main()
{
    int i;
    
    liste *sommet[19];
    remplissage_tableau(sommet);
    remplissage_successeurs(sommet);
    remplissage_predecesseurs(sommet);
    
    printf("\nAffichage CFC :\n");
    for(i=0; i<19; i++)
    {
        nliste *lp = recherche_moin(sommet[i]->etiquette, sommet);
        nliste *ls = recherche_plus(sommet[i]->etiquette, sommet);
        
        printf("CFC(%d)=",sommet[i]->etiquette);
        
        liste_afficher(liste_intersection(ls, lp));
        
        printf("\n");
    }
    printf("\n");
    
    printf("\nAffichage Graphe reduit:\n");
    algo_soms(sommet);

    printf("\nConnexite du Graphe :\n");
    connexite(sommet);
    
    return 0;
    
    
}