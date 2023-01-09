#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define nameMax 9999
#define arrayMax 5

void main();
void goInsert(char inputName[nameMax], int inputKey);
void goRemove(char removeName[nameMax]);
void goDisplay();
void goSearch(char searchName[nameMax]);
void goEdit(char editName[nameMax]);

struct node {

    int key;
    char name[nameMax];
    struct node *link;

};

struct node *array[arrayMax];
int editing = 0;    // 0 = false, 1 = true

void goInsert(char inputName[nameMax], int inputKey) {

    int nameLength = strlen(inputName);
    int nameASCII = 0;
    int a = 0;

    for(a = 0; a < nameLength; a++) {

        nameASCII += inputName[a];

    }

    int keyIndex = nameASCII % arrayMax;

    // Check if already exists.
    struct node *checker = array[keyIndex];
    int alreadyExists = 0;  // 0 = false, 1 = true

    while(checker != NULL) {

        if(strcmp(inputName, checker -> name) == 0) {
            alreadyExists = 1;
            goto jumpToThisArea;
        }

        checker = checker -> link;
    }

    jumpToThisArea:
    if(alreadyExists == 1) {

        strcpy(checker -> name, inputName);
        checker -> key = inputKey;        

    } else {

        struct node *ptr = (struct node *)malloc(sizeof(struct node));
    
        ptr -> key = inputKey;
        strcpy(ptr -> name, inputName);

        if(array[keyIndex] == NULL) {
            array[keyIndex] = ptr;
        } else {

            struct node *temp = array[keyIndex];
            while(temp -> link != NULL) {
                temp = temp -> link;
            }
            temp -> link = ptr;
        }

        ptr -> link = NULL;

    }
    
    if(editing != 1) {
        printf("[] ADD SUCCESSFUL!\n");
    }

}

void goDisplay() {

    int a = 0;
    for(a = 0; a < arrayMax; a++) {

        struct node *displayer = array[a];
        printf("[ARRAY %d] = ", a);
        while(displayer != NULL) {

            printf("[%d] %s", displayer -> key, displayer -> name);
            if(displayer -> link != NULL) {
                printf(", ");
            }

            displayer = displayer -> link;

        }
        printf("\n");

    }

}

void goRemove(char removeName[nameMax]) {

    struct node *before;
    struct node *connector;
    struct node *finder;
    int a = 0;

    int indexFound;
    int removeExists = 0;   // 0 = false, 1 = true

    for(a = 0; a < arrayMax; a++) {
        
        connector = array[a];
        finder = array[a];

        while(finder != NULL) {

            before = finder;
            finder = finder -> link;

            if(strcmp(before -> name, removeName) == 0) {
                indexFound = a;
                removeExists = 1;
                goto jumpToThisPart;
            }

            connector = before;

        }      

    }

    jumpToThisPart: 
    if(removeExists == 1) {

        if(strcmp(array[indexFound] -> name, removeName) == 0) {
            array[indexFound] = array[indexFound] -> link;
        } else {
            connector -> link = finder;
        }
        free(before);

        if(editing != 1) {
            printf("[] WORD SUCCESSFULLY REMOVED!\n");
        }

    } else {
        printf("[] WORD TO REMOVE NOT FOUND!\n");
    }

}

void goSearch(char searchName[nameMax]) {

    struct node *searcher;
    int a = 0;
    int searchFound = 0;    // 0 = false, 1 = true

    int arrayFound;
    
    for(a = 0; a < arrayMax; a++) {

        searcher = array[a];

        while(searcher != NULL) {

            if(strcmp(searcher -> name, searchName) == 0) {
                arrayFound = a;
                searchFound = 1;
                goto jumpToThisPart;
            }

            searcher = searcher -> link;
        }

    }

    jumpToThisPart:
    if(searchFound == 1) {
        printf("[] WORD TO SEARCH FOUND.\n\n");
        printf("Array Found: [%d]\n", arrayFound);
        printf("Name: %s\n", searcher -> name);
        printf("Key: %d\n", searcher -> key);
    } else {
        printf("[] WORD TO SEARCH DOES NOT EXIST.\n");
    }

}

void goEdit(char editName[nameMax]) {
    
    struct node *editor;
    int a;
    int editExists = 0; // 0 = false, 1 = true
    int indexFound;

    for(a = 0; a < arrayMax; a++) {
        editor = array[a];

        while(editor != NULL) {

            if(strcmp(editor -> name, editName) == 0) {
                editExists = 1;
                indexFound = a;
                goto jumpToThisPart;
            }

            editor = editor -> link;
        }
    }

    jumpToThisPart:
    if(editExists == 1) {

        char newName[nameMax];
        int newKey;

        printf("NAME TO EDIT: %s\n", editor -> name);

        printf("\nEnter New Name: ");
        fgets(newName, nameMax, stdin);
        newName[strcspn(newName, "\n")] = '\0';
    
        printf("Enter New Key: ");
        scanf("%d", &newKey);
        while ((getchar()) != '\n');

        int newNameLength = strlen(newName);
        int newNameASCII = 0;

        for(a = 0; a < newNameLength; a++) {
            newNameASCII += newName[a];
        }

        int originalKey = indexFound;
        int newNameKey  = newNameASCII % arrayMax;

        if(originalKey == newNameKey) {
            strcpy(editor -> name, newName);
            editor -> key = newKey;
        } else {
            editing = 1;
            goRemove(editName);
            goInsert(newName, newKey);
            editing = 0;
        }

        printf("[] WORD SUCCESSFULLY EDITED!\n");


    } else {
        printf("[] WORD TO EDIT NOT FOUND!\n");
    }

}

void main() {

    int choice = 0;

    do {

        printf("---------------------------------------------------\n");
        printf("                SEPARATE CHAINING                  \n");
        printf("---------------------------------------------------\n");
        printf("[1] Add\n");
        printf("[2] Remove\n");
        printf("[3] Search\n");
        printf("[4] Display\n");
        printf("[5] Edit\n");
        printf("[6] Exit\n");
        
        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        while ((getchar()) != '\n');

        switch(choice) {
            case (1):

                printf("---------------------------------------------------\n");
                printf("                        ADD                        \n");
                printf("---------------------------------------------------\n");

                char inputName[nameMax];
                int inputKey;
                
                printf("Enter Name: ");
                fgets(inputName, nameMax, stdin);
                inputName[strcspn(inputName, "\n")] = '\0';

                printf("Enter Key: ");
                scanf("%d", &inputKey);
                while ((getchar()) != '\n');

                goInsert(inputName, inputKey);

                break;
            case (2):

                printf("---------------------------------------------------\n");
                printf("                       REMOVE                      \n");
                printf("---------------------------------------------------\n");

                char removeName[nameMax];
                
                printf("Enter Name: ");
                fgets(removeName, nameMax, stdin);
                removeName[strcspn(removeName, "\n")] = '\0';

                goRemove(removeName);

                break;
            case (3):

                printf("---------------------------------------------------\n");
                printf("                       SEARCH                      \n");
                printf("---------------------------------------------------\n");

                char searchName[nameMax];
                
                printf("Enter Name: ");
                fgets(searchName, nameMax, stdin);
                searchName[strcspn(searchName, "\n")] = '\0';

                goSearch(searchName);

                break;
            case (4):

                printf("---------------------------------------------------\n");
                printf("                      DISPLAY                      \n");
                printf("---------------------------------------------------\n");

                goDisplay();

                break;
            case (5):
                printf("---------------------------------------------------\n");
                printf("                        EDIT                       \n");
                printf("---------------------------------------------------\n");

                char editName[nameMax];
                
                printf("Enter Name to Edit: ");
                fgets(editName, nameMax, stdin);
                editName[strcspn(editName, "\n")] = '\0';

                goEdit(editName);

                break;
            case (6):
                printf("---------------------------------------------------\n");
                printf("                        EXIT                       \n");
                printf("---------------------------------------------------\n");
                printf("[] Thank you for using my program!\n");
                printf("[] Terminating program.\n");
                break;
        }

    } while(choice != 6);
    

}

/*
    inputName[strcspn(inputName, "\n")] = '\0';
    while ((getchar()) != '\n');
*/