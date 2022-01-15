void findMax()
{
    int max = 0;
    Node *temp;
    temp = head;
    while(temp != NULL)
    {
        if(temp -> key > max)
        {
            max = temp->key;
        }
        temp = temp->next;
    }
    cout<<max;
    
}

//Question 2

void Queue::enqueue(node *newNode)
{
    node *temp = new node;
    if(head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else{
        temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next= newNode;
        tail = newNode;
    }
}

//alternate solution
void Queue::enqueue(node *newNode)
{
    if(head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else{
        tail -> next = newNode;
        tail = newNode;
    }
}

//Question 1
node * DeleteNode(node *head, int value)
{
    node *temp = new node;
    node *current = new node;
    temp = head;
    while(temp != NULL)
    {
        if(temp -> value == value)
        {
            if(temp ->prev == NULL)
            {
                current = temp->next;
                temp->next->prev = NULL;
                delete temp;
                head = current;
            }
            else if(temp->next == NULL)
            {
                current = temp->prev;
                temp->prev->next =NULL;
                delete temp;
                temp = current;
            }
            else
            {
                current = temp->next;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
                temp = current;
            }
        }
        else
        {
            temp = temp->next;
        }
    }
    return head;
}

//Question 2
node* Queue::dequeue()
{
    node *temp = new node;
    if(head == NULL)
    {
        return NULL;
    }
    else if(head == tail)
    {

        temp = head;
        delete head;
        head = NULL;
        tail = NULL;
        return temp;
    }
    else
    {
        temp = head;
        delete head;
        head = temp->next;
        return temp;
    }
}