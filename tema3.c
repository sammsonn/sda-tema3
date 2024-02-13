/* SAMSON Alexandru-Valentin - 312CC */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#define SIZE_MAX 31

int main(int argc, char *argv[])
{
    int i, task, nodes, roads, cost, dictSize, sourceNr, destinationNr,
        componentsNr, distance, depth, weight, roadNodes, isRoad, count,
        totalRoadDistance, maxWeight, end[SIZE_MAX], totalCost[SIZE_MAX],
        bestRoad[SIZE_MAX], depths[SIZE_MAX], distances[SIZE_MAX];
    FILE *fr, *fw;
    char dictionary[SIZE_MAX][SIZE_MAX], source[SIZE_MAX], destination[SIZE_MAX];
    Graf graph;

    // Deschiderea fișierelor de intrare și ieșire
    fr = fopen("tema3.in", "r");
    fw = fopen("tema3.out", "w");

    // Citirea valorii argumentului task din linia de comandă
    task = atoi(argv[1]);

    // Cerința 1
    if (task == 1)
    {
        // Citirea numărului de noduri și muchii
        fscanf(fr, "%d %d", &nodes, &roads);
        dictSize = 0;
        // Inițializarea grafului
        graph = initGraph(graph, nodes);

        // Citirea datelor despre fiecare muchie și adăugarea lor în graf
        for (i = 1; i <= roads; i++)
        {
            fscanf(fr, "%s %s %d", source, destination, &cost);
            sourceNr = addWord(dictionary, &dictSize, source);
            destinationNr = addWord(dictionary, &dictSize, destination);

            graph = insertEdge(graph, sourceNr, destinationNr, cost, 0);
            graph = insertEdge(graph, destinationNr, sourceNr, cost, 0);
        }

        // Determinarea numărului de componente
        // conexe și scrierea rezultatului în fișier
        componentsNr = countConnectedComponents(graph, end);
        fprintf(fw, "%d\n", componentsNr);

        // Aplicarea algoritmului lui Kruskal pentru fiecare componentă
        // conexă și scrierea costului minim al arborelui de acoperire în fișier
        kruskal(&graph, end, componentsNr, totalCost);
        qsort(totalCost, componentsNr, sizeof(int), compareInts);

        for (i = 0; i < componentsNr; i++)
        {
            fprintf(fw, "%d\n", totalCost[i]);
            printf("%d\n", totalCost[i]);
        }
    }
    // Cerința 2
    else if (task == 2)
    {
        // Citirea numărului de noduri și muchii
        fscanf(fr, "%d %d", &nodes, &roads);
        dictSize = 0;
        // Inițializarea grafului
        graph = initGraph(graph, nodes);

        // Citirea datelor despre fiecare muchie și adăugarea lor în graf
        for (i = 1; i <= roads; i++)
        {
            fscanf(fr, "%s %s %d", source, destination, &distance);
            sourceNr = addWord(dictionary, &dictSize, source);
            destinationNr = addWord(dictionary, &dictSize, destination);

            graph = insertEdge(graph, sourceNr, destinationNr, 0, distance);
        }

        // Citirea adâncimii pentru fiecare nod și adăugarea acesteia în graf
        for (i = 1; i <= nodes; i++)
        {
            fscanf(fr, "%s %d", source, &depth);
            sourceNr = addWord(dictionary, &dictSize, source);

            graph = insertDepth(graph, sourceNr, depth);
        }

        // Citirea greutății
        fscanf(fr, "%d", &weight);

        // Calcularea scorului pentru fiecare muchie din graf
        graph = calculateScore(graph);
        // Adăugarea cuvântului "Corabie" în dicționar
        // și obținerea numărului asociat
        sourceNr = addWord(dictionary, &dictSize, "Corabie");
        // Adăugarea cuvântului "Insula" în
        // dicționar și obținerea numărului asociat
        destinationNr = addWord(dictionary, &dictSize, "Insula");
        // Aplicarea algoritmului Dijkstra pentru a determina
        // drumul cel mai scurt între "Corabie" și "Insula"
        roadNodes = dijkstra(&graph, sourceNr, destinationNr, dictionary,
                             bestRoad, &isRoad);

        if (!isRoad)
        {
            // Dacă nu există drum între cele două noduri, se
            // afișează un mesaj corespunzător în fișierul de ieșire
            fprintf(fw, "Echipajul nu poate ajunge la insula\n");
        }
        else
        {
            // Adăugarea cuvântului "Insula" în dicționar
            // și obținerea numărului asociat
            sourceNr = addWord(dictionary, &dictSize, "Insula");
            // Adăugarea cuvântului "Corabie" în dicționar
            // și obținerea numărului asociat
            destinationNr = addWord(dictionary, &dictSize, "Corabie");
            // Aplicarea algoritmului Dijkstra pentru a determina
            // drumul cel mai scurt între "Insula" și "Corabie"
            roadNodes = dijkstra(&graph, sourceNr, destinationNr, dictionary,
                                 bestRoad, &isRoad);

            if (!isRoad)
            {
                // Dacă nu există drum între cele două noduri, se afișează
                // un mesaj corespunzător în fișierul de ieșire
                fprintf(fw, "Echipajul nu poate transporta comoara inapoi la corabie\n");
            }
            else
            {
                // Inversarea ordinei elementelor din vectorul bestRoad
                invertIntArray(bestRoad, roadNodes);
                totalRoadDistance = 0;
                count = 0;

                // Parcurgerea drumului cel mai scurt și
                // scrierea nodurilor în fișierul de ieșire
                for (i = 2; i <= roadNodes; i++)
                {
                    fprintf(fw, "%s ", dictionary[bestRoad[i]]);
                }
                fprintf(fw, "\n");

                // Obținerea distanțelor și adâncimilor pentru fiecare pereche
                // de noduri consecutive și actualizarea valorilor corespunzătoare
                for (i = 2; i < roadNodes; i++)
                {
                    getData(graph, bestRoad[i], bestRoad[i + 1], distances,
                            depths, &count);
                }

                maxWeight = depths[0];

                // Calcularea distanței totale a drumului
                for (i = 0; i < count; i++)
                {
                    totalRoadDistance = totalRoadDistance + distances[i];
                }

                // Determinarea greutății maxime și scrierea
                // rezultatelor în fișierul de ieșire
                for (i = 0; i < count - 1; i++)
                {
                    if (maxWeight > depths[i])
                    {
                        maxWeight = depths[i];
                    }
                }

                fprintf(fw, "%d\n%d\n%d\n", totalRoadDistance, maxWeight,
                        weight / maxWeight);
            }
        }
    }

    // Închiderea fișierelor de intrare și ieșire
    fclose(fr);
    fclose(fw);

    // Eliberarea memoriei ocupate de graf
    clearGraphMemory(graph);

    return 0;
}
