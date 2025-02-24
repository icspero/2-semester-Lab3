#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <map>
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

int canon(int n, vector<int> A){
    vector<int> prime = sieveEratosthenes(500);
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

int test_Miller(int n, int t){

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
        return false;
    }

    int res = canon(n, A);

    if (res == 1) {
        return true;
    }
    else {
        return false;
    }
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
    srand(time(0));
    vector<int> sieve = sieveEratosthenes(500); //решето простых
    int t = 5;
    int test_k = 3;
    int k;
    int m;
    int n;
    bool isPrime;
    vector<int> primeNums; 
    vector<int> primeLostCount; 
    vector<bool> primeTestAgree; 
    for (int l = 0; l < 10; l++){
        isPrime = false;
        k = 0;
        while (!isPrime){
            m = 1;
            for (int i = 0; i < 2; i++) {
                m *= pow(sieve[rand() % sieve.size()/4], (rand() % 2) + 1); 
            }
            n = 2 * m + 1;
            if (test_Miller(n, t)) {
                primeNums.push_back(n);
                isPrime = true;
                if (probability_Test(n, test_k)){
                    primeTestAgree.push_back(true);
                }
                else{
                    primeTestAgree.push_back(false);
                }
            }
            else{
                if (probability_Test(n, test_k)){
                    k++;
                }
            }
        }
        primeLostCount.push_back(k);
    }
    cout << setw(89) << "Тест Миллера" << endl;
    printTable(primeNums, primeTestAgree, primeLostCount);
}