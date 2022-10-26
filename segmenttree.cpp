#include <iostream>
#define n 500001
using namespace std;
struct tree
{
  int left,right,sum,lz;
  int max_,min_;
};
tree node[n*4];
int a[n];
void build(int left,int right,int num)
{
    node[num].left=left;
    node[num].right=right;
    
    if(left==right)
    {
        node[num].sum=a[left];
        node[num].max_=a[left];
        node[num].min_=a[left];
        return;
    }
    
    int mid=(left+right)/2;
    build(left,mid,2*num);
    build(mid+1,right,2*num+1);
    node[num].sum=node[2*num].sum+node[2*num+1].sum;
    node[num].max_=max(node[2*num].max_,node[2*num+1].max_);
    node[num].min_=min(node[2*num].min_,node[2*num+1].min_);
}
void push(int l,int r,int num)
{
    node[num*2].lz=node[num].lz;
    node[num*2+1].lz=node[num].lz;
    node[num].sum+=(r-l+1)*node[num].lz;
    node[num].lz=0;
}
int sum_all(int l, int r,int i)
{
    if (node[i].left>=l&&node[i].right<=r)return node[i].sum;
    
    int mid = (node[i].left + node[i].right) / 2,p=0;
    push(node[i].left,node[i].right,i);
    if (l <= mid)p+=sum_all( l, r,i*2);
    if(r>mid)p+=sum_all(l, r,i*2+1);
    return p;
}
void modify(int l, int r,int i,int val)
{
    if (node[i].left>=l&&node[i].right<=r)
    {
        node[i].lz+=val;
        return;
    }
    
    int mid = (node[i].left + node[i].right) / 2;

    if (l <= mid)modify( l, r,i*2,val);
    if(r>mid)modify(l, r,i*2+1,val);
}
int main()
{
    int t,i,m,L,R,k,cmd;
    cin>>t;
    for(i=0;i<t;i++)cin>>a[i];
    build(0,t-1,1);
    cin>>m;
    while(m--)
    {
        cin>>cmd;
        
        if(cmd==2)
        {
            cin>>L>>R;
            cout<<sum_all(L-1,R-1,1)<<endl;
        }
        else
        {
            cin>>L>>R>>k;
            modify(L-1,R-1,1,k);
            cout<<sum_all(L-1,R-1,1)<<endl;
        }
        
    }

    return 0;
}
