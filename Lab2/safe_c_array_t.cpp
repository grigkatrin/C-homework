#include <iostream>

template<class T>
class safe_c_array_t {
private:
    T *array_t;
    size_t array_size;

public:
    explicit safe_c_array_t(size_t size) {
    	array_size = size;
        array_t = new T[size];
    }

    safe_c_array_t(const safe_c_array_t &current) {
    	array_size = current.array_size;
        array_t = new T[array_size];
        for (int i = 0; i < array_size; i++) {
            array_size[i] = current[i];
        };
    }

    void operator=(safe_c_array_t &current) {
        if (this != &current) {
            delete[] array_t;
            array_size = current.array_size;
            array_t = new T[array_size];
            for (int i = 0; i < array_size; i++) {
                array_size[i] = current[i];
            };
        };
    }

    const T operator[](int index) const {
        if (index < 0 || index >= array_size) {
            std::cout << "Index out of range";
            exit(-1);
        };

        return array_t[index];
    }

    T &operator[](int index) {
        if (index < 0 || index >= array_size) {
            std::cout << "Index out of range";
            exit(-1);
        };

        return array_t[index];
    }

    ~safe_c_array_t() {
        delete[] array_t;
    }
};

int main() {
    safe_c_array_t cur(10);
    cur[2] = 7;
    std::cout << cur[2];
    return 0;
}
