#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
 
typedef pair<int, int> myPair;
 
 
class Graph {
    int VER;
    list<pair<int, int> >* List;
 
public:
    Graph(int VER);
    void addEdge(int, int , int );
    void shortestPath(int );
};
 
 
Graph::Graph(int VER)
{
    this->VER = VER;
    List = new list<myPair>[VER];
}
 
void Graph::addEdge(int u, int v, int w)
{
    List[u].push_back(make_pair(v, w));
    List[v].push_back(make_pair(u, w));
}
 
void Graph::shortestPath(int num)
{
    priority_queue<myPair, vector<myPair>, greater<myPair> >
        pq;
 
    vector<int> dist(VER, INF);
 
    pq.push(make_pair(0, num));
    dist[num] = 0;
 
    while (!pq.empty()) {
 
        int u = pq.top().second;
        pq.pop();
 
        list<pair<int, int> >::iterator i;
        for (i = List[u].begin(); i != List[u].end(); ++i) {
 
            int v = (*i).first;
            int weight = (*i).second;
 
            if (dist[v] > dist[u] + weight) {
 
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
 
    cout << "Resultados: \n";
    for (int i = 0; i < VER; ++i)
       
        cout << "Desde el " << num <<" hasta el " << i << " el coste es: " << dist[i] << endl;
}
 
 
int main(){
 
    int VER = 9;
    Graph graf(VER);
 
    graf.addEdge(0, 1, 4);
    graf.addEdge(0, 7, 5);
    graf.addEdge(1, 2, 2);
    graf.addEdge(1, 7, 9);
    graf.addEdge(2, 3, 15);
    graf.addEdge(2, 8, 10);
    graf.addEdge(2, 5, 13);
    graf.addEdge(3, 4, 4);
    graf.addEdge(3, 5, 14);
    graf.addEdge(4, 5, 3);
    graf.addEdge(5, 6, 5);
    graf.addEdge(6, 7, 1);
    graf.addEdge(6, 8, 6);
    graf.addEdge(7, 8, 7);
 
    graf.shortestPath(0);
 
    return 0;
