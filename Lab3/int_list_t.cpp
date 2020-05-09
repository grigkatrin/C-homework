#include "int_list_t.h"

int_list_t::int_list_t() {
    first = new node_t(0, nullptr, nullptr);
    last = new node_t(0, nullptr, first);
    first->next = last;
    list_size = 0;
}

int_list_t::node_t *int_list_t::get(int pos) const {
    if (pos <= list_size / 2) {
        node_t *current = int_list_t().first->next;
        while (pos > 0) {
            current = current->next;
            pos--;
        }

        return current;
    } else {
        node_t *current = int_list_t().last->prev;
        while (pos < list_size) {
            current = current->prev;
            pos++;
        }

        return current;
    }
}

int_list_t::int_list_t(const int_list_t &other) {
    list_size = other.list_size;
    auto current = other.first->next;
    int current_pos = 1;
    while (current != other.last) {
        insert(current_pos, current->value);
        current = current->next;
        current_pos++;
    }
}

int_list_t::int_list_t(size_t count, int value) {
    list_size = count;
    for (int i = 1; i < count; ++i) {
        push_back(value);
    }
}

int_list_t::~int_list_t() {
    node_t *current = first->next;
    while (current != last) {
        delete current->prev;
        current = current->next;
    }
    delete last;
}

int_list_t &int_list_t::operator=(const int_list_t &other) {
    if (this != &other) {
        int_list_t current(other);
        swap(current);
    }
    return *this;
}

int &int_list_t::operator[](size_t pos) {
    node_t *current = get(pos);
    return current->value;
}

const int &int_list_t::operator[](size_t pos) const {
    node_t *pointer = get(pos);
    return pointer->value;
}

int &int_list_t::back() {
    return last->prev->value;
}

const int int_list_t::back() const {
    return last->prev->value;
}

int &int_list_t::front() {
    return first->next->value;
}

const int int_list_t::front() const {
    return first->next->value;
}

size_t int_list_t::size() const {
    return list_size;
}

bool int_list_t::empty() const {
    return (list_size == 0);
}

void int_list_t::clear() {
    node_t *current = first->next;
    node_t *next_node = current->next;
    while (next_node != last) {
        delete (current);
        current = next_node;
        next_node = current->next;
    }
    delete (first);
    delete (last);
    list_size = 0;
}

void int_list_t::insert(size_t pos, int new_val) {
    node_t *current = get(pos);
    node_t *new_node = new node_t(new_val, current, current->prev);
    current->prev->next = new_node;
    current->prev = new_node;
    list_size++;
}

void int_list_t::push_front(int new_val) {
    node_t *current = new node_t(new_val, nullptr, nullptr);
    current->next = first->next;
    first->next = current;
    current->prev = first;
    list_size++;
}

void int_list_t::push_back(int new_val) {
    node_t *current = new node_t(new_val, nullptr, nullptr);
    current->prev = last->prev;
    current->next = last;
    last->prev = current;
    list_size++;
}

void int_list_t::erase(size_t pos) {
    node_t *current = get(pos);
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    list_size--;
}

void int_list_t::pop_front() {
    node_t *current = first->next;
    first->next = current->next;
    current->next->prev = first;
    delete current;
    list_size--;
}

void int_list_t::pop_back() {
    node_t *current = last->prev;
    current->prev->next = last;
    last->prev = current->prev;
    delete current;
    list_size--;
}

int_list_t int_list_t::splice(size_t start_pos, size_t count) {
    int_list_t result_list;
    node_t *current = get(start_pos);
    result_list.first->next = current;
    node_t *end_1 = current->prev;

    for (int i = 0; i < count - 1; i++) {
        current = current->next;
    }

    result_list.last->prev = current;
    node_t *end_2 = current->next;

    end_1->next = end_2;
    end_2->prev = end_1;

    list_size -= count;
    result_list.list_size = count;
    return result_list;
}

int_list_t &int_list_t::merge(int_list_t &other) {
    last->prev->next = other.first->next;
    other.first->next->prev = last->prev;
    other.last->prev->next = last;
    last->prev = other.last->prev;

    other.first->next = last;
    other.last->prev = first;
    list_size += other.list_size;
    other.list_size = 0;

    return *this;
}

void int_list_t::reverse() {
    node_t *current = first->next;
    node_t *next_node = current->next;
    while (next_node != last) {
        std::swap(current->next, current->prev);
        current = next_node;
        next_node = current->next;
    }
    first->next->prev = first;
    last->prev->next = last;
    std::swap(first->next, last->prev);
}

void int_list_t::swap(int_list_t &other) {
    std::swap(first, other.first);
    std::swap(last, other.last);
    std::swap(list_size, other.list_size);
}

std::istream &operator>>(std::istream &stream, int_list_t &list) {
    int value = 0;
    list.clear();
    while (stream >> value) {
        list.push_back(value);
    }
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const int_list_t &list) {
    auto current = list.first->next;
    while (current != list.last) {
        stream << current->value << " ";
        current = current->next;
    }
    return stream;
}