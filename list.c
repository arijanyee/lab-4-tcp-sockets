#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t *list_alloc(void) {
    list_t *list = malloc(sizeof(list_t));
    if (list == NULL) return NULL;
    list->head = NULL;
    return list;
}

void list_free(list_t *list) {
    if (list == NULL) return;

    node_t *current = list->head;
    while (current != NULL) {
        node_t *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int list_length(list_t *list) {
    int length = 0;
    if (list == NULL) return 0;

    node_t *current = list->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

void list_add_to_front(list_t *list, int value) {
    if (list == NULL) return;

    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) return;

    node->value = value;
    node->next = list->head;
    list->head = node;
}

void list_add_to_back(list_t *list, int value) {
    if (list == NULL) return;

    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) return;

    node->value = value;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
        return;
    }

    node_t *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
}

void list_add_at_index(list_t *list, int index, int value) {
    if (list == NULL || index < 0 || index > list_length(list)) return;

    if (index == 0) {
        list_add_to_front(list, value);
        return;
    }

    node_t *current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }

    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) return;

    node->value = value;
    node->next = current->next;
    current->next = node;
}

int list_remove_from_front(list_t *list) {
    if (list == NULL || list->head == NULL) return -1;

    node_t *old = list->head;
    int value = old->value;
    list->head = old->next;
    free(old);
    return value;
}

int list_remove_from_back(list_t *list) {
    if (list == NULL || list->head == NULL) return -1;

    if (list->head->next == NULL) {
        return list_remove_from_front(list);
    }

    node_t *current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    node_t *old = current->next;
    int value = old->value;
    current->next = NULL;
    free(old);
    return value;
}

int list_remove_at_index(list_t *list, int index) {
    if (list == NULL || index < 0 || index >= list_length(list)) return -1;

    if (index == 0) {
        return list_remove_from_front(list);
    }

    node_t *current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }

    node_t *old = current->next;
    int value = old->value;
    current->next = old->next;
    free(old);
    return value;
}

int list_get_elem_at(list_t *list, int index) {
    if (list == NULL || index < 0) return -1;

    node_t *current = list->head;
    for (int i = 0; current != NULL; i++) {
        if (i == index) return current->value;
        current = current->next;
    }
    return -1;
}

char *listToString(list_t *list) {
    static char buffer[1024];
    buffer[0] = '\0';

    if (list == NULL) return buffer;

    node_t *current = list->head;
    while (current != NULL) {
        char item[32];
        snprintf(item, sizeof(item), "%d", current->value);

        if (buffer[0] != '\0') {
            if (strlen(buffer) + 2 >= sizeof(buffer)) break;
            strcat(buffer, " ");
        }

        if (strlen(buffer) + strlen(item) >= sizeof(buffer)) break;
        strcat(buffer, item);
        current = current->next;
    }

    return buffer;
}