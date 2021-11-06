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
void searchRun(int*& arrPtr, int& pivit, RunPtrSize& run, const int& minRun);
void timsort(MyVector<int>& vector);


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
	int pos = beg + (end - beg + 1) / 2;
	while ((arr[pos] > el) || (arr[pos + 1] <= el))
	{
		if (arr[pos] > el)
			end = pos;
		else if (arr[pos + 1] <= el)
			beg = pos;
		pos = beg + (end - beg + 1) / 2;
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

void searchRun(int*& arrPtr, int& pivit, RunPtrSize& run, const int& minRun)
{
	int* arrPtrPivit = arrPtr + pivit;
	int p = 1;
	int size = 2;

	if (arrPtrPivit[0] > arrPtrPivit[1])
	{
		while (arrPtrPivit[p] >= arrPtrPivit[p + 1]) { p++; }
		RunPtrSize runRev = { arrPtrPivit, p + 1 };
		reverse(runRev);
	}

	while (p < (minRun - 1))
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

	while (arrPtrPivit[p + 1] >= arrPtrPivit[p])
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
		while (i != begSize && j != nextSize)
		{
			if (tmpArr[i] <= nextArr[j])
			{
				begArr[count] = tmpArr[i];
				i++;
			}
			else
			{
				begArr[count] = nextArr[j];
				j++;
			}
			count++;
		}

		if (i != begSize)
		{
			for (int k = count; k < (nextSize + begSize); k++)
			{
				begArr[k] = tmpArr[i];
				i++;
			}
		}
		delete[] tmpArr;
	}
	else
	{
		int* tmpArr = new int[nextSize];

		memmove_s(reinterpret_cast<void*>(tmpArr), sizeof(int) * nextSize,
			reinterpret_cast<void*>(nextArr), sizeof(int) * nextSize);

		int i = nextSize - 1, j = begSize - 1, count = nextSize + begSize - 1;
		while (i != -1 && j != -1)
		{
			if (tmpArr[i] >= nextArr[j])
			{
				begArr[count] = tmpArr[i];
				i--;
			}
			else
			{
				begArr[count] = nextArr[j];
				j--;
			}
			count--;
		}

		if (i != -1)
		{
			for (int k = count; k > -1; k--)
			{
				begArr[k] = tmpArr[i];
				i--;
			}
		}
		delete[] tmpArr;
	}
}

void galloping(int* begArr, const int& begSize, int* nextArr, const int& nextSize)
{
	if (begSize <= nextSize)
	{
		int* tmpArr = new int[begSize];

		memmove_s(reinterpret_cast<void*>(tmpArr), sizeof(tmpArr),
			reinterpret_cast<void*>(begArr), sizeof(begArr));

		int i = 0, j = 0, count = 0;
		int conditionTmp = 0, conditionNext = 0;
		while (i < begSize && j < nextSize)
		{
			if (tmpArr[i] <= nextArr[j])
			{
				begArr[count] = tmpArr[i];
				i++; conditionTmp++;

				if (conditionTmp == 7 && tmpArr[i] <= nextArr[j])
				{
					int bin = 2, begin = i;
					while (tmpArr[i] <= nextArr[j])
					{
						i += bin; bin *= 2;
					}
					int lastPoint = binSearch(tmpArr, i - bin / 2, i, nextArr[j]);
					i = lastPoint + 1;

					memmove_s(reinterpret_cast<void*>(begArr + count), sizeof(int) * (lastPoint - begin + 1),
						reinterpret_cast<void*>(tmpArr + begin), sizeof(int) * (lastPoint - begin + 1));

					count += lastPoint - begin + 1;
					conditionTmp = 0;
				}
			}
			else
			{
				begArr[count] = nextArr[j];
				j++; conditionNext++;

				if (conditionNext == 7 && tmpArr[i] >= nextArr[j])
				{
					int bin = 2, begin = j;
					while (tmpArr[i] >= nextArr[j])
					{
						j += bin; bin *= 2;
					}
					int lastPoint = binSearch(nextArr, j - bin / 2, j, tmpArr[i]);
					j = lastPoint + 1;

					memmove_s(reinterpret_cast<void*>(begArr + count), sizeof(int) * (lastPoint - begin + 1),
						reinterpret_cast<void*>(nextArr + begin), sizeof(int) * (lastPoint - begin + 1));

					count += lastPoint - begin + 1;
					conditionNext = 0;
				}
			}
			count++;
		}

		if (i != begSize)
		{
			memmove_s(reinterpret_cast<void*>(begArr + count), sizeof(int) * (nextSize + begSize - count),
				reinterpret_cast<void*>(tmpArr + i), sizeof(int) * (nextSize + begSize - count));
		}
		delete[] tmpArr;
	}
	else
	{
		int* tmpArr = new int[nextSize];

		memmove_s(reinterpret_cast<void*>(tmpArr), sizeof(tmpArr),
			reinterpret_cast<void*>(nextArr), sizeof(nextArr));

		int i = nextSize - 1, j = begSize - 1, count = nextSize + begSize - 1;
		int conditionTmp = 0, conditionNext = 0;
		while (i > -1 && j > -1)
		{
			if (tmpArr[i] >= nextArr[j])
			{
				begArr[count] = tmpArr[i];
				i--; conditionTmp++;

				if (conditionTmp == 7 && tmpArr[i] >= nextArr[j])
				{
					int bin = 2, begin = i;
					while (tmpArr[i] >= nextArr[j])
					{
						i -= bin; bin *= 2;
					}
					int lastPoint = binSearch(tmpArr, i, i + bin / 2, nextArr[j]);
					i = lastPoint - 1;
					count -= begin - lastPoint + 1;

					memmove_s(reinterpret_cast<void*>(begArr + count), sizeof(int) * (begin - lastPoint + 1),
						reinterpret_cast<void*>(tmpArr + i), sizeof(int) * (begin - lastPoint + 1));

					conditionTmp = 0;
				}
			}
			else
			{
				begArr[count] = nextArr[j];
				j--; conditionNext++;

				if (conditionNext == 7 && tmpArr[i] <= nextArr[j])
				{
					int bin = 2, begin = j;
					while (tmpArr[i] <= nextArr[j])
					{
						j -= bin; bin *= 2;
					}
					int lastPoint = binSearch(nextArr, j, j + bin / 2, tmpArr[i]);
					j = lastPoint - 1;
					count -= begin - lastPoint + 1;

					memmove_s(reinterpret_cast<void*>(begArr + count), sizeof(int) * (begin - lastPoint + 1),
						reinterpret_cast<void*>(nextArr + j), sizeof(int) * (begin - lastPoint + 1));

					conditionNext = 0;
				}
			}
			count--;
		}

		if (i != -1)
		{
			memmove_s(reinterpret_cast<void*>(begArr), sizeof(int) * (count + 1),
				reinterpret_cast<void*>(tmpArr), sizeof(int) * (count + 1));
		}
		delete[] tmpArr;
	}
}

void timsort(MyVector<int>& vector)
{
	int minRun = getMinrun(vector.getSize());
	int* pArr = vector.getArrPtr();
	int sizeArr = vector.getSize();

	MyStack<RunPtrSize> stackOfArr;

	int p = 0;								//pivit.
	RunPtrSize run = { pArr + p, 2 };		//initializing run.

	while (p < sizeArr)
	{
		searchRun(pArr, p, run, minRun);

		if (stackOfArr.getSize() < 1)
			stackOfArr.push(run);
		else if (stackOfArr.getSize() == 1)
		{
			if (stackOfArr.peek().size > run.size)
				stackOfArr.push(run);
			else
			{
				merge(stackOfArr.peek().runPtr, stackOfArr.peek().size, run.runPtr, run.size);
				stackOfArr.peek() = { stackOfArr.peek().runPtr, stackOfArr.peek().size + run.size };
			}
		}
		else
		{
			int sizeX = 0, sizeY = 0, sizeZ = 0;	//for cycle condition
			do
			{
				RunPtrSize Y = stackOfArr.pop();  sizeY = Y.size;
				RunPtrSize X = stackOfArr.peek(); sizeX = X.size;
				RunPtrSize Z = run;				  sizeZ = Z.size;

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

				if (Y.size > 0)
					stackOfArr.push(Y);
				if (Z.size > 0)
					stackOfArr.push(Z);

			} while ((sizeY <= sizeZ || (sizeX <= (sizeY + sizeZ))) && stackOfArr.getSize() >= 2);
		}

		while (stackOfArr.getSize() > 1)
		{
			RunPtrSize runPop = stackOfArr.pop();
			merge(stackOfArr.peek().runPtr, stackOfArr.peek().size, runPop.runPtr, runPop.size);
			stackOfArr.peek() = { stackOfArr.peek().runPtr, stackOfArr.peek().size + runPop.size };
		}
	}

}
#endif
