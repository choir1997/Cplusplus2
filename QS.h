#ifndef CS235_LAB_10_QS_H
#define CS235_LAB_10_QS_H
#include <iostream>
#include <sstream>

#include "QSInterface.h"

using namespace std;

template <typename T>
class QS : public QSInterface<T> {
private:
    size_t array_capacity;
    unsigned int array_index;
    size_t array_size;
    T* qsArray;
    size_t comparisonCount;
    size_t exchangeCount;
public:
    QS() : array_capacity(1), array_index(0), array_size(0), qsArray(new T[array_capacity]), comparisonCount(0), exchangeCount(0) {}
    ~QS() { deleteArray(); }

    bool setArray(const size_t& capacity) {
        if (capacity <= 0) {
            return false;
        }
        deleteArray();
        clear();
        array_capacity = capacity;
        qsArray = new T[array_capacity];
        return true;
    }

    size_t capacity() const {
        return array_capacity;
    }

    size_t size() const {
        return array_size;
    }

    bool clear() {
        array_size = 0;
        array_index = 0;
        return true;
    }

    void deleteArray() {
        delete[] qsArray;
        qsArray = NULL;
    }

    bool addElement(T element) {
        unsigned int i;
        i = array_index;
        if (array_size >= array_capacity) {
            reallocate();
        }
        qsArray[i] = element;
        array_index++;
        array_size++;
        return true;
    }

    void reallocate() {
        array_capacity = array_capacity * 2;
        T* new_data = new T[array_capacity];
        for (size_t i = 0; i < array_size; i++) {
            new_data[i] = qsArray[i];
        }
        deleteArray();
        qsArray = new_data;
    }

    bool sortAll() {
        return sort(0, array_size);
    }

    bool sort(size_t left, size_t right) {
        exchangeCount = 0;
        comparisonCount = 0;
        comparisonCount += right - left - 1;
        return recurseArray(left, right);
    }

    int medianOfThree(size_t left, size_t right);

    bool recurseArray(size_t left, size_t right);

    int partition(size_t left, size_t right, size_t pivotIndex);

    int statsArrayComparison() {
        return comparisonCount;
    }

    int statsArrayExchange() {
        return exchangeCount;
    }

    string toString() const {
        ostringstream outputString;
        if (array_size == 0) {
            outputString << "Empty";
        }
        for (unsigned int i = 0; i < array_size; i++) {
            if (i == array_size - 1) {
                outputString << qsArray[i];
                break;
            }
            outputString << qsArray[i] << ",";
        }
        return outputString.str();
    }

    friend ostream &operator<<(ostream &os, QS<T> &qs) {
        os << qs.toString();
        return os;
    }
};

template<typename T>
int QS<T>::medianOfThree(size_t left, size_t right) {
    size_t middleIndex;
    if ((left >= right) || array_size == 0 || left < 0 || right > array_size) {
        return -1;
    }
    middleIndex = (left + right) / 2;

    if (qsArray[middleIndex] < qsArray[left]) {
        comparisonCount++;
        swap(qsArray[left], qsArray[middleIndex]);
        exchangeCount++;
    }
    if (qsArray[right - 1] < qsArray[middleIndex]) {
        comparisonCount++;
        swap(qsArray[middleIndex], qsArray[right - 1]);
        exchangeCount++;
    }
    if (qsArray[middleIndex] < qsArray[left]) {
        comparisonCount++;
        swap(qsArray[left], qsArray[middleIndex]);
        exchangeCount++;
    }
    return middleIndex;
}

template<typename T>
bool QS<T>::recurseArray(size_t left, size_t right) {

    if (left == right - 1) {
        return true;
    }
    int pivotIndex = medianOfThree(left, right);
    if (pivotIndex == -1) {
        return false;
    }
    int newPivotIndex = partition(left, right, pivotIndex);
    if (newPivotIndex == -1) {
        return false;
    }
    recurseArray(left, newPivotIndex);
    recurseArray(newPivotIndex, right);

    return true;
}

template<typename T>
int QS<T>::partition(size_t left, size_t right, size_t pivotIndex) {

    if (right > array_size || left < 0 || array_size == 0 || left >= right || pivotIndex >= right) {
        return -1;
    }
    swap(qsArray[left], qsArray[pivotIndex]);

    size_t up = left + 1;
    size_t down = right - 1;

    do {
        comparisonCount ++;
        while ((up != right - 1) && !(qsArray[left] < qsArray[up])) {
            ++up;
        }
        while (qsArray[left] < qsArray[down]) {
            --down;
        }
        if (up < down) {
            swap(qsArray[up], qsArray[down]);
            exchangeCount++;
        }
    } while (up < down);

    swap(qsArray[left], qsArray[down]);
    exchangeCount = exchangeCount + 2;
    return down;
}

#endif //CS235_LAB_10_QS_H
