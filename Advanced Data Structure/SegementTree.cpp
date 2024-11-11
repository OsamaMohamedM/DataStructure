#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    int data;
    Node(int data)
    {
        this->data= data;
    }
    Node(){
        data = 0;
    }
     void modify( int x)
     {
        data+=x;
     }
};

class SegmentTree{
private:
    long long tree_size;
    vector<Node>segments;

    void init(vector<int>&arr ,int ni ,int lx, int rx)
    {
        if(rx-lx==1)
        {
            if(lx<arr.size())
            {
                segments[ni] = Node(arr[lx]);
            }
            return;
        }

        int mid = (lx+rx)/2;
        init(arr , 2*ni +1 , lx , mid);
        init(arr , 2*ni +2 , mid , rx);
        segments[ni] = merge(segments[2*ni+1] , segments[2*ni+2]);
    }

    Node merge(Node&lft , Node&rht)
    {
        Node ans = Node();
       ans.data = lft.data + rht.data;
        return ans;
    }
    void set(int idx , int value , int ni , int lx , int rx)
    {
        if(rx - lx ==1)
        {
            segments[ni].modify(value);
            return;
        }
        int mid = (lx+rx)/2;
        if(idx<mid)
        {
            set(idx , value , 2*ni +1 , lx , mid);
        }else
        {
            set(idx , value , 2*ni +2 , mid , rx);
        }
        segments[ni] = merge(segments[2*ni+1] , segments[2*ni+2]);
    }
    Node get(int l , int r , int ni , int lx , int rx)
    {
        if(lx>=l && rx<=r)
            return segments[ni];
        if(lx>=r || rx<=l)
            return Node();
        int mid  = (lx+rx)/2;
     Node lf = get(l ,r ,2*ni +1 ,lx ,mid);
     Node rt = get(l ,r ,2*ni +2 ,mid ,rx);
        return merge(lf ,rt);
    }
public:
    SegmentTree(int n)
    {
        tree_size=1;
        while (tree_size<n)tree_size<<=1ll;
        segments.resize(2*tree_size , Node());
    }

    void set(int idx , int val)
    {
        set(idx, val , 0 , 0 ,tree_size);
    }

    int get(int l ,int r)
    {
        return get(l , r , 0 , 0 , tree_size).data;
    }
    void build(vector<int>&arr)
    {
        init(arr , 0 , 0 , arr.size());
    }
};
int main()
{
    int n;
    cin>>n;
    SegmentTree* tree = new SegmentTree(n);
    vector<int> arr(n);
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    tree->build(arr);
    int query ;cin>>query;
    while(query--)
    {
        int op ;cin>>op;
        if(op==1)
        {
            int l, r;
            cin >> l >> r;
            cout<<tree->get(l, r)<<'\n';
        }
        else
        {
            int idx, val;
            cin >> idx >> val;
            tree->set(idx, val);
        }
    }
}