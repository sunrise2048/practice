#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
string a;
int s[N];
bool ch1(){
    int l=0,r=(n<<1);
    for(int i=1;i<=(n<<1);++i){
        if(s[i]<0){
            if(!l)l=i;
            r=i;
        }
    }
    int mxl=0,mxr=(n<<1);
    for(int i=0;i<=l;++i){
        if(s[i]>s[mxl])mxl=i;
    }
    for(int i=r;i<=(n<<1);++i){
        if(s[i]>s[mxr])mxr=i;
    }
    for(int i=mxl+1;i<=mxr;++i){
        if(s[mxl]+s[mxr]-s[i]<0)return 0;
    }
    cout<<"1\n";
    cout<<mxl+1<<' '<<mxr<<'\n';
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        cin>>a;
        a="0"+a;
        bool fl=1;
        for(int i=1;i<=(n<<1);++i){
            s[i]=s[i-1]+(a[i]=='('?1:-1);
            if(s[i]<0)fl=0;
        }
        if(fl){
            cout<<"0\n";
            continue;
        }
        if(!ch1()){
            int mx=1;
            for(int i=1;i<=(n<<1);++i){
                if(s[i]>s[mx])mx=i;
            }
            cout<<"2\n";
            cout<<1<<' '<<mx<<'\n';
            cout<<mx+1<<' '<<2*n<<'\n';
        }
    }
    return 0;
}