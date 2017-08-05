/*
 * TarjanWeightedLCA.h
 *
 *  Created on: Aug 4, 2017
 *      Author: Wesley Leung
 */

#ifndef ALGORITHMS_GRAPH_LCA_TARJANLCA_H_
#define ALGORITHMS_GRAPH_LCA_TARJANLCA_H_

#include <bits/stdc++.h>
#include <datastructures/graph/WeightedGraph.h>
#include <datastructures/math/UF.h>

using namespace std;

/**
 * The {@code TarjanWeightedLCA} class represents a data structure for finding the
 * lowest common ancestor when the queries are known in advance. The constructor
 * take time proportional to <em>N</em> + <em>Q</em>.
 *
 * @author Wesley Leung
 */
class TarjanWeightedLCA {
private:
    const bool WHITE = false;
    const bool BLACK = true;

    bool *color;
    int *ancestor;
    vector<pair<int, int>> *queriesList;
    vector<int> answers;
    UF *uf;

    void dfs(WeightedGraph *G, int v, int prev) {
        ancestor[v] = v;
        for (WeightedEdge *e : G->adj(v)) {
            int w = e->other(v);
            if (w == prev) continue;
            dfs(G, w, v);
            uf->join(v, w);
            ancestor[uf->find(v)] = v;
        }
        color[v] = BLACK;
        for (pair<int, int> q : queriesList[v]) {
            if (color[q.first] == BLACK) answers[q.second] = ancestor[uf->find(q.first)];
        }
    }

public:
    TarjanWeightedLCA(WeightedGraph *G, vector<pair<int, int>> queries) : answers(queries.size()) {
        color = new bool[G->getV()];
        ancestor = new int[G->getV()];
        queriesList = new vector<pair<int, int>>[G->getV()];
        uf = new UF(G->getV());
        for (int v = 0; v < G->getV(); v++) {
            color[v] = WHITE;
        }
        for (int i = 0; i < queries.size(); i++) {
            queriesList[queries[i].first].push_back(make_pair(queries[i].second, i));
            queriesList[queries[i].second].push_back(make_pair(queries[i].first, i));
        }
        dfs(G, 0, -1);
    }

    vector<int> &getAnswers() {
        return answers;
    }
};

#endif /* ALGORITHMS_GRAPH_LCA_TARJANLCA_H_ */
