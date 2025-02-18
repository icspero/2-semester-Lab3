#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>
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
    vector<int> check;
    int X = 500;

    for (int i = 2; i <= X; i++){
        prime.push_back(i);
    }

    for (int i = 0; i < div.size(); i++) {
        for (int j = 2; j < prime.size(); j++){
            prime.erase(remove_if(prime.begin(), prime.end(), [&div, &i](int j) { return j % div[i] == 0 && j != div[i]; }), prime.end());
        }
    }

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

int main(){
    int n, t;
    srand(time(0));
    cout << "Enter the number: ";
    cin >> n;
    cout << "Enter t: ";
    cin >> t;

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
}