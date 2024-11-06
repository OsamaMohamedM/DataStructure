#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;
class Heap {
protected:
    vector<int> tree;

    int right(int idx) {
        return 2 * idx + 2;
    }

    int left(int idx) {
        return 2 * idx + 1;
    }

    int parent(int idx) {
        return (idx - 1) / 2;
    }

    int size() {
        return tree.size();
    }

    virtual void downHeap(int idx) = 0;
    virtual void upHeap(int idx) = 0;

public:
    virtual ~Heap() {} ;

    void insert(int value) {
        tree.push_back(value);
        upHeap(size() - 1);
    }

    void pop() {
        tree[0] = tree.back();
        tree.pop_back();
        downHeap(0);
    }

    int top() {
        return tree[0];
    }
};

class maxHeap : public Heap {
protected:
    void downHeap(int idx) override {
        int l = left(idx);
        int r = right(idx);
        int mixidx = idx;
        if (l < size() && tree[mixidx] < tree[l]) {
            mixidx = l;
        }
        if (r < size() && tree[mixidx] < tree[r]) {
            mixidx = r;
        }
        if (mixidx != idx) {
            swap(tree[idx], tree[mixidx]);
            downHeap(idx);
        }
    }

    void upHeap(int idx) override {
        int par = parent(idx);
        if (idx && tree[idx] > tree[par]) {
            swap(tree[idx], tree[par]);
            upHeap(par);
        }
    }
};

class minHeap : public Heap {
protected:
    void downHeap(int idx) override {
        int l = left(idx);
        int r = right(idx);
        int mixidx = idx;
        if (l < size() && tree[mixidx] > tree[l]) {
            mixidx = l;
        }
        if (r < size() && tree[mixidx] > tree[r]) {
            mixidx = r;
        }
        if (mixidx != idx) {
            swap(tree[idx], tree[mixidx]);
            downHeap(idx);
        }
    }

    void upHeap(int idx) override {
        int par = parent(idx);
        if (idx && tree[idx] < tree[par]) {
            swap(tree[idx], tree[par]);
            upHeap(par);
        }
    }
};

int main() {
   

    return 0;
}
