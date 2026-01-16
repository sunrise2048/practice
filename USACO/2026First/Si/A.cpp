#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int T;
int op;
ll x,t;
int main(){
    cin>>T;
    while(T--){
        cin>>op>>x>>t;
        if(op==1){
            ll nt=2*x-1;
            if(nt>t){
                cout<<x<<'\n';
                continue;
            }
            while(true){
                ll d=min(x,t-nt);
                x-=d;
                nt+=d;
                if(nt==t)break;
                ++nt;
                x=nt/2;
            }
            cout<<x<<'\n';
            continue;
        }
        ll nt=t;
        while(x<=nt/2){
            ll d=(nt/2-x)*2/3;
            while(x+d<(nt-d)/2)++d;
            while(x+d-1>=(nt-d+1)/2)--d;
            x+=d;nt-=d;
            if(x==nt/2){
                --nt;x=0;
            }
        }
        cout<<x<<'\n';
    }
    return 0;
}