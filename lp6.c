#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* initializeList() 
{
    Node* header = createNode(0);   
    header->next = header;         
    return header;
}

void insertAtBeginning(Node* header, int data) 
{
    Node* newNode = createNode(data);

    newNode->next = header->next;
    header->next = newNode;

    header->data++; 
    printf("Inserted %d at beginning.\n", data);
}

void insertAtEnd(Node* header, int data) 
{
    Node* newNode = createNode(data);
    Node* temp = header;

    while (temp->next != header)
        temp = temp->next;

    temp->next = newNode;
    newNode->next = header;

    header->data++;  
    printf("Inserted %d at end.\n", data);
}

void insertAtPosition(Node* header, int data, int pos) 
{
    int count = header->data;

    if (pos < 1 || pos > count + 1) 
    {
        printf("Invalid position! Valid range is 1 to %d\n", count + 1);
        return;
    }

    Node* newNode = createNode(data);
    Node* temp = header;
    int i = 1;

    while (i < pos) 
    {
        temp = temp->next;
        i++;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    header->data++; 
    printf("Inserted %d at position %d.\n", data, pos);
}

void insertByOrder(Node *header, int value)
{
    Node *newNode = createNode(value);
    Node *curr = header;

    while (curr->next != header && curr->next->data < value)
        curr = curr->next;

    newNode->next = curr->next;
    curr->next = newNode;

    header->data++;
    printf("Inserted %d in sorted order.\n", value);
}


void deleteBeginning(Node* header)
{
    if (header->next == header) 
    {
        printf("List is empty.\n");
        return;
    }

    Node* first = header->next;      
    header->next = first->next;      

    printf("Deleted: %d\n", first->data);
    header->data--;
    free(first);
}

void deleteAtEnd(Node* header) 
{
    if (header->next == header)
    {
        printf("List is empty.\n");
        return;
    }

    Node *prev = header;
    Node *curr = header->next;

    while (curr->next != header)
    {
        prev = curr;
        curr = curr->next;
    }

    prev->next = header;   
    printf("Deleted: %d\n", curr->data);
    header->data--;
    free(curr);
}

void deleteAtPosition(Node *header, int pos)
{
    if (header->next == header)
    {
        printf("List is empty.\n");
        return;
    }

    if (pos < 1 || pos > header->data)
    {
        printf("Invalid position!\n");
        return;
    }

    Node *prev = header;
    Node *curr = header->next;
    int count = 1;

    while (count < pos)
    {
        prev = curr;
        curr = curr->next;
        count++;
    }

    prev->next = curr->next;
    printf("Deleted: %d\n", curr->data);
    header->data--;
    free(curr);
}

void deleteByKey(Node *header, int key)
{
    if (header->next == header)
    {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    Node *prev = header;
    Node *curr = header->next;
    while (curr != header)
    {
        if (curr->data == key)
        {
            prev->next = curr->next;
            free(curr);
            printf("Node with value %d deleted.\n", key);
            header->data--;
            return;
        }

        prev = curr;
        curr = curr->next;
    }
    printf("Key %d not found in the list.\n", key);
}

void reverse(Node *header)
{
    if (header->next == header)  
    {
        printf("List is empty. Cannot reverse.\n");
        return;
    }

    Node *prev = header;
    Node *curr = header->next;
    Node *next;

    Node *first = curr;   

    while (curr != header)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    header->next = prev;
    first->next = header;
    printf("List reversed successfully.\n");
}

Node* copyList(Node *header)
{
    Node *newHeader = (Node*)malloc(sizeof(Node));
    newHeader->data = 0;
    newHeader->next = newHeader;

    if (header->next == header)
    {
        printf("Original list is empty. Copied an empty list.\n");
        return newHeader;
    }

    Node *curr = header->next; 
    Node *newTail = newHeader; 

    while (curr != header)
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = curr->data;
        newTail->next = newNode;
        newTail = newNode;
        curr = curr->next;
    }
    newTail->next = newHeader;
    printf("List copied successfully.\n");
    return newHeader;
}

void display(Node* header) 
{
    if (header->next == header) 
    {
        printf("List is empty.\n");
        return;
    }

    Node* temp = header->next;

    printf("\nCSLL (%d nodes): ", header->data);

    while (temp != header) 
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() 
{
    Node* header = initializeList();
    int choice, data, pos,key;

    while (1) 
    {
        printf("\n----- MENU -----\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Insert by Order\n");
        printf("5. Delete at Beginning\n");
        printf("6. Delete at End\n");
        printf("7. Delete at Position\n");
        printf("8. Delete By Key\n");
        printf("9. Reverse Operation\n");
        printf("10. Copy Operation\n");
        printf("11. Display\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                insertAtBeginning(header, data);
                break;
            case 2:
                printf("Enter data: ");
                scanf("%d", &data);
                insertAtEnd(header, data);
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &pos);
                insertAtPosition(header, data, pos);
                break;
            case 4:
                printf("Enter data: ");
                scanf("%d", &data);
                insertByOrder(header, data);
                break;
            case 5:
                deleteBeginning(header);
                break;
            case 6:
                deleteAtEnd(header);
                break;
            case 7:
                printf("Enter position: ");
                scanf("%d", &pos);
                deleteAtPosition(header, pos);
                break;
            case 8:
                printf("Enter key: ");
                scanf("%d", &key);
                deleteByKey(header, key);
                break;
            case 9:
                reverse(header);
                break;  
            case 10:
                copyList(header);
                break;
            case 11:
                display(header);
                break;
            case 12:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
