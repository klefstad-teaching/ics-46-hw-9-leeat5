#include <vector>
#include "ladder.h"
#include <iostream>
#include <queue>
#include <set>
#include <fstream>
#include <cmath>
using namespace std;

void error(string word1, string word2, string msg) {
    cout << msg << " at: " << word1 << ", " << word2 << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d);
bool is_adjacent(const string& word1, const string& word2) {
    int len1 = len(word1);
    int len2 = len(word2);

    if (abs(len1 - len2) != 1 && len1 - len2 != 0) {
        cout << "improper length" << endl;
        return false;
    }

    if (len1 > len2) { // need to remove a char
        int c1 = 0;
        int c2 = 0;
        int count = 0;
        while (c1 < len1 && c2 < len2) {
            if (word1[c1] != word2[c2]) {
                count++;
                if (count > 1) {
                    return false;
                }
                c2++;
            } else {
                c1++;
                c2++;
            }
        }

    } else if (len2 > len1) { // need to add a char

    } else { // euqla
        int count = 0;
        for (int i = 0; i < len1; ++i) {
            if (word1[i] != word2[i]) {
                ++count;
                if (count > 1) {
                    return false;
                }
            }
        }
    }

}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    Queue<Vector<string>> ladder_queue;
    ladder_queue.push(begin_word);
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        ladder = ladder_queue.front();
        ladder_queue.pop();
        last_word = ladder.back();

        for (string word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (!visited.find(word)) {
                    visited.push(word);
                    Vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                }
            }
        }
    }
    ladder_queue.push(new_ladder);
    return nullptr;

}
void load_words(set<string> & word_list, const string& file_name) {
    fstream inFile;
    inFile >> file_name;
    for (string word : inFile) {
        word_list.push(word);
    }

}
void print_word_ladder(const vector<string>& ladder) {
    for (string word : ladder) {
        cout << word << " ";
    }
}
void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}