#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int main(){
    freopen("1.in","w",stdout);
    int T=100;
    cout<<T*2<<'\n';
    mt19937 mt(time(0));
    for(int i=1;i<=T;++i){
        int l=mt()%6+1,r=mt()%6+1;
        if(l>r)swap(l,r);
        cout<<"0 "<<l<<' '<<r<<'\n';
        cout<<"1 "<<l<<' '<<r<<'\n';
    }
    return 0;
}