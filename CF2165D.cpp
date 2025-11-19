#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e6+5;
int T;
int n;
int a[N];
set<int> stl[N],str[N];
vector<int> ve[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while (T--) {
        cin>>n;
        for (int i=1;i<=n;++i) cin>>a[i];
        for (int i=1;i<=2*n+1;++i) {
            stl[i].clear();
            str[i].clear();
            ve[i].clear();
        }
        for (int i=1;i<=n;++i) {
            stl[a[i]].insert(i);
            str[a[i]].insert(i);
            ve[a[i]].push_back(i);
        }
        int ans=n;
        for (int i=1;i<=(n<<1);++i) {
            for (int id:ve[i]) {
                if (stl[a[id]].count(id)) {
                    auto it=str[a[id]+1].upper_bound(id);
                    if (it!=str[a[id]+1].end()) {
                        --ans;
                        str[a[id]+1].erase(it);
                    }
                }
                if (str[a[id]].count(id)) {
                    auto it=stl[a[id]+1].lower_bound(id);
                    if (it!=stl[a[id]+1].begin()) {
                        --ans;
                        --it;
                        stl[a[id]+1].erase(it);
                    }
                }
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}