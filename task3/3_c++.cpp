#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long long gcd(long long a, long long b) {
    while (b > 0) {
        a %= b;
        swap(a, b); }
    return a;
}

long long power(long long base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; i++) res *= base;
    return res;
}

int main() {
    int a, b;
    if (!(cin >> a >> b)) return 0;
    if (b == 1) {
        cout << "infinity" << endl;
        return 0;
    }

    vector<long long> c(a + 1, 0);
    c[1] = 1;

    for (int k = 1; k < a; ++k) {
        vector<long long> next_c(a + 1, 0);
        for (int i = 1; i <= k; ++i) {
            next_c[i] += i * c[i];
            if (i + 1 <= a) {
                next_c[i + 1] += (k + 1 - i) * c[i];
            }
        }
        c = next_c;
    }

    long long numerator = 0;
    for (int i = 1; i <= a; ++i) {
        numerator += c[i] * power(b, a - i);
    }
    numerator *= b;

    long long denominator = power(b - 1, a + 1);
    long long common = gcd(numerator, denominator);
    numerator /= common;
    denominator /= common;

    cout << numerator << "/" << denominator << endl;

    return 0;
}