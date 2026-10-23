#include <stdio.h>
#include <stdlib.h>

int count = 0;   
typedef struct Node 
{
    int data;
    struct Node *next;
} Node;

Node* createNode(int value) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

Node* createLinkedList() 
{
    Node *head = NULL, *temp = NULL;
    int value, choice;
    while (1) 
    {
        printf("Enter value to insert: ");
        scanf("%d", &value);
        Node* newNode = createNode(value);
        if (head == NULL)
            head =temp= newNode;
        else
            temp->next = newNode;
        temp = newNode;
        count++;
        printf("Add another node? (1-Yes / 0-No): ");
        scanf("%d", &choice);
        if (choice == 0)
            break;
    }
    printf("Linked list created successfully with %d nodes.\n", count);
    return head;
}

Node* insertAtBeginning(Node* head, int value)
{
    if (head == NULL)
        printf("List is empty. Inserting first node at beginning.\n");
    Node* newNode = createNode(value);
    newNode->next = head;
    head = newNode;
    count++;
    printf("Element %d inserted at beginning.\n", value);
    return head;
}

Node* insertAtEnd(Node* head, int value) 
{
    Node* newNode = createNode(value);
    if (head == NULL)
    {
        head = newNode;
        count++;
        printf("Element %d inserted at end.\n", value);
        return head;
    }
    Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    count++;
    printf("Element %d inserted at end.\n", value);
    return head;
}

Node* insertAtPosition(Node* head, int pos, int value) 
{
    if (pos < 1 || pos > count + 1 || (head == NULL && pos != 1)) 
    {
        printf("Invalid position! Valid positions: 1 to %d\n", count + 1);
        return head;
    }
    Node* newNode = createNode(value);
    if (pos == 1)
    {
        newNode->next = head;
        head = newNode;
        count++;
        printf("Element %d inserted at position %d.\n", value, pos);
        return head;
    }
    Node* temp = head;
    for (int i = 1; i < pos - 1; i++)
        temp = temp->next;
    newNode->next = temp->next;
    temp->next = newNode;
    count++;
    printf("Element %d inserted at position %d.\n", value, pos);
    return head;
}

struct Node* insertByOrder(struct Node* head, int value)
{
    struct Node* newNode = createNode(value);

    // Case 1: List empty or insert at beginning
    if (head == NULL || value < head->data)
    {
        newNode->next = head;
        count++;  
        return newNode;   
    }

    // Case 2: Insert in middle or end
    struct Node *curr = head;
    while (curr->next != NULL && curr->next->data < value)
        curr = curr->next;

    newNode->next = curr->next;
    curr->next = newNode;
    count++;
    return head;  
}

Node* deleteBeginning(Node* head) 
{
    if (head == NULL)
    {
        printf("List is empty. Deletion not possible.\n");
        return head;
    }
    Node* temp = head;
    printf("Element %d deleted from beginning.\n", temp->data);
    head = head->next;
    free(temp);
    count--;
    return head;
}

Node* deleteEnd(Node* head) 
{
    if (head == NULL)
    {
        printf("List is empty. Deletion not possible.\n");
        return head;
    }
    if (head->next == NULL)
    {
        printf("Element %d deleted from end.\n", head->data);
        free(head);
        count--;
        return NULL;
    }
    Node* temp = head;
    while (temp->next->next != NULL)
        temp = temp->next;
    printf("Element %d deleted from end.\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
    count--;
    return head;
}

Node* deleteAtPosition(Node* head, int pos)
{
    if (head == NULL)
    {
        printf("List is empty. Deletion not possible.\n");
        return head;
    }
    if (pos < 1 || pos > count)
    {
        printf("Invalid position! Valid positions: 1 to %d\n", count);
        return head;
    }
    if (pos == 1)
    {
        Node* temp = head;
        printf("Element %d deleted from position 1.\n", head->data);
        head = head->next;
        free(temp);
        count--;
        return head;
    }
    Node* temp = head;
    for (int i = 1; i < pos - 1; i++)
        temp = temp->next;
    Node* toDelete = temp->next;
    printf("Element %d deleted from position %d.\n", toDelete->data, pos);
    temp->next = toDelete->next;
    free(toDelete);
    count--;
    return head;
}

Node* deleteByKey(struct Node* head, int key)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return head;
    }
    struct Node *temp = head, *prev = NULL;
    // Case 1: key is in the first node
    if (temp != NULL && temp->data == key)
    {
        head = temp->next;
        free(temp);
        count--;
        return head;
    }
    // Case 2: search rest of list
    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Key %d not found.\n", key);
        return head;
    }
    prev->next = temp->next;
    printf("Key %d deleted from the list.\n", key);
    free(temp);
    count--;
    return head;
}

Node* searchByKey(struct Node* head, int key)
{
    struct Node* temp = head;

    if (head == NULL)
    {
        printf("The list is empty. Cannot search.\n");
        return NULL;
    }
    while (temp != NULL)
    {
        if (temp->data == key)
        {
            printf("Key %d found in the list.\n", key);
            return temp;      
        }
        temp = temp->next;
    }
    printf("Key %d NOT found in the list.\n", key);
    return NULL;             
}

Node* reverseList(struct Node* head)
{
    if (head == NULL)
    {
        printf("List is empty. Cannot reverse.\n");
        return head;
    }
    struct Node *FP = head, *LN = NULL, *temp;
    while (FP != NULL)
    {
        temp= FP;
        FP=FP->next;
        temp->next=LN;
        LN=temp;
    }
    printf("List has been reversed successfully.\n");
    return LN;  
}

Node* copyList(Node* head)
{
    if(head==NULL)
        return NULL;

    Node* newHead=createNode(head->data);
    Node* newCurrent=newHead;
    Node* current=head->next;
    
    while(current!=NULL)
    {
        newCurrent->next=createNode(current->data);
        newCurrent=newCurrent->next;
        current=current->next;
    }
    if (newHead != head && newHead->next != head->next)
        printf("List has been copied successfully.\n");
    else
        printf("Copy Failed! Both lists share the same nodes.\n");
    return newHead;
}

void printList(Node* head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    Node* temp = head;
    printf("Current list (%d nodes): ", count);
    while (temp!= NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    Node* head = NULL;
    int choice, value, pos,key;
    while (1)
    {
        printf("\n1. Create Linked List\n2. Insert at Beginning\n3. Insert at End\n");
        printf("4. Insert at Position\n5. Insert By Order\n6. Delete from Beginning\n7. Delete from End\n");
        printf("8. Delete from Position\n9. Delete By Key\n10. Search by Key\n");
        printf("11. Reverse Operation\n12. Copy Operation\n13. PrintList\n14. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1: head = createLinkedList();
                    break;
            case 2: printf("Enter value: ");
                    scanf("%d", &value);
                    head = insertAtBeginning(head, value);
                    break;
            case 3: printf("Enter value: ");
                    scanf("%d", &value);
                    head = insertAtEnd(head, value);
                    break;
            case 4: printf("Enter position: ");
                    scanf("%d", &pos);
                    printf("Enter value: ");
                    scanf("%d", &value);
                    head = insertAtPosition(head, pos, value);
                    break;
            case 5: printf("Enter value: ");
                    scanf("%d", &value);
                    head = insertByOrder(head,value);
                    break;
            case 6: head = deleteBeginning(head);
                    break;
            case 7: head = deleteEnd(head);
                    break;
            case 8: printf("Enter position: ");
                    scanf("%d", &pos);
                    head = deleteAtPosition(head, pos);
                    break;
            case 9: printf("Enter key: ");
                    scanf("%d", &key);
                    head = deleteByKey(head, key);
                    break;
            case 10: printf("Enter key to search: ");
                    scanf("%d", &key);
                    searchByKey(head, key);
                    break;
            case 11: head=reverseList(head);
                    break;
            case 12: head=copyList(head);
                    break;
            case 13: printList(head);
                    break;
            case 14: printf("Exiting...\n");
                    exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}