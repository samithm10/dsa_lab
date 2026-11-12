#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
    int data;
    struct Node* lptr;
    struct Node* rptr;
} Node;

Node* createNode(int value) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->lptr = newNode->rptr = NULL;
    return newNode;
}

Node* initializeList() 
{
    Node* header = createNode(0);  
    header->lptr = header;
    header->rptr = header;
    return header;
}

void insertAtBeginning(Node* header, int value) 
{
    Node* newNode = createNode(value);

    newNode->rptr = header->rptr;  
    newNode->lptr = header;       

    header->rptr->lptr = newNode;  
    header->rptr = newNode; 

    header->data++;
    printf("Node %d inserted at beginning\n", value);
}

void insertAtEnd(Node* header, int value) 
{
    Node* newNode = createNode(value);

    newNode->lptr = header->lptr;   
    newNode->rptr = header;       
    header->lptr->rptr = newNode; 
    header->lptr = newNode;  

    header->data++;
    printf("Node %d inserted at end\n", value);
}

void insertAtPosition(Node* header, int value, int pos)
{
    if (pos < 1 || pos > header->data + 1)
    {
        printf("Invalid position!\n");
        return;
    }

    Node* temp = header->rptr;   
    int count = 1;

    while (count < pos)
    {
        temp = temp->rptr;      
        count++;
    }

    Node* newNode = createNode(value);

    newNode->rptr = temp;
    newNode->lptr = temp->lptr;

    temp->lptr->rptr = newNode;
    temp->lptr = newNode;

    header->data++;
    printf("Node %d inserted at position %d\n", value, pos);
}

void insertByOrder(Node* header, int value)
{
    Node* temp = header->rptr;   

    while (temp != header && temp->data < value)
        temp = temp->rptr;

    Node* newNode = createNode(value);

    newNode->rptr = temp;
    newNode->lptr = temp->lptr;

    temp->lptr->rptr = newNode;
    temp->lptr = newNode;

    header->data++;
    printf("Node %d inserted\n", value);
}

void deleteAtBeginning(Node* header)
{
    if (header->rptr == header) 
    {
        printf("List is empty — cannot delete!\n");
        return;
    }

    Node* temp = header->rptr;    

    header->rptr = temp->rptr;    
    temp->rptr->lptr = header;   

    printf("Deleted node %d from beginning\n", temp->data);
    free(temp);
    header->data--;
}

void deleteAtEnd(Node* header)
{
    if (header->rptr == header)
    {
        printf("List is empty — cannot delete!\n");
        return;
    }

    Node* temp = header->lptr;   
    temp->lptr->rptr = header;   
    header->lptr = temp->lptr;  

    printf("Deleted node %d from end\n", temp->data);
    free(temp);
    header->data--;
}

void deleteAtPosition(Node* header, int pos)
{
    if (pos < 1 || pos > header->data)
    {
        printf("Invalid position!\n");
        return;
    }
    if (header->rptr == header)
    {
        printf("List is empty — cannot delete!\n");
        return;
    }

    Node* temp = header->rptr;   
    int count = 1;

    while (count < pos)        
    {
        temp = temp->rptr;
        count++;
    }

    temp->lptr->rptr = temp->rptr;  
    temp->rptr->lptr = temp->lptr; 

    printf("Deleted node %d from position %d\n", temp->data, pos);
    free(temp);
    header->data--;
}

void deleteByKey(Node* header, int key)
{
    if (header->rptr == header)
    {
        printf("List is empty — cannot delete!\n");
        return;
    }
    Node* temp = header->rptr;   
    while (temp != header && temp->data != key)
        temp = temp->rptr;

    if (temp == header)
    {
        printf("Key %d not found in the list!\n", key);
        return;
    }

    temp->lptr->rptr = temp->rptr;   
    temp->rptr->lptr = temp->lptr;   

    printf("Deleted node with key %d\n", temp->data);
    free(temp);
    header->data--;
}

void reverse(Node* header)
{
    if (header->rptr == header)   
    {
        printf("List is empty — cannot reverse!\n");
        return;
    }
    Node* temp = header;          
    do
    {
        Node* swap = temp->rptr;
        temp->rptr = temp->lptr;
        temp->lptr = swap;
        temp = swap;         
    }
    while (temp != header);
    printf("List reversed successfully\n");
}

void display(Node* header) 
{
    if (header->rptr == header) 
    {
        printf("List is empty\n");
        return;
    }

    Node* temp = header->rptr;
    printf("CDLL: ");
    while (temp != header) 
    {
        printf("%d <-> ", temp->data);
        temp = temp->rptr;
    }
    printf("(back to header)\n");
}

void copyList(Node* header)
{
    if (header->rptr == header)
    {
        printf("Original list is empty — nothing to copy!\n");
        return;
    }

    Node* newHeader = createNode(0);
    newHeader->rptr = newHeader->lptr = newHeader;

    Node* curr = header->rptr;
    while (curr != header)
    {
        Node* newNode = createNode(curr->data);
        newNode->lptr = newHeader->lptr;
        newNode->rptr = newHeader;

        newHeader->lptr->rptr = newNode;
        newHeader->lptr = newNode;

        curr = curr->rptr;
    }
    display(newHeader);
}

void searchByKey(Node *header, int key) 
{
    Node *temp = header->rptr;

    while (temp != header) 
    {
        if (temp->data == key) 
        {
            printf("Value %d is PRESENT in the list.\n", key);
            return;
        }
        temp = temp->rptr;
    }
    printf("Value %d is NOT PRESENT in the list.\n", key);
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
        printf("9. Search By Key\n");
        printf("10. Reverse Operation\n");
        printf("11. Copy Operation\n");
        printf("12. Display\n");
        printf("13. Exit\n");
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
                deleteAtBeginning(header);
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
                printf("Enter key: ");
                scanf("%d", &key);
                searchByKey(header, key);
                break;
            case 10:
                reverse(header);
                break;  
            case 11:
                copyList(header);
                break;
            case 12:
                display(header);
                break;
            case 13:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}