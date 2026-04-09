#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=(1<<18);
int n;
mt19937 mt(time(0));
int t[N];
int z1,z2;
int main(){
    ios::sync_with_stdio(0);
    cin>>n;
    n=(1<<n)-1;
    int T=420;
    while(T--){
        int x=mt()%n+1,y=mt()%n+1,z=mt()%n+1;
        while(x==y)y=mt()%n+1;
        while(x==z||y==z)z=mt()%n+1;
        cout<<"? "<<x<<' '<<y<<' '<<z<<endl;
        int lc;
        cin>>lc;
        t[lc]++;
    }
    for(int i=1;i<=n;++i){
        if(t[i]>t[z1]){
            z2=z1;z1=i;
        }
        else if(t[i]>t[z2])z2=i;
    }
    for(int i=1;i<=n;++i){
        if(i==z1||i==z2)continue;
        cout<<"? "<<i<<' '<<z1<<' '<<z2<<endl;
        int lc;
        cin>>lc;
        if(lc==i){
            cout<<"! "<<i<<endl;
            break;
        }
    }
    return 0;
}