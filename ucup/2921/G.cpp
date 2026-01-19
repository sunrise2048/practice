#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;

int T;
int n,x;
char S[10];

int main() {
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&x);
        int p=(x+1)/2;
        vector<int> arr0,arr1,arrf1,arrf2;
        for(int i=0;(i+1)*p-1<=n;++i)arrf1.push_back((i+1)*p-1);
        for(int i=0;(i+1)*p-2<=n;++i)arrf2.push_back((i+1)*p-2);
        for(int i=1;i*p<=n;i++) arr0.push_back(i*p);
        for(int i=0;i*p+1<=n;++i)arr1.push_back(i*p+1);
        reverse(arr0.begin(),arr0.end());
        while(x--) {
            scanf("%s",S+1);
            if(S[1]=='+'){
                if(arr0.size())printf("%d\n",arr0.back()),arr0.pop_back();
                else{
                    printf("%d\n",arr1.back()),arr1.pop_back();
                }
            }
            else{
                if(arrf1.size())printf("%d\n",-arrf1.back()),arrf1.pop_back();
                else{
                    printf("%d\n",-arrf2.back());
                    arrf2.pop_back();
                }
            }
            fflush(stdout);
        }
    }
    return 0;
}
