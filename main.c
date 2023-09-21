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
            printf("edit\n");
            break;
        case 5:
            printf("search\n");
            break;
        case 6:
            printf("status\n");
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
        todo[i].id = tache_counter;
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
        printf("le titre: %s.\nle description: %s.\n", todo[i].title, todo[i].description);
        printf("deadline: %d/%d/%d.\n", todo[i].dead_line.day, todo[i].dead_line.month, todo[i].dead_line.year);
        printf("statu: %s.", todo[i].status);
    }
    printf("\n======================================================================== \n", tache_counter);

    menu();

}


int main()
{

//    todos todo[2];
//
//    todo[0].id = 1;
//    todo[0].title = "to eat";
//
//    todo[1].id = 2;
//    todo[1].title = "to play";
//
//
//    for(int i=0; i<2; i++) {
//        printf("id = %d\n", todo[i].id);
//        printf("id = %s\n", todo[i].title);
//    }

      menu();
//      showTodos();


    return 0;
}
