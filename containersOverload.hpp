#ifndef CONTAINERS_OVERLOAD
#define CONTAINERS_OVERLOAD
#include <iostream>
#include <list>
#include <unordered_set>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << *it << ", ";
    }
    if (!v.empty()) {
        os << "\b\b";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& v) {
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << *it << ", ";
    }
    if (!v.empty()) {
        os << "\b\b";
    }
    os << "]";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::list<T>& v) {
    while (!is.eof()) {
        T value;
        is >> value;
        v.push_back(value);
        if (std::cin.get() == '\n') break;
    }
    return is;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::unordered_set<T>& v) {
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << *it << ", ";
    }
    if (!v.empty()) {
        os << "\b\b";
    }
    os << "]";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::unordered_set<T>& v) {
    while (!is.eof()) {
        T value;
        is >> value;
        v.insert(value);
        if (std::cin.get() == '\n') break;
    }
    return is;
}

#endif
