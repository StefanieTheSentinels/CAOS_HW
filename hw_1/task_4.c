#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

int main(void) {
    struct Node *head = NULL;
    struct Node *tail = NULL;
    int x;

    while (scanf("%d", &x) == 1 && x != 0) {
        struct Node *node = malloc(sizeof(struct Node));
        node->value = x;
        node->next = NULL;

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    struct Node *prev = NULL;
    struct Node *cur = head;

    while (cur != NULL) {
        struct Node *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    head = prev;

    cur = head;
    while (cur != NULL) {
        printf("%d ", cur->value);
        cur = cur->next;
    }

    cur = head;
    while (cur != NULL) {
        struct Node *next = cur->next;
        free(cur);
        cur = next;
    }

    return 0;
}