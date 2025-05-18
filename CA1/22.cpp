// Sayyed Mohammad Hosein Mazhari 
// DA CA1 Q2
// Sum of subsequence in the given range
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

int countSubarraysInRange(const vector<int>& nums, int n, int lower, int upper) {
    vector<long long> prefixSum(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
    }

    int number = 0;
    vector<long long> newPrefix;

    for (int i = 0; i <= n; ++i) {
        long long lowerBound = prefixSum[i] - upper;
        long long upperBound = prefixSum[i] - lower;

        auto lowerIt = lower_bound(newPrefix.begin(), newPrefix.end(), lowerBound);
        // cout << "lowerIt: " << lowerIt; 
        auto upperIt = upper_bound(newPrefix.begin(), newPrefix.end(), upperBound);
        // cout << upperIt ;
        number += (upperIt - lowerIt);
        // cout << i << "count: " << count ;
        newPrefix.insert(upper_bound(newPrefix.begin(), newPrefix.end(), prefixSum[i]), prefixSum[i]);
        // cout << newPrefix[i];
    }

    return number;
}

int main() {
    string input;
    getline(cin, input);
    stringstream ss(input);
    
    vector<int> line;
    int num;
    while (ss >> num) {
        line.push_back(num);
    }
    
    int lower_bound, upper_bound;
    cin >> lower_bound >> upper_bound;

    int result = countSubarraysInRange(line, line.size(), lower_bound, upper_bound);
    cout <<  result << endl;

    return 0;
}