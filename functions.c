/* SAMSON Alexandru-Valentin - 312CC */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#define SIZE_MAX 31
#define INT_MAX 99

// Funcție pentru inițializarea unui graf
Graf initGraph(Graf g, int n)
{
    int i;

    // Numărul de noduri din graf
    g.n = n;
    for (i = 1; i <= n; i++)
    {
        // Inițializăm lista de adiacență a
        // fiecărui nod cu valoarea NULL (listă vidă)
        g.a[i] = NULL;
    }

    return g;
}

// Funcție pentru adăugarea unei muchii (x, y) într-un graf
Graf insertEdge(Graf g, int x, int y, int cost, int distance)
{
    PNod nou = (PNod)malloc(sizeof(Nod));

    nou->val = y;
    nou->cost = cost;
    nou->distance = distance;

    // Noul nod devine capul listei de adiacență pentru nodul x
    nou->next = g.a[x];
    // Noul nod este adăugat la începutul listei de adiacență pentru nodul x
    g.a[x] = nou;

    // Returnăm graful modificat
    return g;
}

// Funcție pentru inserarea adâncimii pentru un nod sursă în graf
Graf insertDepth(Graf g, int source_nr, int depth)
{
    int i;

    // Parcurgem lista de adiacență a fiecărui nod din graf
    for (i = 1; i <= g.n; i++)
    {
        PNod list = g.a[i];
        while (list != NULL)
        {
            // Verificăm dacă nodul curent din listă are valoarea nodului sursă
            if (list->val == source_nr)
            {
                // Dacă da, setăm adâncimea nodului
                // curent la valoarea adâncimii primite ca parametru
                list->depth = depth;
            }
            list = list->next;
        }
    }

    // Returnăm graful modificat
    return g;
}

// Funcție pentru calcularea scorului pentru fiecare muchie dintr-un graf
Graf calculateScore(Graf g)
{
    int i;

    for (i = 1; i <= g.n; i++)
    {
        // Obținem capul listei de adiacență pentru nodul i
        PNod list = g.a[i];
        while (list != NULL)
        {
            // Calculăm scorul pentru muchia curentă
            list->score = (float)list->distance / list->depth;
            // Trecem la următorul nod din lista de adiacență
            list = list->next;
        }
    }

    // Returnăm graful modificat
    return g;
}

// Funcție pentru adăugarea unui cuvânt în dicționar
int addWord(char dictionary[][SIZE_MAX], int *dict_size, char word[])
{
    int i;

    for (i = 1; i <= *dict_size; i++)
    {
        // Verificăm dacă cuvântul există deja în dicționar
        if (!strcmp(word, dictionary[i]))
        {
            // Returnăm indexul cuvântului din dicționar
            return i;
        }
    }
    // Creștem dimensiunea dicționarului
    *dict_size = *dict_size + 1;
    // Adăugăm cuvântul la finalul dicționarului
    strcpy(dictionary[*dict_size], word);

    // Returnăm indexul cuvântului adăugat în dicționar
    return i;
}

// Funcție pentru parcurgerea în adâncime (DFS) a unui graf
void dfs(Graf graph, int node, int visited[SIZE_MAX])
{
    // Marcăm nodul curent ca vizitat
    visited[node] = 1;
    // Obținem lista de vecini a nodului curent
    PNod neighbor = graph.a[node];

    while (neighbor != NULL)
    {
        // Verificăm dacă vecinul nu a fost vizitat anterior
        if (!visited[neighbor->val])
        {
            // Apelăm recursiv funcția DFS pentru vecinul nevizitat
            dfs(graph, neighbor->val, visited);
        }
        // Trecem la următorul vecin al nodului curent
        neighbor = neighbor->next;
    }
}

// Funcție pentru numărarea componentelor conexe ale unui graf
int countConnectedComponents(Graf graph, int end[])
{
    int i, count = 0;
    int visited[SIZE_MAX];

    // Inițializăm toate nodurile ca nevizitate
    for (i = 1; i <= graph.n; i++)
    {
        visited[i] = 0;
    }

    for (i = 1; i <= graph.n; i++)
    {
        // Verificăm dacă nodul nu a fost vizitat anterior
        if (!visited[i])
        {
            // Apelăm funcția DFS pentru a explora componenta conexă
            dfs(graph, i, visited);
            // Incrementăm contorul pentru fiecare componentă conexă găsită
            count++;
            // Salvăm indicele ultimului nod din componenta conexă curentă
            end[count - 1] = i - 1;
        }
    }
    // Salvăm indicele ultimului nod din graf
    end[count] = graph.n;

    // Returnăm numărul de componente conexe găsite
    return count;
}

// Funcție pentru crearea unui set în cadrul structurii UnionFind
void makeSet(UnionFind *uf, int size)
{
    int i;

    uf->parent = (int *)malloc((size + 1) * sizeof(int));
    uf->rank = (int *)malloc((size + 1) * sizeof(int));

    for (i = 1; i <= size; i++)
    {
        // Inițializăm fiecare element ca fiind părintele său
        uf->parent[i] = i;
        // Inițializăm rangul fiecărui element cu 0
        uf->rank[i] = 0;
    }
}

// Funcție pentru găsirea reprezentantului (părintelui) unui element într-un set
int find(UnionFind *uf, int x)
{
    // Dacă elementul x nu este părintele său
    if (uf->parent[x] != x)
    {
        // Recursiv, găsim părintele real
        // al lui x și îl actualizăm pentru optimizare
        uf->parent[x] = find(uf, uf->parent[x]);
    }

    // Returnăm părintele lui x (reprezentantul setului)
    return uf->parent[x];
}

// Funcție pentru unirea a două seturi într-un set comun
void unionSets(UnionFind *uf, int x, int y)
{
    // Găsim reprezentantul setului din x
    int rootX = find(uf, x);
    // Găsim reprezentantul setului din y
    int rootY = find(uf, y);

    // Dacă rangul (adâncimea) setului din x este mai mic decât cel din y
    if (uf->rank[rootX] < uf->rank[rootY])
    {
        // Setăm părintele lui x să fie reprezentantul setului din y
        uf->parent[rootX] = rootY;
    }
    // Dacă rangul (adâncimea) setului din x este mai mare decât cel din y
    else if (uf->rank[rootX] > uf->rank[rootY])
    {
        // Setăm părintele lui y să fie reprezentantul setului din x
        uf->parent[rootY] = rootX;
    }
    // Dacă rangurile seturilor sunt egale
    else
    {
        // Setăm părintele lui y să fie reprezentantul setului din x
        uf->parent[rootY] = rootX;
        // Creștem rangul (adâncimea) setului din x cu 1
        uf->rank[rootX]++;
    }
}

// Funcție de comparare a două muchii (edges) pentru
// sortarea acestora în ordine crescătoare după greutate
int compareEdges(const void *a, const void *b)
{
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;

    // Returnăm diferența de greutate dintre cele două muchii
    return edgeA->weight - edgeB->weight;
}

// Algoritmul Kruskal pentru găsirea arborelui
// minim de acoperire într-un graf neorientat
void kruskal(Graf *graph, int end[], int components_nr, int total_cost[])
{
    int numNodes = graph->n;
    Edge edges[35];

    int k, i = 1, j, count = 1;
    
    // Parcurgem fiecare componentă conexă
    for (j = 1; j <= components_nr; j++)
    {
        int numEdges = 0;

        // Colectăm toate muchiile din graf
        for (; i <= end[count]; i++)
        {
            PNod neighbor = graph->a[i];
            while (neighbor != NULL)
            {
                if (i < neighbor->val)
                {
                    edges[numEdges].source = i;
                    edges[numEdges].destination = neighbor->val;
                    edges[numEdges].weight = neighbor->cost;
                    numEdges++;
                }
                neighbor = neighbor->next;
            }
        }

        // Sortăm muchiile în ordine crescătoare a greutății
        qsort(edges, numEdges, sizeof(Edge), compareEdges);

        // Creăm o structură de date Union-Find
        UnionFind uf;
        makeSet(&uf, numNodes);

        int numSelectedEdges = 0;
        int totalWeight = 0;

        for (k = 0; k < numEdges; k++)
        {
            int source = edges[k].source;
            int destination = edges[k].destination;
            int weight = edges[k].weight;

            // Verificăm dacă includerea acestei muchii va crea un ciclu
            if (find(&uf, source) != find(&uf, destination))
            {
                unionSets(&uf, source, destination);
                numSelectedEdges++;
                totalWeight += weight;

                // Oprim dacă am selectat (numNodes - 1) muchii
                if (numSelectedEdges == numNodes - 1)
                {
                    break;
                }
            }
        }
        count++;
        total_cost[j - 1] = totalWeight;

        free(uf.parent);
        free(uf.rank);
    }
}

// Funcție de comparare pentru sortarea întregilor în ordine crescătoare
int compareInts(const void *a, const void *b)
{
    int *A = (int *)a;
    int *B = (int *)b;

    // Returnăm diferența dintre valorile întregilor
    return *A - *B;
}

// Algoritmul lui Dijkstra pentru a găsi
// cel mai scurt drum într-un graf ponderat
int dijkstra(Graf *graph, int source, int destination,
             char dictionary[][SIZE_MAX], int best_road[], int *isRoad)
{
    int i, n = graph->n;
    int road_nodes = 0;
    float score[SIZE_MAX];
    int visited[SIZE_MAX];
    int previous[SIZE_MAX];

    // Inițializăm array-urile score, visited și previous
    for (i = 1; i <= n; i++)
    {
        // Inițializăm scorul cu o valoare mare
        score[i] = INT_MAX;
        // Setăm toate nodurile ca nevizitate
        visited[i] = 0;
        // Setăm nodul anterior ca inexistent
        previous[i] = -1;
    }

    score[source] = 0; // Scorul nodului sursă este 0

    for (i = 1; i <= n; i++)
    {
        // Găsim nodul cu scorul minim care nu a fost vizitat încă
        float minScore = INT_MAX;
        int minNode = -1;
        for (int j = 1; j <= n; j++)
        {
            if (!visited[j] && score[j] < minScore)
            {
                minScore = score[j];
                minNode = j;
            }
        }

        if (minNode == -1)
            break;

        // Marchăm nodul ca vizitat
        visited[minNode] = 1;

        // Actualizăm scorurile nodurilor adiacente
        PNod current = graph->a[minNode];
        while (current != NULL)
        {
            int neighbor = current->val;
            float edgeScore = current->score;
            if (!visited[neighbor] &&
                score[minNode] + edgeScore < score[neighbor])
            {
                score[neighbor] = score[minNode] + edgeScore;
                previous[neighbor] = minNode;
            }
            current = current->next;
        }
    }

    if (score[destination] == INT_MAX)
    {
        // Destinația nu este atinsă, deci nu există drum
        *isRoad = 0;
    }
    else
    {
        // Destinația este atinsă, există un drum
        *isRoad = 1;
        // Reconstruim drumul cel mai scurt prin nodurile anterioare
        int current = destination;
        road_nodes++;
        best_road[road_nodes] = current;

        while (current != -1)
        {
            current = previous[current];
            road_nodes++;
            best_road[road_nodes] = current;
        }
    }
    // Returnăm numărul de noduri în drumul cel mai scurt
    return road_nodes;
}

// Inversează un array de numere întregi
void invertIntArray(int arr[], int size)
{
    int start = 1;
    int end = size;

    while (start < end)
    {
        // Schimbă elementele de la pozițiile start și end
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        // Mută pozițiile start și end spre centrul array-ului
        start++;
        end--;
    }
}

// Obține date din graf pentru o anumită pereche de noduri (x, y)
void getData(Graf g, int x, int y, int distances[], int depths[], int *count)
{
    int min_distance = INT_MAX;
    // Lista de adiacență pentru nodul x în graf
    PNod list = g.a[x];

    while (list != NULL)
    {
        // Verifică dacă există o muchie către nodul y
        if (list->val == y)
        {
            // Verifică și actualizează distanța minimă
            if (min_distance > list->distance)
            {
                min_distance = list->distance;
            }
            // Salvează adâncimea muchiei în array-ul depths
            depths[*count] = list->depth;
        }

        // Trece la următorul nod adiacent în lista de adiacență
        list = list->next;
    }

    // Salvează distanța minimă în array-ul distances
    distances[*count] = min_distance;
    // Incrementează numărul de date obținute (count)
    *count = *count + 1;
}

// Eliberează memoria ocupată de graf
void clearGraphMemory(Graf g)
{
    int i;

    for (i = 1; i <= g.n; i++)
    {
        // Obține lista de adiacență pentru nodul curent
        PNod current = g.a[i];

        while (current != NULL)
        {
            PNod next = current->next;
            // Eliberează memoria ocupată de nodul curent
            free(current);
            // Trece la următorul nod în listă
            current = next;
        }
    }
}
