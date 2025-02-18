#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;

int powmod(int a, int x, int mod){
    int res = 1;
    for (int i = 1; i <= x; i++){
        res = res * a;
        res = res % mod;
    }
    return res;
}

int canon(int n, vector<int> A){
    // Решето Эратосфена
    vector<int> div{2, 3, 5, 7, 11, 13, 17, 19};
    vector<int> prime;
    
    int X = 500;

    for (int i = 2; i <= X; i++){
        prime.push_back(i);
    }

    for (int i = 0; i < div.size(); i++) {
        for (int j = 2; j < prime.size(); j++){
            prime.erase(remove_if(prime.begin(), prime.end(), [&div, &i](int j) { return j % div[i] == 0 && j != div[i]; }), prime.end());
        }
    }
    
    vector<int> check;
    map<int, int> q;
    int N = n - 1;

    for (int i = 0; i < prime.size(); i++){
        int R = N;
        int k = 0;
        if (R % prime[i] == 0){
            while(R % prime[i] == 0){
                R /= prime[i];
                k += 1;
            }
            q.insert({prime[i], k});
        }
        else {
            continue;
        }
    }

    for (auto i : q) {
        for (int j = 0; j < A.size(); j++){
            int res = (powmod(j, ((n - 1)/i.first), n));
            check.push_back(res);
            if (res != 1){
                break;
            }
        }
    }

    for (int i = 0; i < check.size(); i++){
        if (check[i] != 1){
            return 1;
        }
    }

    return 0;
}

int test(int n, int t){

    vector<int> A;

    for (int i = 0; i < t; i++){
        A.push_back(rand() % (n - 2) + 2);
    }

    int k = 0;
    for (int i = 0; i < A.size(); i++){
        int res = powmod(A[i], n - 1, n);
        k += res;
    }

    if (A.size() != k){
        cout << "n - составное!" << endl;
        return 0;
    }

    int res = canon(n, A);

    if (res == 1) {
        cout << "n - простое!" << endl;
    }
    else {
        cout << "n - составное!" << endl;
    }

    return 0;
}

int generate_m(const vector<int>& prime, int bit) {
    srand(time(0));

    int max = pow(2, bit) - 1; // максимальное значение для n
    int min = pow(2, bit - 1); // минимальное значение для n
    int m_max = (min - 1) / 2; // максимальное значение для m, учитывая n = 2m + 1

    bool flag = false;
    int m;

    while (!flag) {
        int temp = 1;
        
        // Генерация числа m
        for (int i = 0; i < bit / 2; i++) {
            int alpha = rand() % (bit / 2) + 1;  // случайная степень
            for (int j = 0; j < alpha; j++) {
                temp *= prime[i];  // возведение простого числа в степень alpha
                if (temp > m_max) { // Если m выходит за пределы, прерываем цикл
                    break;
                }
            }
            if (temp > m_max) {
                break;
            }
        }

        // Проверка, что m попадает в нужный диапазон
        if (temp >= min / 2 && temp <= m_max) {
            m = temp;
            flag = true;
        }
    }

    return m;
}

int main() {
    // Решето Эратосфена
    vector<int> div{2, 3, 5, 7, 11, 13, 17, 19};
    vector<int> prime;
    
    int X = 500;

    for (int i = 2; i <= X; i++){
        prime.push_back(i);
    }

    for (int i = 0; i < div.size(); i++) {
        for (int j = 2; j < prime.size(); j++){
            prime.erase(remove_if(prime.begin(), prime.end(), [&div, &i](int j) { return j % div[i] == 0 && j != div[i]; }), prime.end());
        }
    }

    int bit;
    map<int, int> res;
    
    cout << "Размер в битах: "; 
    cin >> bit;

    int m = generate_m(prime, bit);

    int n = 2 * m + 1;

    cout << "Полученное n: " << n << endl;
}