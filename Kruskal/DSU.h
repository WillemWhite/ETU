#ifndef DSU_H
#define DSU_H
#include <iostream>
#include "vector.h"

template <class T>
class SetUnion {
public:
    T memb;
    T lead;
    SetUnion() { memb = NULL; lead = NULL; }
    SetUnion(T membArg, T leadArg) { memb = membArg; lead = leadArg; }
};

template <class T>
class DSU {
private:
    Vector<SetUnion<T>> arrOfUnion;
public:
    DSU() { this->arrOfUnion; }
    DSU(const DSU<T>& other) { this->arrOfUnion = other.arrOfUnion; }
    //call only vector destructor
    ~DSU() { };
public:
    void makeSet(const T&);
    void makeUnion(const T&, const T&);
    T find(const T&);
    int getSize() { return this->arrOfUnion.getSize(); }
    SetUnion<T>* getArrPtr() { return this->arrOfUnion.getArrPtr(); }
    void operator = (const DSU<T>& other) { this->arrOfUnion = other.arrOfUnion; }
    //for supported data types.
    void output();
};

template<class T>
inline void DSU<T>::makeSet(const T& elem) {
    SetUnion<T> su(elem, elem);
    this->arrOfUnion.add(su, 0);
}

template<class T>
inline void DSU<T>::makeUnion(const T& leadOfSet1, const T& leadOfSet2) {
    for (int i = 0; i < this->arrOfUnion.getSize(); i++) {
        if (this->arrOfUnion.take(i)->lead == leadOfSet2) {
            SetUnion<T> su = { this->arrOfUnion.take(i)->memb, leadOfSet1 };
            this->arrOfUnion.setElem(su, i);
        }
    }
}

template<class T>
inline T DSU<T>::find(const T& memb) {
    for (int i = 0; i < this->arrOfUnion.getSize(); i++) {
        if (this->arrOfUnion.take(i)->memb == memb)
            return this->arrOfUnion.take(i)->lead;
    }
    return NULL;
}

template<class T>
inline void DSU<T>::output() {
    std::cout << std::endl << "DSU member(child):  ";
    for (int i = 0; i < this->arrOfUnion.getSize(); i++)
        std::cout << this->arrOfUnion.take(i)->memb << " ";
    std::cout << std::endl << "DSU leader(parent): ";
    for (int i = 0; i < this->arrOfUnion.getSize(); i++)
        std::cout << this->arrOfUnion.take(i)->lead << " ";
    std::cout << std::endl;
}
#endif //DSU_H
