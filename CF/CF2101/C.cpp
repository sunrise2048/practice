#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
int a[N];
set<int> stl,str;
ll sum;
bool chl(int l){
    auto it=stl.upper_bound(a[l]);
    if(it==stl.begin())return 0;
    return 1;
}
bool chr(int r){
    auto it=str.upper_bound(a[r]);
    if(it==str.begin())return 0;
    return 1;
}
void insl(int l){
    sum-=l;
    auto it=stl.upper_bound(a[l]);
    --it;
    stl.erase(it);
}
void insr(int r){
    sum+=r;
    auto it=str.upper_bound(a[r]);
    --it;
    str.erase(it);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while (T--) {
        cin>>n;
        sum=0;
        stl.clear();str.clear();
        for (int i=1;i<=n;++i) {
            stl.insert(i);str.insert(i);
        }
        for (int i=1;i<=n;++i) cin>>a[i];
        int l=1,r=n;
        while (l<=r) {
            while (l<=r&&!chl(l)) ++l;
            while (l<=r&&!chr(r)) --r;
            if (l<=r) {
                insl(l);insr(r);
                ++l;--r;
            }
        }
        cout<<sum<<'\n';
    }
    return 0;
}