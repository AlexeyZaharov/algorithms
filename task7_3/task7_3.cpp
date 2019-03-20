/*
Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 106.
Отсортировать массив методом MSD по битам (бинарный QuickSort).
*/

#include <iostream>
#include <bitset>

template <typename T>
class my_comparator {
public:
    bool operator() (const T& elem, const size_t& ind) const {
        return ((elem >> (ind - 1)) & 1)  != 1;
    }
};

template <typename T, typename _cmp = my_comparator<T>>
size_t partition(T* array, const size_t& beg, const size_t& end, const size_t& bit){
    _cmp cmp;
    size_t i = beg;
    size_t j = end;

    while(true) {
        while(i < j && cmp(array[i], bit)) {
            ++i;
        }

        while(j > i && !cmp(array[j], bit)) {
            --j;
        }

        if(i < j) {
            std::swap(array[i], array[j]);
        }
        else {
            break;
        }
    }

    return i;
}

template <typename T, typename _cmp = my_comparator<T>>
void sorting(T* array, const size_t& beg, const size_t& end, const size_t& bit) {
    _cmp cmp;

    if(end - beg  + 1 <= 1 || bit == 0) {
        return;
    }

    size_t ind = partition<T, _cmp>(array, beg, end, bit);

    /*for (size_t i = 0; i < 3; ++i) {
        std::cout << std::bitset<sizeof(T)*8>(array[i]) << std::endl;
    }

    std::cout << std::endl << std::endl;*/

    if(ind != 0 && (ind != end || (ind == end && !cmp(array[ind], bit)))) {
        sorting<T, _cmp>(array, beg, ind - 1, bit - 1);
        sorting<T, _cmp>(array, ind, end, bit - 1);
    }
    else {
        sorting<T, _cmp>(array, beg, end, bit - 1);
    }
}

template <typename T, typename _cmp = my_comparator<T>>
void binary_msd_sort(T* array, const size_t& size) {
    sorting<T, _cmp>(array, 0, size - 1, sizeof(T)*8);
}

int main() {
    size_t size = 0;

    std::cin >> size;

    if(size != 0) {
        long long array[size];

        for(size_t i = 0; i < size; ++i) {
            std::cin >> array[i];
        }

        binary_msd_sort<long long>(array, size);

        for(size_t i = 0; i < size; ++i) {
            std::cout << array[i] << ' ';
        }
    }
    else {
        std::cout << 0;
    }

    return 0;
}
