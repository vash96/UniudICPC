/**
    diciamo che la stringa S ha s0 '0' e s1 '1', mentre la stringa T ne ha rispettivamente t0 e t1
    chiaramente S avrà anche delta = |S| - s0 - s1 volte il carattere '?'
    ricordando che gli '0' possono trasformarsi in '1' ma non vale il viceversa,
    se non ho abbastanza '0' in S (s0 + delta < t0) oppure ho troppi '1' (s1 > t1) allora la trasformazione è impossibile
    altrimenti è possibile: siano anzitutto n0 il numero di '0' in S che stanno dove dovrebbero esserci gli '1' n1 l'analogo
    per gli '1'. Sicuramente dobbiamo fare almeno delta operazioni ('?' diventano '0' o '1'). è immediato capire che ci servono
    ancora almeno max(n0, n1) operazioni. questo minimo è raggiungibile. Basta sostituire alcuni '?' in modo opportuno da cercare
    di bilanciare i pesi e uguagliare n0 e n1. Se non è possibile uguagliarli, vuoldire che è necessario sostituire alcuni '0'
    con degli '1'. In ogni caso, risulta che dopo le prime delta mosse ne uso altre max(n0, n1). SOL = delta + max(n0, n1)
**/

#include<bits/stdc++.h>
using namespace std;
int TESTS;
string S, T;

int main(){
    cin>>TESTS;

    for(int t = 1; t <= TESTS; t++){
        cin>>S>>T;

        int n0 = 0, n1 = 0, s0 = 0, s1 = 0, t0 = 0, t1 = 0;

        for(int i = 0; i < (int)(S.size()); i++){
            s0 += (S[i] == '0');
            s1 += (S[i] == '1');
            t0 += (T[i] == '0');
            t1 += (T[i] == '1');
            if(S[i] != T[i]){
                n0 += (S[i] == '0');
                n1 += (S[i] == '1');
            }
        }

        int delta = (int)(S.size()) - s0 - s1;

        cout<<"Case "<<t<<": ";

        if(s1 > t1 || s0 + delta < t0){
            cout<<"-1";
        }
        else{
            cout<<delta + max(n0, n1);
        }


        cout<<endl;
    }

    return 0;
}
