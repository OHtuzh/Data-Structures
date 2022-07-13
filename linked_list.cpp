#include <iostream>


template<typename T>
class LinkedList
{
private:
    typedef struct node
    {
        T data;
        node* prev;
        node* next;
    } node;

    node* head;
    node* tail;
    int size;


public:
    LinkedList()
    {
        head = tail = NULL;
        size = 0;
    }

    ~LinkedList()
    {
        node* tmp = tail;
        node* tmp2;
        while (tmp != NULL) 
        {
            tmp2 = tmp;
            tmp = tmp->next;
            delete tmp2;
        }
    }

    int get_size()
    {
        return size;
    }

    void add(const T& value)
    {
        if (head == NULL)
        {
            node* tmp = new node;
            tmp->data = value;
            tmp->prev = tmp->next = NULL;
            head = tail = tmp;
        }
        else
        {
            node* tmp = new node;
            tmp->data = value;
            tmp->next = NULL;
            tmp->prev = head;

            head->next = tmp;
            head = head->next;
        }
        size++;
    }

    T& get(unsigned const int& index)
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of a range");
        }
        else if (index < size / 2)
        {
            node* tmp = tail;
            for (int i = 0; i < index; i++)
            {
                tmp = tmp->next;
            }
            return tmp->data;
        }
        else
        {
            node* tmp = head;
            for (int i = size - 1; i > index; i--)
            {
                tmp = tmp->prev;
            }
            return tmp->data;
        }
    }

    T pop()
    {
        node* tmp = head;
        T returnValue = tmp->data;

        head = head->prev;
        if (head != NULL) head->next = NULL;
        else tail = NULL;

        size--;
        delete tmp;
        return returnValue;
    }

    T pop(unsigned const int& index)
    {
        node* tmp;
        if (index >= size)
        {
            throw std::out_of_range("Indext out of a range");
        }
        else if (index < size / 2)
        {
            tmp = tail;
            for (int i = 0; i < index; i++)
            {
                tmp = tmp->next;
            }
        }
        else
        {
            tmp = head;
            for (int i = size - 1; i > index; i--)
            {
                tmp = tmp->prev;
            }
        }

        T returnValue = tmp->data;


        if (tmp->prev == NULL && tmp->next == NULL)  
        {
            delete head;
            head = tail = NULL;
        }  
        else if (tmp->prev == NULL)
        {
            tail = tail->next;
            delete tail->prev;
            tail->prev = NULL;
        }
        else if (tmp->next == NULL)
        {
            head = head->prev;
            delete head->next;
            head->next = NULL;
        }
        else
        {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            delete tmp;
        }

        size--;
        return returnValue;
    }

    void insert(const T& value, unsigned const int& index)
    {
        if (index >= size)
        {
            node* tmp;
            int start_size = size;
            for (int i = 0; i < index + 1 - start_size; i++)
            {
                tmp = new node;
                
                if (head == NULL)
                {
                    tmp->prev = tmp->next = NULL;
                    head = tail = tmp;
                }
                else
                {
                    tmp->prev = head;
                    tmp->next = NULL;
                    head->next = tmp;
                    head = head->next;
                }
                size++;
            }
            head->data = value;
        }
        else 
        {
            node* tmp;

            if (index < size / 2)
            {
                tmp = tail;
                for (int i = 0; i < index; i++)
                {
                    tmp = tmp->next;
                }
            }
            else
            {
                tmp = head;
                for (int i = size - 1; i > index; i--)
                {
                    tmp = tmp->prev;
                }
            }
            node* nw = new node;

            nw->data = value;
            nw->prev = tmp->prev;
            nw->next = tmp;

            if (tmp->prev != NULL)
            {
                tmp->prev->next = nw;
                tmp->prev = nw;
            }
            size++;
        }
    }
};
