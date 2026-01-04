#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5005;
int T;
int n,d;
int fa[N],nd[N];
vector<int> nl;
vector<int> id;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>d;
        if(d>n*(n-1)/2){
            cout<<"NO\n";
            continue;
        }
        int ns=0;
        for(int i=2;i<=n;++i){
            fa[i]=i/2;
            nd[i]=nd[fa[i]]+1;
            ns+=nd[i];
        }
        if(ns>d){
            cout<<"NO\n";
            continue;
        }
        {
            int no=1;
            nl.clear();
            while(no<=n){
                nl.push_back(no);
                no*=2;
            }
        }
        id.clear();
        for(int i=2;i<=n;++i){
            if((i&-i)==i)continue;
            id.push_back(i);
        }
        sort(id.begin(),id.end(),[](const int& x,const int& y){
            return nd[x]<nd[y];
        });
        while(ns!=d){
            int no=id.back();id.pop_back();
            int ld=nd[no];
            int td=nl.size();
            if(td-ld+ns<=d){
                ns+=td-ld;
                nd[no]=td;
                fa[no]=nl.back();
                nl.push_back(no);
                continue;
            }
            int nf=nl[d-ns+ld-1];
            fa[no]=nf;
            break;
        }
        cout<<"YES\n";
        for(int i=2;i<=n;++i){
            cout<<fa[i]<<' ';
        }cout<<'\n';
    }
    return 0;
}