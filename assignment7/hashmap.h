// Keanu Aloua
// Custom HashMap header file
// NOTE: All in one header file due to errors with source files using templates

#include <iostream>
#include <string>

template <typename t1, typename t2>
class hashMap
{
    public:
        struct hashPair {
        // This will be a pair for each entry in the hash table
            t1 key;
            t2 value;
            hashPair * link;
        };

        struct iteratorPair {
        // Points to an existing pair in the hash table
            t1 * key;
            t2 * value;
            iteratorPair * link;
        };

        class iterator
        {
            public:
                friend class hashMap;
                iterator();
                const iterator& operator ++(int);
                bool operator ==(const iterator&) const;
                bool operator !=(const iterator&) const;
                t1 first();
                t2 second();

            private:
                iterator(iteratorPair *);
                iteratorPair * element;
        };

        hashMap ();
        ~hashMap ();
        t2& operator [](t1);
        iterator begin() const;
        iterator end() const;

    private:
        void resize();
        int h(std:: string) const;
        int items;
        int size;
        hashPair ** table;
        iteratorPair * head;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~ HashMap Public Functions ~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename t1, typename t2>
hashMap<t1, t2>::hashMap() {
    size = 5;
    items = 0;
    head = nullptr;
    table = new hashPair*[size];

    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

template <typename t1, typename t2>
hashMap<t1, t2>::~hashMap() {

    // Deallocating the hash map
    for (int i = 0; i < size; i++) {
        hashPair * node = table[i];

        while (node != nullptr) {
            hashPair * next = node->link;
            delete node;
            node = next;
        }
    }

    delete table;

    // Deallocating the iterator linked list
    while (head != nullptr) {
        iteratorPair * next = head->link;
        delete head;
        head = next;
    }

    delete head;
}

template <typename t1, typename t2>
t2& hashMap<t1, t2>::operator[](t1 key) {

    float loadFactor = static_cast<float>(items) / size;
    if (loadFactor >= 0.5) { resize(); }

    int index = h(key);

    while (index < size) {
        hashPair * node = table[index]; // Gets head of a linked list in the table

        if (node == nullptr || node->link == nullptr) {
        // Checking if there is 1 or 2 nodes in the map index list

            // Checks first node and key
            if (node != nullptr && node->key == key) { return node->value; }

            // Else creates a new hash pair and iterator pair
            hashPair * pair = new hashPair;
            iteratorPair * iterPair = new iteratorPair;

            // Setting hashmap pair
            pair->key = key;
            pair->value = t2();
            pair->link = nullptr;

            // Adding new node into hash map
            if (node == nullptr) { table[index] = pair; }
            else { node->link = pair; }

            // Setting iterator pair
            iterPair->key = &(pair->key);
            iterPair->value = &(pair->value);
            iterPair->link = nullptr;

            items++; // Incrementing item count

            iteratorPair * iterNode = head;

            // If iterator list is empty, then allocate
            if (head == nullptr) {
                head = iterPair;
            }
            else {
            // Else traverse through list
                while (iterNode->link != nullptr) {
                    iterNode = iterNode->link;
                }

                // Adds the new iterator pair
                iterNode->link = iterPair;
            }

            return pair->value;
        }
        else {
        // If there's two nodes, then check both nodes
            while (node != nullptr) {
                if (node->key == key) { return node->value; }
                node = node->link;
            }
        }
  
        // Check for new index in table
        index = (index + 1) % size;
    }

    return table[index]->value;
}

template <typename t1, typename t2>
typename hashMap<t1, t2>::iterator hashMap<t1, t2>::begin() const {
    return head;
}

template <typename t1, typename t2>
typename hashMap<t1, t2>::iterator hashMap<t1, t2>::end() const {
    iterator i = nullptr;

    return i;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ HashMap Private Functions ~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename t1, typename t2>
void hashMap<t1, t2>::resize() {

    // Deleting old linked list
    while (head != nullptr) {
        iteratorPair * next = head->link;
        delete head;
        head = next;
    }

    delete head;

    // Creating bigger hashmap table
    int oldSize = size;
    size *= 2;
    items = 0; 
    hashPair ** oldTable = table;
    table = new hashPair*[size];

    // Setting nodes in old table into new table
    for (int i = 0; i < oldSize; i++) {
        hashPair * node = oldTable[i];

        while (node != nullptr) {
            (*this)[node->key] = node->value;
            node = node->link;
        }
    }

    // Deleting old table
    for (int i = 0; i < oldSize; i++) {
        hashPair * oldNode = oldTable[i];

        while (oldNode != nullptr) {
            hashPair * nextOld = oldNode->link;
            delete oldNode;

            oldNode = nextOld;
        }
    }

    delete oldTable;
}

template <typename t1, typename t2>
int hashMap<t1, t2>::h(std::string key) const {
    int result = 0;

    // Adds each letter's ASCII value from the given key
    for (int i = 0; i < key.size(); i++) {
        result += key[i];
    }

    return result % size;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~ Iterator Class ~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <typename t1, typename t2>
hashMap<t1, t2>::iterator::iterator() {
    element = nullptr;
}

template <typename t1, typename t2>
hashMap<t1, t2>::iterator::iterator(iteratorPair * p) {
    element = p;
}

template <typename t1, typename t2>
const typename hashMap<t1, t2>::iterator& hashMap<t1, t2>::iterator::operator++(int) {
    element = element->link;
    return *this;
}

template <typename t1, typename t2>
bool hashMap<t1, t2>::iterator::operator==(const hashMap<t1, t2>::iterator& rhs) const {
    if (this->element == rhs.element) {
        return true;
    }

    return false;
}

template <typename t1, typename t2>
bool hashMap<t1, t2>::iterator::operator!=(const hashMap<t1, t2>::iterator& rhs) const {
    if (this->element == rhs.element) {
        return false;
    }

    return true;
}

template <typename t1, typename t2>
t1 hashMap<t1, t2>::iterator::first() {
    return *(element->key);
}

template <typename t1, typename t2>
t2 hashMap<t1, t2>::iterator::second() {
    return *(element->value);
}
