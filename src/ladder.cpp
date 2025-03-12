#include <vector>
#include "ladder.h"
#include <iostream>
#include <queue>
#include <set>
#include <fstream>
#include <cmath>
#include <cassert>

using namespace std;

void error(string word1, string word2, string msg) {
    cout << msg << " at: " << word1 << ", " << word2 << endl;
}
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}
bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();

    if (str1 == str2) {
        return true;
    }

    if (abs(len1 - len2) > d) {
        return false;
    }

    if (len1 == len2) {
        int count = 0;
        for (int i = 0; i < len1; i++) {
            if (str1[i] != str2[i]) {
                count++;
                if (count > d) {
                    return false;
                }
            }
        }
        return count == d; // handles either 0 or 1

    } else {
        int c1 = 0;
        int c2 = 0;
        int count = 0;
        while (c1 < len1 && c2 < len2) {
            if (str1[c1] != str2[c2]) {
                count++;
                if (count > d) {
                    return false;
                }

                if (len1 > len2) {
                    c1++;
                } else {
                    c2++;
                }

            } else {
                c1++;
                c2++;
            }
        }

        count += (c1 < len1) + (c2 < len2);
        return count == d;
    
    
    }

    return false;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    set<string> word_list2 = word_list;
    word_list2.insert(begin_word); // force add tje first word
    cout << begin_word << " " << end_word << endl;
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        // cout << last_word << " last word" << endl;

        for (const string& word : word_list2) {
            // cout << "word : wordlist " << word << endl;
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    // cout << "new ladder size: " << new_ladder.size() << endl;

                    visited.insert(word);

                    if (word == end_word) {
                        return new_ladder;
                    }

                    ladder_queue.push(new_ladder);

                }
            }
        }
    }
    error("no word ladder found!" , begin_word, end_word);
    return {};

}
void load_words(set<string> & word_list, const string& file_name) {
    fstream inFile(file_name);
    string word;
    while (inFile >> word) {
        // cout << word << " ";
        // cout << endl;
        word_list.insert(word);
    }

}
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.size() > 0) {
        for (string word : ladder) {
            cout << "Word ladder found: " <<word << " ";
        }
    } else {
        cout << "No word ladder found.";
    }
    
    cout << endl;
}
// void my_assert(e) {
//     cout << e << ((e) ? " passed": " failed") << endl;
// }
void verify_word_ladder() {

    set<string> word_list;

    // load_words(word_list, "src/words.txt");
    load_words(word_list, "src/words.txt");

    assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    cout << "passed cat dog" << endl;
    assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    cout << "passed marty curls" << endl;

    assert(generate_word_ladder("code", "data", word_list).size() == 6);
    cout << "passed code data" << endl;

    assert(generate_word_ladder("work", "play", word_list).size() == 6);
    cout << "passed work play" << endl;

    assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    cout << "passed sleep awake" << endl;

    assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
    cout << "passed car cheat" << endl;

}