#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 50

#define MAX_LIST_SIZE 10

typedef struct {
  char data[MAX_LIST_SIZE][MAX_STR_LEN];
  int count;
} StaticList;

void initializeStaticList(StaticList *list);
void addStaticElement(StaticList *list, const char *text);
void removeStaticElement(StaticList *list, const char *text);
void searchStaticElement(StaticList *list, const char *text);
void printStaticList(StaticList *list);

typedef struct {
  char* data;
  struct Node* next;
} Node;

typedef Node* DynamicList;

void initializeDynamicList(DynamicList *list);
void addDynamicElement(DynamicList *list, const char *text);
void removeDynamicElement(DynamicList *list, const char *text);
void printDynamicList(DynamicList *list);
void freeDynamicList(DynamicList *list);

void staticListMenu();
void dynamicListMenu();

int main() {
  int option;
  do {
    printf("1 - Static List\n");
    printf("2 - Dynamic List\n");
    printf("0 - Exit\n");
    scanf("%d", &option);

    switch (option) {
      case 1:
        staticListMenu();
        break;
      case 2:
        dynamicListMenu();
        break;
      case 0:
        break;
      default:
        printf("Invalid option\n");
        break;
    }
  } while (option != 0);
  
  return 0;
};

// static list
void initializeStaticList(StaticList *list) {
  list->count = 0;
}

void addStaticElement(StaticList *list, const char *text) {
  if (list->count >= MAX_LIST_SIZE) {
    printf("List is full\n");
    return;
  }

  strcpy(list->data[list->count], text);
  list->count++;
  printf("Element added successfully\n");
}

void removeStaticElement(StaticList *list, const char *text) {
  int i, pos = -1;

  for (i = 0; i < list->count; i++) {
    if (strcmp(list->data[i], text) == 0) {
      pos = i;
      break;
    }
  }

  if (pos == -1) {
    printf("Element not found\n");
    return;
  }

  for (i = pos; i < list->count - 1; i++) {
    strcpy(list->data[i], list->data[i + 1]);
  }

  list->count--;
  printf("Element removed successfully\n"); 
}

void searchStaticElement(StaticList *list, const char *text) {
  int i;

  for (i = 0; i < list->count; i++) {
    if (strcmp(list->data[i], text) == 0) {
      printf("Element: %s\n", list->data[i]);
      return;
    }
  }
  printf("Element not found\n");
}

void printStaticList(StaticList *list) {
  int i;

  if (list->count == 0) {
    printf("List is empty\n");
    return;
  }

  printf("List: [");
  for (i = 0; i < list->count; i++) {
    printf("%s, ", list->data[i]);
  }
  printf("]\n");
}

// dynamic list
void initializeDynamicList(DynamicList *list) {
  *list = NULL;
}

void addDynamicElement(DynamicList *list, const char *text) {
  Node *newNode = (Node *)malloc(sizeof(Node));

  if (newNode == NULL) {
    printf("Memory allocation failed\n");
    return;
  }

  newNode->data = (char *)malloc(strlen(text) + 1);

  if (newNode->data == NULL) {
    printf("Memory allocation failed\n");
    free(newNode);
    return;
  }

  strcpy(newNode->data, text);
  newNode->next = *list;
  *list = newNode;

  printf("Element %s added successfully\n", text);
}

void removeDynamicElement(DynamicList *list, const char *text) {
  Node *current = *list;
  Node *previous = NULL;

  while (current != NULL && strcmp(current->data, text) != 0) {
    previous = current;
    current = current->next;
  }

  if (current == NULL) {
    printf("Element not found\n");
    return;
  }

  if (previous == NULL) {
    *list = current->next;
  } else {
    previous->next = current->next;
  }

  free(current->data);
  free(current);

  printf("Element %s removed successfully\n", text);
}

void printDynamicList(DynamicList *list) {
  Node *current = *list;

  if (current == NULL) {
    printf("List is empty\n");
    return;
  }

  printf("List: [");
  while (current != NULL) {
    printf("%s, ", current->data);
    current = current->next;
  }
  printf("]\n");
}

// static list menu
void staticListMenu() {
  StaticList list;
  int option;
  char text[MAX_STR_LEN];
  
  initializeStaticList(&list);
  
  do {
    printf("\n=== Static List Menu ===\n");
    printf("1 - Add element\n");
    printf("2 - Remove element\n");
    printf("3 - Search element\n");
    printf("4 - Print list\n");
    printf("0 - Back to main menu\n");
    printf("Choose an option: ");
    scanf("%d", &option);
    
    switch (option) {
      case 1:
        printf("Enter text to add: ");
        scanf("%s", text);
        addStaticElement(&list, text);
        break;
      case 2:
        printf("Enter text to remove: ");
        scanf("%s", text);
        removeStaticElement(&list, text);
        break;
      case 3:
        printf("Enter text to search: ");
        scanf("%s", text);
        searchStaticElement(&list, text);
        break;
      case 4:
        printStaticList(&list);
        break;
      case 0:
        break;
      default:
        printf("Invalid option\n");
        break;
    }
  } while (option != 0);
}

// dynamic list menu
void dynamicListMenu() {
  DynamicList list;
  int option;
  char text[MAX_STR_LEN];
  
  initializeDynamicList(&list);
  
  do {
    printf("\n=== Dynamic List Menu ===\n");
    printf("1 - Add element\n");
    printf("2 - Remove element\n");
    printf("3 - Print list\n");
    printf("0 - Back to main menu\n");
    printf("Choose an option: ");
    scanf("%d", &option);
    
    switch (option) {
      case 1:
        printf("Enter text to add: ");
        scanf("%s", text);
        addDynamicElement(&list, text);
        break;
      case 2:
        printf("Enter text to remove: ");
        scanf("%s", text);
        removeDynamicElement(&list, text);
        break;
      case 3:
        printDynamicList(&list);
        break;
      case 0:
        freeDynamicList(&list);
        break;
      default:
        printf("Invalid option\n");
        break;
    }
  } while (option != 0);
}

// free dynamic list memory
void freeDynamicList(DynamicList *list) {
  Node *current = *list;
  Node *next;
  
  while (current != NULL) {
    next = current->next;
    free(current->data);
    free(current);
    current = next;
  }
  
  *list = NULL;
}
