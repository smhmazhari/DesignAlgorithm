// Sayyed Mohammad Hosein Mazhari 
// DA CA1 Q1
// same BST with different Permutation
#include <iostream>
#include <vector>
using namespace std;

const int MODULO = 1e9 + 7;

long long modularInverse(long long a) {
    long long result = 1;
    long long mod = MODULO - 2; 
    while (mod) {
        if (mod % 2) result = (result * a) % MODULO;
        a = (a * a) % MODULO;
        mod /= 2;
    }
    return result;
}

void computeFactorials(int size, vector<long long>& factorial) {
    factorial[0] = 1;
    for (int i = 1; i <= size; ++i) {
        factorial[i] = (factorial[i - 1] * i) % MODULO;
    }
}

long long combinations(const vector<long long>& factorial, int total, int select) {
    if (select > total) return 0;
    return (factorial[total] * modularInverse(factorial[select]) % MODULO *
            modularInverse(factorial[total - select]) % MODULO) % MODULO;
}

long long dfs(const vector<int>& nums, const vector<long long>& factorial) {
    int n = nums.size();
    if (n <= 2) return 1;

    vector<int> left_tree, right_tree;
    for (int i = 1; i < n; ++i) {
        if (nums[i] < nums[0]) {
            left_tree.push_back(nums[i]);
        } else {
            right_tree.push_back(nums[i]);
        }
    }

    long long left_ans = dfs(left_tree, factorial) % MODULO;
    long long right_ans = dfs(right_tree, factorial) % MODULO;
    int llen = left_tree.size();

    return (left_ans * right_ans % MODULO * combinations(factorial, llen + right_tree.size(), llen) % MODULO) % MODULO;
}

int main() {
    int n;
    cin >> n;
    
    vector<long long> factorial(n + 1);
    computeFactorials(n, factorial);

    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    long long ans = dfs(nums, factorial);
    cout << ans - 1 << endl;

    return 0;
}
