#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <cmath>


using namespace std;


class Array {
protected:

    int size;
    int* mass;

public:
    void print() {  // вывод элементов
        for (int i = 0; i < size; i++) {
            cout << mass[i] << "\t";
        }
        cout << endl;
    }

    Array(int n=3) {  // конструктор с параметром
        size = n;
        mass = new int[size];
        for (int i = 0; i < n; i++) {
            mass[i] = i;
        }
    }

    Array(const Array& other) // конструктор копирования
    {
        size = other.size;
        mass = new int[size];
        for (int i = 0; i < size; i++)
        {
            mass[i] = other.mass[i];
        }
    }

    Array& operator=(const Array& other) {  // перегрузка оператора присваивания
        size = other.size;
        if (mass) {
            delete[] this->mass;
        }
        mass = new int[other.size];
        for (int i = 0; i < other.size; i++) {
            mass[i] = other.mass[i];
        }
    }

    ~Array() {  // деструктор
        delete[] mass;
    }

    void set_elem(int n, int value) {  // сеттер
        if (value < -100 | value > 100) {
            throw invalid_argument("Элемент больше 100 или меньше -100!\n");
        }
        else if (n > size - 1) {
            throw out_of_range("Вы превысели размер массива!\n");
        }
        mass[n] = value;
        cout << "Элемент добавлен!\n";
    }

    int get_elem(int n) {  // геттер
        if (n < 0 | n >= size) {
            throw out_of_range("Такого элемента не существует!\n");
        }
        return mass[n];
    }

    void push_back(int elem) {  // добавление элемента в конец массива
        if (elem > 100 || elem < -100) {
            throw out_of_range("Элемент больше 100 или меньше -100!\n");
        }
        int* new_mass = new int[size + 1];
        for (int i = 0; i < size; i++) {
            new_mass[i] = mass[i];
        }
        new_mass[size] = elem;
        delete[] mass;
        mass = new_mass;
        size++;
        cout << "Элемент добавлен в конец списка!\n";
    }

    Array operator +(const Array &other) {  // перегрузка оператора сложения
        if (mass && other.mass && size == other.size) {
            Array temp(other.size);
            temp.size = size;
            for (int i = 0; i < size; i++) {
                temp.mass[i] = mass[i] + other.mass[i];
            }
            return temp;
        }
    }

    Array operator -(const Array &other) {  // перегрузка оператора вычитания
        if (mass && other.mass && size == other.size) {
            Array temp(other.size);
            temp.size = size;
            for (int i = 0; i < size; i++) {
                temp.mass[i] = mass[i] - other.mass[i];
            }
            return temp;
        }
    }
    friend ostream& operator<<(ostream& os, const Array& a) {
        string temp = "[";
        for (int i = 0; i < a.size - 1; i++) {
            temp += to_string(a.mass[i]) + ", ";
        }
        temp += to_string(a.mass[a.size - 1]) + ']';

        return os << "Массив длиной: " << a.size << endl << temp << endl;
    } 
};

// Template class

template <class T>  
class Temp {
protected:
    int size;
    int* buf;

public: 
  
    Temp(int n=10) { // конструктор
        size = n;
        buf = new int[size];
    }

    ~Temp() {  // деструктор
        delete[] buf;
    }

    void set_elem(int m, T value) {  // сеттер
        if (m > size - 1) {
            throw out_of_range("Вы превысели размер массива!\n");
        }
        buf[m] = value;
        cout << "Элемент добавлен в список!\n";
    }
    
    template <int>  // сеттер для целочисленного списка
    void set_elem(int m, int value) {
        if (m > size - 1) {
            throw out_of_range("Вы превысели размер массива!\n");
        }
        buf[m] = value;
        cout << "Элемент добавлен в список!\n";
    }
    
    void dist_vectors(T a1, T a2) {  // расстояние между векторами не из целых чисел
        throw logic_error("Вектор должен состоять из целых чисел!\n");
    }

    template <int>  // расстояние между векторами из целых чисел 
    int dist_vectors(T a1, T a2) {
        if (a1.size() != a2.size()) {
            throw out_of_range("Векторы разной длины!\n");
        }
        int n = 0;
        for (int i = 0; i < a1.size(); i++) {
            n += pow((a2[i] - a1[i]), 2);
        }
        n = sqrt(n);
        return n;
    }

    Temp& operator=(const Temp& other) {  // перегрузка оператора присваивания
        size = other.size;
        if (buf) {
            delete[] this->buf;
        }
        buf = new int[other.size];
        for (int i = 0; i < other.size; i++) {
            buf[i] = other.buf[i];
        }
    }

    T get_elem(int m) {  // геттер
        if (m > size - 1) {
            throw out_of_range("Вы превысели размер массива!\n");
        }
        return buf[m];
    }

    friend ostream& operator<<(ostream& os, const Temp& a) {  // операция вывода
        string temp = "[";
        for (int i = 0; i < a.size - 1; i++) {
            temp += to_string(a.buf[i]) + ", ";
        }
        temp += to_string(a.buf[a.size - 1]) + ']';

        return os << "Массив длиной: " << a.size << endl << temp << endl;
    }
};



int main()
{
    setlocale(LC_ALL, "ru");

    int n;
    cout << "Введите размер массива а!" << endl;
    cin >> n;

    Array p;
    Array a(n);
    a.print();

    Array b = a;
    b.print();

    a.set_elem(2, 8);
    a.push_back(99); 
    cout << "список a:" << endl;
    a.print();

    b.push_back(9);
    cout << "список b:" << endl;
    b.print();

    Array c = a + b;
    cout << "список с:" << endl;
    c.print();

    Temp<int> shablon1(2);
    shablon1.set_elem(0, 1);
    shablon1.set_elem(1, 1);

    /*
    try {
        a.get_elem(12);
        a.set_elem(2, 67);
        a.set_elem(69, 3);
        cout << a;
        a.set_elem(5, 1200);
    }
    catch (const out_of_range &message) {
        cout << message.what();
    }
    catch (const invalid_argument & message) {
        cout << message.what();
    }
    catch (const bad_alloc & message) {
        cout << "Ошибка выделения памяти!";
    }
    catch (const logic_error & message) {
        cout << message.what();
    }
    */

    return 0;
}