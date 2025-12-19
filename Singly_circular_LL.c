#include <stdio.h>
#include <stdlib.h>

/* --------- Structure of Node ---------
   data  : stores value
   next  : stores address of next node
-------------------------------------- */
struct node {
    int data;
    struct node *next;
};

/* tail pointer always points to LAST node */
struct node *tail = NULL;

/* --------- INSERT AT BEGINNING --------- */
void insert_begin(int value) {

    // create a new node
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = value;

    // if list is empty
    if(tail == NULL) {
        tail = newNode;          // tail points to new node
        tail->next = tail;       // node points to itself (circular)
    }
    else {
        newNode->next = tail->next;  // new node points to first node
        tail->next = newNode;        // last node points to new node
    }

    printf("%d inserted at beginning\n", value);
}

/* --------- INSERT AT END --------- */
void insert_end(int value) {

    // create a new node
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = value;

    // if list is empty
    if(tail == NULL) {
        tail = newNode;          // tail points to new node
        tail->next = tail;       // circular link
    }
    else {
        newNode->next = tail->next;  // new node points to first node
        tail->next = newNode;        // old last points to new node
        tail = newNode;              // update tail to new last node
    }

    printf("%d inserted at end\n", value);
}

/* --------- DELETE FROM BEGINNING --------- */
void delete_begin() {

    // if list is empty
    if(tail == NULL) {
        printf("List is empty\n");
        return;
    }

    // only one node in list
    if(tail->next == tail) {
        printf("%d deleted\n", tail->data);
        free(tail);
        tail = NULL;
    }
    else {
        struct node *temp = tail->next;   // temp points to first node
        tail->next = temp->next;          // last node skips first node
        printf("%d deleted\n", temp->data);
        free(temp);                        // delete first node
    }
}

/* --------- DELETE FROM END --------- */
void delete_end() {

    // if list is empty
    if(tail == NULL) {
        printf("List is empty\n");
        return;
    }

    // only one node
    if(tail->next == tail) {
        printf("%d deleted\n", tail->data);
        free(tail);
        tail = NULL;
    }
    else {
        struct node *temp = tail->next;  // start from first node

        // move temp to second last node
        while(temp->next != tail) {
            temp = temp->next;
        }

        temp->next = tail->next;  // second last points to first
        printf("%d deleted\n", tail->data);
        free(tail);               // delete last node
        tail = temp;              // update tail
    }
}

/* --------- DISPLAY LIST --------- */
void display() {

    // if list is empty
    if(tail == NULL) {
        printf("List is empty\n");
        return;
    }

    struct node *temp = tail->next;  // start from first node

    printf("Singly Circular Linked List: ");

    // loop until we come back to first node
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while(temp != tail->next);

    printf("(back to start)\n");
}

/* --------- MAIN FUNCTION --------- */
int main() {

    int choice, value;

    do {
        printf("\n--- Singly Circular Linked List ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Delete from Beginning\n");
        printf("4. Delete from End\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insert_begin(value);
                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                insert_end(value);
                break;

            case 3:
                delete_begin();
                break;

            case 4:
                delete_end();
                break;

            case 5:
                display();
                break;

            case 6:
                printf("Exiting program\n");
                break;

            default:
                printf("Invalid choice\n");
        }
    } while(choice != 6);

    return 0;
}