#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
int T;
int n;
int m;
int a[N];
int mi,ma;
void add_ma(int id){
    ++ma;a[id]=ma;
}
void add_mi(int id){
    --mi;a[id]=mi;
}
void sol(int l,int r){
    if(l>r)return;
    sol(l,r-8);
    add_ma(r-7);add_mi(r-6);add_mi(r-5);add_ma(r-4);
    add_mi(r-3);add_ma(r-2);add_ma(r-1);add_mi(r);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        ma=0;mi=1;
        if(n%8==0)sol(1,n);
        else if(n%8==1){
            a[1]=1;mi=ma=1;
            sol(2,n);
        }
        else if(n%8==2){
            sol(1,n-2);
            add_ma(n-1);add_mi(n);
        }
        else if(n%8==3){
            a[1]=1;mi=ma=1;
            sol(2,n-2);
            add_ma(n-1);add_mi(n);
        }
        else if(n%8==4){
            a[1]=2,a[2]=4,a[3]=1,a[4]=3;
            mi=1,ma=4;
            sol(5,n);
        }
        else if(n%8==5){
            a[1]=2,a[2]=5,a[3]=3,a[4]=1,a[5]=4;
            mi=1,ma=5;
            sol(6,n);
        }
        else if(n%8==6){
            a[1]=2,a[2]=4,a[3]=1,a[4]=3;
            mi=1,ma=4;
            sol(5,n-2);
            add_ma(n-1);add_mi(n);
        }
        else{
            a[1]=2,a[2]=5,a[3]=3,a[4]=1,a[5]=4;
            mi=1,ma=5;
            sol(6,n-2);
            add_ma(n-1);add_mi(n);
        }
        int mi=1;
        for(int i=1;i<=n;++i)mi=min(mi,a[i]);
        for(int i=1;i<=n;++i){
            cout<<a[i]-mi+1<<' ';
        }
        cout<<'\n';
    }
    return 0;
}