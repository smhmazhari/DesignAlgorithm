// Sayyed Mohammad Hossein Mazhari 
// CA3 Q3
//https://chatgpt.com/share/6745eb4b-7e4c-800e-a5b1-95b08fa08b7e

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int book_count, max_reach;
    cin >> book_count >> max_reach;

    vector<int> book_heights(book_count);
    for (int i = 0; i < book_count; ++i) {
        cin >> book_heights[i];
    }
    book_heights.push_back(0); // Dummy book

    auto is_arrangement_beautiful = [&](const vector<int>& heights, int reach, int start_index) {
        for (int i = start_index; i < book_count; ++i) {
            bool found_smaller = false;
            for (int j = i + 1; j < min(i + reach + 1, book_count + 1); ++j) {
                if (heights[j] < heights[i]) {
                    found_smaller = true;
                    break;
                }
            }
            if (!found_smaller) {
                return make_pair(false, max(0, i - 1));
            }
        }
        return make_pair(true, 0);
    };

    auto initial_beauty_status = is_arrangement_beautiful(book_heights, max_reach, 0);
    int optimized_start_index = initial_beauty_status.second;

    if (initial_beauty_status.first) {
        cout << "YES" << endl;
        return 0;
    }

    bool beautification_possible = false;
    for (int i = optimized_start_index; i < book_count; ++i) {
        for (int j = i + 1; j < book_count + 1; ++j) {
            if (book_heights[i] > book_heights[j]) {
                swap(book_heights[i], book_heights[j]);
                auto current_beauty_status = is_arrangement_beautiful(book_heights, max_reach, optimized_start_index);
                if (current_beauty_status.first) {
                    beautification_possible = true;
                    break;
                }
                swap(book_heights[i], book_heights[j]); // Swap back
            }
        }
        if (beautification_possible) {
            break;
        }
    }

    if (beautification_possible) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}