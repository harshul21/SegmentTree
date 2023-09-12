#include<iostream>
#include<algortihm>
#define MAX_N (100003)
using namespace std;
int arr[MAX_N];
int seg[4*MAX_N+4];

void build(int idx,int low,int high)
{
    if(low==high)
    {
        seg[idx]=arr[high];
        return;
    }
    int mid=(low+high)/2;
    build(2*idx+1,low,mid);
    build(2*idx+2,mid+1,high);
    seg[idx]=max(seg[2*idx+1],seg[2*idx+2]);
}

int query(int idx,int low,int high,int h,int l)
{
    if(low>=l && high<=r)
    {
        return seg[idx];
    }

    if(high<l || low>r)
    {
        return INT_MIN;
    }

    int mid=(low+high)/2;
    int left=query(2*idx+1,low,mid,l,r);
    int right=query(2*idx+2,mid+1,high,l,r);
    return max(left,right);
}
int main()
{
    int n;
    cin>>n;

    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }

    build(0,0,n-1);
}

//lazy propogation

void updateSegmentTreeLazyPropogaation(int segmentTree[],int lazy[],int startRange,int endRange,int delta,,int low,int high, int idx)
{
    if(low>high)
    {
        return;
    }

    if(lazy[idx]!=0)
    {
        segmentTree[idx]+=lazy[idx];
        if(low!=high)
        {
            lazy[2*pos+1]+=lazy[pos];
            lazy[2*pos+2]+=lazy[pos];
        }
        lazy[pos]=0;
    }

    //no overlap condn
    if(startRange>high || endRange<low)
    {
        return;
    }

    //total overlap condn
    if(startRange<=low && endRange>=high)
    {
        segmentTree[idx]+=delta;
        if(low!=high)
        {
            lazy[2*pos+1]+=delta;
            lazy[2*pos+2]+=delta;
        }

        return;
    }

    int mid=(low+high)/2;
    updateSegmentTreeLazyPropogaation(segmentTree,lazy,startRange,endRange,delta,low,mid,2*idx+1);
    updateSegmentTreeLazyPropogaation(segmentTree,lazy,startRange,endRange,delta,mid+1,high,2*idx+2);

    seg[idx]=min(seg[2*idx+1],seg[2*idx+2]);
}

int rangeMinQueryLazyPropogation(int segmentTree[],int lazy[],int startRange,int endRange,int delta,,int low,int high, int idx)
{
    if(low>high)
    {
        return INT_MAX;
    }

    if(lazy[idx]!=0)
    {
        segmentTree[idx]+=lazy[idx];
        if(low!=high)
        {
            lazy[2*pos+1]+=lazy[pos];
            lazy[2*pos+2]+=lazy[pos];
        }
        lazy[pos]=0;
    }

    //no overlap condn
    if(startRange>high || endRange<low)
    {
        return INT_MAX;
    }

    //total overlap condn
    if(startRange<=low && endRange>=high)
    {
        return segmentTree[idx];
    }

    int mid=(low+high)/2;
    int left=rangeMinQueryLazyPropogation(segmentTree,lazy,startRange,endRange,delta,low,mid,2*pos+1);
    int right=rangeMinQueryLazyPropogation(segmentTree,lazy,startRange,endRange,delta,mid+1,high,2*pos+2);

    seg[pos]=min(left,right);
}
