#include <iostream>
#include <vector>
using namespace std;

const int LOG = 20;

int n;
vector<vector<int>> g;
vector<bool> used;
vector<int> euler;
vector<int> first;
vector<int> dist;
vector<int> bin_log;
int cur = 0;
struct Point{
    int dist, ind;
};

void dfs(int v, int p){
    used[v] = 1;
    dist[v] = cur;
    first[v] = euler.size();
    euler.push_back(v);
    for (int to : g[v]){
        if (!used[to]){
            cur++;
            dfs(to, v);
            euler.push_back(v);
        }
    }
    cur--;
}

int lca(int l, int r, vector<vector<Point>> &a){
    if (r < l)
        swap(l, r);
    //cout << l << " " << r << endl;
    int len = r - l + 1;
    int k = bin_log[len];
   // cout << k << endl;
    //cout << a[l][k].dist << " " << a[r - (1 << k) + 1][k].dist << "\n";
    if (a[l][k].dist < a[r - (1 << k) + 1][k].dist){
        return a[l][k].ind;
    }
    else{
        return a[r - (1 << k) + 1][k].ind;
    }
}

int main()
{
    cin >> n;

    g.resize(n);
    used.resize(n);
    dist.resize(n);
    first.resize(n);
    dist.resize(n);

    for (int i = 0; i < n - 1; i++){
        int from, to;
        cin >> from >> to;
        from--, to--;
        g[from].push_back(to);
        g[to].push_back(from);
    }
    dfs(0, 0);
    bin_log.resize(euler.size(), 0);
    bin_log[1] = 0;
    for (int i = 2; i <= euler.size(); i++){
        bin_log[i] = bin_log[i / 2] + 1;
    }

    vector<vector<Point>> a(euler.size(), vector<Point>(LOG, {0, 0}));
    for (int i = 0; i < euler.size(); i++){
        a[i][0].dist = dist[euler[i]];
        a[i][0].ind  = euler[i];
    }

    for (int k = 1; k < LOG; k++){
        for (int i = 0; i + (1 << k) - 1 < euler.size(); i++){
            if (a[i][k - 1].dist < a[i + (1 << (k - 1))][k - 1].dist){
                a[i][k].dist = a[i][k - 1].dist;
                a[i][k].ind = a[i][k - 1].ind;
            }
            else{
                a[i][k].dist = a[i + (1 << (k - 1))][k - 1].dist;
                a[i][k].ind = a[i + (1 << (k - 1))][k - 1].ind;
            }
        }
    }
   /*cout << "EULER\n";
    for (int i = 0; i < euler.size(); i++)
        cout << euler[i] << " ";
    cout << "\nDIST\n";
    for (int i = 0; i < dist.size(); i++)
        cout << dist[i] << " ";
    cout << "\n";
    for (int i = 0; i < dist.size(); i++){
        for (int j = 0;  j< LOG; j++){
            cout << a[i][j].dist << " ";
        }
        cout << "\n";
    }
    cout << "BIN";
    for (int i = 0; i < euler.size(); i++)
        cout << bin_log[i] << " ";*/

    cout << "Q\n";
    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << lca(first[l], first[r], a) + 1 << "\n";
    }
    return 0;
}
/*
11
1 7
1 6
4 6
11 6
3 5
5 4
8 10
10 6
2 9
9 10
*/
