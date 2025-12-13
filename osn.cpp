#include<bits/stdc++.h>
using namespace std;
#define int long long 

const int maxn = 2e5+10;
int n, dp[maxn], st[4*maxn];
// dp[i] = maksimum jumlah hari aman sampai hari ke-i
// Segment Tree untuk menyimpan nilai dp dan bonus kontribusi hari aman

void upd(int v, int l, int r, int i, int x){
    if(l > i || r < i) return;
    if(l == r && r == i) st[v] += x;
    else{
        int m = (l+r) >> 1;
        upd(2*v, l, m, i, x); upd(2*v+1, m+1, r, i, x);
        st[v] = max(st[2*v], st[2*v+1]);
    }
}

int getmax(int v, int l, int r, int L, int R){
    if(l > R || r < L) return 0;
    if(l >= L && r <= R) return st[v];
    int m = (l+r) >> 1;
    return max(getmax(2*v, l, m, L, R), getmax(2*v+1, m+1, r, L, R));
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++){
        int a; cin >> a;

        // Jika A[i] <= i, maka hari i bisa aman
        // apabila reset terakhir terjadi di hari (i - A[i])
        if(a <= i) upd(1, 0, n, i-a, 1);

        if(a <= i) upd(1, 0, n, i-a, 1);
        dp[i] = getmax(1, 0, n, 0, i-1);
        // Ambil nilai dp maksimum dari semua kemungkinan reset sebelumnya

        upd(1, 0, n, i, dp[i]);
    }
    cout << n - dp[n];
}
