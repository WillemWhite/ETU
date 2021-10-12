#ifndef MY_LIST_H
#define MY_LIST_H

#include <iostream>

template <class T>

class MyList
{
private:


    template <class T>
    class Node
    {
    public:

        Node* ptrNext;
        T data;

        Node(T data = T(), Node* ptrNext = nullptr)
        {
            this->data = data;
            this->ptrNext = ptrNext;
        }

    };

    Node<T>* head;
    unsigned int size;

public:


    MyList();

    MyList(const MyList*);

    ~MyList();

public:

    //adding (element, point) in front of the list
    void pushFront(const T);

    //adding (element, point) in the list
    void push(const T, const unsigned int);

    //adding (element) to the end of the list
    void pushBack(const T);

    //removing element from chosen point in the list
    void remove(const unsigned int);

    //searching element in the list
    int search(const T);

    //taking element from chosen point in the list
    T take(const unsigned int);

    //getting size of the list
    int getSize() { return this->size; }



public:


    void input();

    void output();

};

//Definition code.
template<class T>
inline MyList<T>::MyList()
    : size(0)
    , head(nullptr) {};

template<class T>
inline MyList<T>::MyList(const MyList* other)
    : size(other->size)
    , head(other->head) {};

template<class T>
inline MyList<T>::~MyList()
{
    while (this->size != 0)
    {
        this->remove(0);
    }
    std::cout << "Deconstruct" << std::endl;
}
;

template<class T>
inline void MyList<T>::pushFront(const T element)
{
    this->head = new Node<T>(element, this->head);
    this->size++;
}
;

template<class T>
inline void MyList<T>::push(const T element, const unsigned int point)
{

    if (point == 0)
    {
        this->pushFront(element);
    }
    else if (point < this->size)
    {
        Node<T>* current = this->head;

        for (unsigned int i = 1; i < point; i++)
        {
            current = current->ptrNext;
        }

        Node<T>* swap = current->ptrNext;

        current->ptrNext = new Node<T>(element);
        current = current->ptrNext;

        current->ptrNext = swap;

        this->size++;
    }
    else
    {
        std::cerr << "You entered the wrong point." << std::endl;
    }

}
;

template<class T>
inline void MyList<T>::pushBack(const T data)
{

    if (this->head == nullptr)
    {
        this->head = new Node<T>(data);
    }
    else
    {
        Node<T>* current = this->head;

        while (current->ptrNext != nullptr)
        {
            current = current->ptrNext;
        }
        
        Node<T>* tail = new Node<T>(data);

        current->ptrNext = tail;
    }

    this->size++;

}
; 

template<class T>
inline void MyList<T>::remove(const unsigned int point)
{
    if (point == 0)
    {
        Node<T>* swap = this->head->ptrNext;

        delete this->head;

        this->head = swap;

        this->size--;
    }

    else if (point < this->size)
    {
        Node<T>* current = this->head;

        for (unsigned int i = 0; i < point; i++)
        {
            current = current->ptrNext;
        }

        Node<T>* swap = current->ptrNext;

        delete current;

        current = this->head;

        for (unsigned int i = 1; i < point; i++)
        {
            current = current->ptrNext;
        }

        current->ptrNext = swap;

        this->size--;
    }

    else
    {
        std::cerr << std::endl << std::endl << "You entered the wrong point."
            << std::endl << std::endl;
    }

}
;

template<class T>
inline int MyList<T>::search(const T element)
{
    int point = 0;

    Node<T>* current = this->head;

    while (current != nullptr)
    {
        if (current->data != element)
        {
            current = current->ptrNext;
            point++;
        }
        else
        {
            return point;
        }

    }

    std::cerr << std::endl << std::endl << "Element does not exist."
        << std::endl << std::endl;

    return 0;
}
;

template<class T>
inline T MyList<T>::take(const unsigned int point)
{
    if (point < this->size)
    {
        Node<T>* current = this->head;

        for (unsigned int i = 0; i < point; i++)
        {
            current = current->ptrNext;
        }

        return current->data;
    }
    else
    {
        std::cerr << std::endl << std::endl << "You entered the wrong point."
            << std::endl << std::endl;
        return 0;
    }
}
;

template<class T>
inline void MyList<T>::input()
{
    std::cout << std::endl;

    std::cout << "Please, enter the number of input elements: ";
    unsigned int number;
    std::cin >> number;
    std::cout << std::endl;

    T data = T();

    for (unsigned int i = 0; i < number; i++)
    {
        std::cout << "Enter " << i << " element: ";
        std::cin >> data;
        std::cout << std::endl;

        this->pushBack(data);
    }

    std::cout << std::endl;
}
;

template<class T>
inline void MyList<T>::output()
{
    if (this->head == nullptr)

        std::cout << std::endl << "List is empty." << std::endl;

    else
    {
        std::cout << std::endl;

        Node<T>* current = this->head;

        do
        {
            std::cout << current->data << " ";
            current = current->ptrNext;

        } while (current != nullptr);

        std::cout << std::endl;
    }
}
;
//End of definition code.

#endif //MY_LIST_H