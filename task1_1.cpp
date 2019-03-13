#include <iostream>

void fill_array(int* array, const size_t& size) {
    for (size_t i = 0; i < size; ++i) {
        std::cin >> array[i];
    }
}

std::pair<size_t, size_t> max_sum(const int* array_one, const int* array_two, const size_t& size) {
    size_t right_index_one = 0, right_index_two = 0;
    size_t real_index_one = 0;

    for (size_t i = 1; i < size; ++i) {
        if ( array_one[real_index_one] < array_one[i] ) {
            real_index_one = i;
        }

        if (array_one[real_index_one] + array_two[i] > array_one[right_index_one] + array_two[right_index_two]) {
            right_index_one = real_index_one;
            right_index_two = i;
        }
    }

    return std::make_pair(right_index_one, right_index_two);
}

int main() {
    size_t size = 0;

    std::cin >> size;

    int* array_one = new int[size];
    int* array_two = new int[size];

    fill_array(array_one, size);
    fill_array(array_two, size);

    auto pair = max_sum(array_one, array_two, size);

    std::cout << pair.first << ' ' << pair.second;

    delete[] array_one;
    delete[] array_two;

    return 0;
}
