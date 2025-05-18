// Sayyed Mohammad Hosein Mazhari 
// DA CA2 Q4
//Magic statues
// https://chatgpt.com/share/672f3e6d-3014-8007-af3c-8da6fd05e45e
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getMaxCoins(vector<int>& powers) {
    int count = powers.size();
    powers.insert(powers.begin(), 1);
    powers.push_back(1);
    
    vector<vector<int>> profit(count + 2, vector<int>(count + 2, 0));
    
    for (int len = 1; len <= count; ++len) {
        for (int start = 1; start <= count - len + 1; ++start) {
            int end = start + len - 1;
            for (int mid = start; mid <= end; ++mid) {
                int coins = profit[start][mid - 1] + profit[mid + 1][end] + powers[start - 1] * powers[mid] * powers[end + 1];
                profit[start][end] = max(profit[start][end], coins);
            }
        }
    }
    
    return profit[1][count];
}

int main() {
    int num;
    cin >> num;
    vector<int> powers(num);
    for (int i = 0; i < num; ++i) {
        cin >> powers[i];
    }
    cout << getMaxCoins(powers) << endl;
    return 0;
}
