#ifndef MY_STACK_H
#define MY_STACK_H

#include <iostream>
#include "my_vector.h"

template <class T>

class MyStack
{
private:


    unsigned int size;

    MyVector<T> stackArray;

public:


    MyStack();

    MyStack(MyStack*);

    ~MyStack() { this->stackArray.setArrPtr(nullptr); };

public:

    //Returns bool value
    bool isNotEmpty();

    T peek();

    T pop();

    void push(T);

    int getSize();

    void setSize(int n);

    MyVector<T> getVec();

    void setVec(MyVector<T> vector);

public:


    void input();

    void output();

};

//Definition code.
template<class T>
inline MyStack<T>::MyStack()
{
    this->stackArray.setSize(1);
    this->size = 0;
}
;

template<class T>
inline MyStack<T>::MyStack(MyStack* other)
{
    this->stackArray.setArrPtr(other->stackArray.getArrPtr());
    this->stackArray.setSize(other->stackArray.getSize());
    this->size = other->size;
}
;

template<class T>
inline bool MyStack<T>::isNotEmpty()
{
    if (this->size == 0)
        return false;
    else
        return true;
}
;

template<class T>
inline T MyStack<T>::peek()
{
    if (this->isNotEmpty())
        return this->stackArray.take(this->size - 1);
    else
    {
        std::cerr << std::endl << std::endl << "Stack is empty." << std::endl;
        return T();
    }
}
;

template<class T>
inline T MyStack<T>::pop()
{
    T out = this->peek();
    this->stackArray.remove(this->size - 1);
    this->size--;
    return out;
}
;

template<class T>
inline void MyStack<T>::push(T item)
{
    if (this->isNotEmpty())
        this->stackArray.add(item, this->size);
    else
        this->stackArray.add(item, 0);
    this->size++;
}
;

template<class T>
inline int MyStack<T>::getSize()
{
    return this->size;
}
;

template<class T>
inline void MyStack<T>::setSize(int n)
{
    this->size = n;
}
;

template<class T>
inline MyVector<T> MyStack<T>::getVec()
{
    return stackArray;
}
;

template<class T>
inline void MyStack<T>::setVec(MyVector<T> vector)
{
    this->stackArray = vector;
}
;

template<class T>
inline void MyStack<T>::input()
{
    std::cout << std::endl;

    unsigned int number = 0;
    std::cout << "Please, enter the number of items "
        << "you want to input in the stack: ";
    std::cin >> number;
    std::cout << std::endl;

    T item = T();
    for (unsigned int i = 0; i < number; i++)
    {
        std::cout << "Please, enter " << i << " item: ";
        std::cin >> item;
        this->push(item);
    }

    std::cout << std::endl;
}
;

template<class T>
inline void MyStack<T>::output()
{
    std::cout << std::endl;

    this->stackArray.output();

    std::cout << std::endl;
}
;

//End of definition code.

#endif //MY_STACK_H
