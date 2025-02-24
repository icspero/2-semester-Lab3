#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <map>
#include <iomanip>
#include <random>

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
        int a = rand() % (num - 4) + 2;
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

int GOST_341094(int t, int q) {
    int n;
    int u;
    int p;
    bool isPrime = false;
    double e;
    do{
        e = rand();
        while (e > 1){
            e /= 10;
        }
        n = static_cast<int>(round(pow(2, t-1)/q) + round((pow(2,t-1) * e) / q));
        if (n % 2 == 1){
            ++n;
        }
        u = 0;
        while (!isPrime){
            p = (n + u) * q + 1;
            if (p > pow(2, t)){
                break;
            }
            if (powmod(2, p-1, p) == 1 && powmod(2, n+u, p) != 1){
                isPrime = true;
            }
            else{
                u += 2;
            }
        }
    }
    while(!isPrime);
    return p;
}

void printTable(const vector<int>& primeNums, const vector<bool>& primeTestAgree) {
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

}

int main(){
    srand(time(0));
    vector<int> sieve;
    vector<int> primeNums;
    vector<bool> primeTestAgree;
    // vector<int> T = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int t = 15;
    int q;
    int test_k = 3;
    for (int g = 0; g < 10; g++){
        // int t = T[g];
        sieve = sieveEratosthenes(pow(2, t/2));
        q = sieve[rand()%(sieve.size())];
        q = GOST_341094(t, q);
        primeNums.push_back(q);
        primeTestAgree.push_back(probability_Test(q, test_k));
    }
    cout << setw(85) << "ГОСТ Р 34.10-94" << endl;
    printTable(primeNums, primeTestAgree);
}

