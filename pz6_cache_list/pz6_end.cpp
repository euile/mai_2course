#include <iostream>
#include <string>
using namespace std;


template <class Type>
struct LinkedList {

    LinkedList() : size(0), head(nullptr), tail(nullptr), instance(0) { }
    int get_inst() { return instance++; }
    size_t get_size() { return size; }
    void print_all() {
        Node<Type>* boof = head;
        while (boof != nullptr) {
            cout << boof->name << "\tdata: " << boof->data << "\tcount: " << boof->cache << endl;
            boof = boof->next;
        }

        cout << endl << endl;
    }
   

    ~LinkedList() {
        Node<Type>* boof = tail->prev;
        while (boof) {
            delete tail;
            tail = boof;
            boof = boof->prev;
        }
    }


    void push_back(Type data, string name_ = "default") {
        if (name_ == "default")
            name_ += to_string(get_inst());
        if (head == nullptr) {
            head = new Node<Type>(data, name_);
            tail = head;
        }
        else {
            tail->next = new Node<Type>;
            tail->next->prev = tail;
            tail = tail->next;
            tail->data = data;
            tail->name = name_;
        }
        ++size;
    }
    void push_front(Type data, string name_ = "default") {

        if (name_ == "default")
            name_ += to_string(get_inst());
        head = new Node<Type>(data, head, nullptr, name_);
        if (size == 1)
            tail = head->next;
        if (size == 0)
            tail = head;
        if (head->next != nullptr) {
            head->next->prev = head;
        }
        ++size;
    }


    Type* search_by_name(string name_) {
        Node<Type>* boof = head;
        while (boof != nullptr) {
            if (boof->name == name_) {
                break;
            }
            boof = boof->next;
        }
        if (!boof)
            return nullptr;
        boof->cache += 1;

        Node<Type>* boof2 = boof;
        while (boof2->prev != nullptr && boof2->prev->cache < boof->cache) {
            boof2 = boof2->prev;
        }
        swap_1(boof, boof2);
    }

private:
    template <class T>
    struct Node {
        Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr, string name = "", int cache_ = 0)
            : data(data), next(pNext), prev(pPrev), name(name), cache(cache_) {}
        Node(T data, string name) :data(data), next(nullptr), prev(nullptr), name(name), cache(0) {}
        Node* next;
        Node* prev;
        T data;
        string name;
        int cache;
    };
    Node<Type>* tail;
    Node<Type>* head;
    int instance;
    size_t  size;

    void swap_1(Node <Type>* a, Node<Type>* b) {
        if (a == b || a == nullptr || b == nullptr) { return; }

        if (a->next == b) {
            if (a->prev != nullptr) {
                b->prev = a->prev;
                a->prev->next = b;
            }
            else {
                b->prev = nullptr;
                head = b;
            }
            if (b->next != nullptr) {
                a->next = b->next;
                b->next->prev = a;
            }
            else {
                a->next = nullptr;
                tail = b;
            }
            b->next = a;
            a->prev = b;
            return;

        }
        else if (b->next == a) {
            swap_1(b, a);
            return;
        }

        if (a->prev == nullptr && b->next == nullptr) {
            b->next = a->next;
            a->next = nullptr;

            b->next->prev = b;
            b->prev->next = a;

            a->prev = b->prev;
            b->prev = nullptr;

            head = b;
            tail = a;
            return;
        }
        else if (b->prev == nullptr && a->next == nullptr) {
            swap_1(b, a);
            return;
        }

        if (a->prev != nullptr && b->next == nullptr) {
            b->next = a->next;
            a->next = b->prev;

            b->next->prev = b;
            b->prev = a->prev;
            a->prev = a->next;
            b->prev->next = b;
            a->prev->next = a;
            a->next = nullptr;
            tail = a;
            return;
        }
        else if (b->prev != nullptr && a->next == nullptr) {
            swap(b, a);
            return;
        }

        if (a->prev == nullptr && b->next != nullptr) {
            a->prev = b->prev;
            a->prev->next = a;
            b->prev = a->next;

            a->next = b->next;
            b->next = b->prev;
            b->next->prev = b;
            a->next->prev = a;
            b->prev = nullptr;
            head = b;
            return;
        }
        else if (b->prev == nullptr && a->next != nullptr) {
            swap_1(b, a);
            return;
        }

        Node<Type>* boof = a->prev;
        a->prev->next = b;
        b->prev->next = a;
        boof = a->prev;
        a->prev = b->prev;
        b->prev = boof;

        a->next->prev = b;
        b->next->prev = a;
        boof = a->next;
        a->next = b->next;
        b->next = boof;
    }
};

int main() {
    LinkedList <int> example;

    example.push_front(2204, "Alina");
    example.push_back(1602, "Sonya");
    example.push_back(408, "Yana");
    example.push_back(2203, "Gleb");
    example.push_back(2808, "Sasha");
    example.print_all();
    example.search_by_name("Sonya");
    example.search_by_name("Yana");
    example.search_by_name("Alina");
    example.print_all();
    example.search_by_name("Alina");
    example.search_by_name("Sonya");
    example.print_all();
    example.search_by_name("Alina");

    example.print_all();

    return 0;
    
}