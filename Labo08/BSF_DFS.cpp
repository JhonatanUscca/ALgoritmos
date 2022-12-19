#include <iostream>
#include <map>
#include <vector>
#include <list>
using namespace std;
 
class Graph
{
    int V;  
    vector<list<int>> adj;  
public:
    Graph(int V);  
    map<int, bool> visited;
    void addEdge(int v, int w);
    void BFS(int s);
    void DFS(int v);
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj.resize(V);
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}
 
void Graph::BFS(int data)
{
 
    vector<bool> visited;
    visited.resize(V,false);
    list<int> queue;
    visited[data] = true;
    queue.push_back(data);
 
    while(!queue.empty())
    {
        data = queue.front();
        cout << data << " ";
        queue.pop_front();
 
        for (auto adjecent: adj[data])
        {
            if (!visited[adjecent])
            {
                visited[adjecent] = true;
                queue.push_back(adjecent);
            }
        }
    }
}
 
void Graph::DFS(int data)
{
    visited[data] = true;
    cout << data << " ";
    list<int>::iterator i;
    for (i = adj[data].begin(); i != adj[data].end(); ++i)
        if (!visited[*i])
            DFS(*i);
}
 
int main()
{
 
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 3);
 
 
    cout << "Vertice inical (2) \n";
    cout << "Rsultado del BFS: \n";
    g.BFS(2);
    cout << endl;
   
    cout << "Vertice inical (2) \n";
    cout << "Rsultado: \n";
    cout << "Rsultado del DFS: \n";
    g.DFS(2);
   
    return 0;
}
