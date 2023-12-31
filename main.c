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
    int the_rest_days;
    char title[30];
    char description[100];
    char status[30];
    deadline dead_line;

} todos;

todos todo[100];


int tache_counter = 0, delete_taches_counter = 0; done_counter = 0, undone_counter = 0;


void menu() {


    int chois;

    printf("\n                      =======================================================================\n");
    printf("                      ====                             -MENU-                            ====\n\n");
    printf("                        1. Ajouter une nouvelle tache.\n");
    printf("                        2. Ajouter plusieurs nouvelles taches.\n");
    printf("                        3. Afficher la liste de toutes les taches.\n");
    printf("                        4. Modifier une tache.\n");
    printf("                        5. Supprimer une tache par identifiant.\n");
    printf("                        6. Rechercher les Taches.\n");
    printf("                        7. Statistiques.\n");
    printf("                        0. Exite.\n");
    printf("                      =======================================================================\n");


    printf("\n                                                     le Choix: ");
    printf("\n                                                       --> ");
    scanf("%d", &chois);



    switch(chois) {
        case 1:
            add_todo(1);
            break;

        case 2:
            system("cls");
            printf("\n  combien de taches tu veux ajouter:\n  --> ");
            int n=0;
            scanf("%d", &n);
            add_todo(n);
            break;

        case 3:
            show_todos();
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

        case 0:
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


int id_to_index(int target_tache_id) {

    int target_tache_index;

    for(int i=0; i<tache_counter; i++) {
        if(todo[i].id == target_tache_id) {
            target_tache_index = i;
        }
    }

    return target_tache_index;
}

void add_todo(int n) {

    system("cls");

    int loop_to = n + tache_counter;

    // add user info to the todos.
    for(int i=tache_counter; i<loop_to; i++) {

        int statu_chois;

        printf("\n");
        // id.
        todo[i].id = tache_counter + 1 + delete_taches_counter;
        // title.
        printf("  Entre le titre de tache %d: ", i+1);
        scanf(" %[^\n]", todo[i].title);
        // description description.
        printf("\n  Entre le description de tache %d: ", i+1);
        scanf(" %[^\n]", todo[i].description);
        // status.
        strcpy(todo[i].status, "undone");
        // deadline.
        printf("\n  Ending time of the tache %d: \n", i+1);
        printf("                              Year: ");
        scanf("%d", &todo[i].dead_line.year);
        printf("                              Month: ");
        scanf("%d", &todo[i].dead_line.month);
        printf("                              Day: ");
        scanf("%d", &todo[i].dead_line.day);

        tache_counter++;
        undone_counter++;

        printf("\n");

    }

    system("cls");

    system("COLOR 0A");
    if(n == 1) {
        printf("\n %d tache added succasfuly!\n\n", n);
    } else {
        printf("\n %d taches added succasfuly!\n\n", n);
    }


    system("pause");
    system("COLOR 0F");
    system("cls");

    menu();

}

void show_todos() {

    system("cls");

    int show_chois;

    printf("\n\n  TRIER:\n");
    printf("  1. Trier les taches par ordre alphabetique.\n");
    printf("  2. Trier les taches par deadline.\n");
    printf("  3. Afficher les taches dont le deadline est dans 3 jours ou moins.\n\n  le choix:\n        --> ");

    scanf("%d", &show_chois);

    switch(show_chois) {
        case 1:
            sort_by_alphabetical();
            break;

        case 2:
            sort_by_deadline();
            break;

        case 3:
            show_less_than3days();
            break;

    }

    system("pause");
    system("cls");

    menu();

}

void sort_by_alphabetical() {

//    printf("you wanna sort by alphabits.");

    printf("\n  **************************** (%d) TACHES TRIEES PAR ORDRE ALPHABETIQUE **************************** \n", tache_counter);

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
        printf("\n  ----------------- TACHE %d ----------------- \n", i+1);
        printf("  - id: %d.\n", todo[i].id);
        printf("  - le titre: %s.\n  - le description: %s.\n", todo[i].title, todo[i].description);
        printf("  - deadline: %d/%d/%d.\n", todo[i].dead_line.day, todo[i].dead_line.month, todo[i].dead_line.year);
        printf("  - statu: %s.", todo[i].status);
        printf("\n  -------------------------------------------- \n", i+1);

    }
        printf("\n  *********************************************************************************************** \n\n");

    system("pause");
    system("cls");

    menu();


}

void calculate_rest_days() {

    // this return the current time.
    time_t current_time = time(NULL);
    struct tm date = *localtime(&current_time);

    // current date.
    int current_year = date.tm_year + 1900;
    int current_month = date.tm_mon + 1;
    int current_day = date.tm_mday;

    // calculate rest days for each todo.
    for(int i=0; i<tache_counter; i++) {
        todo[i].the_rest_days = (todo[i].dead_line.year - current_year) * 365 + (todo[i].dead_line.month - current_month) * 30 + (todo[i].dead_line.day - current_day);
    }

}

void sort_by_deadline() {

    calculate_rest_days();

    printf("\n  **************************** (%d) TACHES TRIEES PAR DEADLINE **************************** \n", tache_counter);

    // sort the todos by the deadline.
    for(int i=0; i<tache_counter; i++) {
        for(int j=i+1; j<tache_counter; j++) {
            if(todo[i].the_rest_days > todo[j].the_rest_days) {
                todos swapTodo;
                swapTodo = todo[j];
                todo[j] = todo[i];
                todo[i] = swapTodo;
            }
        }
        printf("\n  ----------------- TACHE %d ----------------- \n", i+1);
        printf("  - id: %d.\n", todo[i].id);
        printf("  - le titre: %s.\n  - le description: %s.\n", todo[i].title, todo[i].description);
        printf("  - deadline: %d/%d/%d.\n", todo[i].dead_line.day, todo[i].dead_line.month, todo[i].dead_line.year);
        printf("  - statu: %s.\n", todo[i].status);
        printf(" -------------------------------------------- \n", i+1);
    }

    printf("\n  *************************************************************************** \n\n", tache_counter);

    system("pause");
    system("cls");

    menu();

}

void show_less_than3days() {

    calculate_rest_days();

    printf("\n  ********************* LES TACHES DONT LE DEADLINE EST DANS 3 JOURS OU MOINS ********************* \n");
    for(int i=0; i<tache_counter; i++) {
        if(todo[i].the_rest_days <= 3) {
            printf("\n  ----------------- TACHE %d ----------------- \n", i+1);
            printf("  - id: %d.\n", todo[i].id);
            printf("  - le titre: %s.\n  - le description: %s.\n", todo[i].title, todo[i].description);
            printf("  - deadline: %d/%d/%d.\n", todo[i].dead_line.day, todo[i].dead_line.month, todo[i].dead_line.year);
            printf("  - statu: %s.\n", todo[i].status);
            printf("  -------------------------------------------- \n", i+1);
        }
    }
    printf("\n  ************************************************************************************************* \n\n");

}

void update_todo() {

    int current_statu;

    system("cls");

    int target_tache_id, target_tache_index, n;

    printf("\n  Entre identifiant de tache tu veux modifier: \n  --> ");
    scanf("%d", &target_tache_id);

    printf("\n  MODIFIER: \n");
    printf("  1. Modifier la description d'une tache.\n");
    printf("  2. Modifier le statut d'une tache.\n");
    printf("  3. Modifier le deadline d'une tache.\n\n  le choix:\n        --> ");
    scanf("%d", &n);

    target_tache_index = id_to_index(target_tache_id);

    switch(n) {
        case 1:

            printf("\n  Entrez la nouvelle description: ");
            scanf(" %[^\n]", todo[target_tache_index].description);


            system("cls");
            system("COLOR 0A");

            printf("\n  la description est modifie!\n\n");

            system("pause");
            system("COLOR 0F");
            system("cls");

            menu();
            break;

        case 2:
            do {
            printf("\n  Entre le Nouveau statut de tache %d: \n", target_tache_id);
            printf("  1. undone           2. doing           3. done\n\n  le choix:\n        --> ");
            scanf(" %d", &current_statu);
            } while (current_statu<1 && current_statu>3);

            if(current_statu == 1) {

                strcpy(todo[target_tache_index].status, "undone");

            } else if (current_statu == 2) {

                strcpy(todo[target_tache_index].status, "doing");

            } else if (current_statu == 3) {

                strcpy(todo[target_tache_index].status, "done");
                undone_counter--;
                done_counter++;


            }


            system("cls");
            system("COLOR 0A");

            printf("\n  le statu est modifie!\n\n");

            system("pause");
            system("COLOR 0F");
            system("cls");

            menu();

            break;

        case 3:
            printf("\n23  Entrez la nouvelle deadline: \n\n");
            printf("                              year: ");
            scanf("%d", &todo[target_tache_index].dead_line.year);
            printf("                              month: ");
            scanf("%d", &todo[target_tache_index].dead_line.month);
            printf("                              day: ");
            scanf("%d", &todo[target_tache_index].dead_line.day);

            system("cls");
            system("COLOR 0A");

            printf("\n  le deadline est modifie!\n\n");

            system("pause");
            system("COLOR 0F");
            system("cls");

            menu();
            break;

    }

}

void search_todo() {

    system("cls");

    int search_chois;

    printf("\n  RECHERCHER: \n");
    printf("  1. Rechercher une tache par son Identifiant.\n");
    printf("  2. Rechercher une tache par son Titre.\n\n  le choix:\n        --> ");
    scanf("%d", &search_chois);

    if(search_chois == 1) {

        int Identifiant;

        printf("\n  Entre Identifiant: \n  -->  ");
        scanf("%d", &Identifiant);

        // if the id is not existed.
        if(Identifiant < 0 || Identifiant > tache_counter+delete_taches_counter) {

            system("cls");
            system("COLOR 0C");
            printf("\n  tache avec l'identifiant %d n'existe pas!.\n\n", Identifiant);
            system("pause");
            system("COLOR 0F");
            system("cls");

        // if the id is not existed.
        } else {

            printf("\n  ************************** RECHERCHER PAR IDENTIFIANT ************************** \n");
            for(int i=0; i<tache_counter; i++) {

                if(todo[i].id == Identifiant) {
                    printf("\n ---------------- TACHE %d ---------------- \n", todo[i].id);
                    printf("  -id: %d.\n", todo[i].id);
                    printf("  -le titre: %s.\n  -le description: %s.\n", todo[i].title, todo[i].description);
                    printf("  -deadline: %d/%d/%d.\n", todo[i].dead_line.day, todo[i].dead_line.month, todo[i].dead_line.year);
                    printf("  -statu: %s.\n", todo[i].status);
                    printf("\n ------------------------------------------ \n");
                }

            }
            printf("\n  ******************************************************************************** \n");

            system("pause");
            system("cls");

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

    }


}

void delete_todo() {

    system("cls");

    int target_tache_id;
    int target_tache_index;

    printf("\n  Entre identifiant de tache tu veux Supprimer: \n  --> ");
    scanf("%d", &target_tache_id);

    // if the id is not existed.
    if(target_tache_id < 0 || target_tache_id > tache_counter+delete_taches_counter) {

        system("cls");
        system("COLOR 0C");
        printf("\n  tache avec l'identifiant %d n'existe pas!.\n\n", target_tache_id);
        system("pause");
        system("COLOR 0F");
        system("cls");

    // if the id is not existed.
    } else {

        target_tache_index = id_to_index(target_tache_id);

        if( strcmp(todo[target_tache_index].status, "undone") == 0 ) {
            undone_counter--;
        } else {
            done_counter--;
        }

        for(int i=target_tache_index; i<tache_counter; i++) {
            todo[i] = todo[i+1];
        }

        tache_counter--;
        delete_taches_counter++;

        system("cls");
        system("COLOR 0A");
        printf("\n  tache avec l'identifiant %d supprim� secsusfully!.\n\n", target_tache_id);
        system("pause");
        system("COLOR 0F");
        system("cls");

    }


    menu();

}

void get_Statistics() {

    system("cls");

    int statistics_chois;

    printf("\n\n");
    printf("  STATISTIQUES:\n");
    printf("  1. Afficher le nombre total des taches.\n");
    printf("  2. Afficher le nombre de taches compl�tes et incompl�tes.\n");
    printf("  3. Afficher le nombre de jours restants jusqu'au d�lai de chaque tache.\n\n  le choix:\n        --> ");

    scanf("%d", &statistics_chois);

    switch(statistics_chois) {
        case 1:
            system("cls");
            printf("\n  le nombre total des taches est %d.\n\n", tache_counter);
            break;

        case 2:
            system("cls");
            printf("\n  le nombre de taches compl�tes est (%d).\n", done_counter);
            printf("  le nombre de taches incompl�tes est (%d).\n\n", undone_counter);
            break;

        case 3:
            system("cls");
            show_the_rest_days();
            break;
    }

    system("pause");
    system("cls");

    menu();

}

void show_the_rest_days() {

    calculate_rest_days();

    printf("\n  ********************* LE NOMBRE DE JOURS RESTANTS JUSQU'AU DELAI DE CHAQUE TACHE ********************* \n");
    for(int i=0; i<tache_counter; i++) {
            printf("\n\n  ----------------- TACHE %d ----------------- \n", i+1);
            printf("  - id: %d.\n", todo[i].id);
            printf("  - le titre: %s.\n", todo[i].title);
            printf("  - les jours restants: %d", todo[i].the_rest_days);
            printf("\n  ------------------------------------------- \n");
    }
    printf("\n\n  ****************************************************************************************************** \n\n");

}


int main()
{

    printf("\n\n");
    printf("                                        _____    ______        _ _     _   \n");
    printf("                                       |_   _|   |  _  \\      | (_)   | |  \n");
    printf("                                         | | ___ | | | |___   | |_ ___| |_ \n");
    printf("                                         | |/ _ \\| | | / _ \\  | | / __| __|\n");
    printf("                                         | | (_) | |/ / (_) | | | \\__ \\ |_ \n");
    printf("                                         \\_/\\___/|___/ \\___/  |_|_|___/\\__|\n");
    printf("\n\n\n\n");

    system("pause");

    menu();

    return 0;
}
