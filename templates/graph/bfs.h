#pragma once

#include "test/global_includes.h"
#include "graph.h"

//begintemplate bfs
//description Breadth-First Search Template (unweighted only)
template <int MAX, typename T>
struct BFS {
    int dis[MAX]; queue<int> nxt;
    void bfs(int start, T& graph) {
        vector<int> starts = {start};
        multisource_bfs(starts, graph);
    }
    void multisource_bfs(vector<int> &starts, T& graph) {
        memset(dis, 0x3f, sizeof dis);
        for (int start : starts) {
            dis[start] = 0;
            nxt.push(start);
        }

        while (!nxt.empty()) {
            int cur = nxt.front(), cdis = dis[cur]; nxt.pop();

            for (int adj : graph.adjs(cur)) {
                if (dis[adj] > cdis + 1) {
                    dis[adj] = cdis + 1;
                    nxt.push(adj);
                }
            }
        }
    }
};
//endtemplate bfs

//begintemplate weightedbfs
//description Breadth-First Search Template (weighted only)
template <int MAX, typename T, typename dis_t>
struct WeightedBFS {
    dis_t dis[MAX]; queue<int> nxt;
    void bfs(int start, T& graph) {
        vector<int> starts = {start};
        multisource_bfs(starts, graph);
    }
    void multisource_bfs(vector<int> &starts, T& graph) {
        memset(dis, 0x3f, sizeof dis);
        for (int start : starts) {
            dis[start] = 0;
            nxt.push(start);
        }

        while (!nxt.empty()) {
            int cur = nxt.front(); dis_t cdis = dis[cur]; nxt.pop();

            for (auto adj : graph.adjs(cur)) {
                if (dis[adj.v] > cdis + 1) {
                    dis[adj.v] = cdis + adj.w;
                    nxt.push(adj);
                }
            }
        }
    }
};
//endtemplate weightedbfs

void BFS_CE_TEST() {
    Graph<10> g; g.init(10, 5);
    BFS<10, Graph<10>> bfs; bfs.bfs(1, g);

    WeightedGraph<10, int> wg; wg.init(10, 5);
    WeightedBFS<10, WeightedGraph<10, int>, int> bfs2; bfs2.bfs(1, wg);
}

//TODO: BFS TEST