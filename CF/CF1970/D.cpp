#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=35;
const int M=1e7+5;
int n;
string c[N],b[N];
struct SAM {
    struct Node {
        int ch[2];
        int link, len;
    } st[3605];
    int tot, last;
    
    void init() {
        tot = 1;
        last = 1;
        st[1].ch[0] = st[1].ch[1] = 0;
        st[1].link = 0;
        st[1].len = 0;
    }
    
    void extend(int c) {
        int cur = ++tot;
        st[cur].len = st[last].len + 1;
        st[cur].ch[0] = st[cur].ch[1] = 0;
        
        int p = last;
        while (p && !st[p].ch[c]) {
            st[p].ch[c] = cur;
            p = st[p].link;
        }
        
        if (!p) {
            st[cur].link = 1;
        } else {
            int q = st[p].ch[c];
            if (st[q].len == st[p].len + 1) {
                st[cur].link = q;
            } else {
                int clone = ++tot;
                st[clone] = st[q];
                st[clone].len = st[p].len + 1;
                while (p && st[p].ch[c] == q) {
                    st[p].ch[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    
    long long distinct_substrings() const {
        long long ans = 0;
        for (int v = 2; v <= tot; ++v) {
            ans += st[v].len - st[st[v].link].len;
        }
        return ans;
    }
}sam;
int calc(string s){
    sam.init();
    for(char c:s){
        if(c=='O')sam.extend(0);
        else sam.extend(1);
    }
    return sam.distinct_substrings();
}
int cnt[N][N];
int t[M];
mt19937 mt(time(0));
double be;
double dur_time(){
    return (clock()-be)/CLOCKS_PER_SEC;
}
void solve(){
    be=clock();
    int lm=1e5;
    while(dur_time()<=0.7){
        int fl=0;
        memset(t,0,sizeof(t));
        for(int i=1;i<=n;++i){
            int len=(mt()%16+15)*n;
            c[i].resize(len);
            for(int j=0;j<len;++j){
                if(mt()%10<1)c[i][j]='O';
                else c[i][j]='X';
            }
            for(int j=1;j<i;++j){
                cnt[i][j]=calc(c[i]+c[j]);
                fl+=t[cnt[i][j]];
                t[cnt[i][j]]++;
                cnt[j][i]=calc(c[j]+c[i]);
                fl+=t[cnt[j][i]];
                t[cnt[j][i]]++;
            }
            cnt[i][i]=calc(c[i]+c[i]);
            fl+=t[cnt[i][i]];
            t[cnt[i][i]]++;
            if(fl>=lm)break;
        }
        if(fl<lm){
            lm=fl;
            for(int i=1;i<=n;++i)b[i]=c[i];
        }
    }
    for(int i=1;i<=n;++i)c[i]=b[i];
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            cnt[i][j]=calc(c[i]+c[j]);
        }
    }
    for(int i=1;i<=n;++i){
        cout<<c[i]<<endl;
    }
}
void find_cn(int cn){
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(cnt[i][j]==cn){
                cout<<i<<' '<<j<<endl;
                return;
            }
        }
    }
}
int main(){
    cin>>n;
    solve();
    int q;
    cin>>q;
    while(q--){
        int cn;
        cin>>cn;
        find_cn(cn);
    }
    return 0;
}