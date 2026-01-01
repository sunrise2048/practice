#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1005;
int n;
int a[N];
vector<pair<int,int>> op;
vector<int> id;
void solve(){
    while(true){
        sort(id.begin(),id.end(),[](const int& x,const int& y){
            return a[x]<a[y];
        });
        if(a[id[0]]==0){
            swap(id[0],id[2]);
            id.pop_back();
            return;
        }
        int x=id[0],y=id[1],z=id[2];
        int k=a[y]/a[x];
        int hb=0;
        for(int i=20;i>=0;--i){
            if(k&(1<<i)){
                hb=i;
                break;
            }
        }
        for(int i=0;i<=hb;++i){
            if(k&(1<<i)){
                op.emplace_back(x,y);
                a[y]-=a[x];a[x]*=2;
            }
            else{
                op.emplace_back(x,z);
                a[z]-=a[x];a[x]*=2;
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    int cn=0;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        cn+=(a[i]!=0);
    }
    if(cn<2){
        cout<<"-1\n";
        return 0;
    }
    id.push_back(1);id.push_back(2);
    for(int i=3;i<=n;++i){
        id.push_back(i);
        solve();
    }
    cout<<op.size()<<'\n';
    for(auto [x,y]:op){
        cout<<x<<' '<<y<<'\n';
    }
    return 0;
}