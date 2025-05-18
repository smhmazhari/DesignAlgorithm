//https://chatgpt.com/share/6745e511-3fdc-8007-869e-85c8763de5cf
// Sayyed Mohammad Hossein Mazhari 
// CA3 Q1

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long long testCases;
    cin >> testCases;
    
    while (testCases--) {
        long long numPeople, threshold;
        cin >> numPeople >> threshold;
        
        vector<long long> peopleAges(numPeople);
        for (long long i = 0; i < numPeople; ++i) {
            cin >> peopleAges[i];
        }

        // Handle edge cases
        if (numPeople == 1) {
            cout << (peopleAges[0] / threshold) * threshold << endl;
            continue; 
        }
        if (numPeople == 0) {
            cout << 0 << endl;
            continue; 
        }

        // Find the maximum possible sum of two consecutive ages
        long long maxSum = peopleAges[0];
        for (long long i = 0; i < numPeople - 1; i++) {
            maxSum = max(maxSum, peopleAges[i] + peopleAges[i + 1]);
        }

        // Binary search for the optimal solution
        long long lowerBound = maxSum / threshold;
        long long upperBound = maxSum;
        long long optimalAnswer = 0;

        while (lowerBound <= upperBound) {
            long long mid = (lowerBound + upperBound) / 2;
            long long totalCount = 0;
            vector<long long> adjustedAges = peopleAges; // Create a copy to simulate the distribution

            // Count how many times we can distribute the ages
            for (size_t i = 0; i < adjustedAges.size() - 1; i++) {
                long long pairsCount = (adjustedAges[i] + adjustedAges[i + 1]) / mid;
                totalCount += pairsCount;
                adjustedAges[i + 1] -= max(0LL, pairsCount * mid - adjustedAges[i]);
            }

            // Adjust the bounds based on the count
            if (totalCount >= threshold) {
                lowerBound = mid + 1;
                optimalAnswer = mid;
            } else {
                upperBound = mid - 1;
            }
        }

        cout << optimalAnswer * threshold << endl;
    }
    return 0;
}
