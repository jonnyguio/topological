#include <bits/stdc++.h>
using namespace std;

#define MAX 10005

int main() {
	vector<int> g[MAX];
	int n, m, indeg[MAX] = {0};
	scanf("%d %d", &n, &m);
	for (int i = 0, a; i < n; i++) {
		scanf("%d", &a);
		for (int j = 0, b; j < a; j++) {
			scanf("%d", &b);
			g[i].push_back(b-1);
			indeg[b-1]++;
		}
	}
	queue<int> q;
	for (int i = 0; i < n; i++)
		if (indeg[i] == 0)
			q.push(i);
	vector<int> ord;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		ord.push_back(u);
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if ((--indeg[v]) == 0)
				q.push(v);
		}
	}
	for (int i = 0; i < ord.size(); i++)
		printf("%d ", ord[i]+1);
	puts("");
	return 0;
}
