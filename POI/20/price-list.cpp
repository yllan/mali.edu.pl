#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <climits>
#include <bitset>

using namespace std;

int n, m, k, a, b;
const int max_nodes = 100000;

typedef int vertex_label;
typedef pair<vertex_label, vertex_label> edge;
vector<edge> edges;

vector<vertex_label> neighbors[max_nodes];

void create_vertex()
{
    sort(edges.begin(), edges.end());
    for (vector<edge>::iterator e = edges.begin(); e < edges.end(); e++) {
        neighbors[e->first].push_back(e->second);
    }
}

void solve()
{
    int distance[n];
    for (int i = 0; i < n; i++) 
        distance[i] = INT_MAX;

    // BFS
    distance[k] = 0;
    queue<vertex_label> q;
    q.push(k);

    while (!q.empty()) {
        vertex_label u = q.front();
        q.pop();
        for (vector<vertex_label>::iterator v = neighbors[u].begin(); v < neighbors[u].end(); v++) {
            if (distance[*v] > distance[u] + 1) {
                distance[*v] = distance[u] + 1;
                q.push(*v);
            }
        }
    }

    int distance2[n];
    vector<vertex_label> neighbors_to_explore[max_nodes];
    for (int i = 0; i < n; i++) {
        distance2[i] = INT_MAX;
        neighbors_to_explore[i] = neighbors[i];
    }

    distance2[k] = 0;
    q.push(k);

    while (!q.empty()) {
        vertex_label u = q.front();
        q.pop();

        bitset<max_nodes> direct_neighbor;
        for (vector<vertex_label>::iterator v = neighbors[u].begin(); v < neighbors[u].end(); v++) 
            direct_neighbor[*v] = 1;
        
        for (vector<vertex_label>::iterator v = neighbors[u].begin(); v < neighbors[u].end(); v++) {
            vector<vertex_label> not_checked_vertex;
            for (vector<vertex_label>::iterator w = neighbors_to_explore[*v].begin(); w < neighbors_to_explore[*v].end(); w++) {
                if (distance2[*w] > distance2[u] + 1 && !direct_neighbor[*w]) {
                    // check if there is a path from u->w 
                    distance2[*w] = distance2[u] + 1;
                    q.push(*w);
                } else {
                    not_checked_vertex.push_back(*w);
                }
            }
            neighbors_to_explore[*v] = not_checked_vertex;
        }
    }

    for (int i = 0; i < n; i++) {
        int shortest_path = min(distance[i] * a, (distance[i] % 2) * a + (distance[i] / 2) * b);
        if (distance2[i] != INT_MAX) 
            shortest_path = min(shortest_path, distance2[i] * b);
        printf("%d\n", shortest_path);
    }
}

int main()
{
    scanf("%d %d %d %d %d", &n, &m, &k, &a, &b);

    k--; // make k zeroth based.

    for (int i = 0; i < m; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        edges.push_back(make_pair(v1 - 1, v2 - 1));
        edges.push_back(make_pair(v2 - 1, v1 - 1));
    }

    create_vertex();

    solve();
}