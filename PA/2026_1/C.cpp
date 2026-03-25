#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int main(){
    int x,d,h,m;
    cin>>x>>d>>h>>m;
    int ans=0;
    if(x==5){
        if(d<29||h<2)++h;
        ans=30*24*60;
        ans-=d*24*60+h*60+m;
    }
    else{
        ans=(24+x)*24*60;
        ans-=d*24*60+h*60+m;
    }
    cout<<ans<<'\n';
    return 0;
}