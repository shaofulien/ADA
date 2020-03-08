#include <array>
#include <iostream>
#include <climits>
#include <numeric>  
#include <vector>
#include <memory>
#include <queue>
#include <list>
#include <set>
#include <bitset>
#include <utility>
#include <stack>
using namespace std;

class Graph{
    int V;
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack); 
public:
    vector<vector<int> > adj;
    Graph(int v);
    void addEdge(int v,int w);
    vector<int>  topologicalSort(); 
};

Graph::Graph(int v){
    this->V = v;
    adj.resize(v);
}

void Graph::addEdge(int a,int b){
    adj[a].push_back(b);
}

void Graph::topologicalSortUtil(int v, bool visited[],  
                                stack<int> &Stack) 
{ 
    // Mark the current node as visited. 
    visited[v] = true; 
  
    // Recur for all the vertices adjacent to this vertex 
    list<int>::iterator i; 
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            topologicalSortUtil(*i, visited, Stack); 
  
    // Push current vertex to stack which stores result 
    Stack.push(v); 
} 
  
// The function to do Topological Sort. It uses recursive  
// topologicalSortUtil() 
vector<int>  Graph::topologicalSort() 
{ 
    stack<int> Stack; 
    vector<int> res;
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // Call the recursive helper function to store Topological 
    // Sort starting from all vertices one by one 
    for (int i = 0; i < V; i++) 
      if (visited[i] == false) 
        topologicalSortUtil(i, visited, Stack); 
  
    // Print contents of stack 
    while (Stack.empty() == false) 
    {   res.push_back( Stack.top());
        Stack.pop(); 
    } 
    return res;
} 


int main() {
    ios_base::sync_with_stdio(false);  
    cin.tie(nullptr);
    srand(12);
    int N_hash = 500;
    int N,M,Q;
    cin>>N>>M>>Q;
    int mini_hash[N][N_hash];
    vector<pair<int,int> > query;
    vector<int> topological_order;
    topological_order.resize(N);
    Graph g(N);
    for (int i=0; i<M;i++)
    {
        int temp1,temp2;
        cin>>temp1>>temp2;
        g.addEdge(temp1-1,temp2-1);
    }
    
    topological_order = g.topologicalSort();
    
    for (int i = 0; i < N; ++i)
    {
        /* code */
        for (int j = 0; j < N_hash; ++j)
        {
            mini_hash[i][j] = random();
        }
    }
    for (int k = N-1; k>=0; k--)
    {  
        int visit = topological_order[k];

        for (auto it = g.adj[visit].begin(); 
            it != g.adj[visit].end(); ++it)
        {
            for (int i = 0; i < N_hash; ++i)
            {
                if(mini_hash[*it][i]<mini_hash[visit][i])
                {
                    mini_hash[visit][i] = mini_hash[*it][i];
                }
            }
        }
    }




    for (int i=0; i<Q;i++)
    {
        int temp1,temp2,count=0;
        cin>>temp1>>temp2;
        query.push_back(make_pair(temp1-1,temp2-1));
    }


    for (int i=0; i<Q;i++)
    {   
        int count = 0;
        //cout<<"______"<<endl;
        for (int j = 0; j < N_hash; ++j)
        {   //cout<<mini_hash[j][query[i].first]<<" "<<mini_hash[j][query[i].second]<<endl;
            if(mini_hash[query[i].first][j] == 
                mini_hash[query[i].second][j])
            {
                count++;
            }
        }
        cout<<(count/double(N_hash))<<endl;
    }
   
    return 0;
}
