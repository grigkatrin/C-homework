#include <iostream>

class safe_long_long_t {

private:
    long long value;

public:
    safe_long_long_t(long long temp) {
        value = temp;
    }

    safe_long_long_t(safe_long_long_t const &temp) {
        value = temp.value;
    }

    safe_long_long_t() {
        value = 0;
    }

    long long get_long() {
        return value;
    }

    void operator=(safe_long_long_t l1) {
        value = l1.value;
    }

    safe_long_long_t operator++() {
        return safe_long_long_t(++value);
    }

    safe_long_long_t operator++(int) {
        return safe_long_long_t(value++);
    }

    safe_long_long_t operator--() {
        return safe_long_long_t(--value);
    }

    safe_long_long_t operator--(int) {
        return safe_long_long_t(value--);
    }

    void operator+=(safe_long_long_t long1) {
        value += long1.value;
    }

    void operator-=(safe_long_long_t long1) {
        value -= long1.value;
    }

    void operator*=(safe_long_long_t long1) {
        value *= long1.value;
    }

    void operator/=(safe_long_long_t long1) {
        value /= long1.value;
    }

    void operator%=(safe_long_long_t long1) {
        value %= long1.value;
    }

    ~safe_long_long_t() = default;
};

safe_long_long_t operator+(safe_long_long_t l1, safe_long_long_t l2) {
    safe_long_long_t current = l1;
    current += l2;
    return current;
}

safe_long_long_t operator-(safe_long_long_t l1, safe_long_long_t l2) {
    safe_long_long_t current = l1;
    current -= l2;
    return current;
}

safe_long_long_t operator*(safe_long_long_t l1, safe_long_long_t l2) {
    safe_long_long_t current = l1;
    current *= l2;
    return current;
}

safe_long_long_t operator/(safe_long_long_t l1, safe_long_long_t l2) {
    safe_long_long_t current = l1;
    current /= l2;
    return current;
}

safe_long_long_t operator%(safe_long_long_t &l1, safe_long_long_t &l2) {
    safe_long_long_t current = l1;
    current %= l2;
    return current;
}

bool operator==(safe_long_long_t l1, safe_long_long_t l2) {
    return l1.get_long() == l2.get_long();
}

bool operator<(safe_long_long_t l1, safe_long_long_t l2) {
    return l1.get_long() < l2.get_long();
}

bool operator>(safe_long_long_t l1, safe_long_long_t l2) {
    return l1.get_long() > l2.get_long();
}

bool operator<=(safe_long_long_t l1, safe_long_long_t l2) {
    return l1.get_long() <= l2.get_long();
}

bool operator>=(safe_long_long_t l1, safe_long_long_t l2) {
    return l1.get_long() >= l2.get_long();
}

std::ostream &operator<<(std::ostream &s, safe_long_long_t l1) {
    s << l1.get_long();
    return s;
}

std::istream &operator>>(std::istream &s, safe_long_long_t &l1) {
    s >> l1;
    return s;
}

/*
int main() {
    safe_long_long_t ll = 10;
    std:: cout << ll;
    return 0;
}
 */