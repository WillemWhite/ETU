#ifndef TIMSORT_H
#define TIMSORT_H

#include "my_stack.h"
#include "my_vector.h"

struct RunPtrSize
{
    int* runPtr = nullptr;
    int size = 0;
};

void insertSort(RunPtrSize& arr);
void merge(int* begArr, const int& begSize, int* nextArr, const int& nextSize);
void galloping(int* begArr, const int& begSize, int* nextArr, const int& nextSize);
inline int binSearch(int*& arr, int beg, int end, int& el);
inline int getMinrun(int n);
inline void reverse(RunPtrSize& run);
void searchRun(RunPtrSize& arr, int& pivit, RunPtrSize& run, int minRun);
void timsortMerge(MyVector<int>& vector);
void timsortGalloping(MyVector<int>& vector);


void insertSort(RunPtrSize& arr)
{
    int value = 0;
    for (int j = 1; j < arr.size; j++)
    {
        value = arr.runPtr[j];
        for (int i = j - 1; i >= 0 && arr.runPtr[i] > value; i--)
        {
            arr.runPtr[i + 1] = arr.runPtr[i];
            arr.runPtr[i] = value;
        }
    }
}

inline int getMinrun(int n)
{
    int r = 0;		// becomes 1 if among the shifted bits there is at least 1 nonzero
    while (n >= 64)	// so that minrun is sufficient for composing a sequence,
    {				// because we are constantly dividing by 2 when calculating it.  
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

inline int binSearch(int*& arr, int beg, int end, int& el)
{
    int pos = beg + (end - beg) / 2;
    while ((arr[pos] > el) || (arr[pos + 1] <= el))
    {
        if (arr[pos] > el)
            end = pos;
        else if (arr[pos + 1] <= el)
            beg = pos;
        pos = beg + (end - beg) / 2;
    }
    return pos;
}

inline void reverse(RunPtrSize& run)
{
    for (int i = 0; i < run.size / 2; i++)
    {
        int swap = run.runPtr[i];
        run.runPtr[i] = run.runPtr[run.size - 1 - i];
        run.runPtr[run.size - 1 - i] = swap;
    }
}

void searchRun(RunPtrSize& arr, int& pivit, RunPtrSize& run, int minRun)
{
    if (arr.size - pivit < minRun) { minRun = arr.size - pivit; }	//checking end of array.
    int* arrPtrPivit = arr.runPtr + pivit;
    run.runPtr = arrPtrPivit;
    int p = 1;
    int size = 2;

    if (arrPtrPivit[0] > arrPtrPivit[1])
    {
        while ((arrPtrPivit[p] >= arrPtrPivit[p + 1]) && ((pivit + p) < (arr.size - 1))) { p++; }
        RunPtrSize runRev = { arrPtrPivit, p + 1 };
        reverse(runRev);
    }

    while ((p < (minRun - 1)) && ((pivit + p) < (arr.size - 1)))
    {
        if (arrPtrPivit[p + 1] >= arrPtrPivit[p])
            p++;
        else
        {
            p++;
            RunPtrSize runIns = { arrPtrPivit, p + 1 };
            insertSort(runIns);
        }
    }

    while ((arrPtrPivit[p + 1] >= arrPtrPivit[p]) && ((pivit + p) < (arr.size - 1)))
        p++;

    run.size = p + 1;
    pivit += p + 1;
}

void merge(int* begArr, const int& begSize, int* nextArr, const int& nextSize)
{
    if (begSize <= nextSize)
    {
        int* tmpArr = new int[begSize];

        memmove_s(reinterpret_cast<void*>(tmpArr), sizeof(int) * begSize,
            reinterpret_cast<void*>(begArr), sizeof(int) * begSize);

        int i = 0, j = 0, count = 0;
        while (i < begSize && j < nextSize)
        {
            if (tmpArr[i] <= nextArr[j])
            {
                begArr[count] = tmpArr[i];
                i++; count++;
            }
            else
            {
                begArr[count] = nextArr[j];
                j++; count++;
            }
        }

        if (i < begSize)
        {
            memmove_s(reinterpret_cast<void*>(begArr + count), sizeof(int) * (begSize - i),
                reinterpret_cast<void*>(tmpArr + i), sizeof(int) * (begSize - i));
        }
        delete[] tmpArr;
    }
    else
    {
        int* tmpArr = new int[nextSize];

        memmove_s(reinterpret_cast<void*>(tmpArr), sizeof(int) * nextSize,
            reinterpret_cast<void*>(nextArr), sizeof(int) * nextSize);

        int i = nextSize - 1, j = begSize - 1, count = nextSize + begSize - 1;
        while (i > -1 && j > -1)
        {
            if (tmpArr[i] >= begArr[j])
            {
                begArr[count] = tmpArr[i];
                i--; count--;
            }
            else
            {
                begArr[count] = begArr[j];
                j--; count--;
            }
        }

        if (i > -1)
        {
            memmove_s(reinterpret_cast<void*>(begArr), sizeof(int) * (i + 1),
                reinterpret_cast<void*>(tmpArr), sizeof(int) * (i + 1));
        }
        delete[] tmpArr;
    }
}

void galloping(int* begArr, const int& begSize, int* nextArr, const int& nextSize)
{
    int* tmpArr = new int[begSize];

    memmove_s(reinterpret_cast<void*>(tmpArr), sizeof(int) * begSize,
        reinterpret_cast<void*>(begArr), sizeof(int) * begSize);

    int i = 0, j = 0, count = 0;
    int conditionTmp = 0, conditionNext = 0;

    while (i < begSize && j < nextSize)
    {
        while ((i < begSize && j < nextSize) && (tmpArr[i] <= nextArr[j]))
        {
            begArr[count] = tmpArr[i];
            i++; count++; conditionTmp++;

            if (conditionTmp == 7 && tmpArr[i] <= nextArr[j])
            {
                int bin = 2, begin = i;
                while ((i < begSize) && (tmpArr[i] <= nextArr[j])) { i += bin; bin *= 2; }

                //end processing.
                int lastPoint = 0; 
                if ((i >= begSize) && (tmpArr[begSize - 1] <= nextArr[j]))
                {
                    memmove_s(reinterpret_cast<void*>(begArr + count), sizeof(int) * (begSize - begin),
                        reinterpret_cast<void*>(tmpArr + begin), sizeof(int) * (begSize - begin));
                    i = begSize; continue;
                }
                else if((i >= begSize) && (tmpArr[begSize - 1] > nextArr[j]))
                    lastPoint = binSearch(tmpArr, i - bin / 2, begSize - 1, nextArr[j]);
                else
                    lastPoint = binSearch(tmpArr, i - bin / 2, i, nextArr[j]);

                i = lastPoint + 1;

                memmove_s(reinterpret_cast<void*>(begArr + count), sizeof(int) * (lastPoint - begin + 1),
                    reinterpret_cast<void*>(tmpArr + begin), sizeof(int) * (lastPoint - begin + 1));

                count += lastPoint - begin + 1;
                conditionTmp = 0;
            }
        }
        conditionTmp = 0;

        while ((i < begSize && j < nextSize) && (tmpArr[i] > nextArr[j]))
        {
            begArr[count] = nextArr[j];
            j++; count++; conditionNext++;

            if (conditionNext == 7 && tmpArr[i] >= nextArr[j])
            {
                int bin = 2, begin = j;
                while ((j < nextSize) && (tmpArr[i] >= nextArr[j])) { j += bin; bin *= 2; }

                //end processing.
                int lastPoint = 0;
                if ((j >= nextSize) && (tmpArr[i] >= nextArr[nextSize - 1]))
                {
                    memmove_s(reinterpret_cast<void*>(begArr + count), sizeof(int) * (nextSize - begin),
                        reinterpret_cast<void*>(nextArr + begin), sizeof(int) * (nextSize - begin));
                    j = nextSize; continue;
                }
                else if((j >= nextSize) && (tmpArr[i] < nextArr[nextSize - 1]))
                    lastPoint = binSearch(nextArr, j - bin / 2, nextSize - 1, tmpArr[i]);
                else
                    lastPoint = binSearch(nextArr, j - bin / 2, j, tmpArr[i]);

                j = lastPoint + 1;

                memmove_s(reinterpret_cast<void*>(begArr + count), sizeof(int) * (lastPoint - begin + 1),
                    reinterpret_cast<void*>(nextArr + begin), sizeof(int) * (lastPoint - begin + 1));

                count += lastPoint - begin + 1;
                conditionNext = 0;
            }
        }
        conditionNext = 0;
    }

    if (i < begSize)
    {
        memmove_s(reinterpret_cast<void*>(begArr + count), sizeof(int) * (begSize - i),
            reinterpret_cast<void*>(tmpArr + i), sizeof(int) * (begSize - i));
    }
    delete[] tmpArr;
}

void timsortMerge(MyVector<int>& vector)
{
    int minRun = getMinrun(vector.getSize());
    int* pArr = vector.getArrPtr();
    int sizeArr = vector.getSize();

    MyStack<RunPtrSize> stackOfRun;

    int p = 0;										//pivit.
    RunPtrSize vectorStruct = { pArr, sizeArr };	//struct of vector.
    RunPtrSize run = { pArr, 2 };					//initializing run.

    while (p < sizeArr)
    {
        searchRun(vectorStruct, p, run, minRun);

        if (stackOfRun.getSize() < 1)
            stackOfRun.push(run);
        else if (stackOfRun.getSize() == 1)
        {
            if (stackOfRun.peek().size > run.size)
                stackOfRun.push(run);
            else
            {
                RunPtrSize runInStack = stackOfRun.pop();
                merge(runInStack.runPtr, runInStack.size, run.runPtr, run.size);
                runInStack.size += run.size; stackOfRun.push(runInStack);
            }
        }
        else
        {
            stackOfRun.push(run);
            int sizeX = 0, sizeY = 0, sizeZ = 0;	//for cycle condition
            do
            {
                RunPtrSize Z = stackOfRun.pop();  sizeZ = Z.size;
                RunPtrSize Y = stackOfRun.pop();  sizeY = Y.size;
                RunPtrSize X = stackOfRun.pop();  sizeX = X.size;

                if ((Y.size <= Z.size || (X.size <= (Y.size + Z.size))) && Z.size <= X.size)
                {
                    merge(Y.runPtr, Y.size, Z.runPtr, Z.size);
                    Y.size += Z.size; sizeY += sizeZ;
                    Z.size = 0;       sizeZ = 0;
                }
                if ((Y.size <= Z.size || (X.size <= (Y.size + Z.size))) && Z.size > X.size)
                {
                    merge(X.runPtr, X.size, Y.runPtr, Y.size);
                    X.size += Y.size; sizeX += sizeY;
                    Y.size = 0;       sizeY = 0;
                }

                if (X.size > 0)
                    stackOfRun.push(X);
                if (Y.size > 0)
                    stackOfRun.push(Y);
                if (Z.size > 0)
                    stackOfRun.push(Z);

            } while ((sizeY <= sizeZ || (sizeX <= (sizeY + sizeZ))) && stackOfRun.getSize() > 2);

            while (stackOfRun.getSize() > 1)
            {
                RunPtrSize runPop = stackOfRun.pop();
                merge(stackOfRun.peek().runPtr, stackOfRun.peek().size, runPop.runPtr, runPop.size);
                RunPtrSize runInStack = stackOfRun.pop(); runInStack.size += runPop.size;
                stackOfRun.push(runInStack);
            }
        }
    }
}

void timsortGalloping(MyVector<int>& vector)
{
    int minRun = getMinrun(vector.getSize());
    int* pArr = vector.getArrPtr();
    int sizeArr = vector.getSize();

    MyStack<RunPtrSize> stackOfRun;

    int p = 0;										//pivit.
    RunPtrSize vectorStruct = { pArr, sizeArr };	//struct of vector.
    RunPtrSize run = { pArr, 2 };					//initializing run.

    while (p < sizeArr)
    {
        searchRun(vectorStruct, p, run, minRun);

        if (stackOfRun.getSize() < 1)
            stackOfRun.push(run);
        else if (stackOfRun.getSize() == 1)
        {
            if (stackOfRun.peek().size > run.size)
                stackOfRun.push(run);
            else
            {
                RunPtrSize runInStack = stackOfRun.pop();
                galloping(runInStack.runPtr, runInStack.size, run.runPtr, run.size);
                runInStack.size += run.size; stackOfRun.push(runInStack);
            }
        }
        else
        {
            stackOfRun.push(run);
            int sizeX = 0, sizeY = 0, sizeZ = 0;	//for cycle condition
            do
            {
                RunPtrSize Z = stackOfRun.pop();  sizeZ = Z.size;
                RunPtrSize Y = stackOfRun.pop();  sizeY = Y.size;
                RunPtrSize X = stackOfRun.pop();  sizeX = X.size;

                if ((Y.size <= Z.size || (X.size <= (Y.size + Z.size))) && Z.size <= X.size)
                {
                    galloping(Y.runPtr, Y.size, Z.runPtr, Z.size);
                    Y.size += Z.size; sizeY += sizeZ;
                    Z.size = 0;       sizeZ = 0;
                }
                if ((Y.size <= Z.size || (X.size <= (Y.size + Z.size))) && Z.size > X.size)
                {
                    galloping(X.runPtr, X.size, Y.runPtr, Y.size);
                    X.size += Y.size; sizeX += sizeY;
                    Y.size = 0;       sizeY = 0;
                }

                if (X.size > 0)
                    stackOfRun.push(X);
                if (Y.size > 0)
                    stackOfRun.push(Y);
                if (Z.size > 0)
                    stackOfRun.push(Z);

            } while ((sizeY <= sizeZ || (sizeX <= (sizeY + sizeZ))) && stackOfRun.getSize() > 2);

            while (stackOfRun.getSize() > 1)
            {
                RunPtrSize runPop = stackOfRun.pop();
                galloping(stackOfRun.peek().runPtr, stackOfRun.peek().size, runPop.runPtr, runPop.size);
                RunPtrSize runInStack = stackOfRun.pop(); runInStack.size += runPop.size;
                stackOfRun.push(runInStack);
            }
        }
    }
}

#endif
