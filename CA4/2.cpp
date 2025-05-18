//https://chatgpt.com/share/676d96dc-0b44-800e-add9-496572446021
//Sayyed Mohammad Hossein Mazhari 
//CA4 Q2
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX_DIM = 1009;
const long long LARGE_VAL = 1e12;
char matrix[MAX_DIM][MAX_DIM];
int rowCount, colCount;
long long minDistance[4][MAX_DIM][MAX_DIM];

int rowChange[] = {1, -1, 0, 0};
int colChange[] = {0, 0, 1, -1};

void initializeDistances() {
    int r = 1;
    while (r <= rowCount) {
        int c = 1;
        while (c <= colCount) {
            int k = 1;
            while (k <= 3) {
                minDistance[k][r][c] = LARGE_VAL;
                k++;
            }
            c++;
        }
        r++;
    }
}

void readMatrix() {
    int r = 1;
    while (r <= rowCount) {
        scanf("%s", matrix[r] + 1);
        r++;
    }
}

void executeBFS(int category) {
    deque<pair<int, int>> deq;
    char targetChar = category + '0';

    int r = 1;
    while (r <= rowCount) {
        int c = 1;
        while (c <= colCount) {
            if (matrix[r][c] == targetChar) {
                minDistance[category][r][c] = 0;
                deq.emplace_back(r, c);
            }
            c++;
        }
        r++;
    }

    while (!deq.empty()) {
        pair<int, int> current = deq.front();
        deq.pop_front();

        int r = current.first;
        int c = current.second;

        for (int i = 0; i < 4; ++i) {
            int newRow = r + rowChange[i], newCol = c + colChange[i];

            if (newRow < 1 || newCol < 1 || newRow > rowCount || newCol > colCount || minDistance[category][newRow][newCol] != LARGE_VAL || matrix[newRow][newCol] == '#') {
                continue;
            }

            if (matrix[newRow][newCol] == '.') {
                minDistance[category][newRow][newCol] = minDistance[category][r][c] + 1;
                deq.emplace_back(newRow, newCol);
            } else if (matrix[newRow][newCol] != targetChar) {
                minDistance[category][newRow][newCol] = minDistance[category][r][c];
                deq.emplace_front(newRow, newCol);
            }
        }
    }
}

long long calculateMinimumCost() {
    long long optimalCost = LARGE_VAL;

    int r = 1;
    while (r <= rowCount) {
        int c = 1;
        while (c <= colCount) {
            long long totalCost = minDistance[1][r][c] + minDistance[2][r][c] + minDistance[3][r][c];
            if (matrix[r][c] == '.') {
                totalCost -= 2;
            }
            optimalCost = min(optimalCost, totalCost);
            c++;
        }
        r++;
    }

    return optimalCost;
}

int main() {
    cin >> rowCount >> colCount;

    readMatrix();
    initializeDistances();

    int category = 1;
    while (category <= 3) {
        executeBFS(category);
        category++;
    }

    long long optimalCost = calculateMinimumCost();

    if (optimalCost == LARGE_VAL) {
        printf("-1\n");
    } else {
        printf("%lld\n", optimalCost);
    }

    return 0;
}