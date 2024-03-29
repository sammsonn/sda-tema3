**Nume: SAMSON Alexandru-Valentin**
**Grupă: 312CC**


## Tema 3 - Grafuri


### Descriere:

* Funcția initGraph primește un graf g și numărul de noduri n și inițializează
graful. Se setează numărul de noduri al grafului cu valoarea n. Apoi, se
parcurge fiecare nod din graf și se setează lista de adiacență a fiecărui nod cu
valoarea NULL, adică se creează liste de adiacență inițial vide. La final,
funcția returnează graful modificat.

* Funcția insertEdge primește un graf g, două noduri x și y, precum și costul și
distanța muchiei dintre acestea. Funcția creează un nou nod pentru a reprezenta
muchia și îi setează valorile corespunzătoare: valoarea nodului destinatar,
costul muchiei și distanța muchiei. Noul nod este apoi adăugat la începutul
listei de adiacență a nodului x, iar referința către acest nou nod devine capul
listei de adiacență a nodului x. La final, funcția returnează graful modificat.

* Funcția insertDepth parcurge lista de adiacență a fiecărui nod din graf și
verifică dacă nodul curent din listă are valoareas nodului sursă. Dacă da,
setează adâncimea nodului curent la valoarea adâncimii primite ca parametru.
Funcția returnează graful modificat.

* Funcția calculateScore primește un graf g și calculează scorul pentru fiecare
muchie în funcție de distanța și adâncimea acesteia. Pentru fiecare nod din
graf, se parcurge lista de adiacență asociată și se calculează scorul pentru
fiecare muchie. Scorul rezultat este atribuit câmpului score al nodului
respectiv. La final, funcția returnează graful modificat.

* Funcția addWord primește un dicționar, dimensiunea dicționarului și un cuvânt.
Scopul funcției este de a adăuga cuvântul în dicționar doar dacă acesta nu
există deja. Funcția parcurge dicționarul și compară fiecare cuvânt cu word
utilizând funcția strcmp. Dacă găsește un cuvânt identic în dicționar,
returnează indexul acelui cuvânt. În caz contrar, mărește dimensiunea
dicționarului și adaugă cuvântul la final utilizând funcția strcpy. La final,
funcția returnează indexul cuvântului adăugat în dicționar sau indexul
cuvântului existent dacă acesta a fost găsit anterior în dicționar.

* Funcția dfs realizează parcurgerea în adâncime a unui graf reprezentat prin
liste de adiacență. Funcția primește nodul de pornire node și un vector visited
care indică dacă un nod a fost sau nu vizitat. În cadrul funcției, se marchează
nodul curent ca vizitat în vectorul visited. Apoi se obține lista de vecini a
nodului curent și se parcurge această listă. Pentru fiecare vecin nevizitat, se
apelează recursiv funcția dfs pentru a explora acel vecin. Astfel, se realizează
o parcurgere în adâncime a întregului graf.

* Funcția countConnectedComponents utilizează funcția dfs pentru a număra și a
identifica componentele conexe ale unui graf. Ea primește graful graph și un
vector end pentru a stoca indicele ultimului nod din fiecare componentă conexă.
În cadrul funcției, se inițializează un vector visited pentru a marca nodurile
vizitate. Apoi, se parcurge fiecare nod al grafului. Dacă nodul nu a fost
vizitat anterior, se apelează funcția dfs pentru a explora componenta conexă
care conține acel nod. Contorul count este incrementat pentru fiecare
componentă conexă găsită, iar indicele ultimului nod din componentă este salvat
în vectorul end. La final, se salvează indicele ultimului nod din graf. Funcția
returnează numărul total de componente conexe găsite.

* Funcția makeSet este utilizată în cadrul structurii de date Union-Find pentru
a crea un nou set. Ea primește un pointer către structura UnionFind și
dimensiunea size a setului. În cadrul funcției, se alocă memorie pentru vectorii
parent și rank din cadrul structurii UnionFind, folosind malloc. Acești vectori
vor fi utilizați pentru a reprezenta relațiile de părinte și rangul fiecărui
element din set. Apoi, se parcurge fiecare element din set și se atribuie
fiecărui element părintele său și un rang inițial de 0. Astfel, fiecare element
este inițializat ca un set separat și autonom.

* Funcția find este utilizată în cadrul structurii de date Union-Find pentru a
găsi părintele unui element dintr-un set. Ea primește un pointer către structura
UnionFind și valoarea x a elementului pentru care se face căutarea. În cadrul
funcției, se verifică dacă părintele lui x este diferit de x însuși. Aceasta
înseamnă că x nu este părintele său real și trebuie căutat părintele său
recursiv pentru a găsi reprezentantul setului. Apelul recursiv al funcției find
este utilizat pentru a actualiza părintele lui x direct la părintele real găsit,
ceea ce optimizează ulterior căutările. La final, se returnează părintele lui x,
care reprezintă reprezentantul setului din care face parte x. Funcția returnează
părintele setului în care se află elementul x.

* Funcția unionSets este utilizată în cadrul structurii de date Union-Find
pentru a uni două seturi într-un set comun. Ea primește un pointer către
structura UnionFind și valorile x și y, reprezentând elementele din seturi care
urmează să fie unite. În cadrul funcției, se găsesc reprezentanții (părinții)
reali ai seturilor din x și y utilizând funcția find. Acest lucru se face pentru
a asigura că se operează cu reprezentanții reali în cadrul operațiilor de
uniune. Apoi, se compară rangurile (adâncimile) seturilor rootX și rootY.
Dacă rangul setului rootX este mai mic decât cel al setului rootY, se setează
părintele lui rootX să fie reprezentantul setului rootY, indicând astfel că x se
alătură setului lui y. Dacă rangul setului rootX este mai mare decât cel al
setului rootY, se setează părintele lui rootY să fie reprezentantul setului
rootX, indicând astfel că y se alătură setului lui x. Dacă rangurile seturilor
sunt egale, atunci se alege oricare dintre ele pentru a fi părintele, iar rangul
setului în care se face unirea este incrementat cu 1. Acest lucru menține
balanța în arborele de reprezentanți, asigurând o eficiență mai mare în
operații.

* Funcția compareEdges este utilizată ca argument în funcții de sortare pentru
a ordona un vector de muchii în ordine crescătoare, bazându-se pe greutatea
fiecărei muchii.

* Funcția kruskal implementează algoritmul Kruskal pentru a găsi arborele minim
de acoperire într-un graf neorientat. Se parcurg componentele conexe ale
grafului: numEdges reprezintă numărul de muchii din componenta conexă curentă și
este inițializat cu 0. Se colectează toate muchiile din componenta conexă
curentă și se adaugă în array-ul edges. Muchiile sunt colectate prin parcurgerea
nodurilor și a vecinilor lor în listele de adiacență ale grafului. Muchiile din
componenta conexă curentă sunt sortate în ordine crescătoare a greutății
folosind funcția qsort. Se creează o structură de date Union-Find pentru a
gestiona componente disjuncte. Se selectează muchii pentru formarea arborelui
minim de acoperire: se parcurg muchiile din componenta conexă curentă. Pentru
fiecare muchie, se verifică dacă includerea acesteia va crea un ciclu în
arborele minim de acoperire folosind funcția find din structura Union-Find. Dacă
muchia nu formează un ciclu, aceasta este adăugată în arborele minim de
acoperire prin unirea seturilor la care aparțin nodurile muchiei. Se numără și
se calculează greutatea totală a muchiilor selectate până în acest moment.
Algoritmul se oprește când s-au selectat muchii, deoarece un arbore de acoperire
pentru un graf cu n noduri are exact n-1 muchii. La finalul fiecărei componente
conexe, se stochează costul total al arborelui minim de acoperire în array-ul
total_cost. Se eliberează memoria alocată pentru structura Union-Find (uf) și se
termină funcția.

* Funcția compareInts este utilizată pentru a compara două valori întregi în
scopul sortării lor în ordine crescătoare. Funcția primește două pointeri a și b
la valorile întregi pe care dorim să le comparăm.

* Funcția djikstra implementează algoritmul lui Dijkstra pentru a găsi cel mai
scurt drum într-un graf ponderat de la un nod sursă la un nod destinație. Scorul
fiecărui nod este inițializat cu o valoare mare (INT_MAX), toate nodurile sunt
marcate ca nevizitate, nodurile anterioare sunt setate inițial ca inexistente și
scorul nodului sursă este setat la 0. Se parcurg pașii algoritmului lui
Dijkstra: se găsește nodul cu scorul minim care nu a fost încă vizitat,
se marchează nodul ca vizitat, se actualizează scorurile nodurilor adiacente
nevizitate, dacă este necesar. La finalul algoritmului, se verifică scorul
nodului destinație: dacă scorul este INT_MAX, nu există un drum către destinație
și se setează *isRoad la 0. Altfel, există un drum către destinație și se
setează *isRoad la 1. Se reconstruiește drumul cel mai scurt folosind nodurile
anterioare și se stochează în best_road. Funcția returnează numărul de noduri în
drumul cel mai scurt (road_nodes).

* Funcția invertIntArray primește un array de numere întregi și îl inversează,
schimbând ordinea elementelor în array. Utilizează o abordare de tip
"two-pointer" pentru a swap-ui elementele de la pozițiile start și end în
fiecare iterație până când start devine mai mare sau egal cu end, ceea ce
înseamnă că întregul array a fost inversat.

* Funcția getData primește un graf g, două noduri x și y, și câteva array-uri
pentru a stoca distanțele și adâncimile asociate muchiilor dintre nodurile
x și y. Aceasta parcurge lista de adiacență a nodului x în căutarea unei muchii
către nodul y. Dacă o astfel de muchie este găsită, atunci distanța minimă
dintre x și y este actualizată și adâncimea muchiei este salvată în array-ul
depths. La final, distanța minimă este salvată în array-ul distances, iar
numărul total de date obținute este incrementat cu 1.

* Funcția clearGraphMemory este folosită pentru a elibera memoria ocupată de un
graf. Parcurge fiecare nod al grafului și pentru fiecare nod, parcurge lista de
adiacență și eliberează memoria ocupată de fiecare nod adiacent. Astfel, toate
nodurile și listele de adiacență asociate sunt eliberate din memorie, asigurând
astfel că nu există scurgeri de memorie.

* Funcția main execută diferite acțiuni în funcție de valoarea argumentului task
citit din linia de comandă. Funcția deschide fișierele de intrare și ieșire,
citeste și procesează datele necesare, efectuează operații pe graf și scrie
rezultatele în fișierul de ieșire. La final, se închid fișierele și se
eliberează memoria ocupată de graf.

### Comentarii asupra temei:

* Implementarea mi se pare destul de bună, am reușit să nu am leak-uri de
memorie, dar sigur era posibil să fie și mai eficientă sau mai scurtă. Totuși
sunt mulțumit cu această rezolvare.

* Tema această m-a învățat cum să lucrez cu grafuri, precum și algoritmii lui
Kruskal și Djikstra.

### Punctajul obținut la teste local:

* Punctajul Acumulat este: 120.0/100p!
