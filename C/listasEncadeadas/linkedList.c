#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

void InsertNodeAtBeginning(struct Node **head, int data) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

  newNode->data = data;
  newNode->next = *head;
  *head = newNode;
};

void RemoveNodeAtBeginning(struct Node **head) {
  struct Node* temp = *head;
  *head = (*head)->next;
  free(temp);
};

void PrintList(struct Node *head) {
  while (head != NULL) {
    printf("%d ", head->data);
    head = head->next;
  }
};

int main() {
  struct Node* head = NULL;
  InsertNodeAtBeginning(&head, 10);
  InsertNodeAtBeginning(&head, 20);
  InsertNodeAtBeginning(&head, 30);
  printf("List: ");
  PrintList(head);
  RemoveNodeAtBeginning(&head);
  printf("\nList after removal: ");
  PrintList(head);

  return 0;
};