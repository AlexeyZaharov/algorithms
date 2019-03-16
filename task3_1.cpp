#include <iostream>
#include <cmath>

template <typename T>
class my_queue {
private:
    T* buf;
    size_t capacity;
    size_t head;
    size_t tail;

    void resize(const size_t&& new_capacity);

public:
    my_queue() : buf(nullptr), capacity(0), head(0), tail(0) {}
    
    bool is_empty() {
        return capacity == 0;
    }

    T push_back(const T& elem);

    T pop_front();

    ~my_queue(){
        delete[] buf;
    }
};

int main() {
    enum {NO, YES} success = YES;

    my_queue<int> queue;
    size_t n = 0;

    std::cin >> n;

    if(n == 0) {
        success = NO;
    }

    for (size_t i = 0; i < n; ++i) {
        int command, value;

        std::cin >> command >> value;

        auto pair = std::make_pair(command, value);

        if (success == YES) {
            switch(pair.first) {
                case 2: {
                    int result;
                    if (queue.is_empty()) {
                        result = -1;
                    }
                    else {
                        result = queue.pop_front();
                    }

                    if (result != pair.second) {
                        success = NO;
                    }
                    break;
                }
                case 3: {
                    queue.push_back(pair.second);
                    break;
                }
            }
        }
    }

    success == YES ? std::cout << "YES" : std::cout << "NO";

    return 0;
}

template <typename T>
void my_queue<T>::resize(const size_t&& new_capacity) {
    if(capacity != 0) {
        size_t last_capacity = capacity;
        size_t new_tail = 0;
        capacity = new_capacity;

        T* new_buf = new T[capacity];

        if (head <= tail) {
            for (size_t i = 0, j = head; j <= tail; ++i, ++j) {
                new_buf[i] = buf[j];
                new_tail = i;
            }
        }
        else {
            for (size_t i = 0, j = head; j < last_capacity; ++i, ++j, ++new_tail) {
                new_buf[i] = buf[j];
            }
            for (size_t i = new_tail, j = 0; j <= tail; ++i, ++j) {
                new_buf[i] = buf[j];
                new_tail = i;
            }
        }

        delete[] buf;

        buf = new_buf;
        head = 0;
        tail = new_tail;
        capacity = new_capacity;
    }
    else {
        capacity = 1;
        buf = new T[capacity];
        head = 0;
        tail = 0;
    }
}

template <typename T>
T my_queue<T>::push_back(const T& elem) {
    if ( capacity == 0 || (tail + 1) % capacity == head ) {
        resize(capacity*2);
    }

    tail = (tail + 1) % capacity;
    buf[tail] = elem;

    return elem;
}

template <typename T>
T my_queue<T>::pop_front() {
    assert(is_empty() != true);

    size_t last_head = head;
    T elem = buf[last_head];

    head = (head + 1) % capacity;

    if (last_head == tail) {
        delete[] buf;
        buf = nullptr;
        capacity = 0;
        head = tail = 0;
    }
    else if (head < tail) {
        if (tail - head + 1 <= size_t(capacity / 4)) {
            resize(size_t(capacity / 2));
        }
    }
    else if (head > tail) {
        if ((capacity - head) + (tail + 1) <= size_t(capacity / 4)) {
            resize(size_t(capacity / 2));
        }
    }
    else {
        resize(1);
    }

    return elem;
}
