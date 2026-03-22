#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int T;
int n,m;
int op[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        if(((ll)n*(n+1)/2)%2==0){
            cout<<"Yes\n";
            ll ls=(ll)n*(n+1)/4-n;
            vector<int> sl;
            int ns=0;
            while(ns<=n){
                ll tl=1;
                while((tl+1)*(tl+2)/2-(tl+1)<=ls)++tl;
                sl.push_back(tl);
                ns+=tl;
                ls-=tl*(tl+1)/2-tl;
            }
            int ed=0;
            int nop=0;
            for(int nl:sl){
                nop^=1;
                for(int i=1;i<=nl;++i)op[ed+i]=nop;
                ed+=nl;
            }
            for(int i=1;i<=n;++i){
                for(int j=1;j<=m;++j){
                    cout<<op[i]<<' ';
                }
                cout<<'\n';
            }
        }
        else if(((ll)m*(m+1)/2)%2==0){
            cout<<"Yes\n";
            ll ls=(ll)m*(m+1)/4-m;
            vector<int> sl;
            int ns=0;
            while(ns<=m){
                ll tl=1;
                while((tl+1)*(tl+2)/2-(tl+1)<=ls)++tl;
                sl.push_back(tl);
                ns+=tl;
                ls-=tl*(tl+1)/2-tl;
            }
            int ed=0;
            int nop=0;
            for(int nl:sl){
                nop^=1;
                for(int i=1;i<=nl;++i)op[ed+i]=nop;
                ed+=nl;
            }
            for(int i=1;i<=n;++i){
                for(int j=1;j<=m;++j){
                    cout<<op[j]<<' ';
                }
                cout<<'\n';
            }
        }
        else cout<<"No\n";
    }
    return 0;
}