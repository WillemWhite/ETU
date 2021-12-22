#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
//Here you can see my modified vector library from the 1st lab

template <class T>

class Vector {
private:
    int size = 0;
    T* arrPtr = nullptr;

public:
    Vector();
    Vector(int);        //creating vector with const size and typename T
    Vector(const Vector&);   //overload
    Vector(T*& arr, int arrSize = 0);
    ~Vector() { this->delArrPtr(); }

public:
    //adding (element, point) in the vector
    void add(T&, int);
    //removing element from chosen point in the vector
    void remove(int);
    //searching element in the vector
    int search(T&);
    //taking element from chosen point in the vector
    T* take(int);
    //setting element in the vector by a point
    void setElem(T&, int);
    //getting size of the vector
    int getSize() { return this->size; };
    //changing size of the vector
    void setSize(int);
    T* getArrPtr() { return this->arrPtr; };
    void setArrPtr(T*&);
    void delArrPtr();
    void operator = (const Vector<T>&);

public:
    //for supported data types.
    void input();
    void output();
};

//Definition code.
template <class T>
inline Vector<T>::Vector()
    : size(0) {
    this->arrPtr = nullptr;
}
;

template <class T>
inline Vector<T>::Vector(int n)
    : size(n) {
    this->arrPtr = new T[this->size];
    for (int i = 0; i < n; i++)
        this->arrPtr[i] = T();
}
;

template <class T>
inline Vector<T>::Vector(const Vector& other) {
    *this = other;
}
;

template <class T>
inline Vector<T>::Vector(T*& arr, int arrSize)
    : size(arrSize) {
    this->arrPtr = arr;
}
;

template<class T>
inline void Vector<T>::setSize(int n) {
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
;

template<class T>
inline void Vector<T>::setArrPtr(T*& newNamePtr) {
    delete[] this->arrPtr;
    this->arrPtr = newNamePtr;
}
;

template<class T>
inline void Vector<T>::delArrPtr() {
    if (this->arrPtr)
        delete[] this->arrPtr;
    this->arrPtr = nullptr;
}
;

template<class T>
void Vector<T>::add(T& element, int point) {
    this->setSize(this->size + 1);
    for (int i = this->getSize() - 1; i > point; i--)
        this->arrPtr[i] = this->arrPtr[i - 1];
    this->arrPtr[point] = element;
}
;

template<class T>
void Vector<T>::remove(int point) {
    for (int i = point; i < this->getSize(); i++)
        this->arrPtr[i] = this->arrPtr[i + 1];
    this->setSize(this->size - 1);
}
;

template<class T>
inline int Vector<T>::search(T& element) {
    int point = -1; //if you have this output, you have an issue
    for (int i = 0; i < this->size; i++)
        if (this->arrPtr[i] == element)
            point = i;
    return point;
}
;

template<class T>
inline T* Vector<T>::take(int point) {
    return &this->arrPtr[point];
}
;

template<class T>
void Vector<T>::setElem(T& element, int point) {
    this->arrPtr[point] = element;
}
;

template<class T>
void Vector<T>::input() {
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
;

template<class T>
inline void Vector<T>::output() {
    std::cout << std::endl;
    for (int i = 0; i < this->size; i++) {
        std::cout << this->arrPtr[i] << " ";
        if ((i + 1) % 30 == 0) { std::cout << std::endl; }
    }
}
;

template<class T>
inline void Vector<T>:: operator = (const Vector<T>& other) {
    this->size = other.size;
    this->arrPtr = new T[this->size];
    memmove_s(this->arrPtr, sizeof(T) * this->size,
        other.arrPtr, sizeof(T) * this->size);
}
;
//End of definition code.

#endif //VECTOR_H
