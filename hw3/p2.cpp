#include <array>
#include <iostream>
#include <climits>
#include <numeric>  
#include <vector>
#include <list>
#include <limits.h> 
#include <memory>
#include <tuple>
#define LONG_LONG_MAX 9223372036854775807LL
using namespace std;
struct AdjListNode 
{ 
  long long dest; 
  long long weight; 
  struct AdjListNode* next; 
}; 

// A structure to represent an adjacency list 
struct AdjList 
{ 
  struct AdjListNode *head; // polong longer to head node of list 
}; 

// A structure to represent a graph. A graph is an array of adjacency lists. 
// Size of array will be V (number of vertices in graph) 
struct Graph 
{ 
  long long V; 
  struct AdjList* array; 
}; 

// A utility function to create a new adjacency list node 
struct AdjListNode* newAdjListNode(long long dest, long long weight) 
{ 
  struct AdjListNode* newNode = 
      (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
  newNode->dest = dest; 
  newNode->weight = weight; 
  newNode->next = NULL; 
  return newNode; 
} 

// A utility function that creates a graph of V vertices 
struct Graph* createGraph(long long V) 
{ 
  struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
  graph->V = V; 

  // Create an array of adjacency lists. Size of array will be V 
  graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList)); 

  // Initialize each adjacency list as empty by making head as NULL 
  for (long long i = 0; i < V; ++i) 
    graph->array[i].head = NULL; 

  return graph; 
} 

// Adds an edge to an undirected graph 
void addEdge(struct Graph* graph, long long src, long long dest, long long weight) 
{ 
  // Add an edge from src to dest. A new node is added to the adjacency 
  // list of src. The node is added at the beginning 
  struct AdjListNode* newNode = newAdjListNode(dest, weight); 
  newNode->next = graph->array[src].head; 
  graph->array[src].head = newNode; 

  // Since graph is undirected, add an edge from dest to src also 
  newNode = newAdjListNode(src, weight); 
  newNode->next = graph->array[dest].head; 
  graph->array[dest].head = newNode; 
} 

// Structure to represent a min heap node 
struct MinHeapNode 
{ 
  long long v; 
  long long dist; 
}; 

// Structure to represent a min heap 
struct MinHeap 
{ 
  long long size;  // Number of heap nodes present currently 
  long long capacity; // Capacity of min heap 
  long long *pos;  // This is needed for decreaseKey() 
  struct MinHeapNode **array; 
}; 

// A utility function to create a new Min Heap Node 
struct MinHeapNode* newMinHeapNode(long long v, long long dist) 
{ 
  struct MinHeapNode* minHeapNode = 
    (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode)); 
  minHeapNode->v = v; 
  minHeapNode->dist = dist; 
  return minHeapNode; 
} 

// A utility function to create a Min Heap 
struct MinHeap* createMinHeap(long long capacity) 
{ 
  struct MinHeap* minHeap = 
    (struct MinHeap*) malloc(sizeof(struct MinHeap)); 
  minHeap->pos = (long long *)malloc(capacity * sizeof(long long)); 
  minHeap->size = 0; 
  minHeap->capacity = capacity; 
  minHeap->array = 
    (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*)); 
  return minHeap; 
} 

// A utility function to swap two nodes of min heap. Needed for min heapify 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) 
{ 
  struct MinHeapNode* t = *a; 
  *a = *b; 
  *b = t; 
} 

// A standard function to heapify at given idx 
// This function also updates position of nodes when they are swapped. 
// Position is needed for decreaseKey() 
void minHeapify(struct MinHeap* minHeap, long long idx) 
{ 
  long long smallest, left, right; 
  smallest = idx; 
  left = 2 * idx + 1; 
  right = 2 * idx + 2; 

  if (left < minHeap->size && 
    minHeap->array[left]->dist < minHeap->array[smallest]->dist ) 
  smallest = left; 

  if (right < minHeap->size && 
    minHeap->array[right]->dist < minHeap->array[smallest]->dist ) 
  smallest = right; 

  if (smallest != idx) 
  { 
    // The nodes to be swapped in min heap 
    MinHeapNode *smallestNode = minHeap->array[smallest]; 
    MinHeapNode *idxNode = minHeap->array[idx]; 

    // Swap positions 
    minHeap->pos[smallestNode->v] = idx; 
    minHeap->pos[idxNode->v] = smallest; 

    // Swap nodes 
    swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 

    minHeapify(minHeap, smallest); 
  } 
} 

// A utility function to check if the given minHeap is ampty or not 
long long isEmpty(struct MinHeap* minHeap) 
{ 
  return minHeap->size == 0; 
} 

// Standard function to extract minimum node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
{ 
  if (isEmpty(minHeap)) 
    return NULL; 

  // Store the root node 
  struct MinHeapNode* root = minHeap->array[0]; 

  // Replace root node with last node 
  struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
  minHeap->array[0] = lastNode; 

  // Update position of last node 
  minHeap->pos[root->v] = minHeap->size-1; 
  minHeap->pos[lastNode->v] = 0; 

  // Reduce heap size and heapify root 
  --minHeap->size; 
  minHeapify(minHeap, 0); 

  return root; 
} 

// Function to decreasy dist value of a given vertex v. This function 
// uses pos[] of min heap to get the current index of node in min heap 
void decreaseKey(struct MinHeap* minHeap, long long v, long long dist) 
{ 
  // Get the index of v in heap array 
  long long i = minHeap->pos[v]; 

  // Get the node and update its dist value 
  minHeap->array[i]->dist = dist; 

  // Travel up while the complete tree is not hepified. 
  // This is a O(Logn) loop 
  while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) 
  { 
    // Swap this node with its parent 
    minHeap->pos[minHeap->array[i]->v] = (i-1)/2; 
    minHeap->pos[minHeap->array[(i-1)/2]->v] = i; 
    swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]); 

    // move to parent index 
    i = (i - 1) / 2; 
  } 
} 

// A utility function to check if a given vertex 
// 'v' is in min heap or not 
bool isInMinHeap(struct MinHeap *minHeap, long long v) 
{ 
if (minHeap->pos[v] < minHeap->size) 
  return true; 
return false; 
} 


// The main function that calulates distances of shortest paths from src to all 
// vertices. It is a O(ELogV) function 
long long dijkstra(struct Graph* graph, long long src,long long D,long long mode) 
{ 
  long long V = graph->V;// Get the number of vertices in graph 
  long long dist[V];   // dist values used to pick minimum weight edge in cut 
  // minHeap represents set E 
  struct MinHeap* minHeap = createMinHeap(V); 

  // Initialize min heap with all vertices. dist value of all vertices 
  for (long long v = 0; v < V; ++v) 
  { 
    dist[v] = LONG_LONG_MAX; 
    minHeap->array[v] = newMinHeapNode(v, dist[v]); 
    minHeap->pos[v] = v; 
  } 

  // Make dist value of src vertex as 0 so that it is extracted first 
  minHeap->array[src] = newMinHeapNode(src, dist[src]); 
  minHeap->pos[src] = src; 
  dist[src] = 0; 
  decreaseKey(minHeap, src, dist[src]); 

  // Initially size of min heap is equal to V 
  minHeap->size = V; 

  // In the followin loop, min heap contains all nodes 
  // whose shortest distance is not yet finalized. 
  while (!isEmpty(minHeap)) 
  { 
    // Extract the vertex with minimum distance value 
    struct MinHeapNode* minHeapNode = extractMin(minHeap); 
    long long u = minHeapNode->v; // Store the extracted vertex number 

    // Traverse through all adjacent vertices of u (the extracted 
    // vertex) and update their distance values 
    struct AdjListNode* pCrawl = graph->array[u].head; 
    while (pCrawl != NULL) 
    { 
      long long v = pCrawl->dest; 

      // If shortest distance to v is not finalized yet, and distance to v 
      // through u is less than its previously calculated distance
      if (mode==1){      
          if (isInMinHeap(minHeap, v) && dist[u] != LONG_LONG_MAX ) 
            { 
              dist[v] = min(dist[v],max(pCrawl->weight ,dist[u])); 

              // update distance value in min heap also 
              decreaseKey(minHeap, v, dist[v]); 
            } 
            pCrawl = pCrawl->next; 

      } 
      else{
        if (isInMinHeap(minHeap, v) && dist[u] != LONG_LONG_MAX &&  
                                      pCrawl->weight + dist[u] < dist[v]) 
          { 
              dist[v] = dist[u] + pCrawl->weight; 

              // update distance value in min heap also 
              decreaseKey(minHeap, v, dist[v]); 
          } 
          pCrawl = pCrawl->next; 
      }

    } 
  } 
  return dist[D];
  // prlong long the calculated shortest distances 
  //prlong longArr(dist, V); 
} 

int main() {
    ios_base::sync_with_stdio(false);  
    cin.tie(nullptr);
    long long V,E,H,D,temp_v1,temp_v2,temp_d,temp_l;
    cin>>V;
    cin>>E;
    cin>>H;
    cin>>D;
    struct Graph* graph1 = createGraph(V);
    struct Graph* graph2 = createGraph(V);
    vector<tuple<long long, long long, long long, long long>> edges; 
    for (long long i=0;i<E;i++){
      cin>>temp_v1;
      cin>>temp_v2;
      cin>>temp_d;
      cin>>temp_l;
      addEdge(graph1, temp_v1, temp_v2, temp_l); 
      addEdge(graph1, temp_v2, temp_v1, temp_l); 
      edges.push_back(make_tuple(temp_v1,temp_v2,temp_d,temp_l));
    } 
    
    long long min_protection = dijkstra(graph1,H,D,1); 
    //cout<<min_protection;
    //cout<< (get<0>(edges[0]));
    for (long long i =0 ;i<E;i++){
      if (get<3>(edges[i])<=min_protection) {
        addEdge(graph2, get<0>(edges[i]), get<1>(edges[i]), get<2>(edges[i]));
        addEdge(graph2, get<1>(edges[i]), get<0>(edges[i]), get<2>(edges[i]));
        //cout<< get<0>(edges[i])<<" "<< get<1>(edges[i])<<" "<< get<2>(edges[i])<<" "<< get<3>(edges[i])<<" "<<endl;
      }
    }

    long long min_distance = dijkstra(graph2, H,D,3); 
    cout<<min_distance<<" ";
    cout<<min_protection;

    return 0;
}



