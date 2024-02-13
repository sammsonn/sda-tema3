/* SAMSON Alexandru-Valentin - 312CC */

#define SIZE_MAX 31

typedef struct nod
{
    int val, cost;
    int depth, distance;
    float score;
    struct nod *next;
} Nod, *PNod;

typedef struct graf
{
    int n;
    PNod a[SIZE_MAX];
} Graf;

typedef struct edge
{
    int source, destination, weight;
} Edge;

typedef struct unionfind
{
    int *parent;
    int *rank;
} UnionFind;

Graf initGraph(Graf g, int n);
Graf insertEdge(Graf g, int x, int y, int cost, int distance);
Graf insertDepth(Graf g, int source_nr, int depth);
Graf calculateScore(Graf g);
void dfs(Graf graph, int node, int visited[SIZE_MAX]);
void makeSet(UnionFind *uf, int size);
void unionSets(UnionFind *uf, int x, int y);
void kruskal(Graf *graph, int end[], int components_nr, int total_cost[]);
void invertIntArray(int arr[], int size);
void getData(Graf g, int x, int y, int distances[], int depths[], int *count);
void clearGraphMemory(Graf g);
int addWord(char dictionary[][SIZE_MAX], int *dict_size, char word[]);
int countConnectedComponents(Graf graph, int beginning[]);
int find(UnionFind *uf, int x);
int compareEdges(const void *a, const void *b);
int compareInts(const void *a, const void *b);
int dijkstra(Graf *graph, int source, int destination,
             char dictionary[][SIZE_MAX], int best_road[], int *isRoad);
