#include<iostream>
 
using namespace std;
 
struct node
{
  int data;
  struct node *link;
};
 
struct vertexlist
{
  struct node *vlisthead;
};
 
struct Graph
{
  int v;
  struct vertexlist *vl; 
};
 
struct Graph* CreateGraph(int n)
{
  int i;
  struct Graph *vlist = new Graph;
  vlist->v = n;
 
  vlist->vl = new vertexlist[n+1];
 
  for(i = 0; i < n+1; i++)
  {
    vlist->vl[i].vlisthead = NULL;
  }
 
  return vlist;
}
 
struct node* NewNode(int value)
{
  struct node *newnode = new node;
  newnode->data = value;
  newnode->link = NULL;
 
  return newnode;
}
 

  struct Graph *G = CreateGraph(5);
class Box {
public:
    Box(int id){
       id_ = id;
    }
    bool addNeighbourNode(node *newnode2)
    {
      if(id_!=newnode2->data){
      
        if(G->vl[id_].vlisthead == NULL)
        {
          G->vl[id_].vlisthead = newnode2;
        }
        else
        {
          newnode2->link = G->vl[id_].vlisthead;
          G->vl[id_].vlisthead = newnode2;
        }
        return true;
      }
      else {
        return false;
      }
    }
private:
    int id_;
};

void print(int nodeid  , int count){
  cout<<"\n\tV("<<nodeid<<")---> ";
  
  cout << count;
  
  cout << "  followers" ;
    int x1 = 0;
  int i;
  if (count == 0) return;
  for(i = 0; i < nodeid-2; i++)
  {
    cout<<"\n\tV("<<i+1<<") -> {  ";
    while(x1 < count)
    {
      cout<<G->vl[i+1].vlisthead->data<<"  ";
      G->vl[i+1].vlisthead = G->vl[i+1].vlisthead->link;
      x1++;
    }
    x1 = 0;
    cout<<"}";
  }
  
}

int main()
{
  int i, v, e;
 
  cout<<"Enter the number of vertexes of the graph: ";
  cin>>v;
  cout<<"\nEnter the number of edges of the graph: ";
  cin>>e;
  int edge[e][2];
 
  for(i = 0; i < e; i++)
  {
    cout<<"\nEnter the vertex pair for edge "<<i+1;
    cout<<"\nV(1): ";
    cin>>edge[i][0];
    cout<<"V(2): ";
    cin>>edge[i][1];
    int x=edge[i][0];
    if(edge[i][1]>v){
      
  cout<<"\n ERROR ";
      break;
    }
    
    
    node *newnode2 = NewNode(edge[i][1]);
    Box(x).addNeighbourNode(newnode2);
    
  }
  int x1 ;
  cout<<"\n\nThe incidence list representation for the given graph: ";
  for(i = 0; i < v; i++)
  {
    x1=0;
    cout<<"\n\tV("<<i+1<<") -> {  ";
    while(G->vl[i+1].vlisthead != NULL)
    {
      cout<<"\t ";
       cout<< G->vl[i+1].vlisthead->data <<"  ";
      G->vl[i+1].vlisthead = G->vl[i+1].vlisthead->link;
      x1++;
    }
  cout << "}";
    print(i+1,x1);  
		
      cout<<"\n ";
  }
}
