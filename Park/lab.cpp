#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cmath>

using namespace std;

int n = 0;
int m = 0;
int map[9][9] = { 0, };
vector <pair<int, int>> bi;
vector <pair<int, int>> nul;
int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };//북,동,남,서

int result = 0;


void bfs(void) {
    queue<pair<int, int>> q;
    bool check_b[100][100] = { false, };

    for (int i = 0; i < bi.size(); i++) {
        int vx = bi[i].first;
        int vy = bi[i].second;

        q.push(make_pair(vx,vy));
        check_b[vx][vy] = true;
    }

    while (!q.empty()) {
        int c_x = q.front().first;
        int c_y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int n_x = c_x + dir[i][0];
            int n_y = c_y + dir[i][1];

            if (0 <= n_x && n_x < n && 0 <= n_y && n_y < m && !check_b[n_x][n_y] && map[n_x][n_y] == 0) {
                check_b[n_x][n_y] = true;
                q.push(make_pair(n_x, n_y));
            }
        }

    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == 0 && check_b[i][j] == false) {
                cnt++;
            }
        }
    }
    result = max(result, cnt);
}

void dfs(int Idx, int cnt) {
    if (cnt == 3) { // 벽 3개일경우
        bfs();
        return;
    }


    for (int i = Idx; i < nul.size(); i++) {
        if (map[nul[i].first][nul[i].second] == 0) {
            map[nul[i].first][nul[i].second] = 1;
            dfs(i + 1, cnt + 1);
            map[nul[i].first][nul[i].second] = 0;
        }
    }
}



int main(void) {

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];

            if (map[i][j] == 2) {
                bi.push_back(make_pair(i, j));
            }
            if (map[i][j] == 0) {
                nul.push_back(make_pair(i, j));
            }
        }
    }

    dfs(0, 0);
    printf("%d\n", result);
}
