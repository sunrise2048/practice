#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=998244353;
int T;
int n;
int a[N];
int z1,zn;
vector<int> id1,id2;
int p1,p2;
int p[N];
int op[N];
int b[N];
ll jc[N],ny[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
void init_jc(){
    const int n=2e5;
    jc[0]=1;
    for(int i=1;i<=n;++i)jc[i]=jc[i-1]*i%mod;
    ny[n]=ksm(jc[n]);
    for(int i=n;i;--i)ny[i-1]=ny[i]*i%mod;
}
ll C(int x,int y){
    if(x<y||y<0)return 0;
    return jc[x]*ny[y]%mod*ny[x-y]%mod;
}
void init(){
    if((z1&1)==(zn&1)){
        if(z1<zn){
            int no=z1;
            while(no>0){
                id1.push_back(no);
                no-=2;
            }
            if(no==-1)no=2;
            else no=1;
            while(no<=n){
                id1.push_back(no);
                no+=2;
            }
            if(no==n+1)no=n;
            else no=n-1;
            while(no!=zn){
                id1.push_back(no);
                no-=2;
            }
            no=z1;
            while(no!=zn){
                id2.push_back(no);
                no+=2;
            }
        }
        else{
            int no=z1;
            while(no!=zn){
                id1.push_back(no);
                no-=2;
            }
            no=z1;
            while(no<=n){
                id2.push_back(no);
                no+=2;
            }
            if(no==n+1)no=n;
            else no=n-1;
            while(no>0){
                id2.push_back(no);
                no-=2;
            }
            if(no==-1)no=2;
            else no=1;
            while(no!=zn){
                id2.push_back(no);
                no+=2;
            }
        }
        return;
    }
    int no=z1;
    while(no>0){
        id1.push_back(no);
        no-=2;
    }
    if(no==-1)no=2;
    else no=1;
    while(no!=zn){
        id1.push_back(no);
        no+=2;
    }
    no=z1;
    while(no<=n){
        id2.push_back(no);
        no+=2;
    }
    if(no==n+1)no=n;
    else no=n-1;
    while(no!=zn){
        id2.push_back(no);
        no-=2;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init_jc();
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i)b[i]=0;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            if(a[i])b[a[i]]=i;
            if(a[i]==1)z1=i;
            if(a[i]==n)zn=i;
        }
        for(int i=1;i<=n;++i)p[i]=op[i]=0;
        id1.clear();id2.clear();
        p1=p2=0;
        init();
        for(int i=1;i<id1.size();++i){
            p[id1[i]]=i;
            op[id1[i]]=1;
        }
        for(int i=1;i<id2.size();++i){
            p[id2[i]]=i;
            op[id2[i]]=2;
        }
        ll ans=1;
        for(int i=2;i<n;++i){
            if(!b[i])continue;
            int no=b[i];
            if(op[no]==1){
                int np1=p[no];
                int np2=i-p[no]-1;
                if(np1<=p1||np2<p2){
                    ans=0;
                    break;
                }
                ans=ans*C(np1+np2-p1-p2-1,np1-p1-1)%mod;
                p1=np1,p2=np2;
            }
            else{
                int np1=i-p[no]-1;
                int np2=p[no];
                if(np1<p1||np2<=p2){
                    ans=0;
                    break;
                }
                ans=ans*C(np1+np2-p1-p2-1,np2-p2-1)%mod;
                p1=np1,p2=np2;
            }
        }
        cout<<ans*C(id1.size()+id2.size()-p1-p2-2,id1.size()-p1-1)%mod<<'\n';
    }
    return 0;
}