#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <iomanip>

using namespace std;

int powmod(int a, int x, int mod){
    int res = 1;
    for (int i = 1; i <= x; i++){
        res = res * a;
        res = res % mod;
    }
    return res;
}

vector<int> sieveEratosthenes(int n) {
    vector<bool> is_prime(n + 1, true);
    vector<int> primes;
    
    is_prime[0] = is_prime[1] = false; // 0 и 1 не являются простыми
    
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false; // отмечаем все кратные i как составные
            }
        }
    }
    
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

bool probability_Test(int num, int k){ // Миллер-Рабин
    if (num == 2 || num == 3){
        return true;
    }
    if (num < 2 || num % 2 == 0){
        return false;
    }
    int s = 0;
    int d = num-1;
    while (d % 2 == 0){
        d /= 2;
        s++;
    }
    for (int i = 0; i < k; i++){
        int a = rand() % (num - 4) + 2; // от 2 до num - 2
        int x = powmod(a, d, num);
        int y;
        for (int j = 0; j < s; j++){
            y = powmod(x, 2, num);
            if (y == 1 && x != 1 && x != (num - 1)) {
                return false;
            }
            x = y;
        }
        if (y != 1) {
            return false;
        }
    }
    return true;
}

int NOD(int a, int p) {     // проверка на взаимно простые числа
    while (p != 0) {        // поиск НОД (обобщенный алгоритм Евклида)
        int r = p;          // a и r переносят числа
        p = a % p;          // каждую итерацию после первой берем остаток от пред. делителя и остатка
        a = r;              // a%b = c >> b%c = g >> c%g = d
    }
    return a;
}

vector<int> canon(int n) {
    vector<int> prime = sieveEratosthenes(2000);
    vector<int> q;
    int N = n - 1;

    for (int i = 0; i < prime.size(); i++){
        int R = N;
        int k = 0;
        if (R % prime[i] == 0){
            while(R % prime[i] == 0){
                R /= prime[i];
                k += 1;
            }
            for (int j = 0; j < k; j++) {
                q.push_back(prime[i]);
            }
        }
        else {
            continue;
        }
    }

    int r, f;
    vector<int> F;

    while (true) {
        int r = 1;
        int f = 1;
        
        F.push_back(q[q.size()-1]);
        q.pop_back();

        for(int i = 0; i < F.size(); i++) {
            f = f * F[i];
        }

        for (int i = 0; i < q.size(); i++){
            r = r * q[i];
        }

        if (f > r && r % 2 == 0) {
            return F;
        }
        else {
            continue;
        }
    }
}

int test_Poclington(int n, int t) {
    vector<int> A;
    vector<int> check;

    if (n == 1 || n == 0) {
        return false;
    }

    vector<int> prime = sieveEratosthenes(8);
    for (int i = 0; i < prime.size(); i++) {
        if (n == prime[i]) {
            return true;
        }
    }

    for (int i = 0; i < t; i++){
        A.push_back(rand() % (n - 2) + 2);
    }

    for (int i = 0; i < A.size(); i++) {
        int res = powmod(A[i], n - 1, n);
        if (res != 1) {
            return false;
        }
    }

    vector<int> F = canon(n);

    for (int i = 0; i < A.size(); i++) {
        int temp_a = A[i]; 
        for (int i = 0; i < F.size(); i++) {
            int res = powmod(temp_a, (n - 1)/F[i], n);
            if (res == 1) {
                break;
            }
            else {
                check.push_back(res);
            }
        }
    }

    for (int i = 0; i < check.size(); i++) {
        if (check[i] == 1) {
            return false;
        }
        else {
            return true;
        }
    }

    return false;
}

int bitLen(int number){
    int bitCount = 0;
    while (number != 0){
        bitCount++;
        number /= 2;
    }
    return bitCount;
}

void printTable(const vector<int>& primeNums, const vector<bool>& primeTestAgree, const vector<int>& primeLostCount) {
    int n = primeNums.size();
    int colWidth = 12;

    auto printLine = [&](int count) {
        cout << "+";
        for (int i = 0; i <= count; i++) {
            cout << string(colWidth, '-') << "+";
        }
        cout << endl;
    };

    printLine(n);
    cout << "| " << setw(colWidth + 1) << left << "№";
    for (int i = 0; i < n; i++) {
        cout << "| " << setw(colWidth - 1) << left << i + 1;
    }
    cout << "|" << endl;

    printLine(n);

    cout << "| " << setw(colWidth - 1) << left << "P";
    for (int num : primeNums) {
        cout << "| " << setw(colWidth - 1) << left << num;
    }
    cout << "|" << endl;
    printLine(n);

    cout << "| " << setw(colWidth + 3) << left << "Тест";
    for (bool result : primeTestAgree) {
        cout << "| " << setw(colWidth - 1) << left << (result ? "+" : "-");
    }
    cout << "|" << endl;
    printLine(n);

    cout << "| " << setw(colWidth - 1) << left << "K";
    for (int k : primeLostCount) {
        cout << "| " << setw(colWidth - 1) << left << k;
    }
    cout << "|" << endl;
    printLine(n);

}

int main() {

    int t = 5;
    int test_k = 3;
    int m;
    int r;
    bool isPrime;
    int k;
    vector<int> primeNums;
    vector<int> primeLostCount;
    vector<bool> primeTestAgree;
    for (int g = 0; g < 10; g++){
        isPrime = false;
        k = 0;
        while(!isPrime){
            random_device rd;
            mt19937 gen(rd());

            // генерация случайного числа в диапазоне (6, 16)
            uniform_int_distribution<> bitDist(6, 16);
            int bit = bitDist(gen);

            int F = 1;
            vector<int> sieve = sieveEratosthenes(500);

            // генерация F
            uniform_int_distribution<> sieveDist(0, sieve.size() - 1);
            while (F < pow(2, bit / 2) || F > pow(2, bit / 2 + 1)) {
                int temp = sieveDist(gen);
                F = F * sieve[temp];

                if (F > pow(2, bit / 2 + 1)) {
                    F = 1;
                }
            }

            // генерация n
            int n = 0;
            uniform_int_distribution<> nDist(pow(2, bit / 2 - 1), pow(2, bit / 2) - 1);
            for (int r = nDist(gen); r < pow(2, bit / 2); ++r) {
                if (r % 2 == 0) {
                    n = r * F;
                    if (bitLen(n) == bit) {
                        n = n + 1;
                        break;
                    }
                }
            }
            int proverka = 0;
            for (int i = 0; i < primeNums.size(); i++) {
                if (primeNums[i] == n) {
                    proverka += 1;
                }
            }

            if (proverka != 0) {
                continue;
            }

            if (n != 1 && test_Poclington(n, t)) {
                primeNums.push_back(n); 
                isPrime = true;
                if (probability_Test(n, test_k)){ 
                    primeTestAgree.push_back(true);
                }
                else{
                    primeTestAgree.push_back(false);
                }
            }
            else {
                if (probability_Test(n, test_k)){ 
                    k++;
                }
            }
        }
        primeLostCount.push_back(k);
    }

    cout << setw(95) << "Тест Поклингтона" << endl;
    printTable(primeNums, primeTestAgree, primeLostCount);
}