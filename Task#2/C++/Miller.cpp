#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
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
        //cout << "n - составное!" << endl;
        return 0;
    }

    int res = canon(n, A);

    if (res == 1) {
        //cout << "n - простое!" << endl;
        return 1;
    }
    else {
        //cout << "n - составное!" << endl;
        return 0;
    }
}

int generate_m(int bit) {

    srand(time(0));
    vector<int> M;
    
    for (int i = pow(2, bit - 2); i < pow(2, bit - 1); i++) {
        int res = test_Miller(i, 1);
        if (res == 0) {
            M.push_back(i);
        }
        else {
            continue;
        }
    
    }

    int temp = rand() % M.size();

    int m = M[temp];

    return m;
}

int main() {
    int bit;
    cout << "Bit: ";
    cin >> bit;
    int m = generate_m(bit);
    int n = 2 * m + 1;

    int res = test_Miller(n, 5);

    string str;
    if (res == 1) {
        str = " - простое!";
    }
    else {
        str = " - составное!";
    }


    cout << "n = " << n << str << endl;
}