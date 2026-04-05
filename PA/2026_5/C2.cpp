#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int T;
int n,k;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        if(k==1){
            string s="PA";
            if(n>s.size()){
                s="NIE";
            }
            else s.resize(n);
            cout<<s<<'\n';
            continue;
        }
        if(k==2){
            string s="PPAA";
            if(n>s.size()){
                s="NIE";
            }
            else s.resize(n);
            cout<<s<<'\n';
            continue;
        }
        if(k==3){
            string s="AAAPAPPP";
            if(n>s.size()){
                s="NIE";
            }
            else s.resize(n);
            cout<<s<<'\n';
            continue;
        }
        string s;
        for(int i=1;i<=k;++i)s+="A";
        int op=0;
        string t="PAPPAA";
        while(s.size()<n){
            s+=t[op];
            op=(op+1)%6;
        }
        cout<<s<<'\n';
    }
    return 0;
}