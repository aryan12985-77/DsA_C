#include <stdio.h>
#include <stdlib.h>

// Structure of Node (contains data, next & prev pointer)
struct node {
    int data;
    struct node *next;
    struct node *prev;
};

// Tail pointer helps to manage circular property
struct node *tail = NULL;

// ====================== INSERT AT END ==========================
void insert_end(int value) {
    struct node *new1 = (struct node*)malloc(sizeof(struct node));  // allocate memory
    new1->data = value;

    if (tail == NULL) {  // If list is empty
        tail = new1;
        tail->next = tail;  // First node points to itself (circular forward)
        tail->prev = tail;  // First node's prev also points to itself (circular backward)
    } else {
        new1->next = tail->next;  // new node points to first node
        new1->prev = tail;        // previous link to old last node
        tail->next->prev = new1;  // first node's prev now points to new node
        tail->next = new1;        // old last node points to new node
        tail = new1;              // update tail (new node becomes last)
    }
    printf("%d inserted at end.\n", value);
}

// ====================== INSERT AT BEGINNING =====================
void insert_begin(int value) {
    struct node *new1 = (struct node*)malloc(sizeof(struct node));
    new1->data = value;

    if (tail == NULL) {  // if empty list, same as insert end
        tail = new1;
        tail->next = tail;
        tail->prev = tail;
    } else {
        new1->next = tail->next;   // new node next -> first
        new1->prev = tail;         // new node prev -> last
        tail->next->prev = new1;   // old first prev -> new node
        tail->next = new1;         // last next -> new node (making it first)
    }
    printf("%d inserted at beginning.\n", value);
}

// ====================== INSERT AT POSITION ======================
void insert_pos(int value, int pos) {
    if (tail == NULL && pos != 1) {
        printf("List empty! Only position 1 allowed.\n");
        return;
    }

    if (pos == 1) {  // Inserting at beginning
        insert_begin(value);
        return;
    }

    struct node *new1 = (struct node*)malloc(sizeof(struct node));
    new1->data = value;

    struct node *temp = tail->next; // Start from first node
    int i;
    for (i = 1; i < pos - 1 && temp != tail; i++) {
        temp = temp->next;
    }

    new1->next = temp->next;        // new node next points to next of temp
    new1->prev = temp;              // new node prev points to temp
    temp->next->prev = new1;        // next node's prev points to new
    temp->next = new1;              // temp next points to new node

    if (temp == tail)  // If inserted after last, update tail
        tail = new1;

    printf("%d inserted at position %d.\n", value, pos);
}

// ====================== DELETE FIRST NODE =======================
void delete_begin() {
    if (tail == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct node *temp = tail->next;  // temp = first node

    if (tail->next == tail) {  // If only one node exists
        printf("Deleted: %d\n", temp->data);
        free(temp);
        tail = NULL;  // List becomes empty
    } else {
        tail->next = temp->next;           // tail next skips first node
        temp->next->prev = tail;           // new first prev -> tail
        printf("Deleted: %d\n", temp->data);
        free(temp);
    }
}

// ====================== DELETE LAST NODE ========================
void delete_end() {
    if (tail == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct node *temp = tail;

    if (tail->next == tail) {  // only one node
        printf("Deleted: %d\n", tail->data);
        free(tail);
        tail = NULL;
    } else {
        tail->prev->next = tail->next;  // second last next = first
        tail->next->prev = tail->prev;  // first prev = second last
        tail = tail->prev;              // update tail
        printf("Deleted: %d\n", temp->data);
        free(temp);
    }
}

// ====================== DELETE POSITION =========================
void delete_pos(int pos) {
    if (tail == NULL) {
        printf("List is empty!\n");
        return;
    }

    if (pos == 1) {  // delete first
        delete_begin();
        return;
    }

    struct node *temp = tail->next;
    int i;
    for (i = 1; i < pos && temp != tail; i++) {
        temp = temp->next;
    }

    if (i != pos) {
        printf("Position out of range!\n");
        return;
    }

    temp->prev->next = temp->next;   // unlink node from both sides
    temp->next->prev = temp->prev;

    if (temp == tail)  // if last node deleted, update tail
        tail = temp->prev;

    printf("Deleted: %d\n", temp->data);
    free(temp);
}

// ====================== DISPLAY FORWARD =========================
void display_forward() {
    if (tail == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct node *temp = tail->next; // first node

    printf("Forward: ");
    do {
        printf("%d <=> ", temp->data);
        temp = temp->next;
    } while (temp != tail->next);

    printf("(back to start)\n");
}

// ====================== DISPLAY BACKWARD ========================
void display_backward() {
    if (tail == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct node *temp = tail; // start from last

    printf("Backward: ");
    do {
        printf("%d <=> ", temp->data);
        temp = temp->prev;
    } while (temp != tail);

    printf("(back to end)\n");
}

// =============================== MAIN ===========================
int main() {
    int choice, value, pos;

    do {
        printf("\n=== Doubly Circular Linked List Menu ===\n");
        printf("1. Insert End\n2. Insert Beginning\n3. Insert Position\n");
        printf("4. Delete Beginning\n5. Delete End\n6. Delete Position\n");
        printf("7. Display Forward\n8. Display Backward\n9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Enter value: "); scanf("%d",&value); insert_end(value); break;
            case 2: printf("Enter value: "); scanf("%d",&value); insert_begin(value); break;
            case 3: printf("Enter value: "); scanf("%d",&value);
                    printf("Enter position: "); scanf("%d",&pos);
                    insert_pos(value,pos); break;
            case 4: delete_begin(); break;
            case 5: delete_end(); break;
            case 6: printf("Enter position: "); scanf("%d",&pos); delete_pos(pos); break;
            case 7: display_forward(); break;
            case 8: display_backward(); break;
            case 9: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 9);

    return 0;
}

