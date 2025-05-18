// Sayyed Mohammad Hosein Mazhari 
// DA CA1 Q3
// Minimize the cost of talking with people ! 
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

long long calculateCost(vector<long long>& line, int start, int end, long long A, long long B) {
    if (start > end) return 0;
    if (start == end) {
        return (line[start] == 0) ? A : B * line[start];
    }

    long long totalPeople = 0;
    for (int i = start; i <= end; ++i) {
        totalPeople += line[i];
    }

    int length = end - start + 1;
    long long directCost = (totalPeople == 0) ? A : B * totalPeople * length;
    int mid = (start + end) / 2;

    long long lCost = calculateCost(line, start, mid, A, B);
    long long rCost = calculateCost(line, mid + 1, end, A, B);

    long long combinedCost = lCost + rCost;

    return min(directCost, combinedCost);
}

int main() {
    long long n, k, A, B;
    cin >> n >> k >> A >> B;
    long long length = pow(2, n);
    vector<long long> line(length, 0);

    for (int i = 0; i < k; i++) {
        int position;
        cin >> position;
        line[position - 1] += 1;
    }
    // for (int i = 0; i < k; i++) {
    //     line[k - 1] += 1;
    //     cout << line[k - 1 ];
    // }
    long long result = calculateCost(line, 0, length - 1, A, B);
    cout << result << endl;
    return 0;
}
