#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int T,k;
int n;
char c[N];
int op[N];
bool ch(){
    for(int i=1;i<=3*n/2;++i){
        if(c[i]!=c[i+3*n/2])return 0;
    }
    return 1;
}
void solve(int x,int y){
    for(int i=0;i<2;++i){
        for(int j=0;j<2;++j){
            if(c[x+i]==c[y+j]&&c[x+i+1]==c[y+j+1]){
                op[x+i]=op[y+j]=op[x+i+1]=op[y+j+1]=1;
                if(i==0)op[x+2]=2;
                else op[x]=2;
                if(j==0)op[y+2]=2;
                else op[y]=2;
                return;
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T>>k;
    while(T--){
        cin>>n;
        for(int i=1;i<=3*n;++i){
            cin>>c[i];
        }
        if(n&1){
            cout<<"-1\n";
            continue;
        }
        if(ch()){
            cout<<"1\n";
            for(int i=1;i<=3*n;++i){
                cout<<"1";
                if(i!=3*n)cout<<' ';
            }
            cout<<'\n';
            continue;
        }
        cout<<"2\n";
        for(int i=1;i<=n/2;++i){
            solve((i-1)*3+1,(i+n/2-1)*3+1);
        }
        for(int i=1;i<=3*n;++i){
            cout<<op[i];
            if(i!=3*n)cout<<' ';
        }
        cout<<'\n';
    }
    return 0;
}