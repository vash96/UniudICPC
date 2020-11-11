#include <bits/stdc++.h>
using namespace std;

bool check(vector<int> & pos1, vector<int> & pos2)
{
    for(auto i : pos1) {
        for(auto j : pos2) {
            if(i != j) {
                int ii=i, jj=j;
                if(ii > jj)
                    swap(ii, jj);
                cout << ii << " " << jj << endl;
                return true;
            }
        }
    }
    
    return false;
}

int main()
{
    int T;
    cin >> T;
    for(int test=0; test<T; ++test) {
        unordered_map<int, vector<int>*> hmap;
        int money, N;
        cin >> money >> N;
        
        for(int i=0, cost; i<N; ++i) {
            cin >> cost;
            if(hmap.find(cost) == hmap.end())
                hmap[cost] = new vector<int>;
            hmap[cost]->push_back(i+1);
        }
        
        bool flag = false;
        for(auto & el : hmap) {
            if(el.first > money)
                continue;
            
            auto candidate = hmap.find(money - el.first);
            if(candidate != hmap.end()) {
                flag = check(*(el.second), *(candidate->second));
            }
            if(flag)
                break;
        }
    }
}