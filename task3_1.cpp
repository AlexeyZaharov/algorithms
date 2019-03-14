#include <iostream>
#include <cmath>

class my_queue {
private:
    int* buf;
    size_t capacity;
    size_t head;
    size_t tail;

    void resize(const size_t&& new_capacity) {
        if(capacity != 0) {
            size_t last_capacity = capacity;
            size_t new_tail = 0;
            capacity = new_capacity;

            int* new_buf = new int[capacity];

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
            buf = new int[capacity];
            head = 0;
            tail = 0;
        }
    }

public:
    my_queue() : buf(nullptr), capacity(0), head(0), tail(0) {}

    int push_back(const int& elem) {
        if ( capacity == 0 || (tail + 1) % capacity == head ) {
            resize(capacity*2);
        }

        tail = (tail + 1) % capacity;
        buf[tail] = elem;

        return elem;
    }

    int pop_front() {
        if ( capacity == 0) {
            return -1;
        }

        size_t last_head = head;
        int elem = buf[last_head];

        head = (head + 1) % capacity;

        if (last_head == tail) {
            delete[] buf;
            buf = nullptr;
            capacity = 0;
            head = tail = 0;
        }
        else if (head < tail) {
                if (tail - head + 1 <= int(capacity / 4)) {
                    resize(size_t(capacity / 2));
                }
            }
            else if (head > tail) {
                    if ((capacity - head) + (tail + 1) <= int(capacity / 4)) {
                        resize(size_t(capacity / 2));
                    }
                }
                else {
                    resize(1);
                }

        return elem;
    }

    ~my_queue(){
        delete[] buf;
    }
};

int main() {
    enum {NO, YES} success = YES;

    my_queue queue;
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
                    if (queue.pop_front() != pair.second) {
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
