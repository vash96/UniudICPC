/*
Testo: https://open.kattis.com/problems/trendingtopic
Tecnica: implementation
Complessità: O(#days * #distinct_words * log(#distinct_words) )

Idea:
  - Prima lettura dell'input assegna id a stringhe distinte
  - Seconda lettura risolve i due casi:
    * Se <text>, allora vado al giorno seguente e aggiorno le frequenze delle parole che compaiono quel giorno
    * Se <top>, allora prendo le parole interessanti e le ordino per frequenza, stampo le prime N (+ eventuali successive di stessa frequenza)

  - Per mantenere fast le frequenze uso tabella delle somme prefisse: freq[i][j] = quante volte è apparsa
    la parola j nei primi i giorni.
    In questo modo so quante volte appare la parole j negli ultimi 7 giorni in tempo costante (freq[i][j] - freq[i-7][j])

*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<string> input;
    unordered_map<string, int> id;
    vector<string> inv;
    char buffer[30];

    // Meta-stringhe non mi interessano
    auto Meta = [](const string & w) {
        return isdigit(w[0]) or
                w == "<text>" or
                w == "</text>" or
                w == "<top" or
                w == "/>";
    };

    int nextId = 0;
    string word;

    // Prime lettura
    while(scanf("%s", buffer) != EOF) {
        word = buffer;
        input.emplace_back(word);
        if(not Meta(word) and id.find(word) == id.end()) {
            id[word] = nextId++;
            inv.emplace_back(word);
        }
    }

    // Seconda lettura
    vector<vector<int>> freq(1005, vector<int>(nextId, 0));
    int day = 0;
    for(int i=0; i<input.size(); ++i) {
        string w = input[i];
        if(w == "<text>") {
            ++day;
            for(int j=0; j<nextId; ++j) { // Le frequenze da un giorno al successivo non cambiano
                freq[day][j] = freq[day-1][j];
            }

            while(++i<input.size() and (w=input[i]) != "</text>") { // Aggiorno le frequenze finché non trovo tag di fine
                ++freq[day][ id[w] ];
            }

        }else { // w == "<top "
            w = input[++i]; // w == N
            int n = atoi(w.data()); // Converto in int
            ++i; // Scarto "/>"

            // v contiene le parole interessanti (frequenza positiva, lunghe>=4, non tags)
            vector<pair<int, string>> v;
            for(int j=0; j<nextId; ++j) {
                int f = freq[day][j] - freq[clamp(day-7, 0, 1005)][j];
                if(f > 0 and inv[j].length()>=4 and not Meta(inv[j]) ) {
                    v.emplace_back(f, inv[j]);
                }
            }

            // Ordino decrescente per frequenza, a parità di frequenza in lessicografico
            sort(v.begin(), v.end(), [](const pair<int, string> & lhs, const pair<int, string> & rhs) {
                return lhs.first == rhs.first ?
                            lhs.second < rhs.second :
                            lhs.first > rhs.first;
            });

            // Stampo le prime n
            printf("<top %d>\n", n);
            for(int j=0; j<n and j<v.size(); ++j) {
                printf("%s %d\n", v[j].second.data(), v[j].first);
            }
            // Stampo le successive finché stessa freq di N-th
            while(n < v.size() and v[n].first == v[n-1].first) {
                printf("%s %d\n", v[n].second.data(), v[n].first);
                ++n;
            }

            printf("</top>\n");
        }
    }

    return 0;
}