#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int T;
int n;
char c[N];
void shift_c(){
    int be=0;
    for(int i=0;i<n;++i){
        if(c[i]!=c[(i-1+n)%n])be=i;
    }
    vector<char> nc(n);
    for(int i=0;i<n;++i){
        nc[i]=c[(i+be)%n];
    }
    for(int i=0;i<n;++i)c[i]=nc[i];
}
int ch_rr_bb(){
    int z=0;
    for(int i=0;i<n;++i){
        if(c[i]==c[(i+1)%n]){
            if(c[i]=='R')z|=1;
            else z|=2;
        }
    }
    return z;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=0;i<n;++i){
            cin>>c[i];
        }
        shift_c();
        int fl=ch_rr_bb();
        if(fl==3){
            cout<<"NO\n";
            continue;
        }
        if(fl==2){
            for(int i=0;i<n;++i)c[i]='R'+'B'-c[i];
        }
        int cn=0,cn1=0;
        int las=0;
        for(int i=1;i<n;++i){
            if(c[i]!=c[i-1]){
                if((i-las)%2==0)++cn;
                if(c[i-1]=='R')++cn1;
                las=i;
            }
        }
        if(c[n-1]=='R')++cn1;
        if((n-las)%2==0)++cn;
        if(cn1==1){
            cout<<"YES\n";
            continue;
        }
        if(cn!=1)cout<<"NO\n";
        else cout<<"YES\n";
    }
    return 0;
}