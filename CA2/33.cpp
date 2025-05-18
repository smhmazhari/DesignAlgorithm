// Sayyed Mohammad Hosein Mazhari 
// DA CA2 Q3
// Arrangement of symbolic cakes
// https://chatgpt.com/share/672f3f0e-7388-8007-8556-05d2913f19b4
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 100000000;

int count_symbolic_arrangements(int n, int m, int v, int c) {
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(2, 0)));
    dp[0][0][0] = dp[0][0][1] = 1;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 1; k <= v; ++k) {
                if (i >= k) 
                    dp[i][j][0] = (dp[i][j][0] + dp[i - k][j][1]) % MOD;
            }
            for (int k = 1; k <= c; ++k) {
                if (j >= k) 
                    dp[i][j][1] = (dp[i][j][1] + dp[i][j - k][0]) % MOD;
            }
        }
    }
    return (dp[n][m][0] + dp[n][m][1]) % MOD;
}

int main() {
    int n, m, v, c;
    cin >> n >> m >> v >> c;
    cout << count_symbolic_arrangements(n, m, v, c) << endl;
    return 0;
}
