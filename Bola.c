#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>

#define TAILLE_L 8
#define TAILLE_C 19



struct boule // assemblage de variable
{
    int symbole ;
    int couleur ;

};

void COULEUR (int texte, int fond);
int abs(int a); //sous programme de la valeur absolue
void AFF_TABLEAU (struct boule tab2[8][19]);
void CHARGEMENT (struct boule tab2[8][19]);
void SAUVEGARDE ( struct boule tab2[8][19]);
void BOULE_TOMBE (  struct boule tab2[8][19], struct boule tab1[8][19]);
void COMPARAISON_SCORE (struct boule tab2[8][19], int *score_total, int *k);
void PERMUTATION (struct boule tab2[8][19], int *w, int *v, int *x, int *y,char *action);


int main()
{


//fond blanc
    COULEUR(12,15);
    system("cls"); //effacer l ecran
    COULEUR(0,15);

    struct boule tab1[8][19] ;
    struct boule tab2[8][19] ;
    //int numcase;
    int i,j;
    char tabsymbole[]= {'\xA9','\xB6','\xF8','\x24','\x26','\x40','\x80','\xA5'};
    int tabcouleur[]= {1,2,4,9,10,11,13,0};
    int x =0; //
    int k; //indicateur si la comparison est vraie =1 ou fausse =0
    int score_total = 0;

    time_t  tdepart,tarrivee; // 2 variable de temps
    int duree = 0 ; // on initialise la dur�e � 0
    duree = difftime(tarrivee, tdepart); // calcul de la duree

    int niveau;


menu: // label permettant de retourner au menu
    //tab[i][j]=tabsymbole[numcase];
    printf("\n   WELCOME TO BOLA GAME\n ");

    int Menu1;
    printf("\n 1) LANCER UNE PARTIE");
    printf("\n 2) LIRE LES REGLES\n");
    fflush(stdin); // vider la memoire
    scanf("%d",& Menu1);

    while (Menu1 != 1 && Menu1 != 2) // verification
    {
        printf("Mauvaise reponse \n");
        printf("\n 1) LANCER UNE PARTIE");
        printf("\n 2) LIRE LES REGLES\n");

        fflush(stdin);
        scanf("%d",& Menu1);
    }
    if (Menu1 == 2) //AFFICHER LES REGLES
    {
        printf("\nLa grille de jeu contient 8 lignes composees chacunes,alternativement, de 9 et 10 boules. \n\nPour jouer, le joueur doit selectionner deux boules qui se touchent.\n\nSi en les permutant, il se forme au moins une ligne (horizontale ou diagonale) de 3 boules de meme symbole,\n\nla permutation est acceptee. Toutes ces boules sont supprimees, \n\nles boules situees au-dessus dans la grille tombent et les cases vides sont remplies par d autres boules.");
        printf("\n\n\n 1) LANCER UNE PARTIE");
        printf("\n 2) LIRE LES REGLES\n");

        scanf("%d",& Menu1);
        while (Menu1 != 1 && Menu1 != 2)
        {
            printf("\nMuavaise reponse \n");
            printf("\n 1) LANCER UNE PARTIE");
            printf("\n 2) LIRE LES REGLES\n");

            fflush(stdin);
            scanf("%d",& Menu1); //l'ordinateur demande la valeur de menu
        }
    }



    if(Menu1 == 1)
    {
        printf("1 : Niveau 1\n2 : Niveau 2\n3 : Niveau 3\n");
        fflush(stdin);
        scanf("%d", & niveau);

        if(niveau == 1)
        {


        printf("CREATION DU TABLEAU, VEUILLEZ PATIENTER\n");
        Sleep(600); //attendre 600 ms

        for ( i=0 ; i <TAILLE_L ; i++ ) // tant qu'on pas remplie toute les colonnes
        {


            for (j=0; j<TAILLE_C; j++) // tant qu'on est pas arriv� jusqu'� la fin de la ligne

                tab1[i][j].symbole = 0; // remplir par des 0


        }

        for ( i=0 ; i <TAILLE_L ; i++ ) // tant qu'on pas remplie toute les colonnes

        {

            for (j=0; j<TAILLE_C; j++)
            {

                // tant qu'on est pas arriv� jusqu'� la fin de la ligne

                tab1[i][j].symbole=tabsymbole[i];

                tab1[i][j].couleur=tabcouleur[i];

            }

        }
        //MELANGER LE TABLEAU



        srand(time(NULL)); // initialiser la fonction al�aoitre

        for ( i=0 ; i <TAILLE_L ; i++ ) // on se d�place dans le tableau
        {
            for (j=0; j<TAILLE_C; j++)
            {
                tab2[i][j] = tab1 [rand () %8][rand () %19]; // prend un symbole al�atoire dans le tableau
            }
        }
        for(i=0; i<TAILLE_L; i++) // toute les barres valent 0
        {
            for (j=x; j<19; j+=2)
            {
                tab2[i][j].symbole = 0;
            }
            x = (x+1)%2; // soit 0 ou 1 pour les lignes pair on commence � 0 et pour les imapirs � 1
        }

        // TRAITEMENT DU TABLEAU CREER POUR QUE LE JOUEUR NE COMMENCE AVEC AUCUN ALIGEMENT

        COMPARAISON_SCORE (tab2, &score_total, &k);

        while (k == 1) //tant que la comparaison est vraie
        {// cond
            BOULE_TOMBE(tab2, tab1);
            COMPARAISON_SCORE (tab2, &score_total, &k); // variables auxquelles ont fait appel //adresse du pointeur    //k verifie la comparaison
        }
        AFF_TABLEAU (tab2);

        score_total = 0; //On r�initialise le score  du joueur � z�ro

        int x = 0; // les coordonn�es nous permettant de faire la permutation inverse lorsque le joueur effectue une permutation non autoris�e
        int y = 0;
        int v = 0 ;
        int w = 0;
        char action;

        duree=0;
        time(&tdepart);


        printf("\nvotre score est %d", score_total);
        printf("\n\nduree = %d", duree);
        system("PAUSE");

        while ((score_total < 20) && (duree < 120)) //
        {

            AFF_TABLEAU(tab2);

            PERMUTATION (tab2, &w, &v, &x, &y,&action);
            if(action=='Q'){
                goto menu;
            } // permutation de boules

            struct boule tampon2;

            COMPARAISON_SCORE (tab2, &score_total, &k); //on compare les aligements du tableau pour voir si la permutation  est bonne

            while( k != 1) //tant que la pemrutation est fausse
            {
                tampon2= tab2[w][v];
                tab2[w][v] =  tab2[x][y];
                tab2[x][y] = tampon2;

                AFF_TABLEAU (tab2);

                printf("\nVotre pemutation n'engendre aucun n'alignement de 3 boules ou plus. \n Veuillez recommencer");

                printf("votre score est %d", score_total);

                PERMUTATION (tab2, &w, &v, &x, &y,&action);
                if(action=='Q'){
                goto menu;
                }

                COMPARAISON_SCORE (tab2, &score_total, &k);

            }


            COMPARAISON_SCORE (tab2, &score_total, &k);
            while (k == 1) // si il y a un alignement
        {
            BOULE_TOMBE(tab2, tab1);
            COMPARAISON_SCORE (tab2, &score_total, &k);
        }



            time(&tarrivee);// temps � la fin de la boucle
            duree= difftime( tarrivee, tdepart); // nbrre de secondes ecoulees entre t1 et t2

            printf("\n\nduree = %d", duree);
        }


        //RESULTAT DE LA PARTIE
        if (score_total >= 20 && duree <= 120)
        {
            printf("\n\nVOUS AVEZ GAGNE LE NIVEAU 1 !!!"); //SI LE JOUEUR A FAIT 20 PERMUTATIONS DANS LE TEMPS IMPARTIE
        }
        else
        {
            printf("\n\n VOUS AVEZ PERDU");  //SI LE JOUEUR N'A PAS FAIT 20 PERMUTATIONS DANS LE TEMPS IMPARTIE
        }

    }

    //-----------------------------NIVEAU 2----------------------------


    if (niveau == 2)
    {
        printf("CREATION DU TABLEAU, VEUILLEZ PATIENTER\n");
        Sleep(600); //attendre 600 ms

        for ( i=0 ; i <TAILLE_L ; i++ ) // tant qu'on pas remplie toute les colonnes
        {


            for (j=0; j<TAILLE_C; j++) // tant qu'on est pas arriv� jusqu'� la fin de la ligne

                tab1[i][j].symbole = 0; // remplir par des 0


        }

        for ( i=0 ; i <TAILLE_L ; i++ ) // tant qu'on pas remplie toute les colonnes

        {

            for (j=0; j<TAILLE_C; j++)
            {

                // tant qu'on est pas arriv� jusqu'� la fin de la ligne

                tab1[i][j].symbole=tabsymbole[i];

                tab1[i][j].couleur=tabcouleur[i];

            }

        }
        //MELANGER LE TABLEAU



        srand(time(NULL)); // initialiser la fonction al�aoitre

        for ( i=0 ; i <TAILLE_L ; i++ ) // on se d�place dans le tableau
        {
            for (j=0; j<TAILLE_C; j++)
            {
                tab2[i][j] = tab1 [rand () %8][rand () %19]; // prend un symbole al�atoire dans le tableau
            }
        }
        for(i=0; i<TAILLE_L; i++) // toute les barres valent 0
        {
            for (j=x; j<19; j+=2)
            {
                tab2[i][j].symbole = 0;
            }
            x = (x+1)%2; // soit 0 ou 1 pour les lignes pair on commence � 0 et pour les imapirs � 1
        }

        // TRAITEMENT DU TABLEAU CREER POUR QUE LE JOUEUR NE COMMENCE AVEC AUCUN ALIGEMENT

        COMPARAISON_SCORE (tab2, &score_total, &k);

        while (k == 1) //tant que la comparaison est vraie
        {// cond
            BOULE_TOMBE(tab2, tab1);
            COMPARAISON_SCORE (tab2, &score_total, &k); // variables auxquelles ont fait appel //adresse du pointeur    //k verifie la comparaison
        }
        AFF_TABLEAU (tab2);

        score_total = 0; //On r�initialise le score  du joueur � z�ro

        int x = 0; // les coordonn�es nous permettant de faire la permutation inverse lorsque le joueur effectue une permutation non autoris�e
        int y = 0;
        int v = 0 ;
        int w = 0;
        char action;

        duree=0;
        time(&tdepart);


        printf("\nvotre score est %d", score_total);
        printf("\n\nduree = %d", duree);
        system("PAUSE");

        while ((score_total < 40) && (duree < 120)) //
        {

            AFF_TABLEAU(tab2);

            PERMUTATION (tab2, &w, &v, &x, &y,&action);
            if(action=='Q'){
                goto menu;
            } // permutation de boules

            struct boule tampon2;

            COMPARAISON_SCORE (tab2, &score_total, &k); //on compare les aligements du tableau pour voir si la permutation  est bonne

            while( k != 1) //tant que la pemrutation est fausse
            {
                tampon2= tab2[w][v];
                tab2[w][v] =  tab2[x][y];
                tab2[x][y] = tampon2;

                AFF_TABLEAU (tab2);

                printf("\nVotre pemutation n'engendre aucun n'alignement de 3 boules ou plus. \n Veuillez recommencer");

                printf("votre score est %d", score_total);

                PERMUTATION (tab2, &w, &v, &x, &y,&action);
                if(action=='Q'){
                goto menu;
                }

                COMPARAISON_SCORE (tab2, &score_total, &k);

            }


            COMPARAISON_SCORE (tab2, &score_total, &k);
            while (k == 1) // si il y a un alignement
        {
            BOULE_TOMBE(tab2, tab1);
            COMPARAISON_SCORE (tab2, &score_total, &k);
        }



            time(&tarrivee);// temps � la fin de la boucle
            duree= difftime( tarrivee, tdepart); // nbrre de secondes ecoulees entre t1 et t2

            printf("\n\nduree = %d", duree);
        }


        //RESULTAT DE LA PARTIE
        if (score_total >= 40 && duree <= 120)
        {
            printf("\n\nVOUS AVEZ GAGNE LE NIVEAU 2 !!!"); //SI LE JOUEUR A FAIT 20 PERMUTATIONS DANS LE TEMPS IMPARTIE
        }
        else
        {
            printf("\n\n VOUS AVEZ PERDU");  //SI LE JOUEUR N'A PAS FAIT 20 PERMUTATIONS DANS LE TEMPS IMPARTIE
        }
    }

    //------------------------NIVEAU 3-------------------------------------------------

    if (niveau == 3)
    {
        printf("CREATION DU TABLEAU, VEUILLEZ PATIENTER\n");
        Sleep(600); //attendre 600 ms

        for ( i=0 ; i <TAILLE_L ; i++ ) // tant qu'on pas remplie toute les colonnes
        {


            for (j=0; j<TAILLE_C; j++) // tant qu'on est pas arriv� jusqu'� la fin de la ligne

                tab1[i][j].symbole = 0; // remplir par des 0


        }

        for ( i=0 ; i <TAILLE_L ; i++ ) // tant qu'on pas remplie toute les colonnes

        {

            for (j=0; j<TAILLE_C; j++)
            {

                // tant qu'on est pas arriv� jusqu'� la fin de la ligne

                tab1[i][j].symbole=tabsymbole[i];

                tab1[i][j].couleur=tabcouleur[i];

            }

        }
        //MELANGER LE TABLEAU



        srand(time(NULL)); // initialiser la fonction al�aoitre

        for ( i=0 ; i <TAILLE_L ; i++ ) // on se d�place dans le tableau
        {
            for (j=0; j<TAILLE_C; j++)
            {
                tab2[i][j] = tab1 [rand () %8][rand () %19]; // prend un symbole al�atoire dans le tableau
            }
        }
        for(i=0; i<TAILLE_L; i++) // toute les barres valent 0
        {
            for (j=x; j<19; j+=2)
            {
                tab2[i][j].symbole = 0;
            }
            x = (x+1)%2; // soit 0 ou 1 pour les lignes pair on commence � 0 et pour les imapirs � 1
        }

        // TRAITEMENT DU TABLEAU CREER POUR QUE LE JOUEUR NE COMMENCE AVEC AUCUN ALIGEMENT

        COMPARAISON_SCORE (tab2, &score_total, &k);

        while (k == 1) //tant que la comparaison est vraie
        {// cond
            BOULE_TOMBE(tab2, tab1);
            COMPARAISON_SCORE (tab2, &score_total, &k); // variables auxquelles ont fait appel //adresse du pointeur    //k verifie la comparaison
        }
        AFF_TABLEAU (tab2);

        score_total = 0; //On r�initialise le score  du joueur � z�ro

        int x = 0; // les coordonn�es nous permettant de faire la permutation inverse lorsque le joueur effectue une permutation non autoris�e
        int y = 0;
        int v = 0 ;
        int w = 0;
        char action;

        duree=0;
        time(&tdepart);


        printf("\nvotre score est %d", score_total);
        printf("\n\nduree = %d", duree);
        system("PAUSE");

        while ((score_total < 80) && (duree < 120)) //
        {

            AFF_TABLEAU(tab2);

            PERMUTATION (tab2, &w, &v, &x, &y,&action);
            if(action=='Q'){
                goto menu;
            } // permutation de boules

            struct boule tampon2;

            COMPARAISON_SCORE (tab2, &score_total, &k); //on compare les aligements du tableau pour voir si la permutation  est bonne

            while( k != 1) //tant que la pemrutation est fausse
            {
                tampon2= tab2[w][v];
                tab2[w][v] =  tab2[x][y];
                tab2[x][y] = tampon2;

                AFF_TABLEAU (tab2);

                printf("\nVotre pemutation n'engendre aucun n'alignement de 3 boules ou plus. \n Veuillez recommencer");

                printf("votre score est %d", score_total);

                PERMUTATION (tab2, &w, &v, &x, &y,&action);
                if(action=='Q'){
                goto menu;
                }

                COMPARAISON_SCORE (tab2, &score_total, &k);

            }


            COMPARAISON_SCORE (tab2, &score_total, &k);
            while (k == 1) // si il y a un alignement
        {
            BOULE_TOMBE(tab2, tab1);
            COMPARAISON_SCORE (tab2, &score_total, &k);
        }



            time(&tarrivee);// temps � la fin de la boucle
            duree= difftime( tarrivee, tdepart); // nbrre de secondes ecoulees entre t1 et t2

            printf("\n\nduree = %d", duree);
        }


        //RESULTAT DE LA PARTIE
        if (score_total >= 80 && duree <= 120)
        {
            printf("\n\nVOUS AVEZ GAGNE LE NIVEAU 4 !!!"); //SI LE JOUEUR A FAIT 20 PERMUTATIONS DANS LE TEMPS IMPARTIE
        }
        else
        {
            printf("\n\n VOUS AVEZ PERDU");  //SI LE JOUEUR N'A PAS FAIT 20 PERMUTATIONS DANS LE TEMPS IMPARTIE
        }
    }
    }
    return 0;
}



void COULEUR (int texte, int fond)
{

//0=noir 15=blanc
//1=bleu fonc�, 2=vert fonc�, 3=turquoise fonc�, 4=rouge fonc�, 5=violet fonc�
//6=vert kaki, 7=gris clair, 8=gris fonc�
//9=bleu fluo, 10=vert fluo, 11=turquoise fluo, 12=rouge fluo, 13=violet fluo
//14=jaune

    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,fond*16+texte);
}

void AFF_TABLEAU (struct boule tab2[8][19])
{
    int i,j;
    printf("\n                     1 1 1 1 1 1 1 1 1 1   ");
    printf("\n   1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9   ");

    for ( i=0 ; i < TAILLE_L  ; i++ )
    {
        printf("\n");

        if (i%2==0) // lignes impaires pour l'affichage mais lignes paires sur la grille
        {
            printf("  ");

            for (j=1; j<TAILLE_C; j=j+2) // on commence � la case du premeier symbole jusqu'� taille-1 , de 2 en 2
            {
                if (tab2[i][j].symbole == '1') //
                {
                    printf(" |  ");
                }
                else
                {
                    COULEUR(tab2[i][j].couleur,15);
                    printf(" | %c", tab2[i][j].symbole);
                    COULEUR(0,15);
                }
            }

            printf(" |   %d",i+1 );
        }
        else
        {
            printf(" | ");
            COULEUR(0,15);

            for (j=0; j<TAILLE_C; j=j+2)
            {
                if (tab2[i][j].symbole == '1') // si il y une boule �xplos�e
                {
                    printf("  | ");
                }
                else
                {
                    COULEUR(tab2[i][j].couleur,15);

                    printf("%c | ", tab2[i][j].symbole);
                    COULEUR(0,15);
                }
            }
            printf("%d",i+1 );
        }
    }
}


//-----------------       FONCTION COMPARAISON        --------------------------------------------

void COMPARAISON_SCORE (struct boule tab2[8][19], int *score_total, int *k )
{
    // 1) ------------------COMPARAISON DES LIGNES------------------
    int i,j;
    i=0;
    j=0;
    int cpt=0;
    int score1 = 0;
    int score2 =0;

    *k = 0;

    for ( i=0 ; i <TAILLE_L ; i++ ) //De la ligne 1 � 8 (dans notre affichage tableau)

    {

        if (i%2==0) //Si la ligne est impair dans notre affichage du tableau (pair +1)
        {
            char unnom = tab2[i][1].symbole; // unnom = le symbole que l'on va comparer aux suivants dans la ligne
            int depart=1; //Commmence � la colonne 2


            for (j=3; j<TAILLE_C; j=j+2) //De la colonne 4 � 18
            {



                if (tab2[i][j].symbole == unnom && j<TAILLE_C-2) // Si les 2 syboles compar�s correspondent alors :
                {
                    cpt=j; //On continue d'avancer dans la ligne et on met en m�moire la colonne sur laquel on se d�place

                }
                else //Sinon
                {
                    if( (j- depart)/2 >= 3) //Si || la distance entre le 1er symbole que l'on compare et le dernier symbole � la suite|| est sup�rieur ou = � 3
                    {
                        *k = 1;
                        //Alors
                        for (j= depart ; j<cpt ; j=j+2) //on va de la case du 1er symbole au dernier symbole de m�me couleur
                        {
                            tab2[i][j].symbole = '1';  //On les remplace par des char 1
                            score1 += 1;
                        }


                    }
                    unnom = tab2[i][j].symbole; //On commence � comparer � partir du symbole suivant dans la ligne
                    depart = j; // On change la m�moire de la colonne du prochain symbole compar� dans la ligne
                }
            }
        }
        else // Si la ligne est pair dans notre affichage (impair +1)
        {
            char unnom = tab2[i][0].symbole; // On met en m�moire le symbole de la 1�re colonne
            int depart=0; // On met en m�moire la colonne du 1er symbole (ici 1e colonne)

            int cpt; //Initialisation d'un compteur
            for (j=2; j<TAILLE_C; j=j+2) //De la colonne 3 � 19
            {


                if (tab2[i][j].symbole == unnom && j<TAILLE_C -2) //Si les 2 syboles compar�s correspondent alors :
                {
                    cpt=j; //On continue d'avancer dans la ligne et on met en m�moire la colonne sur laquel on se d�place

                }
                else//Sinon
                {
                    //Alors
                    if((j- depart)/2 >= 3) //Si || la distance entre le 1er symbole que l'on compare et le dernier symbole � la suite|| est sup�rieur ou = � 3
                    {
                        *k = 1;
                        for ( j=depart; j<=cpt; j=j+2) //on va de la case du 1er symbole au dernier symbole de m�me couleur
                        {
                            tab2[i][j].symbole = '1'; //On les remplace par des char '1'
                            score2 += 1;
                        }

                    }
                    unnom = tab2[i][j].symbole; // On commence � comparer � partir du symbole suivant dans la ligne
                    depart = j;  // On change la m�moire de la colonne du prochain symbole compar� dans la ligne
                }
            }
        }

    }
    //printf("%d %d",score1,score2);
    printf("\n\n\n Votre score l imp est : %d", score1);
    printf("\n Votre score de l paire est : %d", score2);




    // 2) -----------------COMPARAISON DES DIAGONALES---------

    // a) Diagos : "/"

    int diagonale = 0;
    int departi;
    int departj;
    char unnom;
    int score3 = 0;



    for (diagonale = 0; diagonale <9 ; diagonale++) // De la diagonale 1 � 9 (diagonales orient�es du bas gauche � haut droite en partant de la diagonale en bas a droite mais seulement celle qui parte du bas du tableau)
    {
        j=diagonale * 2;
        i = TAILLE_L - 1;
        departi = i ;
        departj = j;
        unnom = tab2[i][j].symbole; // la case qu'on compare aux autres symbole
        while(i >= 0 && j < TAILLE_C)
        {
            if (tab2[i][j].symbole == unnom && j != TAILLE_C-1 && i != 0 ) // Si dans les cases les symboles qu'on compare sont les m�me alors on avance dans le tableau
            {
                //ici unnom c'est pour la diagonale
                cpt=j;
            }
            else
            {
                if(/* (j- departj) >= 2 || */(abs(departj - j) >= 2 && (i == 0 || j== TAILLE_L -1))) // on determine une valeaur absolue car lorsque l'on se deplace en diagnoale on avance dans le n�gatif mais on veut que ce soit dans le positif
                {
                    *k = 1; //Il y au mois une comparaison qui existe (pour autoriser la permutation)
                    i = departi;
                    for (j= departj ; j<=cpt ; j++) //on se d�place en diagonale de la case de d�part � la case d'arriv�e en avancant de
                    {
                        tab2[i][j].symbole = '1';  //Transforme les cases en  char '1'
                        i--;
                        score3 += 1; //Calcul Score
                    }

                }
                unnom = tab2[i][j].symbole; //On change le symbole que l'on va comaparer
                departj = j; //Et les variables retenant les coordonn�es du symboles de d�part
                departi = i;
            }

            i--; //On se d�place en diagonale
            j++;
        }
    }



    j = 3; //Cas sp�cifiques des 2 diagonales restantes et m�me algorithme que celui d'au dessus
    cpt = 0;

    for (diagonale = 0 ; diagonale < 2 ; diagonale ++)
    {
        i = 0;
        departi = i;
        departj = j;
        unnom = tab2[i][j].symbole;

        while (j != -1)
        {
            if (tab2[i][j].symbole == unnom && j != 0 && i != TAILLE_L -1) // Tkt ca marche
            {
                cpt = j;
            }
            else
            {
                if( abs(departj - j) >= 2 || (abs(departj - j) >= 2 && i == 0) )
                {
                    *k = 1;
                    i = departi;
                    for (j= departj ; j>=cpt ; j--) //on va de la case de d�part � la case d'arriv�e
                    {
                        tab2[i][j].symbole = '1';
                        i++;
                        score3 += 1;
                    }
                }
                unnom = tab2[i][j].symbole;
                departj = j;
                departi = i;
            }
            j-- ;
            i++;
        }
        j = 5;
    }

    printf("\n Votre score / est : %d", score3);

    // b)  Diagos : "\"

    diagonale = 0;
    int score4 = 0;

    for (diagonale = 9; diagonale >= 0 ; diagonale--) //m�me chose mais pour les diagonales de l'autre cot�s
    {
        j=diagonale * 2;
        i = TAILLE_L - 1;
        departi = i ;
        departj = j;
        unnom = tab2[i][j].symbole;
        while(i >= 0 && j < TAILLE_C)
        {
            if (tab2[i][j].symbole == unnom && j != TAILLE_C-1 && i != 0) // Tkt ca marche
            {
                cpt=j;
            }
            else
            {
                if( abs(j- departj) >= 2 || (abs(departj - j) >= 2 && ((i == TAILLE_L-1) || (j == 0))))
                {
                    *k = 1;
                    i = departi;
                    for (j= departj ; j>= cpt ; j--) //on va de la case de d�part � la case d'arriv�e
                    {
                        tab2[i][j].symbole = '1';
                        i--;
                        score4 += 1;
                    }


                }
                unnom = tab2[i][j].symbole;
                departj = j;
                departi = i;
            }


            i--; // on parcourt le tableau en diagnoale on monte dans les lignes et on se d�place vers la gauche dans les colonnes
            j--;
        }
    }






    j = 3;
    cpt = 0;
    for (diagonale = 2 ; diagonale <0 ; diagonale --)
    {
        i = 0;
        departi = i;
        departj = j;
        unnom = tab2[i][j].symbole;
        while (j != -1)
        {

            if (tab2[i][j].symbole == unnom && j != 0 && i != TAILLE_L -1) // Tkt ca marche
            {
                cpt = j;
            }
            else
            {
                if( abs(departj - j) >= 3 || (abs(departj - j) >= 2 && ((i == TAILLE_L-1) || (j == 0))))
                {
                    *k = 1;
                    i = departi;
                    for (j= departj ; j<=cpt ; j++) //on va de la case de d�part � la case d'arriv�e
                    {
                        tab2[i][j].symbole = '1';
                        i++;
                        score4 += 1;
                    }


                }
                unnom = tab2[i][j].symbole;
                departj = j;
                departi = i;

            }

            j++ ;
            i++;
        }





        j = 5;

    }
    printf("\n Votre score est : %d", score4);

    *score_total += score1 + score2 + score3 + score4 ; // nouveau score total = ancien score total + score 1,2,3,4

    printf("\n\n Votre score total est : %d\n", *score_total);

}

void BOULE_TOMBE (  struct boule tab2[8][19], struct boule tab1[8][19])
{
    int i,j;
    int lignetombe;
    int colonnetombe;


    for ( i=0 ; i <TAILLE_L ; i++ )
    {
        for (j=0; j<TAILLE_C; j++)

        {
            if ( tab2[i][j].symbole == '1') //Si il y a un vide
            {

                //Faire tomber la boule � droite
                lignetombe = i;
                colonnetombe = j;
                while (lignetombe != 0 && colonnetombe != TAILLE_C-1) //tant que la case qui est au dessus est vide chercher la case encore auddessus, se placer sur la case encore au dessus sauf qi on a atteint la fin du tableau
                {
                    tab2[lignetombe][colonnetombe] = tab2[lignetombe-1][colonnetombe+1]; // la boule qui �tait au dessus a droite du vide descend
                    tab2[lignetombe-1][colonnetombe+1].symbole = '1' ; //Le vide monte en haut a droite
                    lignetombe -- ; //On change les indices tant qu'on est pas arriv� sur bord haut ou bord droit du tableau
                    colonnetombe ++ ;

                    //Animation des boules qui tombent
                    Sleep(150);
                    system("cls"); //Efface TABLEAU

                    AFF_TABLEAU(tab2);
                }
                //QUAND ON EST ARRIVE A UN BORD DU TABLEAU (EN HAUT ou A DROITE), ON FAIT APPARAITRE UNE NOUVELLE BOULE A LA PLACE DU VIDE
                srand(time(NULL)); //Initialisation de la fonction al�atoire
                tab2[lignetombe][colonnetombe] = tab1 [rand () %8][rand() %19]; //On tire une boule al�atoirement dans le tab1
                fflush(stdin);

            }

        }


    }

}


//FONCTION SAUVEGARDE
void SAUVEGARDE ( struct boule tab2[8][19])
{
    FILE *fichier;
    int i ;
    int j ;
    char nomfichier [10];
    printf ("Nom du fichier? : ");
    scanf("%s",nomfichier);
    strcat(nomfichier, ".txt");
    fichier=fopen(nomfichier,"w+"); //ouvrir le fichier en �criture * // w+ effacer le fichier avant de le sauvegarder
    for (i=0 ; i< TAILLE_L ; i++)
    {

        for (j=0; j<TAILLE_C; j++)
        {
            fprintf ( fichier, "%d %d\n", tab2[i][j].couleur, tab2[i][j].symbole);
        }

    } //ecrire dans le fichier
    fclose(fichier); //fermer le fichier
}

//FONCTION CHARGEMENT
void CHARGEMENT (struct boule tab2[8][19])
{
    FILE *fichier;
    int i ;
    int j;
    char nomfichier [50];
    printf ("Nom du fichier?");
    scanf("%s",nomfichier);
    strcat(nomfichier, ".txt"); // ajouter 2 chaines de caract�re
    fichier=fopen(nomfichier,"r"); //ouvrir le fichier en lecture
    for (i=0 ; i< TAILLE_L ; i++)
    {

        for (j=0; i<TAILLE_C; j++)
        {
            fscanf ( fichier,  "%d%d", &(tab2[i][j].couleur), &(tab2[i][j].symbole));  //lire le fichier
        } //ecrire dans le fichier

    }
    fclose(fichier); //fermer le fichier

}


//FONCTION VALEUR ABSOLUE
int abs(int a)
{
    if (a<0)
    {
        return -a;
    }
    return a;

}

void PERMUTATION (struct boule tab2[8][19], int *w, int *v, int *x, int *y,char *action)    //ICI ON UTILISE DES POINTEURS CAR ON A BESOIN DE RETOURNER PLUSIEURS VALEURS
{


    int ligneboule1;
    int colonneboule1;
    int colonneboule2;
    int ligneboule2;

    printf("\n\n Que voules vous faire ?\n C: CONTINUER\n Q: QUITTER\n"); // VOULEZ VOUS CONTINUER DE JOUER ? C = continuer, Q = QUITTER
    fflush(stdin);
    scanf("%c",action);
    if(*action=='Q') //
    {
        SAUVEGARDE(tab2);
        goto fin;
    }
    printf("\n\n Quelles boules souhaitez vous permuter? \n ");
    printf("\n la premiere boule :  \n colonne : \n ");
    scanf ("%d",&colonneboule1);
    printf("\n la premiere boule :  \n ligne : \n ");
    scanf ("%d",&ligneboule1);


    printf("test: B1: %c\n",tab2[ligneboule1-1][colonneboule1-1].symbole); //test pour verifier le contenu de la case

    while (ligneboule1 <= 0 || ligneboule1 > 8 || colonneboule1 > 19 || colonneboule1 <= 0 ||  tab2[ligneboule1-1][colonneboule1-1].symbole==0)//si la case est une barre, redemander
    {
        printf("\n\n Quelles boules souhaitez vous permuter? \n ");
        printf("\n la premiere boule :  \n colonne : \n ");
        fflush(stdin);
        scanf ("%d",&colonneboule1);
        printf("\n la premiere boule :  \n ligne : \n ");
        fflush(stdin);
        scanf ("%d",&ligneboule1);

    }
    printf("\n la deuxieme boule :  \n colonne :  \n ");
    fflush(stdin);
    scanf ("%d",&colonneboule2);
    printf("\n la deuxieme boule :  \n ligne :  \n ");
    fflush(stdin);
    scanf ("%d",&ligneboule2);

    printf("test: B2:%c \n",tab2[ligneboule2-1][colonneboule2-1].symbole);
    while ((ligneboule2 <= 0 || ligneboule2 > 8) || (colonneboule2 > 19 || colonneboule2 <= 0) || (tab2 [ligneboule2-1][colonneboule2-1].symbole==0 || abs(colonneboule2 - colonneboule1) > 2) || (abs(ligneboule2 - ligneboule1) >=2)) //si la case est vide, redemander
    {
        printf("\n la deuxieme boule :  \n colonne :  \n ");
        fflush(stdin);
        scanf ("%d",&colonneboule2);
        printf("\n la deuxieme boule :  \n ligne :  \n ");
        fflush(stdin);
        scanf ("%d",&ligneboule2);

    }

    colonneboule1 = colonneboule1-1;
    ligneboule1 = ligneboule1-1;
    colonneboule2 = colonneboule2-1;
    ligneboule2 = ligneboule2-1;

    struct boule tampon;

    tampon= tab2[ligneboule1][colonneboule1];
    tab2[ligneboule1][colonneboule1] =  tab2[ligneboule2][colonneboule2];
    tab2[ligneboule2][colonneboule2] = tampon;
fin:
    *v = colonneboule1; //cooordonn�es des boules qu'on doit permuter v : colonne de la premiere boule w : ligne premier boule etc
    *w = ligneboule1;
    *y = colonneboule2;
    *x = ligneboule2;
}
