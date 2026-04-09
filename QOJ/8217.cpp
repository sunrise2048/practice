#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=105;
int T;
int n;
string s[N];
void solve(int n){
    if(n<=7){
        if(n==2){
            s[1]="..";
            s[2]="..";
        }
        else if(n==3){
            s[1]="##.";
            s[2]="...";
            s[3]="...";
        }
        else if(n==4){
            s[1]="#.#.";
            s[2]="#.#.";
            s[3]="....";
            s[4]="....";
        }
        else if(n==5){
            s[1]="##.#.";
            s[2]="...#.";
            s[3]="#....";
            s[4]="#.##.";
            s[5]=".....";
        }
        else if(n==6){
            s[1]="#.#.#.";
            s[2]="#.#.#.";
            s[3]="......";
            s[4]="#.#.#.";
            s[5]="#.#.#.";
            s[6]="......";
        }
        else{
            s[1]="##.#.#.";
            s[2]="...#.#.";
            s[3]="##.....";
            s[4]="....##.";
            s[5]="#.#....";
            s[6]="#.#.##.";
            s[7]=".......";
        }
        return;
    }
    solve(n-6);
    int l=1;
    while(l<=n-6){
        if(l+2==n-6){
            s[l]+="#.#.#.";
            s[l+1]+="#.#.#.";
            s[l+2]+="......";
            l+=3;
            continue;
        }
        s[l]+="##.##.";
        s[l+1]+="......";
        l+=2;
    }
    l=1;
    while(l<=n){
        if(l+2==n){
            s[n-5]+="##.";
            s[n-4]+="...";
            s[n-3]+="##.";
            s[n-2]+="...";
            s[n-1]+="##.";
            s[n]+="...";
            l+=3;
            continue;
        }
        s[n-5]+="#.";s[n-4]+="#.";s[n-3]+="..";s[n-2]+="#.";s[n-1]+="#.";s[n]+="..";
        l+=2;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n+1;++i)s[i].clear();
        solve(n+1);
        for(int i=1;i<=n;++i){
            s[i].pop_back();
            cout<<s[i]<<'\n';
        }
    }
    return 0;
}