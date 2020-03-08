#include <array>
#include <iostream>
#include <climits>
#include <numeric>
#include <vector>
#include <memory>
#include <queue> 
#include <algorithm>
#include <map>
#include <list> 
#include <unordered_map>
#include <stack> 
#define NINF INT_MIN 
#include <tuple>
using namespace std;

// Graph is represented using adjacency list. Every  
// node of adjacency list contains vertex number of  
// the vertex to which edge connects. It also  
// contains weight of the edge  
class AdjListNode {  
    int v;  
    int weight;  
    
public:  
    AdjListNode(int _v, int _w)  
    {  
        v = _v;  
        weight = _w;  
    }  
    int getV() { return v; }  
    int getWeight() { return weight; }  
};  
    
// Class to represent a graph using adjacency list  
// representation  
class Graph {  
    int V; // No. of vertices'  
    
    // Pointer to an array containing adjacency lists  
    list<AdjListNode>* adj;  
    bool isCyclicUtil(int v, bool visited[], bool *rs);
    // A function used by longestPath  
    void topologicalSortUtil(int v, bool visited[],  
                             stack<int>& Stack);  
    
public:  
    Graph(int V); // Constructor  
    ~Graph(); // Destructor 
  
    // function to add an edge to graph  
    void addEdge(int u, int v, int weight);  
    
    // Finds longest distances from given source vertex  
    long long longestPath(); 
    bool isCyclic(); 
};  
    
Graph::Graph(int V) // Constructor  
{  
    this->V = V;  
    adj = new list<AdjListNode>[V];  
}  
  
Graph::~Graph() // Destructor  
{  
    delete [] adj;  
}  
  
  
void Graph::addEdge(int u, int v, int weight)  
{  
    AdjListNode node(v, weight);  
    adj[u].push_back(node); // Add v to u's list  
}  
    
// A recursive function used by longestPath. See below  
// link for details  
// https:// www.geeksforgeeks.org/topological-sorting/  
void Graph::topologicalSortUtil(int v, bool visited[],  
                                stack<int>& Stack)  
{  
    // Mark the current node as visited  
    visited[v] = true;  
    
    // Recur for all the vertices adjacent to this vertex  
    list<AdjListNode>::iterator i;  
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {  
        AdjListNode node = *i;  
        if (!visited[node.getV()])  
            topologicalSortUtil(node.getV(), visited, Stack);  
    }  
    
    // Push current vertex to stack which stores topological  
    // sort  
    Stack.push(v);  
}  
    
// The function to find longest distances from a given vertex.  
// It uses recursive topologicalSortUtil() to get topological  
// sorting.  
long long  Graph::longestPath()  
{  
    stack<int> Stack;  
    long long dist[V];  
    
    // Mark all the vertices as not visited  
    bool* visited = new bool[V];  
    for (int i = 0; i < V; i++)  
        visited[i] = false;  
    
    // Call the recursive helper function to store Topological  
    // Sort starting from all vertices one by one  
    for (int i = 0; i < V; i++)  
        if (visited[i] == false)  
            topologicalSortUtil(i, visited, Stack);  
    
    // Initialize distances to all vertices as infinite and  
    // distance to source as 0  
    for (int i = 0; i < V; i++)  
        dist[i] = NINF;   
    
    // Process vertices in topological order  
    while (Stack.empty() == false) {  
        // Get the next vertex from topological order  
        int u = Stack.top();  
        Stack.pop();  
        if (dist[u] == NINF){
          dist[u] = 0;
        }
        // Update distances of all adjacent vertices  
        list<AdjListNode>::iterator i;  
        if (dist[u] != NINF) {  
            for (i = adj[u].begin(); i != adj[u].end(); ++i)  
                if (dist[i->getV()] < dist[u] + i->getWeight())  
                    dist[i->getV()] = dist[u] + i->getWeight();  
        }  
    }  
    
    // Print the calculated longest distances  
    delete [] visited; 
    long long max = NINF;
    for (int i = 0; i < V; i++){
      if(dist[i]>max){
        max = dist[i];
      }
    }  
    return max;
}  
    
bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
  if(visited[v] == false)
  {
    // Mark the current node as visited and part of recursion stack
    visited[v] = true;
    recStack[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<AdjListNode>::iterator i;  
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
    {
      if ( !visited[i->getV()] && isCyclicUtil(i->getV(), visited, recStack) )
        return true;
      else if (recStack[i->getV()])
        return true;
    }

  }
  recStack[v] = false; // remove the vertex from recursion stack
  return false;
}

// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS() in https://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclic()
{
  // Mark all the vertices as not visited and not part of recursion
  // stack
  bool *visited = new bool[V];
  bool *recStack = new bool[V];
  for(int i = 0; i < V; i++)
  {
    visited[i] = false;
    recStack[i] = false;
  }

  // Call the recursive helper function to detect cycle in different
  // DFS trees
  for(int i = 0; i < V;i++)
    if (isCyclicUtil(i, visited, recStack))
      return true;

  return false;
}

void remove_duplicate(std::vector<int> &vec) {
  std::sort(vec.begin(), vec.end());
  vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

int find_index(std::vector<int> &vec,int value){
  int left=0;
  int right = vec.size();
  while (left<right){

    int mid = (left+right)/2;
    if(value == vec[mid]){
      return mid;
    }
    else if (value<vec[mid]){
      right = mid;
    }
    else {
      left=mid+1;
    }

  }

}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T,N_songs,N_jumps,N_notes;
    cin>>T;
    for (int i =0;i<T;i++){
        cin>>N_songs;
        cin>>N_jumps;

        //std::vector<std::map<int, int>> direc(N_songs+1);
        //vector<int> notes[N_songs+1]; 
        vector<int> direc[N_songs+1];
        vector<tuple<int,int,int,int>> jump_detail;
        jump_detail.reserve(N_jumps);
        int N_nodes = 0;
        int N_igonre = 0 ;
        int is_cycle = 0 ;

        for (int s1=1; s1<=N_songs; s1++){
          cin>>N_notes; 
          direc[s1].reserve(N_jumps/N_songs);
          direc[s1].push_back(0);
          direc[s1].push_back(N_notes);
        }
        
        for (int j=0; j< N_jumps; j++){
          int s1,t1,s2,t2;
          cin>>s1>>t1>>s2>>t2;
          
          if(s1==s2 and t1<=t2){
            continue;
          }
          if(s1==s2 and t1>t2){
            is_cycle=1;
          }

          direc[s1].push_back(t1);
          direc[s2].push_back(t2);

          jump_detail.push_back(make_tuple(s1,t1,s2,t2));
        }
        if(is_cycle){
          cout << "LoveLive!"<<"\n";
          continue;
        } 

        std::vector<int> offset;
        offset.push_back(0);
        offset.push_back(0);

        for (int s =1;s<=N_songs; s++){
          remove_duplicate(direc[s]);
          offset.push_back (offset[s]+direc[s].size());
        }

        //cout<<offset[N_songs+1];

        //graph construction     
        Graph g(offset[N_songs+1]); 

        for (int s=1; s<=N_songs; s++){
          for (int q=0;q<direc[s].size()-1;q++)
          {
              g.addEdge( q+offset[s] ,q+offset[s]+1,direc[s][q+1]-direc[s][q] );
          }
        }
 
        
        for (int j=0; j<jump_detail.size(); j++){
          int s1 = get<0>(jump_detail[j]);
          int t1 = get<1>(jump_detail[j]);
          int s2 = get<2>(jump_detail[j]);
          int t2 = get<3>(jump_detail[j]);
          g.addEdge(find_index(direc[s1],t1)+offset[s1], find_index(direc[s2],t2)+offset[s2],1);

        }
      
      if(g.isCyclic())
        cout << "LoveLive!"<<"\n";
      else{
        cout<<g.longestPath()<<"\n"; 
        }
      }//query end



    return 0;
}
