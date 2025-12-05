#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int T;
int n;
int x,y;
string s;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>x>>y>>s;
        x=abs(x);y=abs(y);
        for(int i=n-1;i>=0;--i){
            int op=s[i];
            if(op=='8'){
                if(x)--x;
                if(y)--y;
            }
            else{
                if(x>y){
                    --x;
                }
                else if(y) --y;
            }
        }
        if(x+y==0)cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}