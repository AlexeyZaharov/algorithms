/*
Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition реализуйте методом прохода двумя 
итераторами от начала массива к концу.
*/


#include <iostream>

template <typename T>
class my_comparator {
public:
    bool operator() (const T& one, const T& two) const {
        return one < two;
    }
};

template <typename T, typename _cmp = my_comparator<T>>
size_t choose_pivot(T* array, const size_t& beg, const size_t& end){
    _cmp cmp;
    size_t middle = (beg + end) / 2;

    size_t pos = 0;

    if ( cmp(array[beg], array[middle]) ) {
        if ( cmp(array[end], array[beg]) ) {
            pos = beg;
        }
        else {
            pos = cmp(array[end], array[middle]) ? end : middle;
        }
    }
    else {
        if ( cmp(array[end], array[middle]) ) {
            pos = middle;
        }
        else {
            pos = cmp(array[end], array[beg]) ? end : beg;
        }
    }

    return pos;
}

template <typename T, typename _cmp = my_comparator<T>>
size_t partition(T* array, const size_t& beg, const size_t& end){
    size_t pivot = choose_pivot(array, beg, end);
    _cmp cmp;

    std::swap(array[pivot], array[end]);

    size_t i = beg;
    for(size_t j = beg; j < end; ++j) {
        if(array[j] <= array[end]) {
            std::swap(array[i++], array[j]);
        }
    }

    std::swap(array[i], array[end]);

    return i;
}

template <typename T>
T kstat(const T* array, const size_t& size, size_t& k) {
    size_t beg = 0;
    size_t end = size - 1;
    size_t pos = 0;

    T buf[size];

    for (size_t i = 0; i < size; ++i) {
        buf[i] = array[i];
    }

    do {
        pos = partition(buf, beg, end);

        if (pos < k) {
            beg = pos + 1;
        }
        else if (pos > k) {
            end = pos - 1;
        }

    }
    while( pos != k);

    return buf[pos];
}

int main() {
    size_t size = 0;
    size_t k = 2;

    std::cin >> size >> k;

    if(size != 0) {
        int array[size];

        for(size_t i = 0; i < size; ++i) {
            std::cin >> array[i];
        }

        std::cout << kstat<int>(array, size, k);
    }
    else {
        std::cout << 0;
    }

    return 0;
}
