#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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


int tache_counter = 0, delete_taches_counter = 0; done_counter = 0, undone_counter = 0;


void menu() {


    int chois;

    puts("=======================================================================\n");
    puts("====                              MENU                             ====\n");
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
            add_todo(1);
            break;

        case 2:
            printf("combien de taches tu veux ajouter:\n--> ");
            int n=0;
            scanf("%d", &n);
            add_todo(n);
            break;

        case 3:
            show_todos();
            break;

        case 4:
            system("cls");
            printf("\nQuelle tache tu veux modifier: \n--> ");
            int target_tache;
            scanf("%d", &target_tache);
            printf("1. Modifier la description d'une tache.\n");
            printf("2. Modifier le statut d'une tache.\n");
            printf("3. Modifier le deadline d'une tache.\n--> ");
            int r;
            scanf("%d", &r);

            update_todo(r, target_tache);
            break;

        case 5:
            delete_todo();
            break;

        case 6:
            search_todo();
            break;

        case 7:
            get_Statistics();
            break;

        case 8:
            return 0;

        default:
            printf("the one you chose is not existed.\n");
            menu();
            break;

    }

}



void add_todo(int n) {

    system("cls");

    n += tache_counter - delete_taches_counter;

    // add user info to the todos.
    for(int i=tache_counter - delete_taches_counter; i<n; i++) {

        int statu_chois;

        printf("\n");
        // id.
        todo[i].id = tache_counter+1;
        // title.
        printf("entre le titre de tache %d: ", i+1);
        scanf(" %[^\n]", todo[i].title);
        // description description.
//        printf("entre le description de tache %d: ", i+1);   to uncoment
//        scanf(" %[^\n]", todo[i].description);
        // status.
        strcpy(todo[i].status, "undone");
        // deadline.
        printf("ending time of the tache %d: \n", i+1);
        printf("                            year: ");
        scanf("%d", &todo[i].dead_line.year);
//        printf("                            month: "); to uncoment
//        scanf("%d", &todo[i].dead_line.month);
//        printf("                            day: "); to uncoment
//        scanf("%d", &todo[i].dead_line.day);

        tache_counter++;
        undone_counter++;

        printf("\n");

    }

    menu();

}

void show_todos() {

    printf("\n=========================== IL Y A %d TACHES =========================== \n", tache_counter - delete_taches_counter);
    // show the todos.
    for(int i=0; i<tache_counter - delete_taches_counter; i++) {
        // title and description.
        printf("\n=================== TACHE %d =================== \n", i+1);
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

void update_todo(int n, int tache) {

    int current_statu;

    switch(n) {
        case 1:
            printf("entrez la nouvelle description: ");
            scanf(" %[^\n]", todo[tache-1].description);
            menu();
            break;

        case 2:
            do {
            printf("statut de tache %d: \n", tache);
            printf("1. undone           2. doing           3. done\n-->");
            scanf(" %d", &current_statu);
            } while (current_statu<1 && current_statu>3);

            if(current_statu == 1) {
                strcpy(todo[tache-1].status, "undone");
//                strcmp(todo[tache-1].status, "undone");
                undone_counter++;

            } else if (current_statu == 2) {
                strcpy(todo[tache-1].status, "doing");
                undone_counter--;

            } else if (current_statu == 3) {
                strcpy(todo[tache-1].status, "done");
                done_counter++;
                undone_counter--;

            }


            menu();

            break;

        case 3:
            printf("entrez la nouvelle deadline: \n\n");
            printf("                            year: ");
            scanf("%d", &todo[tache-1].dead_line.year);
            printf("                            month: ");
            scanf("%d", &todo[tache-1].dead_line.month);
            printf("                            day: ");
            scanf("%d", &todo[tache-1].dead_line.day);

            menu();
            break;

    }

}

void search_todo() {

    int search_chois;

    printf("1. Rechercher une tache par son Identifiant.\n");
    printf("2. Rechercher une tache par son Titre.\n--> ");
    scanf("%d", &search_chois);

    if(search_chois == 1) {

        int Identifiant;

        printf("entre Identifiant: ");
        scanf("%d", &Identifiant);

        for(int i=0; i<tache_counter; i++) {
            if(todo[i].id == Identifiant) {
                printf("\n=================== TACHE %d =================== \n", todo[i].id);
                printf("id: %d.\n", todo[i].id);
                printf("le titre: %s.\nle description: %s.\n", todo[i].title, todo[i].description);
                printf("deadline: %d/%d/%d.\n", todo[i].dead_line.day, todo[i].dead_line.month, todo[i].dead_line.year);
                printf("statu: %s.\n", todo[i].status);
                printf("\n======================================================================== \n");
            }
        }

        menu();

    } else if (search_chois == 2) {

        char titre[50];

        printf("entre le titre: ");
        scanf(" %[^\n]", &titre);

        for(int i=0; i<tache_counter; i++) {
            if(strcmp(todo[i].title, titre) == 0) {
                printf("\n=================== TACHE %d =================== \n", todo[i].id);
                printf("id: %d.\n", todo[i].id);
                printf("le titre: %s.\nle description: %s.\n", todo[i].title, todo[i].description);
                printf("deadline: %d/%d/%d.\n", todo[i].dead_line.day, todo[i].dead_line.month, todo[i].dead_line.year);
                printf("statu: %s.\n", todo[i].status);
                printf("\n======================================================================== \n");
            }
        }

        menu();

    } else {
        printf("the one you chose is not existed."); // to color red

        menu();

    }



}

void delete_todo() {

    int target_tache_id;
    int target_tache_index;

    printf("\nEntre identifiant de tache tu veux Supprimer: \n--> ");
    scanf("%d", &target_tache_id);


    for(int i=0; i<tache_counter; i++) {
        if(todo[i].id == target_tache_id) {
            target_tache_index = i;
        }
    }

    for(int i=target_tache_index; i<tache_counter; i++) {
        todo[i] = todo[i+1];
    }

    delete_taches_counter++;

    printf("tache %d deleted secsusfully. %d\n", target_tache_id);

    menu();

}

void get_Statistics() {

    int statistics_chois;

    printf("\n\n");
    printf("1. Afficher le nombre total des taches.\n");
    printf("2. Afficher le nombre de taches complètes et incomplètes.\n");
    printf("3. Afficher le nombre de jours restants jusqu'au délai de chaque tache.\n--> ");

    scanf("%d", &statistics_chois);

    switch(statistics_chois) {
        case 1:
            printf("le nombre total des taches est %d.\n", tache_counter);
            break;

        case 2:
            printf("le nombre de taches complètes (%d).\n", done_counter);
            printf("le nombre de taches incomplètes eat (%d).\n", undone_counter);
            break;

        case 3:
            printf("this statistic is coming soon...\n");
            break;
    }

    menu();

}


int main()
{

    menu();

    return 0;
}
