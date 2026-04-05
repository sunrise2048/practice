#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;

int T;

vector<vector<int> > solve(int n,int a,int b,int c) {
    if(abs(a-b)>n-c) return {};
    if(abs(b-c)>n-a) return {};
    if(abs(a-c)>n-b) return {};
    if(1ll*a*b*c<n) return {};
    vector<vector<int> > res(3);
    for(int i=1;i<=n;i++) res[0].push_back(i);
    int d=0;
    while(n>0 && 1ll*(a-1)*(b-1)*(c-1)>=n-1) d++,n--,a--,b--,c--;
    if(n) {
        if(n<a+b+c-2) {
            assert(a==2 && b==2 && c==n-1);
            assert(n>2);
            for(int i=n;i>=1;i--) res[1].push_back(i),res[2].push_back(i);
            swap(res[1][0],res[1][1]);
            swap(res[2][1],res[2][2]);
        }
        else {
            set<ll> st;
            for(int i=1;i<=a;i++) st.insert(i);
            for(int i=0;i<b;i++) st.insert(1+1ll*i*a*c);
            for(int i=0;i<c;i++) st.insert(1+1ll*i*a);
            assert(st.size()==a+b+c-2);
            int p=0;
            while(st.size()<n) st.insert(++p);
            map<ll,int> mp;
            int cnt=0;
            vector<ll> arr;
            for(ll i:st) mp[i]=++cnt,arr.push_back(i);
            int l,r=arr.size()-1;
            while(r>=0) {
                l=r;
                while(l>0 && (arr[l-1]-1)/a==(arr[r]-1)/a) l--;
                for(int i=l;i<=r;i++) res[1].push_back(mp[arr[i]]);
                r=l-1;
            }
            l=0;
            while(l<arr.size()) {
                r=l;
                while(r+1<arr.size() && (arr[r+1]-1)/a/c==(arr[l]-1)/a/c) r++;
                for(int i=r;i>=l;i--) res[2].push_back(mp[arr[i]]);
                l=r+1;
            }
        }
    }
    for(int i=1;i<=d;i++) res[1].push_back(n+i),res[2].push_back(n+i);
    return res;
}

int main() {
    freopen("memory.in","r",stdin);
    freopen("memory.ans","w",stdout);
    scanf("%d",&T);
    while(T--) {
        int n,a,b,c,op;
        scanf("%d%d%d%d%d",&n,&a,&b,&c,&op);
        vector<vector<int> > res=solve(n,a,b,c);
        int w[3][3];
        w[0][1]=w[1][0]=a;
        w[0][2]=w[2][0]=b;
        w[1][2]=w[2][1]=c;
        int p[3]={0,1,2};
        do{
            if(w[p[0]][p[1]]<=w[p[0]][p[2]] && w[p[0]][p[2]]<=w[p[1]][p[2]]) {
                vector<vector<int> > res=solve(n,w[p[0]][p[1]],w[p[0]][p[2]],w[p[1]][p[2]]);
                if(!res.size()) printf("NO\n");
                else {
                    printf("YES\n");
                    if(op) {
                        int pp[3];
                        for(int i=0;i<3;i++) pp[p[i]]=i;
                        for(int i=0;i<3;i++) {
                            for(int j:res[pp[i]]) printf("%d ",j);printf("\n");
                        }
                    }
                }
                break;
            }
        }while(next_permutation(p,p+3));
    }
    return 0;
}
