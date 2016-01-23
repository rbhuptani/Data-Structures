//#define using_Graphs
#include <iostream>
#include <list>
#include <queue>
#include <stack>
using namespace std;
class Graph{
public:
    Graph(int V);
    int getV();
    void setV(int v);
    list<int> getAdjList(int vertex);
    void setAdjList(int vertex,list<int> adj);
    void addEdge(int v,int w);
    void BFS(int start);
    void DFSIterative(int start);
    void DFS(int start);
    void DFSUtil(int start,bool *visited);
    void topoSort();
    void topoSortHelp(int vertex,bool *visited,stack<int> &order);
private:
    int _V=0;
    list<int> *_adj=nullptr;
};

void Graph::topoSort(){
    stack<int> order;
    bool *Visited = (bool *)malloc(_V*sizeof(bool));
    for(int i=0;i<_V;i++)
        Visited[i] = false;
    for(int i=0;i<_V;i++)
        if(!Visited[i])
            topoSortHelp(i,Visited,order);
    cout<<endl<<"Topological Sort Order :"<<endl;
    cout<<endl<<"========================"<<endl;
    while(!order.empty()){
        cout<<order.top()<<" ";
        order.pop();
    }
}
void Graph::topoSortHelp(int vertex,bool *visited,stack<int> &order){
    visited[vertex] = true;
    list<int>::const_iterator iv;
    for(iv = _adj[vertex].begin();iv!=_adj[vertex].end();iv++)
        if(!visited[*iv])
            topoSortHelp(*iv,visited,order);
    order.push(vertex);
}


Graph::Graph(int V){
    _V = V;
    _adj = new list<int>[V];
}

int Graph::getV(){
    return _V;
}
void Graph::setV(int v){
    _V = v;
}
list<int> Graph::getAdjList(int vertex){
    return _adj[vertex];
}
void Graph::setAdjList(int vertex,list<int> adj){
    _adj[vertex] = adj;
}
void Graph::addEdge(int v,int w){
    _adj[v].push_back(w);
}
void Graph::BFS(int S){
    if(S >= _V)
        return;
    queue<int> Q;
    bool *Visited = (bool *)malloc(_V*sizeof(bool));
    for(int i=0;i<_V;i++)
        Visited[i] = false;

    Q.push(S);
    Visited[S] = true;
    while(!Q.empty()){
        S = Q.front();
        cout<<S<<" ";
        Q.pop();
        list<int> adj = getAdjList(S);
        for(list<int>::iterator it = adj.begin();it != adj.end();it++){
            if(!Visited[*it]){
                Visited[*it] = true;
                Q.push(*it);
            }
        }
    }
}
void Graph::DFS(int S){
    bool *Visited = (bool *)malloc(_V*sizeof(bool));
    for(int i=0;i<_V;i++)
        Visited[i] = false;

    DFSUtil(S,Visited);
}
void Graph::DFSUtil(int S,bool *Visited){
    Visited[S] = true;
    cout<<S<<" ";
    list<int> adj = getAdjList(S);
    for(list<int>::iterator it = adj.begin();it != adj.end();it++)
            if(!Visited[*it])
                DFSUtil(*it,Visited);
}
void Graph::DFSIterative(int S){
    stack<int>  STACK;
    bool *Visited = (bool *)malloc(_V*sizeof(bool));
    for(int i=0;i<_V;i++)
        Visited[i] = false;
    STACK.push(S);
    Visited[S] = true;
    while(!STACK.empty()){
        S = STACK.top();
        cout<<S<<" ";
        STACK.pop();
        list<int> adj = getAdjList(S);
        for(list<int>::reverse_iterator rit = adj.rbegin();rit != adj.rend();rit++){
            if(!Visited[*rit]){
                Visited[*rit] = true;
                STACK.push(*rit);
            }
        }
    }
}

#ifdef using_Graphs
int main(){
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout<<endl<<"BFS representation :"<<endl;
    g.BFS(2);
    cout<<endl<<"DFS(recursive) representation : "<<endl;
    g.DFS(2);
    cout<<endl<<"DFS(iterative) representation : "<<endl;
    g.DFSIterative(2);
    g.topoSort();
    return 0;
}
#endif // using_Graphs
