/*
5_1. Реклама.

В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа).
Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать только в целочисленные моменты
времени. Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно.
Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть. Требуется
определить минимальное число показов рекламы.
*/


#include <iostream>

template <typename T>
class my_comparator {
public:
    bool operator() (const T& one, const T& two) const {
        return (one.second < two.second) ||
                (one.second == two.second && one.first < two.first);
    }
};

template <typename T, typename _cmp = my_comparator<T>>
void merge(T* array, const size_t& size_one, size_t& size_two){
    T* buf = new T[size_one];
    _cmp cmp;

    for (size_t i = 0; i < size_one; ++i) {
        buf[i] = array[i];
    }

    size_t ind_one = 0, ind_two = 0, cur = 0;

    while(ind_one < size_one && ind_two < size_two) {
        if (cmp( buf[ind_one], array[size_one + ind_two] )) {
            array[cur++] = buf[ind_one++];
        }
        else {
            array[cur++] = array[size_one + ind_two++];
        }
    }

    if (ind_one == size_one) {
        while (ind_two < size_two) {
            array[cur++] = array[size_one + ind_two++];
        }
    }
    else {
        while (ind_one < size_one) {
            array[cur++] = buf[ind_one++];
        }
    }
}

template <typename T>
void merge_sort(T* array, const size_t& size) {
    if(size <= 1) {
        return;
    }

    size_t size_of_first_part = size/2;
    size_t size_of_second_part = size - size_of_first_part;

    merge_sort(array, size_of_first_part);
    merge_sort(array + size_of_first_part, size_of_second_part);

    merge(array, size_of_first_part, size_of_second_part);
}

template <typename T>
size_t number_of_advertising(const std::pair<T, T>* array, const size_t& size) {
    size_t ind = 0, num = 2;
    std::pair<T, T> unique_array[size];

    for(size_t i = 0; i < size; ++i) {
        if (array[i].second == array[i+1].second) {
            continue;
        }
        else {
            unique_array[ind++] = array[i];
        }
    }

    size_t last_advertising = unique_array[0].second;
    size_t before_last_advertising = unique_array[0].second - 1;

    for(size_t i = 1; i < ind; ++i) {
        num += 2;
        if (unique_array[i].first <= before_last_advertising) {
            num -= 2;
        }
        else if (unique_array[i].first <= last_advertising) {
            --num;
            before_last_advertising = last_advertising;
        }
        else {
            last_advertising = unique_array[i].second;
            before_last_advertising = unique_array[i].second - 1;
        }
    }

    //for( size_t i = 0; i < ind; ++i) {
    //    std::cout << "(" << unique_array[i].first << ", " << unique_array[i].second << ") ";
    //}

    //std::cout << std::endl;

    return num;
}

int main() {
    size_t size = 0;

    std::cin >> size;

    if(size != 0) {
        std::pair<int, int> array[size];

        for(size_t i = 0; i < size; ++i) {
            std::cin >> array[i].first >> array[i].second;
        }

        merge_sort<std::pair<int, int>>(array, size);

        std::cout << number_of_advertising(array, size);
    }
    else {
        std::cout << 0;
    }

    return 0;
}
