#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



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

    printf("=======================================================================\n");
    printf("====                             -MENU-                            ====\n\n");
    printf("  1. Ajouter une nouvelle tache.\n");
    printf("  2. Ajouter plusieurs nouvelles taches.\n");
    printf("  3. Afficher la liste de toutes les taches.\n");
    printf("  4. Modifier une tache.\n");
    printf("  5. Supprimer une tache par identifiant.\n");
    printf("  6. Rechercher les Taches.\n");
    printf("  7. Statistiques.\n");
    printf("  8. Exite.\n");
    printf("=======================================================================\n\n");


    printf("\n                           le Choix: ");
    printf("\n                                 --> ");
    scanf("%d", &chois);



    switch(chois) {
        case 1:
            add_todo(1);
            break;

        case 2:
            system("cls");
            printf("combien de taches tu veux ajouter:\n--> ");
            int n=0;
            scanf("%d", &n);
            add_todo(n);
            break;

        case 3:
            show_todos();
//            sort_by_alphabetical();
            break;

        case 4:
            update_todo();
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
            system("cls");
            system("COLOR 0C");
            printf("\n  the one you chose is not existed.\n\n\n");
            system("pause");
            system("COLOR 0F");
            menu();
            break;

    }

}



void add_todo(int n) {


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

    system("cls");

    system("COLOR 0A");
    if(n == 1) {
        printf("\n  tache added succasfuly!\n\n");
    } else {
        printf("\n  taches added succasfuly!\n\n");
    }

    system("pause");

    system("COLOR 0F");

    menu();

}

void show_todos() {

    int show_chois;

    printf("\n\nTRIER:\n");
    printf("1. Trier les taches par ordre alphabetique.\n");
    printf("2. Trier les taches par deadline.\n");
    printf("3. Afficher les taches dont le deadline est dans 3 jours ou moins.\n--> ");
    scanf("%d", &show_chois);

    switch(show_chois) {
        case 1:
            sort_by_alphabetical();
            break;
        case 2:
            sort_by_deadline();
            break;
        case 3:
            printf("\n  sort by deadline less than 3 days coming soon.\n\n");
            break;
    }


//    printf("\n**************************** IL Y A (%d) TACHES **************************** \n", tache_counter - delete_taches_counter);
    // show the todos.
//    for(int i=0; i<tache_counter - delete_taches_counter; i++) {
//        // title and description.
//        printf("\n----------------- TACHE %d ----------------- \n", i+1);
//        printf("id: %d.\n", todo[i].id);
//        printf("le titre: %s.\nle description: %s.\n", todo[i].title, todo[i].description);
//        printf("deadline: %d/%d/%d.\n", todo[i].dead_line.day, todo[i].dead_line.month, todo[i].dead_line.year);
//        printf("statu: %s.\n", todo[i].status);
//    }
//    printf("\n*************************************************************************** \n\n", tache_counter);

    system("pause");
    menu();

}

void sort_by_alphabetical() {

//    printf("you wanna sort by alphabits.");

    printf("\n**************************** IL Y A (%d) TACHES **************************** \n", tache_counter - delete_taches_counter);

    for(int i=0; i<tache_counter; i++) {

        for(int j=i+1; j<tache_counter; j++) {
            if(strcmp(todo[i].title, todo[j].title) > 0) {
                todos newTodo;
                newTodo = todo[j];
                todo[j] = todo[i];
                todo[i] = newTodo;
            }
        }
        // title and description.
        printf("\n----------------- TACHE %d ----------------- \n", i+1);
        printf("- id: %d.\n", todo[i].id);
        printf("- le titre: %s.\n- le description: %s.\n", todo[i].title, todo[i].description);
        printf("- deadline: %d/%d/%d.\n", todo[i].dead_line.day, todo[i].dead_line.month, todo[i].dead_line.year);
        printf("- statu: %s.\n", todo[i].status);

    }
        printf("\n*************************************************************************** \n\n", tache_counter);

    system("pause");

    menu();


}

void sort_by_deadline() {

    time_t current_time = time(NULL);
    printf("%ld\n", current_time);

    struct tm date = *localtime(&current_time);

    int current_year = date.tm_year + 1900;
    int current_month = date.tm_mon + 1;
    int current_day = date.tm_mday;

    printf("\nyear: %d\n", current_year);
    printf("month: %d\n", current_month);
    printf("day: %d\n", current_day);


//    for()

//    printf("hour: %d\n", date.tm_hour);
//    printf("hour: %d\n", date.tm_min);



    menu();

}





void update_todo() {

    int current_statu;

    system("cls");
    int target_tache, n;

    printf("\nQuelle tache tu veux modifier: \n--> ");
    scanf("%d", &target_tache);
    printf("1. Modifier la description d'une tache.\n");
    printf("2. Modifier le statut d'une tache.\n");
    printf("3. Modifier le deadline d'une tache.\n--> ");
    scanf("%d", &n);

    switch(n) {
        case 1:


            printf("entrez la nouvelle description: ");
            scanf(" %[^\n]", todo[target_tache-1].description);


            system("cls");
            system("COLOR 0A");

            printf("\n  la description est modifie!\n\n");

            system("pause");
            system("COLOR 0F");

            menu();
            break;

        case 2:
            do {
            printf("statut de tache %d: \n", target_tache);
            printf("1. undone           2. doing           3. done\n-->");
            scanf(" %d", &current_statu);
            } while (current_statu<1 && current_statu>3);

            if(current_statu == 1) {
                strcpy(todo[target_tache-1].status, "undone");
//                strcmp(todo[tache-1].status, "undone");
                undone_counter++;

            } else if (current_statu == 2) {
                strcpy(todo[target_tache-1].status, "doing");
                undone_counter--;

            } else if (current_statu == 3) {
                strcpy(todo[target_tache-1].status, "done");
                done_counter++;
                undone_counter--;

            }


            system("cls");
            system("COLOR 0A");

            printf("\n  le statu est modifie!\n\n");

            system("pause");
            system("COLOR 0F");

            menu();

            break;

        case 3:
            printf("entrez la nouvelle deadline: \n\n");
            printf("                            year: ");
            scanf("%d", &todo[target_tache-1].dead_line.year);
            printf("                            month: ");
            scanf("%d", &todo[target_tache-1].dead_line.month);
            printf("                            day: ");
            scanf("%d", &todo[target_tache-1].dead_line.day);

            system("cls");
            system("COLOR 0A");

            printf("\n  le deadline est modifie!\n\n");

            system("pause");
            system("COLOR 0F");

            menu();
            break;

    }

}

void search_todo() {

    system("cls");

    int search_chois;

    printf("\n  RECHERCHER: \n");
    printf("  1. Rechercher une tache par son Identifiant.\n");
    printf("  2. Rechercher une tache par son Titre.\n  --> ");
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

//        else {
//                system("cls");
//                system("COLOR 0C");
//
//                printf("\n  todo avec l'identifiant %d n'existe pas!\n\n", target_tache_id);
//
//                system("pause");
//
//                system("COLOR 0F");
//        }

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

    }

//    else {
//
//        system("cls");
//        system("COLOR 0C");
//
//        printf("\n  todo avec le titre \"%s\" n'existe pas!\n\n", target_tache_id);
//
//        system("pause");
//
//        system("COLOR 0F");
//
//        menu();
//
//    }



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

    system("cls");
    system("COLOR 0A");

    printf("\n  tache %d deleted secsusfully!.\n\n", target_tache_id);

    system("pause");

    system("COLOR 0F");

    menu();

}

void get_Statistics() {

    system("cls");

    int statistics_chois;

    printf("\n\n");
    printf("  1. Afficher le nombre total des taches.\n");
    printf("  2. Afficher le nombre de taches complètes et incomplètes.\n");
    printf("  3. Afficher le nombre de jours restants jusqu'au délai de chaque tache.\n\n  --> ");

    scanf("%d", &statistics_chois);

    switch(statistics_chois) {
        case 1:
            printf("\n  le nombre total des taches est %d.\n\n", tache_counter);
            break;

        case 2:
            printf("\n  le nombre de taches complètes est (%d).\n", done_counter);
            printf("  le nombre de taches incomplètes est (%d).\n\n", undone_counter);
            break;

        case 3:
            printf("\n  this statistic is coming soon...\n\n");
            break;
    }

    system("pause");

    menu();

}


int main()
{

    printf("                   _____    ______        _ _     _   \n");
    printf("                  |_   _|   |  _  \\      | (_)   | |  \n");
    printf("                    | | ___ | | | |___   | |_ ___| |_ \n");
    printf("                    | |/ _ \\| | | / _ \\  | | / __| __|\n");
    printf("                    | | (_) | |/ / (_) | | | \\__ \\ |_ \n");
    printf("                    \\_/\\___/|___/ \\___/  |_|_|___/\\__|\n");
    printf("\n\n\n\n");

    system("pause");

    menu();

    return 0;
}
