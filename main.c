#include <stdio.h>
#include <stdlib.h>
#include "add.h"
#include "show.h"

int tache_counter = 0;


void menu() {


    int chois;

    puts("=======================================================================\n");
    puts("=                                 MENU                                =\n");
    puts("=======================================================================\n");
    printf("1. Ajouter une nouvelle tache.\n");
    printf("2. Ajouter plusieurs nouvelles taches.\n");
    printf("3. Afficher la liste de toutes les tâches.\n");
    printf("4. Modifier une tache\n");
    printf("5. Supprimer une tache par identifiant.\n");
    printf("6. Rechercher les Taches.\n");
    printf("7. Statistiques.\n");
    printf("8. Exite.\n");

    printf("\n                           choisissez-en un: ");
    printf("\n                           --> ");
    scanf("%d", &chois);



    switch(chois) {
        case 1:
            add(1);
            break;
        case 2:
            printf("combien de taches tu veux ajouter:\n--> ");
            int n=0;
            scanf("%d", &n);
            add(n);
            break;
        case 3:
            showTodos();
            break;

        case 4:
            system("cls");
            printf("\nQuelle tache tu veux modifier: \n--> ");
            int target_tache;
            scanf("%d", &target_tache);
            printf("1. Modifier la description d'une tache.\n");
            printf("2. Modifier le statut d’une tache.\n");
            printf("3. Modifier le deadline d’une tache.\n--> ");
            int r;
            scanf("%d", &r);

            update(r, target_tache);
            break;

        case 5:
            printf("edit\n");
            break;

        case 6:
            printf("Rechercher une tache par son Identifiant.\n");
            printf("\n");
            int
            search();
            break;
        case 7:
            printf("Statistiques\n");
            break;
        case 8:
            return 0;
        default:
            printf("the one you chose is not existed.\n");
            menu();
            break;
    }

}


// les structures.
typedef struct {
    int year;
    int month;
    int day;
} deadline;

typedef struct {
    int id;
    char title[30];
    char description[100];
    char status[30];
    deadline dead_line;

} todos;

todos todo[100];


void add(int n) {

    system("cls");

    n += tache_counter;

    // add user info to the todos.
    for(int i=tache_counter; i<n; i++) {
        printf("\n");
        // id.
        todo[i].id = tache_counter+1;
        // title.
        printf("entre le titre de tache %d: ", i+1);
        scanf(" %[^\n]", todo[i].title);
        // description description.
        printf("entre le description de tache %d: ", i+1);
        scanf(" %[^\n]", todo[i].description);
        // status.
        printf("statut de tache %d: ", i+1);
        scanf(" %[^\n]", todo[i].status);
        // deadline.
        printf("ending time of the tache %d: \n", i+1);
        printf("                            year: ");
        scanf("%d", &todo[i].dead_line.year);
        printf("                            month: ");
        scanf("%d", &todo[i].dead_line.month);
        printf("                            day: ");
        scanf("%d", &todo[i].dead_line.day);


        tache_counter++;

        printf("\n");
    }

    menu();

}

void showTodos() {

    printf("\n=========================== IL Y A %d TACHES =========================== \n", tache_counter);
    // show the todos.
    for(int i=0; i<tache_counter; i++) {
        // title and description.
        printf("\n=================== TACHE %d =================== \n", todo[i].id+1);
        printf("id: %d.\n", todo[i].id);
        printf("le titre: %s.\nle description: %s.\n", todo[i].title, todo[i].description);
        printf("deadline: %d/%d/%d.\n", todo[i].dead_line.day, todo[i].dead_line.month, todo[i].dead_line.year);
        printf("statu: %s.\n", todo[i].status);
    }
    printf("\n======================================================================== \n", tache_counter);

    menu();

}

void sort_by_alphabetical() {

    for(int i=0; i<3; i++) {
        printf("%d", todo[i].id);
        printf("%s. \n", todo[i].title);
    }

}

void update(int n, int tache) {

    printf("the num is: %d, and the tache is %d.\n", n, tache);
//    for(int i=0; i<tache_counter; i++) {
//        if()
//    }
    switch(n) {
        case 1:
            printf("\n", n, tache);
            scanf("%s", todo[tache].description);
            menu();
            break;
//            todo[tache].description =
        case 2:
            printf("\n", n, tache);
            scanf("%s", todo[tache].status);
            menu();
            break;
//            todo[tache].status =
        case 3:
            printf("\n", n, tache);
            scanf("%d", todo[tache].dead_line.year);
            scanf("%d", todo[tache].dead_line.month);
            scanf("%d", todo[tache].dead_line.day);
            menu();
            break;
//            todo[tache].dead_line =
    }

}

void search() {

}
int main()
{

      menu();

    return 0;
}
