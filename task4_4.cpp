#include <iostream>
#include <cmath>

class my_heap {
private:
    int* buf;
    size_t cur_ind;

    void sift_up(size_t ind) {
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

    void sift_down(const size_t& ind) {
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

public:
    my_heap(const size_t& screen_size) : cur_ind(0) {
        buf = new int[screen_size];
    }

    void insert(const int& elem) {
        buf[cur_ind++] = elem;

        sift_up(cur_ind - 1);
    }

    int extract_max() {
        if(cur_ind != 0) {
            int max = buf[0];

            buf[0] = buf[--cur_ind];
            sift_down(0);

            return max;
        }
        else {
            throw;
        }
    }

    int peek_max() const {
        return buf[0];
    }

    ~my_heap(){
        delete[] buf;
    }
};

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

        my_heap heap(screen_size);
        for(size_t i = 0; i < screen_size - 1; ++i) {
            heap.insert(array[i]);
        }

        for (size_t i = screen_size - 1, j = 0; i < size; ++i, ++j) {
            heap.insert(array[i]);
            array_2[j] = heap.peek_max();
        }

        for (size_t i = 0; i < size - screen_size + 1; ++i) {
            std::cout << array_2[i] << ' ';
        }

        delete[] array_2;
    }


    delete[] array;


    return 0;
}
