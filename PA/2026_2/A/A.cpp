#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5005;
const double k=0.76;
const int sd1=1033,sd2=19260817;
const int sd_sf=1024;
const int bs=60;
int p[N],fp[N];
int xs[2][N];
int n,T;
mt19937 mt1(sd1),mt2(sd2),mt_sf(sd_sf);
void init(){
    iota(p+1,p+n+1,1);
    shuffle(p+1,p+n+1,mt_sf);
    for(int i=1;i<=n;++i){
        fp[p[i]]=i;
    }
    for(int i=1;i<=n;++i){
        xs[0][i]=mt1()%2;
        xs[1][i]=mt2()%2;
    }
}
class SOL{
public:
    int a[N];
    int b[N];
    int bea,eda;
    ll la,ra;
    int beb,edb;
    ll lb,rb;
    ll nb;
    int sc;
    void fh(int* a,int* p){
        vector<int> na(n+1);
        for(int i=1;i<=n;++i){
            na[i]=a[p[i]];
        }
        for(int i=1;i<=n;++i)a[i]=na[i];
    }
    void ask(int nm){
        if(eda!=n&&bea>eda){
            eda=min(n,bea+bs-1);
            la=0,ra=(1ll<<(eda-bea+1));
        }
        if(edb!=n&&beb>edb){
            edb=min(n,beb+bs-1);
            lb=0,rb=(1ll<<(edb-beb+1));
            nb=0;
            for(int i=0;i<=edb-beb;++i){
                if(a[beb+i])nb|=(1ll<<i);
            }
        }
        if(sc==0){
            ll d=max(1ll,(rb-lb)/3);;
            ll md1=lb+d,md2=lb+2*d;
            char lc;
            if(nb<md1){
                lc='P';
                rb=md1;
            }
            else if(nb<md2){
                lc='K';
                lb=md1,rb=md2;
            }
            else{
                lc='N';
                lb=md2;
            }
            cout<<lc<<endl;
            d=max(1ll,(ra-la)/3);;
            md1=la+d,md2=la+2*d;
            char c;
            cin>>c;
            if(c=='P'){
                ra=md1;
                if(lc=='K')--sc;
                if(lc=='N')++sc;
            }
            else if(c=='K'){
                la=md1,ra=md2;
                if(lc=='N')--sc;
                if(lc=='P')++sc;
            }
            else{
                la=md2;
                if(lc=='P')--sc;
                if(lc=='K')++sc;
            }
            return;
        }
        int op=1;
        if(beb<bea||(beb==bea&&((rb-lb)>(ra-la)||(rb-lb==ra-la&&nm))))op=0;
        if(sc==1){
            if(op){
                ll md=3*(ra-la)/4+la;
                cout<<"P"<<endl;
                char c;
                cin>>c;
                if(c=='P'){
                    la=md;
                }
                else{
                    ra=md;
                    --sc;
                }
            }
            else{
                ll md=3*(rb-lb)/4+lb;
                if(nb<md){
                    rb=md;
                    --sc;
                    cout<<"K"<<endl;
                }
                else{
                    lb=md;
                    cout<<"P"<<endl;
                }
                char c;
                cin>>c;
            }
        }
        else{
            if(op){
                ll md=3*(ra-la)/4+la;
                cout<<"P"<<endl;
                char c;
                cin>>c;
                if(c=='P'){
                    la=md;
                }
                else{
                    ra=md;
                    ++sc;
                }
            }
            else{
                ll md=3*(rb-lb)/4+lb;
                if(nb<md){
                    rb=md;
                    ++sc;
                    cout<<"N"<<endl;
                }
                else{
                    lb=md;
                    cout<<"P"<<endl;
                }
                char c;
                cin>>c;
            }
        }
    }
    void sol(int op){
        bea=beb=1;
        eda=edb=0;
        sc=0;
        for(int i=1;i<=n;++i){
            b[i]=0;
            char c;
            cin>>c;
            a[i]=c-'0';
            a[i]^=xs[op][i];
        }
        if(op)fh(a,p);
        while(bea<=n||beb<=n){
            ask(op);
            if(la==ra-1){
                for(int i=0;i<=eda-bea;++i){
                    if(la&(1ll<<i))b[bea+i]=1;
                }
                bea=eda+1;
            }
            if(lb==rb-1){
                beb=edb+1;
            }
        }
        if(!op)fh(b,fp);
        cout<<"! ";
        for(int i=1;i<=n;++i){
            cout<<(b[i]^xs[op^1][i]);
        }
        cout<<endl;
    }
}sol;
int main(){
    string name;
    cin>>name;
    cin>>n>>T;
    init();
    while(T--){
        if(name=="Algosia"){
            sol.sol(0);
        }
        else{
            sol.sol(1);
        }
    }
    return 0;
}