#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int T;
ll n,m,k;
bool ch(ll x,ll y){
    if(x>y){
        swap(x,y);
    }
    if(x==0)return 2*y-1<=m;
    ll cn=2*x-1;
    cn+=(y-x)+y;
    return cn<=m;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        int lc=k-1,rc=n-k;
        ll tl=0,tr=0;
        while(true){
            if(tl==lc){
                if(tr==rc)break;
                if(ch(tl,tr+1)){
                    ++tr;
                    continue;
                }
                break;
            }
            if(tr==rc){
                if(ch(tl+1,tr)){
                    ++tl;
                    continue;
                }
                break;
            }
            if(tl<tr){
                if(ch(tl+1,tr)){
                    ++tl;
                    continue;
                }
                break;
            }
            if(ch(tl,tr+1)){
                ++tr;
                continue;
            }
            break;
        }
        cout<<tl+tr+1<<'\n';
    }
    return 0;
}