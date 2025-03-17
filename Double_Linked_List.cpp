#include <stdio.h>
#include <stdlib.h>

struct node {
    int angka;
    struct node *next;
    struct node *prev;
};

struct node *createnode(int angka) {
    struct node *newnode = (struct node*) malloc(sizeof(struct node));
    newnode->angka = angka;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

struct node *head = NULL;
struct node *tail = NULL;

void push_front(int angka) {
    if (head == NULL) {
        head = tail = createnode(angka);
    } else {
        struct node *temp = createnode(angka);
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
}

void push_back(int angka) {
    if (head == NULL) {
        head = tail = createnode(angka);
    } else {
        struct node *temp = createnode(angka);
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

void push_mid(int angka) {
    if (head == NULL) {
        head = tail = createnode(angka);
    } else if (head == tail) {
        if (head->angka > angka) {
            push_front(angka);
        } else {
            push_back(angka);
        }
    } else if (head->angka > angka) {
        push_front(angka);
    } else if (tail->angka < angka) {
        push_back(angka);
    } else {
        struct node *temp = createnode(angka);
        struct node *start = head;
        while (start != NULL && start->next->angka < angka) {
            start = start->next;
        }
        struct node *a = start;
        struct node *b = start->next;
        a->next = temp;
        b->prev = temp;
        temp->prev = a;
        temp->next = b;
    }
}

void del_front() {
    if (head == NULL) {
        printf("List kosong\n");
    } else if (head == tail) {
        free(head);
        head = NULL;
        tail = NULL;
    } else {
        struct node *temp = head->next;
        temp->prev = NULL;
        free(head);
        head = temp;
    }
}

void del_back() {
    if (head == NULL) {
        printf("List kosong\n");
    } else if (head == tail) {
        free(head);
        head = NULL;
        tail = NULL;
    } else {
        struct node *temp = tail->prev;
        temp->next = NULL;
        free(tail);
        tail = temp;
    }
}

void del_mid(int angka) {
    if (head == NULL) {
        printf("List kosong\n");
    } else if (head->angka == angka) {
        del_front();
    } else if (tail->angka == angka) {
        del_back();
    } else {
        struct node *start = head;
        while (start != NULL && start->angka != angka) {
            start = start->next;
        }
        if (start == NULL) {
            printf("Tidak ditemukan\n");
            return;
        }
        struct node *a = start->prev;
        struct node *b = start->next;
        free(start);
        a->next = b;
        b->prev = a;
    }
}

void print() {
    struct node *start = head;
    while (start != NULL) {
        printf("%d ", start->angka);
        start = start->next;
    }
    printf("\n");
}

int main() {
    push_front(20);
    push_front(12);
    push_back(3);
    print();
    return 0;
}
