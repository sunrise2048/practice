#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1005;
int n;
void prt(int x,int y){
    cout<<min(x,y)<<' '<<max(x,y)<<'\n';
}
void cyc(vector<int>& id,int y){
    for(int x:id)prt(x,y);
}
void solve(int n){
    if(n<=1)return;
    solve(n-4);
    vector<int> id;
    for(int i=1;i<=n-4;++i)id.push_back(i);
    cyc(id,n-3);
    id.push_back(n-3);reverse(id.begin(),id.end());
    cyc(id,n-2);
    reverse(id.begin(),id.end());id.pop_back();
    cyc(id,n-1);
    id.push_back(n-1);reverse(id.begin(),id.end());
    cyc(id,n);
    prt(n-2,n-1);prt(n-3,n);prt(n-3,n-1);prt(n-2,n);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    if(n%4>1){
        cout<<"NO\n";
        return 0;
    }
    cout<<"YES\n";
    solve(n);
    return 0;
}