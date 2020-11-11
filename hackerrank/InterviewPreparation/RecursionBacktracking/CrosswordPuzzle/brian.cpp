#include <bits/stdc++.h>

using namespace std;

bool CheckHorizontal(const vector<string> & crossword, int i, int j, const string & s)
{
    if(j > 0 and crossword[i][j-1] != '+' or
        j+s.length() > crossword[i].length() or
        j+s.length() < crossword[i].length() and crossword[i][j+s.length()] != '+') {
        return false;
    }
    
    for(int x=0; x<s.length(); ++x) {
        if(crossword[i][j+x] != '-' and crossword[i][j+x] != s[x]) {
            return false;
        }
    }
    
    return true;
}
bool CheckVertical(const vector<string> & crossword, int i, int j, const string & s)
{
    if(i > 0 and crossword[i-1][j] != '+' or
        i+s.length() > crossword.size() or
        i+s.length() < crossword.size() and crossword[i+s.length()][j] != '+') {
        return false;
    }
    
    for(int x=0; x<s.length(); ++x) {
        if(crossword[i+x][j] != '-' and crossword[i+x][j] != s[x]) {
            return false;
        }
    }
    
    return true;
}

vector<string> AssignHorizontal(const vector<string> & crossword, int i, int j, const string & s)
{
    vector<string> ret(crossword);
    for(int x=0; x<s.length(); ++x) {
        ret[i][j+x] = s[x];
    }
    return ret;
}

vector<string> AssignVertical(const vector<string> & crossword, int i, int j, const string & s)
{
    vector<string> ret(crossword);
    for(int x=0; x<s.length(); ++x) {
        ret[i+x][j] = s[x];
    }
    return ret;
}

pair<bool, vector<string>> backtracking(int curr, vector<string> crossword, vector<string> & words)
{
    if(curr < 0) {
        return {true, crossword};
    }
    
    for(int i=0; i<crossword.size(); ++i) {
        for(int j=0; j<crossword[i].length(); ++j) {
            if(crossword[i][j] != '+') {
                if(CheckHorizontal(crossword, i, j, words[curr])) {
                    auto rec =
                        backtracking (
                            curr-1, 
                            AssignHorizontal(crossword, i, j, words[curr]),
                            words
                        );
                        
                    if(rec.first) {
                        return rec;
                    }
                }
                
                if(CheckVertical(crossword, i, j, words[curr])) {
                    auto rec =
                        backtracking (
                            curr-1, 
                            AssignVertical(crossword, i, j, words[curr]),
                            words
                        );
                        
                    if(rec.first) {
                        return rec;
                    }
                }
            }
        }
    }
    
    return {false, {}};
}

// Complete the crosswordPuzzle function below.
vector<string> crosswordPuzzle(vector<string> crossword, string words) {
    words += ';';
    vector<string> Words;
    for(int i=0, last=0; i<words.length(); ++i) {
        if(words[i] == ';') {
            Words.emplace_back(words.begin()+last, words.begin()+i);
            last = i+1;
        }
    }
    
    bool flag = false;
    for(auto & row : crossword) {
        for(auto & c : row) {
            if(c == 'X') {
                c = '+';
                flag = true;
            }
        }
    }
    
    auto ans = backtracking(Words.size()-1, crossword, Words).second;
    
    if(flag) {
        for(auto & row : ans) {
            for(auto & c : row) {
                if(c == '+') {
                    c = 'X';
                }
            }
        }
    }
    
    return ans;
}