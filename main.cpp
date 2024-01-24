#include <iostream>
#include <string>
#include <limits>
#include <sstream>

struct Node {
    int val;
    Node *next;

    Node(int _val) : val(_val), next(nullptr) {}
};

struct list {
    Node *first;
    Node *last;
    Node *last_non_zero = nullptr;

    list() : first(nullptr), last(nullptr) {}
    ~list() {
        if (is_empty()) return;
        Node *p = first;
        Node *n = nullptr;
        while (p) {
            n = p;
            p = p->next;
            delete n;
        }
    }

    bool is_empty() {
        return first == nullptr;
    }

    void push_zero() {
        Node *p = new Node(0);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }

    void push_non_zero(int _val) {
        Node *p = new Node(_val);
        if (is_empty()) {
            first = p;
            last = p;
        }
        else if (last_non_zero) {
            p->next = last_non_zero->next;
            last_non_zero->next = p;
        }
        else {
            p->next = first;
            first = p;
        }
        last_non_zero = p;
        if (!last_non_zero->next)
            last = p;
    }

    void print() {
        if (is_empty()) return;
        Node *p = first;
        while (p) {
            std::cout << p->val << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }
};

int main(int argc, char *argv[]) {

    int capacity;
    std::cin >> capacity;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string arr_str;
    std::getline(std::cin, arr_str);
    std::istringstream iss(arr_str);

    list l;

    int number;
    while (iss >> number) {
        if (number > 0) {
            l.push_non_zero(number);
        }
        else {
            l.push_zero();
        }
    }

    l.print();
}