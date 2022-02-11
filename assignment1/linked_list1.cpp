//Keanu Aloua
// January 24, 2022

#include "linked_list.h"

template <typename type>
LL<type>::LL()
    : head(nullptr),
      tail(nullptr)
{
    // Nothing
}

template <typename type>
LL<type>::LL(const LL<type>& copy)
{

}

template <typename type>
void LL<type>::tailInsert(const type& num)
{
    node* current = head;

    if (head == nullptr)
    {
        current->data = num;
        current->next = nullptr;
        current->prev = nullptr;
    }
    else
    {
        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->data = num;
        current->next = nullptr;
        current->prev->next = current;
    }
}