#include <iostream>
#include <vector>
#include <queue>
#define up(i,a,b) for (int i = a; i <= b; i++)
#define pii pair<int, int>
#define f first
#define s second
#define bit(x,i) ((x >> i) & 1)
using namespace std;

const int maxn = 21;
const int LIM = 1010580540;
char a[maxn][maxn];
int n,m;
pii st;
pii V[11];
int cnt;

void input(){
    cnt = 0;
    up(i,1,n){
        up(j,1,m){
            cin >> a[i][j];
            if (a[i][j] == 'o') st = make_pair(i, j);
            if (a[i][j] == '*'){
                V[++cnt] = make_pair(i, j);
            }
        }
    }
}

queue<pii> Q;
int dis[maxn][maxn];
const int dx[] = {0, 1, 0, -1, 0};
const int dy[] = {0, 0, 1, 0, -1};
int P[maxn];

bool beyond(int x, int y){
    return (x < 1 || x > n || y < 1 || y > m);
}

int BFS(pii root, pii fi){
    Q = queue<pii>();
    memset(dis, -1, sizeof(dis));
    Q.push(root);
    dis[root.f][root.s] = 0;

    while (!Q.empty()){
        pii x = Q.front();
        Q.pop();
        int ux = x.f;
        int uy = x.s;

        up(i,1,4){
            int vx = ux + dx[i];
            int vy = uy + dy[i];
            if (dis[vx][vy] != -1) continue;
            if (beyond(vx, vy) || a[vx][vy] == 'x') continue;

            Q.push(make_pair(vx, vy));
            dis[vx][vy] = dis[ux][uy] + 1;
            if (vx == fi.f && vy == fi.s) return dis[vx][vy];
        }
    }
    return LIM;
}

int T[11][11];
int F[(1 << 11)][11];
void Dp_Bit(){
    int res = LIM;
    memset(F, 60, sizeof(F));
    int mask = (1 << cnt) - 1;
    up(i, 0, cnt-1){
        F[1 << i][i] = P[i+1];
    }
    up(x, 0, mask){
        up(i, 0, cnt-1){
            if (bit(x, i))
            up(j, 0, cnt-1){
                F[x][i] = min(F[x][i], F[x - (1 << i)][j] + T[j][i]);
            }
            if (x == mask) res = min(res, F[x][i]);
        }
    }

    if (res == LIM) res = -1;
    cout << res << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> m >> n){
        if (n == 0 && m == 0) exit(0);
        input();
        up(i,1,cnt){
            P[i] = BFS(st, V[i]);
        }

        up(i,1,cnt){
            up(j, i+1, cnt){
                T[i-1][j-1] = T[j-1][i-1] = BFS(V[i], V[j]);
            }
        }

        Dp_Bit();
    }
}
