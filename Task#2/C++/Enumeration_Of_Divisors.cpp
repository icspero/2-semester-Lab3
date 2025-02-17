#include <iostream>
#include <math.h>
using namespace std;

// Функция перебора делителей
int dividers(int num) {
	int k = 0;
	if (num == 1) {
		cout << "Not prime, not composite";
		return 0;
	}
	for (int i = 2; i <= sqrt(num); i++) {
		if (num % i == 0) {
			k += 1;
		}
	}
	if (k == 0) {
		cout << "Is prime";
	}
	else {
		cout << "Not prime";
	}
	return 0;
}

int main() {
	int num;
	cout << "Enter the number: ";
	cin >> num;
	dividers(num);
	return 0;
}
