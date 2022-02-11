//Linked List header class

#include <iostream>

template <typename type>
class LL
{
    struct node
    {
        type data;
        node * prev;
        node * next;
    };
    
    public:
        class iterator
        {
            public:
                friend class LL;
                iterator();
                iterator(node*);
                type operator*() const;
                const iterator& operator++(int);
                const iterator& operator--(int);
                bool operator==(const iterator&) const;
                bool operator!=(const iterator&) const;
            
            private:
                node * current;
        };

        LL(); // Sets head and tail to NULL
        LL(const LL<type>&); // Makes a deep copy
        // const LL<type>& operator=(const LL<type>&); // Deep copy assignment operator
        ~LL(); // Destructor to deallocate
        void tailInsert(const type&);
        iterator begin() const;
        iterator end() const;
        void swapNodes(iterator&, iterator&);

    private:
        node * head;
        node * tail;
};

// ------------------------------------------------
// ---------------- Iterator Class ----------------
// ------------------------------------------------
template <typename type>
LL<type>::iterator::iterator()
{
    current = NULL;
}

template <typename type>
LL<type>::iterator::iterator(node* ptr)
{
    current = ptr;
}

template <typename type>
type LL<type>::iterator::operator*() const
{
    return current->data;
}

template <typename type>
const typename LL<type>::iterator& LL<type>::iterator::operator++(int)
{
    current = current->next;
    return *this; // Returns object
}

template <typename type>
const typename LL<type>::iterator& LL<type>::iterator::operator--(int)
{
    current = current->prev;
    return *this; // Returns object
}

template <typename type>
bool LL<type>::iterator::operator==(const iterator& rhs) const
{
    if (this->current == rhs.current) {
        return true;
    }
    else {
        return false;
    }
}

template <typename type>
bool LL<type>::iterator::operator!=(const iterator& rhs) const
{
    if (this->current != rhs.current) {
        return true;
    }
    else { 
        return false; 
    }
}

// ------------------------------------------------
// ------------------- LL Class -------------------
// ------------------------------------------------

template <typename type>
LL<type>::LL()
{
    head = NULL;
    tail = NULL;
}

template <typename type>
LL<type>::LL(const LL<type>& copy)
{
    this = copy;
}

template <typename type>
LL<type>::~LL()
{
    // If head->next == NULL then it has reached the end of the list 
    while (head->next != NULL)
    {
        node * temp = head->next;
        delete head;

        head = temp;
    }
}

template <typename type>
void LL<type>::tailInsert(const type& num)
{
    // Creates an allocated new node
    node * newNode = new node;

    if (head == NULL)
    {
        newNode->data = num;
        newNode->prev = NULL;
        newNode->next = NULL;

        // Since its the first node, both head and tail point to this node
        head = newNode;
        tail = newNode;
    }
    else
    {
        node * temp = head;

        // Goes through the list until the next node points to null
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        // Last node points to the new node
        temp->next = newNode;

        newNode->data = num;
        newNode->prev = temp;
        newNode->next = NULL;

        // This new node becomes the tail
        tail = newNode;
    }
}

template <typename type>
typename LL<type>::iterator LL<type>::begin() const
{
    iterator temp = iterator(head);

    return temp; // temp.current == head
}

template <typename type>
typename LL<type>::iterator LL<type>::end() const
{
    iterator temp = iterator(tail);

    return temp; // temp.current == tail
}

template <typename type>
void LL<type>::swapNodes(iterator& it1, iterator& it2)
{
    // Finding addresses
    node * i1 = it1.current;
    node * i2 = it2.current;

    node * i1Left = i1->prev;
    node * i1Right = i1->next;

    node * i2Left = i2->prev;
    node * i2Right = i2->next;

    // Checks to see if left iterator was head
    if (i1 == head) 
    { 
        i2->prev = NULL;
        head = i2; // Since i1 was the head, i2 is the head now
    }
    else 
    { 
        i1Left->next = i2;
        i2->prev = i1Left;
    }

    // Checks to see if right iterator was the tail
    if (i2 == tail) 
    { 
        tail = i1; // Since i2 was the tail, i1 is the tail now
        i1->next = NULL;
    }
    else
    {
        i1->next = i2Right;
        i2Right->prev = i1;
    }

    // Points both nodes to each other
    i2->next = i1;
    i1->prev = i2;

    // Keeping iterators constant
    it2.current = i1;
    it1.current = i2;
}