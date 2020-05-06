#include "int_list_t.h"

int_list_t::int_list_t() {
    list_size = 0;
}

int_list_t::node_t *int_list_t::get(int pos) const {
    if (pos <= list_size / 2) {
        node_t *current = int_list_t().first;
        while (pos > 0) {
            current = current->next;
            pos--;
        }

        return current;
    } else {
        node_t *current = int_list_t().last;
        while (pos < list_size) {
            current = current->prev;
            pos++;
        }

        return current;
    }
}

int_list_t::int_list_t(const int_list_t &other) {
    list_size = other.list_size;
    first = new node_t(other.first->value, nullptr, nullptr);
    last = new node_t(other.last->value, first, nullptr);
    first->next = last;
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
    first = new node_t(value, nullptr, nullptr);
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
    delete current;
}

int_list_t &int_list_t::operator=(const int_list_t &other) {
    if (this != &other) {
        const int_list_t &current(other);
        return const_cast<int_list_t &>(current);
    } else {
        return *this;
    }
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
    return last->value;
}

const int &int_list_t::back() const {
    return last->value;
}

int &int_list_t::front() {
    return first->value;
}

const int &int_list_t::front() const {
    return first->value;
}

size_t int_list_t::size() const {
    return list_size;
}

bool int_list_t::empty() const {
    return (list_size != 0) ? 'TRUE' : 'FALSE';
}

void int_list_t::clear() {
    node_t *current = first;
    node_t *next_node = current->next;
    while (next_node != last) {
        delete (current);
        current = next_node;
        next_node = current->next;
    }
    delete (current);
    delete (next_node);
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
    current->next = first;
    first->prev = current;
    first = current;
    list_size++;
}

void int_list_t::push_back(int new_val) {
    node_t *current = new node_t(new_val, nullptr, nullptr);
    current->prev = last;
    last->next = current;
    last = current;
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
    node_t *current = first;
    first->next->prev = nullptr;
    first = current->next;
    delete current;
    list_size--;
}

void int_list_t::pop_back() {
    node_t *current = last;
    last->prev->next = nullptr;
    last = current->prev;
    delete current;
    list_size--;
}

void int_list_t::reverse() {
    node_t *current = first;
    node_t *next_node = current->next;
    while (next_node != last) {
        std::swap(current->next, current->prev);
        current = next_node;
        next_node = current->next;
    }
    std::swap(current->next, current->prev);
    std::swap(next_node->next, next_node->prev);
}