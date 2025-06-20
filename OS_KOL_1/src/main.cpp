#include <iostream>
#include <vector>
#include <unordered_set>
#include <stdexcept>

class FactorialCalculator {
public:
    static std::vector<unsigned long long> first_n_factorials(int n) {
        if (n < 1) {
            throw std::invalid_argument("n должно быть натуральным числом больше 0.");
        }
        std::vector<unsigned long long> factorials(n);
        factorials[0] = 1; // 0! = 1
        for (int i = 1; i < n; ++i) {
            factorials[i] = factorials[i - 1] * (i + 1);
        }
        return factorials;
    }
};

class UniqueElements {
public:
    static std::vector<int> remove_duplicates(const std::vector<int>& input) {
        std::unordered_set<int> seen;
        std::vector<int> unique_elements;

        for (int num : input) {
            if (seen.insert(num).second) {
                unique_elements.push_back(num);
            }
        }
        return unique_elements;
    }
};

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    Node* reverseUtil(Node* node) {
        if (!node || !node->next) {
            return node;
        }
        Node* rest = reverseUtil(node->next);
        node->next->next = node;
        node->next = nullptr;
        return rest;
    }

public:
    LinkedList() : head(nullptr) {}

    void insert(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void reverse() {
        head = reverseUtil(head);
    }

    void display() const {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    // Пример использования

    // Факториалы
    int n = 5;
    try {
        std::vector<unsigned long long> factorials = FactorialCalculator::first_n_factorials(n);
        std::cout << "Первые " << n << " факториалов: ";
        for (auto f : factorials) {
            std::cout << f << " ";
        }
        std::cout << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    // Удаление дубликатов
    std::vector<int> input = { 1, 2, 2, 3, 4, 4, 5 };
    std::vector<int> unique = UniqueElements::remove_duplicates(input);
    std::cout << "Массив без дубликатов: ";
    for (auto u : unique) {
        std::cout << u << " ";
    }
    std::cout << std::endl;

    // Связный список
    LinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);

    std::cout << "Исходный список: ";
    list.display();

    list.reverse();
    std::cout << "Развернутый список: ";
    list.display();

    return 0;
}