#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
int a[N];
int cn0,cn1;
int main(){
    ios::sync_with_stdio(0);
    cin>>T;
    while(T--){
        cin>>n;
        cn0=0,cn1=0;
        for(int i=1;i<=n;++i){
            char c;
            cin>>c;
            a[i]=c-'0';
            if(a[i])cn1++;
            else cn0++;
        }
        vector<int> id;
        for(int i=1;i<=cn0;++i){
            if(a[i])id.push_back(i);
        }
        for(int i=1;i<=cn1;++i){
            if(!a[i+cn0])id.push_back(i+cn0);
        }
        if(id.empty())cout<<"Bob\n";
        else{
            cout<<"Alice\n";
            cout<<id.size()<<'\n';
            for(int no:id){
                cout<<no<<' ';
            }
            cout<<'\n';
        }
    }
    return 0;
}