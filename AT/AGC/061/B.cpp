#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=105;
int T;
int n;
int c[N][N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        if(n==1){
            cout<<"Yes\n1 1\n";
            continue;
        }
        if(n==2){
            cout<<"No\n";
            continue;
        }
        cout<<"Yes\n";
        if(n&1){
            for(int i=1;i<=n;++i){
                c[i][i]=c[i][i+1]=n;
            }
            for(int i=n-1;i>n/2;--i){
                int d=(n-i)*2;
                for(int j=1;j<=i;++j){
                    c[j][(d+j-1)%(n+1)+1]=c[j][(d+j)%(n+1)+1]=i;
                }
                d+=i;
                for(int j=1;j<=n-i;++j){
                    c[j+i][(d+j-1)%(n+1)+1]=c[j+i][(d+j)%(n+1)+1]=n-i;
                }
            }
        }
        else{
            for(int i=1;i<=n;++i){
                c[i][i]=c[i][i+1]=n;
            }
            c[2][1]=c[2][n+1]=1;
            c[1][n+1]=c[3][n+1]=c[3][1]=c[n][1]=2;
            for(int i=2;i<=n;++i){
                c[i%n+1][i]=c[(i+1)%n+1][i]=n-1;
            }
            for(int i=n-2;i>n/2;--i){
                int d=(n-2-i)*2+3;
                for(int j=1;j<=i;++j){
                    c[(d+j-1)%n+1][j]=c[(d+j)%n+1][j]=i;
                }
                d+=i;
                for(int j=1;j<=n-i+1;++j){
                    c[(d+j-1)%n+1][i+j]=c[(d+j)%n+1][i+j]=n-i+1;
                }
            }
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n+1;++j){
                cout<<c[i][j]<<' ';
            }cout<<'\n';
        }
    }
    return 0;
}