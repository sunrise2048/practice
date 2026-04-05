#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int T;
int x,y;
int main(){
    ios::sync_with_stdio(0);
    cin>>T;
    while(T--){
        cin>>x>>y;
        int cn=0;
        if(x==y)cn=1;
        else{
            int c=max(x,y)-min(x,y);
            for(int i=1;i<=c;++i){
                if(c%i==0)++cn;
            }
        }
        cout<<cn<<'\n';
        while(x--)cout<<"1 ";
        while(y--)cout<<"-1 ";
        cout<<'\n';
    }
    return 0;
}