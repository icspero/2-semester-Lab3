#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

int canon(int n){
    

    return 0;
}

int main(){
    // Решето Эратосфена
    vector<int> div{2,3,5,7,11,13,17,19};
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

    int n;
    cout << "Enter the number: ";
    cin >> n;
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
        cout << i.first << " : " << i.second << endl;
    }
}