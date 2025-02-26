#include <stdio.h>
#include <stdbool.h>

#define N 10000

int sz[N];
void initialize_weighted_quick_union() {
    for (int i = 0; i < N; i++) sz[i] = 1;
}

int root__quick_union_path_compression(int* id, int i) {
    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}

int root__quick_union(const int* id, int i) {
    while (i != id[i]) {
        i = id[i];
    }
    return i;
}

bool connected__quick_union(int* id, int p, int q) {
    return root__quick_union_path_compression(id, p) == root__quick_union_path_compression(id, q);
}

void union__weighted_quick_union(int* id, int p, int q) {
    int root_p = root__quick_union_path_compression(id, p);
    int root_q = root__quick_union_path_compression(id, q);

    if (root_p == root_q) return ;

    if (sz[root_p] < sz[root_q]) {
        id[root_p] = root_q;
        sz[root_q] += sz[root_p];
    } else {
        id[root_q] = root_p;
        sz[root_p] += sz[root_q];
    }
}

void union__quick_union(int* id, int p, int q) {
    int root_p = root__quick_union(id, p);
    int root_q = root__quick_union(id, q);
    id[root_p] = root_q;
}

bool connected__quick_find(const int* id, int p, int q) {
    return id[p] == id[q];
}

void union__quick_find(int* id, int p, int q) {
    int pid = id[p];
    int qid = id[q];
    for (int i = 0; i < N; ++i) {
        if (id[i] == pid) id[i] = qid;
    }
}

bool connected(int* id, int p, int q) {
    return connected__quick_union(id, p, q);
}

void add_union(int* id, int p, int q) {
    union__weighted_quick_union(id, p, q);
}

void dynamic_connectivity_client() {
    int id[N];

    for (int i = 0; i < N; i++) {
        id[i] = i;
    }

    while (true) {
        int p, q;
        printf("Enter two integers (p q): ");
        if (scanf("%d %d", &p, &q) != 2) {
            break;
        }

        if (!connected(id, p, q)) {
            add_union(id, p, q);
            printf(" %d %d\n", p, q);
        } else {
            printf("%d and %d are already connected.\n", p, q);
        }
    }
}

int main() {

    initialize_weighted_quick_union();
    dynamic_connectivity_client();

    return 0;
}
