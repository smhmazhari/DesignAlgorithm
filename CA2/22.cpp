// Sayyed Mohammad Hosein Mazhari 
// DA CA2 Q2
// Aladdin and the magic lamp giant
// https://chatgpt.com/share/672f3e03-8654-8007-b7f4-5bb249c22a24
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

double aladdin_win_probability(int n, int m, int k) {
    if (m > n) {
        return 0.0;
    }
    if (m == 0) {
        return 1.0;
    }
    vector<double> dp(n + 1, 0.0);
    dp[0] = 1.0;
    double win_prob = 0.0;

    double interval_sum = 0.0;
    for (int i = 1; i <= n; i++) {
        interval_sum += dp[i - 1];
        if (i > k) {
            interval_sum -= dp[i - 1 - k];
        }
        if (i < m) {
            dp[i] = interval_sum / k;
        } else if (i >= m) {
            win_prob += interval_sum / k;
        }
    }
    return win_prob;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    cout << fixed << setprecision(5) << aladdin_win_probability(n, m, k) << endl;
    return 0;
}