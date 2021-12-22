#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue {
private:
    int size = 0;
    T** elemArr = nullptr;
public:
    Queue() { this->size = 0; this->elemArr = nullptr; }
    Queue(T* elem) { elemArr = new T * (elem); size = 1; }
    ~Queue();
};

template <class T>
void pushBack(Queue<T>& queue, T*& elem) {
    if (queue.elemArr == NULL) { queue.elemArr = new T * (elem); queue.size++; }
    else
    {
        T** tmp = queue.elemArr;
        queue.elemArr = new T * [queue.size + 1];
        memmove_s(queue.elemArr + 1, sizeof(T*) * queue.size,
            tmp, sizeof(T*) * queue.size);

        queue.elemArr[0] = elem;
        queue.size++;
        delete[] tmp;
    }
}

template <class T>
T* popFront(Queue<T>& queue) {
    if (queue.elemArr == NULL) return NULL;
    else if (queue.size == 1)
    {
        T* elem = queue.elemArr[0];
        queue.elemArr = NULL;
        queue.size = 0;

        delete[] queue.elemArr;
        return elem;
    }
    else
    {
        T** tmp = queue.elemArr;
        T* elem = queue.elemArr[queue.size - 1];
        queue.elemArr = new T * [queue.size - 1];
        memmove_s(queue.elemArr, sizeof(T*) * (queue.size - 1),
            tmp, sizeof(T*) * (queue.size - 1));

        queue.size--;
        delete[] tmp;
        return elem;
    }
}

template<class T>
inline Queue<T>::~Queue() {
    if (this->elemArr)
        delete this->elemArr;
    this->elemArr = nullptr;
}
#endif //QUEUE_H