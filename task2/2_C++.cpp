#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <iomanip>

using namespace std;

ostream& operator<<(ostream& os, __int128 n) {
    if (n == 0) return os << "0";
    string s = "";
    __int128 temp = n;
    while (temp > 0) {
        s += (char)('0' + (temp % 10));
        temp /= 10;
    }
    reverse(s.begin(), s.end());
    return os << s;
}

int get_len(__int128 n) {
    if (n == 0) return 1;
    int len = 0;
    while (n > 0) { n /= 10; len++; }
    return len;
}

__int128 power(__int128 a, __int128 b, __int128 m) {
    __int128 res = 1;
    a %= m;
    while (b > 0) {
        if (b % 2 == 1) res = (__int128)res * a % m;
        a = (__int128)a * a % m;
        b /= 2;
    }
    return res;
}

vector<int> primes_500; 
void sieve() {
    bool is_p[501]; 
    for (int i = 0; i <= 500; i++) is_p[i] = true;
    is_p[0] = is_p[1] = false; 
    for (int p = 2; p * p <= 500; p++) {
        if (is_p[p]) {
            for (int i = p * p; i <= 500; i += p) 
                is_p[i] = false;
        }
    }
    for (int p = 2; p <= 500; p++) {
        if (is_p[p]) primes_500.push_back(p);
    }
}

bool check_diemitko(__int128 n, __int128 q, __int128 r, int a) {
    if (n <= 1) return false;
    if (power(a, n - 1, n) != 1) return false; 
    if (power(a, r, n) == 1) return false;     
    return true; 
}

random_device rd;
mt19937_64 gen(rd());

bool is_prime_simple(__int128 n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    for (__int128 i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

__int128 generate_prime_small(int bits, long &rej) {
    __int128 min_val = (bits == 2) ? 2 : ((__int128)1 << (bits - 1));
    __int128 max_val = ((__int128)1 << bits) - 1;
    
    uniform_int_distribution<long long> dist(min_val, max_val);
    
    while (true) {
        __int128 start = dist(gen);
        if (start % 2 == 0) start++;
        
        for (__int128 p = start; p <= max_val; p += 2) {
            if (is_prime_simple(p)) {
                return p;
            }
            rej++;
        }
        
        for (__int128 p = min_val + (min_val % 2 == 0 ? 1 : 0); p < start; p += 2) {
            if (is_prime_simple(p)) {
                return p;
            }
            rej++;
        }
    }
}


__int128 generate_prime(int bits, long &rej, __int128 &q_out, __int128 &r_out) {
     if (bits <= 12) {
        return generate_prime_small(bits, rej);
    }

    if (bits <= 8) {
        for (int p : primes_500) {
            if (p >= (1 << (bits - 1))) return p;
        }
        return 251;
    }

    __int128 q_sub, r_sub;
    long dummy = 0;
    __int128 q = generate_prime((bits + 1) / 2, dummy, q_sub, r_sub);

    uniform_real_distribution<double> dist(0.0, 1.0);
    __int128 pow_t_1 = (__int128)1 << (bits - 1);   

    while (true) {
        __int128 N = (pow_t_1 / q) + (__int128)(pow_t_1 * dist(gen) / (double)q);
        if (N % 2 != 0) N++;

        for (__int128 u = 0; ; u += 2) {
            __int128 p = (N + u) * q + 1; 
            if (p >= ((__int128)1 << bits)) break; 

            if (check_diemitko(p, q, N + u, 2)) {
                q_out = q; r_out = N + u; 
                return p;
            }
            rej++;
        }
    }
}

int main() {
    int bits;
    cout << "Enter bits: "; cin >> bits; 
    if (bits > 126) return 1;

    sieve();

    vector<__int128> res_primes; 
    vector<string> res_tests;    
    vector<long> res_rejects;    

    while (res_primes.size() < 10) {
        long rej = 0;
        __int128 q, r;
        __int128 p = generate_prime(bits, rej, q, r);

        bool duplicate = false;
        for (__int128 x : res_primes) if (x == p) duplicate = true;
        if (duplicate) continue; 

        bool ok;
        if (bits <= 12) {
            ok = is_prime_simple(p);
        } else {
            ok = check_diemitko(p, q, r, 3);
        }
        res_primes.push_back(p);
        res_tests.push_back(ok ? "true" : "false");
        res_rejects.push_back(rej);
    }

    cout << "\nTest results\n";
    int w = 14;
    string line = string(25 + w * 10, '-');

    cout << left << setw(25) << "N" << "|";
    for (int i = 1; i <= 10; i++) cout << setw(w-1) << i << "|";
    cout << endl << line << endl;

    cout << left << setw(25) << "Prime number" << "|";
    for (__int128 p : res_primes) {
        if (get_len(p) > w - 1) cout << "big num..|";
        else cout << setw(w-1) << p << "|"; 
    }
    cout << endl;

    cout << left << setw(25) << "Result checking" << "|";
    for (string s : res_tests) cout << setw(w-1) << s << "|";
    cout << endl;

    cout << left << setw(25) << "Rejected" << "|";
    for (long r : res_rejects) cout << setw(w-1) << r << "|";
    cout << endl << line << endl;

    return 0; 
}