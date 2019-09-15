#include <bits/stdc++.h>

using namespace std;

vector<int> edges;
vector<int> combination;
int no_edges,no_vertices;
int I[100][100]; //Incidence Matrix
int New_I[100][100];  //Incidence Matrix of Tree
int trees[100][100];  //Array to store Trees
int d[100][100]; //Distance Matrix
int e[100]; //Eccentricity of vertices
int rad = INT_MAX; // Radius of graph
vector <int> c;    //Vector to store centres 
int no_trees;      //No of Spanning Trees

class Graph 
{ 
    int V;    // No. of vertices 
    
    list<int> *adj; // Pointer to an array for adjacency lists 
    bool isCyclicUtil(int v, bool visited[], int parent); 
public: 
    Graph(int V);   // Constructor 
    void addEdge(int v, int w);   // to add an edge to graph 
    bool isTree();   // returns true if graph is tree 
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_back(w); // Add w to v’s list. 
    adj[w].push_back(v); // Add v to w’s list. 
} 
  
// A recursive function that uses visited[] and parent to 
// detect cycle in subgraph reachable from vertex v. 
bool Graph::isCyclicUtil(int v, bool visited[], int parent) 
{ 
    // Mark the current node as visited 
    visited[v] = true; 
  
    // Recur for all the vertices adjacent to this vertex 
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
    { 
        // If an adjacent is not visited, then recur for  
        // that adjacent 
        if (!visited[*i]) 
        { 
           if (isCyclicUtil(*i, visited, v)) 
              return true; 
        } 
  
        // If an adjacent is visited and not parent of current 
        // vertex, then there is a cycle. 
        else if (*i != parent) 
           return true; 
    } 
    return false; 
} 
  
// Returns true if the graph is a tree, else false. 
bool Graph::isTree() 
{ 
    // Mark all the vertices as not visited and not part of  
    // recursion stack 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // The call to isCyclicUtil serves multiple purposes. 
    // It returns true if graph reachable from vertex 0  
    // is cyclcic. It also marks all vertices reachable  
    // from 0. 
    if (isCyclicUtil(0, visited, -1)) 
             return false; 
  
    // If we find a vertex which is not reachable from 0  
    // (not marked by isCyclicUtil(), then we return false 
    for (int u = 0; u < V; u++) 
        if (!visited[u]) 
           return false; 
  
    return true; 
} 

//Function to calculate distance Matrix
int minEdgeBFS(vector <int> edge[], int u, 
                              int v, int n)   
{ 
    // visited[n] for keeping track of visited 
    // node in BFS 
    vector<bool> visited(n, 0); 
  
    // Initialize distances as 0 
    vector<int> distance(n, 0); 
  
    // queue to do BFS. 
    queue <int> Q; 
    distance[u] = 0; 
  
    Q.push(u); 
    visited[u] = true; 
    while (!Q.empty()) 
    { 
        int x = Q.front(); 
        Q.pop(); 
  
        for (int i=0; i<edge[x].size(); i++) 
        { 
            if (visited[edge[x][i]]) 
                continue; 
  
            // update distance for i 
            distance[edge[x][i]] = distance[x] + 1; 
            Q.push(edge[x][i]); 
            visited[edge[x][i]] = 1; 
        } 
    } 
    return distance[v]; 
} 
  
// Function for addition of edge 
void addedge(vector <int> edge[], int u, int v) 
{ 
   edge[u].push_back(v); 
   edge[v].push_back(u); 
} 

//Function to Calculate Graph Centre
void Centre ()
{
  rad=INT_MAX;
  for (int i = 0; i < no_vertices; i++) {
    e[i]=-1;
  }
  for (int i = 0; i < no_vertices; i++) {
    for (int j = 0; j < no_vertices; j++) {
        e[i] = max(e[i], d[i][j]);
    }

  }
 
  for (int i = 0; i < no_vertices; i++) {
    rad = min(rad, e[i]);
  }
  cout<<endl;
  cout<<"Centres of the given Graph"<<endl;
  for (int i = 0; i < no_vertices; i++) {
    if (e[i] == rad) {
        c.push_back(i);
        cout<<i<<" ";
    }
  }
  cout<<endl;
  
}

//Function to Calculate Tree Centre
void COT ()
  {
   rad=INT_MAX;
  for (int i = 0; i < no_vertices; i++) {
    e[i]=-1;
  }
  for (int i = 0; i < no_vertices; i++) {
    for (int j = 0; j < no_vertices; j++) {
        e[i] = max(e[i], d[i][j]);
    }

  }
 
  for (int i = 0; i < no_vertices; i++) {
    rad = min(rad, e[i]);
  }
  cout<<endl;
  cout<<"Centres of the given Tree"<<endl;
  for (int i = 0; i < no_vertices; i++) {
    if (e[i] == rad) {
        c.push_back(i);
        cout<<i<<" ";
    }
  }
  cout<<endl;
  }

//Function to print All combination of (n-1)edges SubGraph
void print(const vector<int>& v) {
  static int count = 0;
  cout<<endl;
  cout << "combination no " << (++count) << " : [ ";
  
  for (int i = 0; i < v.size(); i++) { cout << v[i] << " "; }
  cout << "] " << endl;

  Graph g(no_vertices);
  int ones[2];
  
  for(int i=0;i < v.size(); i++)
    {
    int z=0;
       for(int j=0;j<no_vertices;j++)
      {
            
             if(I[j][v[i]]==1)
              {
                
                ones[z]=j;
                z++;
              }
            
          
      }
      
      g.addEdge(ones[0], ones[1]); 
    }
    static int t=0;
  if(g.isTree())
    {
      for(int i=0;i<v.size();i++)
        {
          trees[t][i]=v[i];
        }
      t++;
      no_trees=t;
    } 
  
  if(g.isTree()) 
    {
      for(int i=0;i<v.size();i++)
        {
          for(int j=0;j<no_vertices;j++)
            {
              New_I[j][i]=I[j][v[i]];
            }
        }
        vector <int> edge[no_vertices];
  
  for(int i=0;i<(no_vertices-1);i++)
      {
        int z=0;
        for(int j=0;j<no_vertices;j++)
          {
            
             if(New_I[j][i]==1)
              {
              
                ones[z]=j;
                z++;
              }
          }
            
    addedge(edge, ones[0], ones[1]);
      }
  
  cout<<endl;
  cout<<"Distance Matrix of Tree"<<endl;
  for(int i=0;i<no_vertices;i++)
      {
        for(int j=0;j<no_vertices;j++)
          {
             d[i][j]=minEdgeBFS(edge, i, j, no_vertices); 
             cout<<d[i][j]<<" ";
          }
          cout<<endl;
      }
      COT();
    }
  
      
    
}

void go(int offset, int k) {
  if (k == 0) {
    print(combination);
    return;
  }
  for (int i = offset; i <= edges.size() - k; ++i) {
    combination.push_back(edges[i]);
    go(i+1, k-1);
    combination.pop_back();
  }
}

int main() {
  int n,k;
  cin>>no_edges>>no_vertices;
  k=no_vertices-1;
  n=no_edges;
  
  for(int i=0;i<no_vertices;i++)
      {
        for(int j=0;j<no_edges;j++)
          {
            cin>>I[i][j];
          }
      }
  int ones[2];
  vector <int> edge[no_vertices];
  
  for(int i=0;i<no_edges;i++)
      {
        int z=0;
        for(int j=0;j<no_vertices;j++)
          {
            
             if(I[j][i]==1)
              {
              
                ones[z]=j;
                z++;
              }
          }
            
    addedge(edge, ones[0], ones[1]);
      }
  
  
  cout<<"Distance Matrix"<<endl;
  for(int i=0;i<no_vertices;i++)
      {
        for(int j=0;j<no_vertices;j++)
          {
             d[i][j]=minEdgeBFS(edge, i, j, no_vertices); 
             cout<<d[i][j]<<" ";
          }
          cout<<endl;
      }
    
    Centre();
  
       
  for (int i = 0; i < n; ++i) { edges.push_back(i); }
  go(0, k);
  cout<<endl;
 
  cout<<"Total_No_Valid_Trees"<<endl;
  cout<<no_trees<<endl;
  cout<<endl;
  
  cout<<"Spanning Trees"<<endl;
  for(int i=0;i<no_trees;i++)
    {
        cout<< ": [ ";
      for(int j=0;j<(no_vertices-1);j++)
        {
          cout<<trees[i][j]<<" ";
        }
      cout << "] " << endl;
    }
  return 0;
}

