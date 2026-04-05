#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2005;
int T;
int n,k;
int a[N][N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        if(k&1){
            cout<<"No\n";
            continue;
        }
        if(k==2||k==n*n-2){
            if(n==2){
                cout<<"Yes\n";
                cout<<"0 1\n1 0\n";
            }
            else cout<<"No\n";
            continue;
        }
        cout<<"Yes\n";
        for(int i=1;i<=n;++i)memset(a[i],0,sizeof(int)*(n+1));
        if(k%4==0){
            int x=1,y=1;
            while(k){
                k-=4;
                a[x][y]=a[x][y+1]=a[x+1][y]=a[x+1][y+1]=1;
                y+=2;
                if(y==n+1){
                    x+=2;y=1;
                }
            }
            for(int i=1;i<=n;++i){
                for(int j=1;j<=n;++j){
                    cout<<a[i][j]<<' ';
                }
                cout<<'\n';
            }
            continue;
        }
        a[1][1]=a[2][1]=a[1][2]=a[3][2]=a[2][3]=a[3][3]=1;
        if(k==n*n-6){
            for(int i=1;i<=n;++i){
                for(int j=1;j<=n;++j){
                    cout<<(a[i][j]^1)<<' ';
                }
                cout<<'\n';
            }
            continue;
        }
        int x=1,y=5;
        k-=6;
        while(k){
            k-=4;
            a[x][y]=a[x][y+1]=a[x+1][y]=a[x+1][y+1]=1;
            y+=2;
            if(y==n+1){
                x+=2;
                if(x==3)y=5;
                else y=1;
            }
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                cout<<a[i][j]<<' ';
            }
            cout<<'\n';
        }
    }
    return 0;
}