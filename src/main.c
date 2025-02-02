#include <stdio.h>
#include <stdlib.h>
#include "../include/box.h"
#include "../include/wagon.h"
#include "../include/train.h"
#include "../include/file_ops.h"

static void display_menu() {
    printf("\n=== Train Loading Management ===\n");
    printf("1) Load a box into train (default wagon selection)\n");
    printf("2) Load a box into specific wagon\n");
    printf("3) Display train\n");
    printf("4) Save train to file\n");
    printf("5) Load train from file\n");
    printf("6) Unload from specific wagon\n");
    printf("7) Unload boxes from tail\n");
    printf("8) Empty Train\n");
    printf("9) Exit\n");
    printf("Choice: ");
}


int main(void) {
    Train* myTrain = create_train("T123");
    float default_wagon_capacity = 1000.0f;
    int box_id_counter = 1;
    char filename[100];

    while (1) {
        display_menu();
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                printf("Enter box size (1=SMALL, 2=MEDIUM, 3=LARGE): ");
                int s;
                if (scanf("%d", &s) != 1 || (s < 1 || s > 3)) {
                    printf("Invalid input.\n");
                    while (getchar() != '\n');
                    continue;
                }

                BoxSize size = (s == 1 ? SMALL : (s == 2 ? MEDIUM : LARGE));
                Box* b = create_box(box_id_counter++, size);
                if (!b) {
                    printf("Box creation failed.\n");
                    continue;
                }

                if (!load_box_into_train(myTrain, b, default_wagon_capacity)) {
                    printf("[WARN] Could not load box.\n");
                }
                break;
            }

            case 2: {
                printf("Enter wagon ID to load box into: ");
                int wagon_id;
                if (scanf("%d", &wagon_id) != 1 || wagon_id <= 0) {
                    printf("Invalid wagon ID.\n");
                    while (getchar() != '\n');
                    continue;
                }

                printf("Enter box size (1=SMALL, 2=MEDIUM, 3=LARGE): ");
                int s;
                if (scanf("%d", &s) != 1 || (s < 1 || s > 3)) {
                    printf("Invalid input.\n");
                    while (getchar() != '\n');
                    continue;
                }

                BoxSize size = (s == 1 ? SMALL : (s == 2 ? MEDIUM : LARGE));
                Box* b = create_box(box_id_counter++, size);
                if (!b) {
                    printf("Box creation failed.\n");
                    continue;
                }

                if (!load_box_into_specific_wagon(myTrain, b, wagon_id)) {
                    printf("[WARN] Could not load box into wagon %d.\n", wagon_id);
                }
                break;
            }

            case 3:
                display_train(myTrain);
                break;

            case 4:
                printf("Enter filename to save: ");
                scanf("%s", filename);
                save_train_to_file(myTrain, filename);
                break;

            case 5:
                printf("Enter filename to load: ");
                scanf("%s", filename);
                load_train_from_file(myTrain, filename);
                break;

            case 6: {
                printf("Enter wagon ID to unload from: ");
                int wID;
                if (scanf("%d", &wID) != 1) {
                    printf("Invalid input.\n");
                    while (getchar() != '\n');
                    continue;
                }

                printf("How many boxes to unload: ");
                int qty;
                if (scanf("%d", &qty) != 1 || qty <= 0) {
                    printf("Invalid input.\n");
                    while (getchar() != '\n');
                    continue;
                }

                printf("Enter box size (1=SMALL, 2=MEDIUM, 3=LARGE): ");
                int s2;
                if (scanf("%d", &s2) != 1 || (s2 < 1 || s2 > 3)) {
                    printf("Invalid input.\n");
                    while (getchar() != '\n');
                    continue;
                }

                BoxSize unloadSize = (s2 == 1 ? SMALL : (s2 == 2 ? MEDIUM : LARGE));
                int unloaded = unload_boxes_from_wagon(myTrain, wID, qty, unloadSize);
                printf("Unloaded %d boxes from wagon %d.\n", unloaded, wID);
                break;
            }

            case 7: {
                printf("How many boxes to unload: ");
                int qty;
                if (scanf("%d", &qty) != 1 || qty <= 0) {
                    printf("Invalid input.\n");
                    while (getchar() != '\n');
                    continue;
                }

                printf("Enter box size (1=SMALL, 2=MEDIUM, 3=LARGE): ");
                int s3;
                if (scanf("%d", &s3) != 1 || (s3 < 1 || s3 > 3)) {
                    printf("Invalid input.\n");
                    while (getchar() != '\n');
                    continue;
                }

                BoxSize unloadSize = (s3 == 1 ? SMALL : (s3 == 2 ? MEDIUM : LARGE));
                int unloaded = unload_boxes_from_tail(myTrain, qty, unloadSize);
                printf("Unloaded %d boxes starting from the tail.\n", unloaded);
                break;
            }

            case 8:
                printf("Resetting Train...\n");
                reset_train(myTrain);
                break;

            case 9: {
                printf("Are you sure you want to exit? (y/n): ");
                char confirm;
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y') {
                    printf("Exiting...\n");
                    free_train(myTrain);
                    return 0;
                } else {
                    printf("Exit canceled.\n");
                }
                break;
            }

            default:
                printf("Invalid choice.\n");
        }
    }

    free_train(myTrain);
    return 0;
}
