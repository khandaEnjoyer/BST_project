

#include <bits/stdc++.h>
using namespace std;
using clk = chrono::high_resolution_clock;

struct Sampler {
    double alfa;
    mt19937 rng;
    uniform_real_distribution<double> prob;
    uniform_int_distribution<int> small, large;

    Sampler(double a, int N)
        : alfa(a), rng(random_device{}()),
          prob(0.0, 1.0),
          small(1, 99),
          large(100, 2*N) {}

    int next() {
        return (prob(rng) < alfa) ? small(rng) : large(rng);
    }
};

/* ========================= BST ========================= */
struct BST {
    struct Node {
        int key;
        Node *l, *r;
        Node(int k) : key(k), l(nullptr), r(nullptr) {}
    };
    Node* root = nullptr;

    void insert(int k) {
        Node** cur = &root;
        while (*cur) {
            if (k < (*cur)->key) cur = &(*cur)->l;
            else if (k > (*cur)->key) cur = &(*cur)->r;
            else return;
        }
        *cur = new Node(k);
    }

    bool find(int k, long long& visits) {
        Node* cur = root;
        while (cur) {
            visits++;
            if (k == cur->key) return true;
            cur = (k < cur->key) ? cur->l : cur->r;
        }
        return false;
    }
};

/* ======================== SPLAY ======================== */
struct Splay {
    struct Node {
        int key;
        Node *l, *r, *p;
        Node(int k): key(k), l(nullptr), r(nullptr), p(nullptr) {}
    };
    Node* root = nullptr;

    void rotL(Node* x) {
        Node* y = x->r;
        x->r = y->l;
        if (y->l) y->l->p = x;

        y->p = x->p;
        if (x->p) {
            if (x->p->l == x) x->p->l = y;
            else x->p->r = y;
        } else root = y;
        
        y->l = x;
        x->p = y;
    }

    void rotR(Node* x) {
        Node* y = x->l;
        x->l = y->r;
        if (y->r) y->r->p = x;
        y->p = x->p;
        if (x->p) {
            if (x->p->l == x) x->p->l = y;
            else x->p->r = y;
        } else root = y;
        y->r = x;
        x->p = y;
    }

    void splay(Node* x) {
    while (x->p) {
        Node* p = x->p;
        Node* g = p->p;

        if (!g) {
            if (x == p->l) rotR(p);
            else rotL(p);
        } else if (x == p->l && p == g->l) {
            rotR(g); rotR(p);
        } else if (x == p->r && p == g->r) {
            rotL(g); rotL(p);
        } else if (x == p->r && p == g->l) {
            rotL(p); rotR(g);
        } else {
            rotR(p); rotL(g);
        }
    }
    root = x;
}

    void insert(int k) {
        if (!root) { root = new Node(k); return; }
        Node* cur = root;
        while (true) {
            if (k < cur->key) {
                if (!cur->l) {
                    cur->l = new Node(k);
                    cur->l->p = cur;
                    splay(cur->l);
                    return;
                }
                cur = cur->l;
            } else if (k > cur->key) {
                if (!cur->r) {
                    cur->r = new Node(k);
                    cur->r->p = cur;
                    splay(cur->r);
                    return;
                }
                cur = cur->r;
            } else return;
        }
    }

    bool find(int k, long long& visits) {
        Node* cur = root;
        while (cur) {
            visits++;
            if (k == cur->key) {
                splay(cur);
                return true;
            }
            cur = (k < cur->key) ? cur->l : cur->r;
        }
        return false;
    }
};

/* ========================= AVL ========================= */
struct AVL {
    struct Node {
        int key, h;
        Node *l, *r;
        Node(int k): key(k), h(1), l(nullptr), r(nullptr) {}
    };
    Node* root = nullptr;

    int h(Node* n) { return n ? n->h : 0; }

    Node* rotL(Node* x) {
        Node* y = x->r;
        x->r = y->l;
        y->l = x;
        x->h = max(h(x->l), h(x->r)) + 1;
        y->h = max(h(y->l), h(y->r)) + 1;
        return y;
    }

    Node* rotR(Node* y) {
        Node* x = y->l;
        y->l = x->r;
        x->r = y;
        y->h = max(h(y->l), h(y->r)) + 1;
        x->h = max(h(x->l), h(x->r)) + 1;
        return x;
    }

    Node* insert(Node* n, int k) {
        if (!n) return new Node(k);
        if (k < n->key) n->l = insert(n->l, k);
        else if (k > n->key) n->r = insert(n->r, k);
        else return n;

        n->h = max(h(n->l), h(n->r)) + 1;
        int bf = h(n->l) - h(n->r);

        // LL case
        if (bf > 1 && k < n->l->key) return rotR(n);
        // RR case
        if (bf < -1 && k > n->r->key) return rotL(n);
        // LR case
        if (bf > 1 && k > n->l->key) {
            n->l = rotL(n->l);
            return rotR(n);
        }
        // RL case
        if (bf < -1 && k < n->r->key) {
            n->r = rotR(n->r);
            return rotL(n);
        }
        return n;
    }

    void insert(int k) { root = insert(root, k); }

    bool find(int k, long long& visits) {
        Node* cur = root;
        while (cur) {
            visits++;
            if (k == cur->key) return true;
            cur = (k < cur->key) ? cur->l : cur->r;
        }
        return false;
    }
};

/* ----------------- wysokość drzewa ----------------- */
template<typename Node>
int height(Node* root) {
    if (!root) return 0;
    queue<Node*> q;
    q.push(root);
    int h = 0;
    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            Node* n = q.front(); q.pop();
            if (n->l) q.push(n->l);
            if (n->r) q.push(n->r);
        }
        h++;
    }
    return h;
}

/* ========================= MAIN ========================= */
int main() {
    int N = 1000000;
    int Q = 100000000;
    vector<double> alfas = {0.3, 0.99};

    vector<int> keys(N);
    iota(keys.begin(), keys.end(), 1);
    shuffle(keys.begin(), keys.end(), mt19937(random_device{}()));

    BST bst;
    Splay splay;
    AVL avl;

    auto t1 = clk::now();
    for (int x : keys) bst.insert(x);
    auto t2 = clk::now();

    auto t3 = clk::now();
    for (int x : keys) splay.insert(x);
    auto t4 = clk::now();

    auto t5 = clk::now();
    for (int x : keys) avl.insert(x);
    auto t6 = clk::now();

    cout << "Czas budowy [s]:\n";
    cout << "BST   = " << chrono::duration<double>(t2-t1).count() << "\n";
    cout << "SPLAY = " << chrono::duration<double>(t4-t3).count() << "\n";
    cout << "AVL   = " << chrono::duration<double>(t6-t5).count() << "\n\n";

    cout << "Wysokosc drzew:\n";
    cout << "BST   = " << height(bst.root) << "\n";
    cout << "SPLAY = " << height(splay.root) << "\n";
    cout << "AVL   = " << height(avl.root) << "\n\n";

    for (double a : alfas) {
        Sampler samp(a, N);
        long long vb=0, vs=0, va=0;

        auto s1 = clk::now();
        for (int i=0;i<Q;i++) bst.find(samp.next(), vb);
        auto s2 = clk::now();

        auto s3 = clk::now();
        for (int i=0;i<Q;i++) splay.find(samp.next(), vs);
        auto s4 = clk::now();

        auto s5 = clk::now();
        for (int i=0;i<Q;i++) avl.find(samp.next(), va);
        auto s6 = clk::now();

        cout << "alfa=" << a << "\n";
        cout << " BST   visits=" << (double)vb/Q
             << " time=" << chrono::duration<double>(s2-s1).count() << "s\n";
        cout << " SPLAY visits=" << (double)vs/Q
             << " time=" << chrono::duration<double>(s4-s3).count() << "s\n";
        cout << " AVL   visits=" << (double)va/Q
             << " time=" << chrono::duration<double>(s6-s5).count() << "s\n\n";
    }
}
