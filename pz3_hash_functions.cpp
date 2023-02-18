#include <iostream>
#include <vector>
//#include <set>
#include <string>
#include <algorithm>
#include <time.h>


using namespace std;


int get_rand_number () {  // рандомное число в диапазоне [0; 35]

    return rand() % 36;
}


string get_rand_string(int n) // рандомная строка из [a..z;0..9]
{
    string result = "";
    int rand_number;
    for (int i = 0; i < n; i++) 
    {
        rand_number = get_rand_number();
        if (rand_number <= 9) {
            result.push_back(char(rand_number + 48)); // цифра
        } else 
        {
            result.push_back(char(rand_number + 87)); // буква
        }
    }
    return result;
}

long long get_hash(string s) // полиномиальное хэширование
{
    const int k = 41, mod = 1e9 + 307;
    long long h = 0, m = 1;
    for (char c : s) {
        int x = (c - 'a' + 1);
        h = (h + m * x) % mod;
        m = (m * k) % mod;
    }
    return h;
}


int main()
{
    vector <string> strings;
    vector <long long> hashes;
    //set <string> set_strings;
    string random_string;
    long long random_hash;
    int collisions = 0;

    for (int lenght = 3; lenght < 7; lenght++) // длина строк от 3 до 6
    {
        cout << "Длина строки: " << lenght << "\n";
        for (int i = 0; i < 2000; i++) 
        {
            random_string = get_rand_string(lenght);
            random_hash = get_hash(random_string);
            
            strings.push_back(random_string);
            //set_strings.insert(random_string);

            if (find(hashes.begin(), hashes.end(), random_hash) != hashes.end()) 
            {
                collisions++;
            }
            hashes.push_back(random_hash);
            // set_strings.insert(random_hash);
        }

        clock_t start = clock();  // измеряем время сравнения хэшей
        for (int i = 0; i < 2000; i++) 
        {
            for (int j = i + 1; j < 1999; j++) 
            {
                if (hashes[i] != hashes[j]) {}
            }
        }
        clock_t end = clock(); 
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "Время сравнения хэшей: "<< seconds << " s\n";


        start = clock();  // измеряем время сравнения строк поэлементно
        for (int i = 0; i < 2000; i++) 
        {
            for (int j = i + 1; j < 1999; j++) 
            {
                for (int k = 0; k < lenght; k++) 
                {
                    if (strings[i][k] != strings[j][k]) {}
                }
            }
        }
        end = clock(); 
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "Время сравнения строк: " << seconds << " s\n";

        
        cout << "Количество коллизий: " << collisions << "\n\n";
        //cout << strings.size() << "\t" << strings[1500] << endl;
        //cout << hashes.size() << "\t" << hashes[1500] << endl << endl;
        

        strings.clear();
        hashes.clear();
        //set_strings.clear();
        collisions = 0;
    }
    return 0;
}
