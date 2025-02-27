#include "dynamic_connectivity.h"

void init_dynamic_connectivity(DynamicConnectivity* dc, int n) {
    for (int i = 0; i < n; i++) {
        dc->id[i] = i;
        dc->sz[i] = 1;
    }
}

int root(DynamicConnectivity* dc, int i) {
    if (dc->id[i] != i) {
        dc->id[i] = root(dc, dc->id[i]);
    }
    return dc->id[i];
}

bool connected(DynamicConnectivity* dc, int p, int q) {
    return root(dc, p) == root(dc, q);
}

void add_union(DynamicConnectivity* dc, int p, int q) {
    int rootP = root(dc, p);
    int rootQ = root(dc, q);

    if (rootP != rootQ) {
        if (dc->sz[rootP] < dc->sz[rootQ]) {
            dc->id[rootP] = rootQ;
            dc->sz[rootQ] += dc->sz[rootP];
        } else {
            dc->id[rootQ] = rootP;
            dc->sz[rootP] += dc->sz[rootQ];
        }
    }
}