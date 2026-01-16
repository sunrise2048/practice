#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int T;
ll a,b,ca,cb,fa;
int main(){
    cin>>T;
    while(T--){
        cin>>a>>b>>ca>>cb>>fa;
        ll cs=b/cb;
        b-=cs*cb;
        a+=cs*ca;
        if(a>=fa){
            cout<<"0\n";
            continue;
        }
        --fa;
        ll ans=(cb-1-b);
        b=cb-1;
        if(ca>=cb){
            ans+=fa-a;
            cout<<ans+1<<'\n';
        }
        else{
            ll sy=fa-a;
            ans+=sy%ca;
            ll cn=sy/ca;
            ans+=cn*cb;
            cout<<ans+1<<'\n';
        }
    }
    return 0;
}