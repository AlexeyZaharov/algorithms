/*
4_4. Скользящий максимум.
Дан массив натуральных чисел A[0..n), n не превосходит 10^8. Так же задан размер 
некоторого окна (последовательно расположенных элементов массива) в этом массиве k, k<=n.
Требуется для каждого положения окна (от 0 и до n-k) вывести значение максимума в окне.

Скорость работы O(n log n), память O(n).

Формат входных данных. Вначале вводится n - количество элементов массива. Затем вводится n строк со значением каждого элемента. Затем вводится k  - размер окна.

Формат выходных данных. Разделенные пробелом значения максимумов для каждого положения окна.
*/

#include <iostream>
#include <cmath>

template <typename T>
class my_heap {
private:
    std::pair<T, size_t>* buf;
    size_t cur_ind;

    void sift_up(size_t ind);

    void sift_down(const size_t& ind);

public:
    my_heap(const size_t& screen_size) : cur_ind(0) {
        buf = new std::pair<T, size_t>[screen_size];
    }

    void insert(const std::pair<T, size_t>& elem);

    std::pair<T, size_t> extract_max();

    std::pair<T, size_t> peek_max() const {
        return buf[0];
    }

    ~my_heap(){
        delete[] buf;
    }
};


template <typename T>
int max_in_screen(my_heap<T>& heap, const size_t& screen_size, const size_t& i) {
    while (heap.peek_max().second < i - screen_size + 1) {
        heap.extract_max();
    }
    return heap.peek_max().first;
}

int main() {
    int* array;
    size_t size = 0;

    std::cin >> size;

    array = new int[size];

    for (size_t i = 0; i < size; ++i) {
        int elem;
        std::cin >> elem;
        array[i] = elem;
    }

    int* array_2;
    size_t screen_size = 0;

    std::cin >> screen_size;

    if (screen_size != 0) {
        array_2 = new int[size - screen_size + 1];

        my_heap<int> heap(size);
        for(size_t i = 0; i < screen_size - 1; ++i) {
            heap.insert(std::make_pair(array[i], i));
        }

        for (size_t i = screen_size - 1, j = 0; i < size; ++i, ++j) {
            heap.insert(std::make_pair(array[i], i));
            array_2[j] = max_in_screen(heap, screen_size, i);
        }

        for (size_t i = 0; i < size - screen_size + 1; ++i) {
            std::cout << array_2[i] << ' ';
        }

        delete[] array_2;
    }

    delete[] array;
    
    return 0;
}

template <typename T>
void my_heap<T>::sift_up(size_t ind) {
    while(ind > 0) {
        size_t parent = (ind - 1)/2;

        if (buf[ind] <= buf[parent]) {
            return;
        }
        else {
            std::swap(buf[ind], buf[parent]);
            ind = parent;
        }
    }
}

template <typename T>
void my_heap<T>::sift_down(const size_t& ind) {
    size_t left = 2*ind + 1;
    size_t right = 2*ind + 2;

    size_t largest = ind;

    if(left < cur_ind && buf[left] > buf[largest]) {
        largest = left;
    }
    if(right < cur_ind && buf[right] > buf[largest]) {
        largest = right;
    }

    if(largest != ind) {
        std::swap(buf[largest], buf[ind]);
        sift_down(largest);
    }
}

template <typename T>
void my_heap<T>::insert(const std::pair<T, size_t>& elem) {
    buf[cur_ind++] = elem;
    sift_up(cur_ind - 1);
}

template <typename T>
std::pair<T, size_t> my_heap<T>::extract_max() {
    if(cur_ind != 0) {
        std::pair<int, size_t> max = buf[0];

        buf[0] = buf[--cur_ind];
        sift_down(0);

        return max;
    }
    else {
        throw;
    }
}
