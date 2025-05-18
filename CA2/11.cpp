// Sayyed Mohammad Hosein Mazhari 
// DA CA2 Q1
// Magic scrolls
// https://chatgpt.com/share/672f3c88-da58-800e-ab82-0d18eec82d6e
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

long long min_magic_sum(int num_of_strings, vector<long long>& magic_cost, vector<string>& scrolls, vector<string>& reversed_scrolls) {
    vector<vector<long long>> dp(num_of_strings, vector<long long>(2, LLONG_MAX));
    dp[0][0] = 0;
    dp[0][1] = magic_cost[0];

    for (int current_string = 1; current_string < num_of_strings; current_string++) {
        if (scrolls[current_string] >= scrolls[current_string - 1]) {
            if (dp[current_string - 1][0] != LLONG_MAX)
                dp[current_string][0] = min(dp[current_string][0], dp[current_string - 1][0]);
        }
        if (scrolls[current_string] >= reversed_scrolls[current_string - 1]) {
            if (dp[current_string - 1][1] != LLONG_MAX)
                dp[current_string][0] = min(dp[current_string][0], dp[current_string - 1][1]);
        }
        if (reversed_scrolls[current_string] >= scrolls[current_string - 1]) {
            if (dp[current_string - 1][0] != LLONG_MAX)
                dp[current_string][1] = min(dp[current_string][1], dp[current_string - 1][0] + magic_cost[current_string]);
        }
        if (reversed_scrolls[current_string] >= reversed_scrolls[current_string - 1]) {
            if (dp[current_string - 1][1] != LLONG_MAX)
                dp[current_string][1] = min(dp[current_string][1], dp[current_string - 1][1] + magic_cost[current_string]);
        }
    }
    long long result = min(dp[num_of_strings - 1][0], dp[num_of_strings - 1][1]);
    return result == LLONG_MAX ? -1 : result;
}

int main() {
    int num_of_strings;
    cin >> num_of_strings;
    vector<long long> magic_cost(num_of_strings);
    for (int current_cost = 0; current_cost < num_of_strings; current_cost++) {
        cin >> magic_cost[current_cost];
    }
    vector<string> scrolls(num_of_strings), reversed_scrolls(num_of_strings);
    for (int current_string = 0; current_string < num_of_strings; current_string++) {
        cin >> scrolls[current_string];
        reversed_scrolls[current_string] = scrolls[current_string];
        reverse(reversed_scrolls[current_string].begin(), reversed_scrolls[current_string].end());
    }

    cout << min_magic_sum(num_of_strings, magic_cost, scrolls, reversed_scrolls) << endl;
    return 0;
}
