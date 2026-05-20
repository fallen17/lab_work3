#include <iostream>
#include <vector>

using namespace std;

int game(const vector<long long> &chain, int n, int m){
    int last_k = 0;
    int index = 0;

    vector<long long> prefix(n + 1, 0);

    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + chain[i];
    }
    long long scorePasha = 0, scoreVik = 0;
    bool pashaTurn = true;

    while (index < n) {
        int max_len = min(m, n - index);
        int best_k = -1;
        long long best_sum = -1e18;
        
        for (int k = 1; k <= max_len; k++) {
            if (k == last_k) continue;

            long long sum = prefix[index + k] - prefix[index];
            if (sum > best_sum || (sum == best_sum && k < best_k)) {
                best_sum = sum;
                best_k = k;
            }
        }
        if (pashaTurn) {
            scorePasha += best_sum;
        } else {
            scoreVik += best_sum;
        }
        last_k = best_k;
        index += best_k;
        pashaTurn = !pashaTurn;
    }
    if (scorePasha > scoreVik) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
    return 0;
}

int main(){
    int m, n;

    cout << "Type in number n" << endl;
    cin >> n;
    cout << "Type in number m" << endl;
    cin >> m;
    cout << "Type in " << n << " numbers" << endl;

    vector<long long> chain_n(n);

    for (int i = 0; i < n; i++){
        cin >> chain_n[i];
    }
    
    game(chain_n, n, m);
}