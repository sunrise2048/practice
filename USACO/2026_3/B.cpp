#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T,typ;
int n;
int a[N];
int cn[N];
int sy[N];
ll s;
set<int> id0,id1;
bool ch1(int x){
    if(x<1||x>n)return 0;
    if(!cn[x])return 0;
    return (cn[x-1]==0||sy[x-1])&&(cn[x+1]==0||sy[x+1]);
}
bool ch0(int x){
    if(!ch1(x))return 0;
    return (cn[x-1]==0||cn[x]<sy[x-1])&&(cn[x+1]==0||cn[x]<sy[x+1]);
}
void upd(int x){
    if(x<1||x>n)return;
    id0.erase(x);id1.erase(x);
    if(cn[x]){
        if(ch0(x))id0.insert(x);
        else if(ch1(x))id1.insert(x);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T>>typ;
    while(T--){
        cin>>n;
        id0.clear();id1.clear();
        s=0;
        memset(cn,0,sizeof(int)*(n+2));
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        a[n+1]=0;
        for(int i=1;i<=n;++i){
            int ls=a[i]-cn[i-1]-cn[i];
            if(ls){
                int ne=min(a[i+1],ls);
                cn[i+1]+=ne;
                cn[i]+=ls-ne;
            }
        }
        for(int i=1;i<=n;++i)s+=cn[i];
        if(!typ){
            cout<<s<<'\n';
            continue;
        }
        for(int i=1;i<=n;++i){
            sy[i]=a[i]-cn[i];
        }
        sy[n+1]=0;
        for(int i=1;i<=n;++i)upd(i);
        vector<pair<int,int>> op;
        while(!id0.empty()||!id1.empty()){
            int no;
            if(id0.size())no=*id0.begin();
            else no=*id1.begin();
            int ncn=cn[no];
            if(cn[no-1])ncn=min(ncn,sy[no-1]);
            if(cn[no+1])ncn=min(ncn,sy[no+1]);
            op.emplace_back(no,ncn);
            cn[no]-=ncn;
            sy[no]-=ncn;
            if(no!=1)sy[no-1]-=ncn;
            if(no!=n)sy[no+1]-=ncn;
            for(int i=no-2;i<=no+2;++i)upd(i);
        }
        cout<<s<<'\n';
        cout<<op.size()<<'\n';
        for(auto [x,y]:op){
            cout<<x<<' '<<y<<'\n';
        }
    }
    return 0;
}