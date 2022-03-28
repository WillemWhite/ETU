#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <iostream>

template <class T>

class MyVector
{
private:


    int size;

    T* arrPtr;

public:


    MyVector();

    //creating vector with const size and typename T
    MyVector(int);

    MyVector(MyVector*);

    MyVector(T* arr, int arrSize = 0);

    ~MyVector() { delete[] arrPtr; };

public:


    //adding (element, point) in the vector
    void add(T, int);

    //removing element from chosen point in the vector
    void remove(int);

    //searching element in the vector
    int search(T);

    //taking element from chosen point in the vector
    T take(int);

    //getting size of the vector
    int getSize() { return this->size; };

    //changing size of the vector
    void setSize(int);

    T* getArrPtr() { return this->arrPtr; };

    void setArrPtr(T*);

public:


    void input();

    void output();
};

//Definition code.
template <class T>
inline MyVector<T>::MyVector()
    : size(0)
{
    this->arrPtr = nullptr;
}

template <class T>
inline MyVector<T>::MyVector(int n)
    : size(n)
{
    this->arrPtr = new T[size];
    for (int i = 0; i < n; i++)
        this->arrPtr[i] = T();
}

template <class T>
inline MyVector<T>::MyVector(MyVector* other)
    : size(other->size)
{
    this->arrPtr = other->arrPtr;
}

template <class T>
inline MyVector<T>::MyVector(T* arr, int arrSize)
    : size(arrSize)
{
    this->arrPtr = arr;
}

template<class T>
inline void MyVector<T>::setSize(int n)
{
    int oldSize = this->size;
    this->size = n;
    T* newNamePtr = new T[this->size];

    for (int i = 0; i < this->size; i++)
        newNamePtr[i] = T();

    for (int i = 0; i < (oldSize >= this->size ? this->size : oldSize); i++)
        newNamePtr[i] = this->arrPtr[i];

    delete[] arrPtr;
    this->arrPtr = newNamePtr;
}

template<class T>
inline void MyVector<T>::setArrPtr(T* newNamePtr)
{
    delete[] this->arrPtr;
    this->arrPtr = newNamePtr;
}

template<class T>
void MyVector<T>::add(T element, int point)
{
    this->setSize(this->size + 1);
    for (int i = point + 1; i < this->getSize(); i++)
        this->arrPtr[i] = this->arrPtr[i - 1];
    this->arrPtr[point] = element;
}

template<class T>
void MyVector<T>::remove(int point)
{
    for (int i = point; i < this->getSize(); i++)
        this->arrPtr[i] = this->arrPtr[i + 1];
    this->setSize(this->size - 1);
}

template<class T>
inline int MyVector<T>::search(T element)
{
    int point = -1; //if you have this output, you have an issue
    for (int i = 0; i < this->size; i++)
        if (this->arrPtr[i] == element)
            point = i;
    return point;
}

template<class T>
inline T MyVector<T>::take(int point)
{
    return this->arrPtr[point];
}

template<class T>
void MyVector<T>::input()
{
    std::cout << std::endl;

    std::cout << "Please, enter size of array: ";
    std::cin >> this->size;
    this->setSize(this->size);
    std::cout << std::endl;

    for (int i = 0; i < this->getSize(); i++)
    {
        std::cout << "Enter " << i << " element of array: ";
        std::cin >> this->arrPtr[i];
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

template<class T>
inline void MyVector<T>::output()
{
    std::cout << std::endl;

    for (int i = 0; i < this->size; i++)
    {
        std::cout << this->arrPtr[i] << " ";
        if ((i + 1) % 30 == 0) { std::cout << std::endl; }
    }
}
//End of definition code.

#endif //MY_VECTOR_H