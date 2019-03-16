#include <iostream>
#include <vector>

int binary_search(const int* array, const size_t beg, const size_t end, const int& value) {
    int index = -1;

    if (beg != end) {
        size_t middle = (beg+end)/2;

        if(array[middle] >= value) {
            index = binary_search(array, beg, middle, value);
        }
        else {
            index = binary_search(array, middle+1, end, value);
        }
    }
    else {
        if (array[beg] == value) {
            index = beg;
        }
    }

    return index;
}

void fill_array(int* array, const size_t& size) {
    for (size_t i = 0; i < size; ++i) {
        std::cin >> array[i];
    }
}

std::vector<int> find_intersection(const int* array_one, const size_t& size_1, const int* array_two, const size_t& size_2) {
    std::vector<int> vector;
    size_t new_beg = 0;
    size_t end = 0;

    for (size_t i = 0; i < size_2 && new_beg < size_1; ++i) {
        while(new_beg*new_beg < size_1 && array_two[i] > array_one[new_beg*new_beg]) {
            if(new_beg != 0)
            	new_beg *= 2;
        	else {
        		new_beg = 1;
        	}
        }
    	if (new_beg*new_beg < size_1){
        	end = new_beg*new_beg;
        }
        else {
    		end = size_1 - 1;
    	}
        int ind = binary_search(array_one, new_beg, end, array_two[i]);

        if (ind != -1) {
            vector.push_back(array_one[ind]);
        }
    }

    return vector;
}

int main() {
    size_t size_1 = 0, size_2 = 0;

    std::cin >> size_1;
    std::cin >> size_2;

    int* array_one = new int[size_1];
    int* array_two = new int[size_2];

    fill_array(array_one, size_1);
    fill_array(array_two, size_2);

    std::vector<int> vector = find_intersection(array_one, size_1, array_two, size_2);

    for (auto& i : vector) {
        std::cout << i << ' ';
    }

    delete[] array_one;
    delete[] array_two;

    return 0;
}
