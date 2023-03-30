#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "main.h"
#define MAXV 200

//Remove espaços em branco de uma string
//Recebe: String de entrada
//Retorna: String sem espaços em branco
void removeSpaces(char* str){
    int i, j;
    for(i = 0, j = 0; str[i] != '\0'; i++){
        if(str[i] != ' ') str[j++] = str[i];
    }
    str[j] = '\0';
}

//Lê o número de vértices do grafo
//Recebe: A linha do f contendo o número
//Retorna: O número
int getVnumber(char *str){
    int number;
    char *aux = (char*) malloc(sizeof(str) + 1);
    strcpy(aux, str);
    strtok(aux, "=");
    aux = strtok(NULL, "=");
    number = atoi(aux);
    aux = strtok(NULL, "=");
    free(aux);
    return number;
}

//Inicializa o grafo preenchendo a matriz com 0
//Recebe: O grafo e seu tamanho
//Retorna: Nada
void startGraph(int graph[][MAXV], int n){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++) graph[i][j] = 0;
    }
}

//Remove o primeiro caractere de uma string
//Recebe: String de entrada
//Retorna: String sem o primeiro caractere
char* removeFirst(char *str){
    char *aux = (char*) malloc(strlen(str) + 1);
    char *ptr = aux;
    str++;
    while(*str){
        *aux = *str;
        aux++;
        str++;
    }
    aux = 0;
    return ptr;
}

//Carrega as arestas do grafo
//Recebe: O grafo, a linha da aresta no f de texto e a opção (orientado ou não)
//Retorna: Nada
void loadgraph(int graph[][MAXV], char *str, int opt){
    int x, y, weight;
    char *aux = (char*) malloc(strlen(str) + 1);
    char *temp = (char*) malloc(strlen(str) + 1);
    strcpy(aux, str);
    strcpy(temp, str);
    strtok(aux, ",");
    x = atoi(removeFirst(aux));
    aux = strtok(NULL, ",");
    strtok(aux, ")");
    y = atoi(aux);
    aux = strtok(NULL, ")");
    aux = strtok(NULL, ")");
    free(aux);
    strtok(temp, ":");
    temp = strtok(NULL, ":");
    weight = atoi(temp);
    temp = strtok(NULL, ":");
    free(temp);
    graph[x][y] = weight;
    if(opt != 1) graph[y][x] = weight;
}

//Verifica se o grafo contem pesos negativos
//Recebe: O grafo e seu tamanho
//Retorna: 0 ou 1
int hasNegative(int graph[][MAXV], int n){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(graph[i][j] < 0) return 1;
        }
    }
    return 0;
}

//Limpa todos os nós da lista
//Recebe: A cabeça da lista
//Retorna: Nada
void deletelist(List* start){
    while (start != NULL){
        List* temp = start;
        start = start -> next;
        free(temp);
    }
}

//Mostra o menu da aplicação
//Recebe: Nada
//Retorna: A opção escolhida
int showMenu(){
    int n;
    printf("\n\n[MENU]\n");
    printf("\t1)Busca em profundidade\n");
    printf("\t2)Busca em largura\n");
    printf("\t3)Dijkstra\n");
    printf("\t4)Bellman-Ford\n");
    printf("\t5)Floyd-Warshall\n");
    printf("\t6)Kruskal\n");
    printf("\t7)Prim\n");
    printf("\t8)Desenhar grafo\n");
    printf("Escolha a opcao: ");
    scanf("%d%*c", &n);
    return n;
}

//Mostra os valores de uma lista
//Recebe: A cabeça da lista
//Retorna: Nada
void printlist(List *l){
    while(l != NULL){
        printf(" %d ", l->data);
        l = l->next;
    }
}

//Insere valores na lista em ordem crescente
//Recebe: Referência da cabeça da lista e o valor a ser inserido
//Retorna: Nada
void sortedInsert(struct no** head, int x){
    struct no* new_node = (struct no*) malloc(sizeof(struct no));
    struct no* current;
    new_node->data = x;
    if (*head == NULL || (*head)->data >= new_node->data){
        new_node->next = *head;
        *head = new_node;
    }else{
        current = *head;
        while(current->next != NULL && current->next->data < new_node->data) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

//Verifica quais são os vértices adjacentes a um vértice
//Recebe: O grafo, seu tamanho e o vértice de origem
//Retorna: Lista de vértices adjacentes
List* getAdj(int graph[][MAXV], int n, int x){
    int j;
    List *l = NULL;
    for(j = 0; j < n; j++){
        if(graph[x][j] != 0) sortedInsert(&l, j);
    }
    return l;
}

//Visita um vértice na busca em profundidade
//Recebe: Vetor de vértices visitados, quantidade de vértices, vértice a ser visitado e o grafo
//Retorna: Nada
void visit(int visited[], int n, int x, int graph[][MAXV]){
    if(visited[x] == 1) return;
    visited[x] = 1;
    printf(" %d ", x);
    List *adj = getAdj(graph, n, x);
    while(adj != NULL){
        visit(visited, n, adj->data, graph);
        adj = adj->next;
    }
    deletelist(adj);
}

//Faz a busca em profundidade
//Recebe: O grafo e seu tamanho
//Retorna: Nada
void deepsearch(int graph[][MAXV], int n){
    int i, visited[MAXV], x;
    printf("Insira o vertice de origem: ");
    scanf("%d%*c", &x);
    for(i = 0; i < n; i++) visited[i] = 0;
    visit(visited, n, x, graph);
    for(i = 0; i < n; i++){
        if(visited[i] == 0) visit(visited, n, i, graph);
    }
}

//Cria uma fila vazia
//Recebe: Nada
//Retorna: A fila vazia
Queue* createQueue(){
    Queue *q = (Queue*) malloc(sizeof(Queue));
    q->start = NULL;
    q->end = NULL;
    return q;
}

//Insere um valor na fila
//Recebe: A fila e o valor
//Retorna: Nada
void enqueue(Queue *q, int x){
    struct no* aux = (struct no*) malloc(sizeof(struct no));
    aux->data = x;
    aux->next = NULL;
    if(q->start == NULL) q->start = aux;
    else q->end->next = aux;
    q->end = aux;
}

//Retira um valor da fila
//Recebe: A fila
//Retorna: Nada
void dequeue(Queue *q){
    if(q->start == NULL) return;
    struct no* aux = q->start;
    if(q->start == q->end) q->end = NULL;
    q->start = q->start->next;
    free(aux);
}

//Faz a busca em largura
//Recebe: O grafo, seu tamanho, vértice de origem, opt(chamada inicial ou recursiva), vetor de vértices visitados
//Retorna: Nada
void widthsearch(int graph[][MAXV], int n, int x, int opt, int visited[]){
    int i, distance[MAXV], current;
    List *adj, *aux;
    Queue *q = createQueue();
    if(opt == 0){
        for(i = 0; i < n; i++){
            if(i == x) continue;
            visited[i] = 0;
            distance[i] = (int)INFINITY;
        }
    }
    visited[x] = 1;
    distance[x] = 0;
    enqueue(q, x);
    if(q->start != NULL) printf(" %d ", q->start->data);
    while(q->start != NULL){
        current = q->start->data;
        adj = getAdj(graph, n, current);
        aux = adj;
        while(adj != NULL){
            if(visited[adj->data] == 0){
                printf(" %d ", adj->data);
                visited[adj->data] = 1;
                distance[adj->data] = distance[current] + 1;
                enqueue(q, adj->data);
            }
            adj = adj->next;
        }
        dequeue(q);
        visited[current] = 2;
        deletelist(aux);
    }
    for(i = 0; i < n; i++){
        if(visited[i] == 0) widthsearch(graph, n, i, 1, visited);
    }
}

//Calcula a quantidade de arestas no grafo
//Recebe: O grafo e seu tamanho
//Retorna: A quantidade de arestas
int calcEdges(int graph[][MAXV], int n){
    int i, j, count;
    count = 0;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(graph[i][j] != 0) count++;
        }
    }
    return count;
}

//Lê as arestas do grafo
//Recebe: O grafo, seu tamanho e a quantidade de arestas
//Retorna: Vetor de arestas
struct Edge* getEdges(int graph[][MAXV], int n, int e){
    int i, j, count;
    struct Edge *aux = (struct Edge *)malloc(e * sizeof(struct Edge));
    count = 0;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(graph[i][j] != 0){
                aux[count].u = i;
                aux[count].v = j;
                aux[count].w = graph[i][j];
                count++;
            }
        }
    }
    return aux;
}

//Insere um valor na lista
//Recebe: A lista e o valor a ser inserido
//Retorna: A lista com o valor inserido
List* insertlist(List *l, int x){
    struct no *aux = (struct no*) malloc(sizeof(struct no));
    aux->data = x;
    aux->next = l;
    return aux;
}

//Mostra o caminho percorrido de um vértice até outro
//Recebe: Vetor de precedentes, vértice de início e vértice de fim
//Retorna: Nada
void showpath(int arr[], int start, int end){
    int current = end;
    List *l = NULL;
    l = insertlist(l, end);
    while(current != start){
        current = arr[current];
        l = insertlist(l, current);
    }
    printlist(l);
    deletelist(l);
}

//Mostra os resultados do algoritmo de bellman-ford
//Recebe: Vetor de distâncias, de precedentes, quantidade de vértices e vértice de início
//Retorna: Nada
void showbellman(int distance[], int p[], int n, int start){
    int i;
    printf("origem:  %d\n", start);
    for(i = 0; i < n; i++){
        if(distance[i] != (int)INFINITY){
            printf("destino:  %d dist.:  %d caminho: ", i, distance[i]);
            showpath(p, start, i);
        }
        else printf("destino:  %d dist.: -- caminho: --", i);
        printf("\n");
    }
}

//Algoritmo de bellman-ford
//Recebe: Grafo e vértice de origem
//Retorna: Nada
void bellmanford(struct Graph *g){
    int i, j, u, v, w, source;
    int d[MAXV], p[MAXV];
    printf("Insira o vertice de origem: ");
    scanf("%d%*c", &source);
    for(i = 0; i < g->V; i++){
        d[i] = (int)INFINITY;
        p[i] = 0;
    }
    d[source] = 0;
    for (i = 1; i <= g->V - 1; i++){
        for(j = 0; j < g->E; j++){
            u = g->edge[j].u;
            v = g->edge[j].v;
            w = g->edge[j].w;
            if(d[u] != (int)INFINITY && d[v] > d[u] + w){
                d[v] = d[u] + w;
                p[v] = u;
            }
        }
    }
    for(i = 0; i < g->E; i++){
        u = g->edge[i].u;
        v = g->edge[i].v;
        w = g->edge[i].w;
        if(d[u] != (int)INFINITY && d[v] > d[u] + w){
            printf("O algoritmo de Bellman-Ford nao pode ser aplicado - grafo com ciclo de peso negativo");
            return;
        }
    }
    showbellman(d, p, g->V, source);
}

//Função auxiliar do mergesort
//Recebe:O array, posições da esquerda, meio e direita
//Retorna: Nada
void merge(struct Edge *arr, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    struct Edge *L = (struct Edge *)malloc(n1 * sizeof(struct Edge));
    struct Edge *R = (struct Edge *)malloc(n2 * sizeof(struct Edge));
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while(i < n1 && j < n2){
        if(L[i].w <= R[j].w){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

//Ordena um vetor de arestas
//Recebe: Vetor de arestas, 0 e o tamanho do vetor - 1
//Retorna: Nada
void mergeSort(struct Edge *arr, int l, int r){
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

//Calcula a posição de um item no vetor de listas
//Recebe: O vetor de listas, seu tamanho e o item
//Retorna: A posição do item
int getindex(List* vet[], int n, int x){
    int i, index;
    index = -1;
    for(i = 0; i < n; i++){
        List *l = vet[i];
        while(l != NULL){
            if(l->data == x) index = i;
            l = l->next;
        }
    }
    return index;
}

//Junta duas listas
//Recebe: As duas listas
//Retorna: Lista unida
List* append(List *l1, List *l2){
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;
    List *aux = l1;
    List *ant = l1;
    while(l1 != NULL){
        ant = l1;
        l1 = l1->next;
    }
    ant->next = l2;
    return aux;
}

//Faz a operação de união entre os conjuntos do algoritmo de Kruskal
//Recebe: O vetor de listas, seu tamanho, e dois vértices
//Retorna: Nada
void unite(List* vet[], int n, int u, int v){
    int x, y;
    x = getindex(vet, n, u);
    y = getindex(vet, n, v);
    List *l1 = vet[x];
    List *l2 = vet[y];
    l1 = append(l1, l2);
    vet[y] = NULL;
}

//Remove metade das arestas, usado pra não ter arestas duplicadas no caso de grafo não orientado
//Recebe: Vetor de arestas e seu tamanho
//Retorna: Vetor de arestas com tamanho modificado
struct Edge* removehalf(struct Edge *e, int n){
    int i, count;
    struct Edge *aux = (struct Edge *)malloc((n / 2) * sizeof(struct Edge));
    count = 0;
    for(i = 0; i < n; i++){
        if(i % 2 == 0){
            aux[count] = e[i];
            count++;
        }
    }
    return aux;
}

//Visita um vértice no grafo
//Recebe: Vetor de vértices visitados, quantidade de vértices, vértice a ser visitado e o grafo
//Retorna: Nada
void visitcon(int visited[], int n, int x, int graph[][MAXV]){
    if(visited[x] == 1) return;
    visited[x] = 1;
    List *adj = getAdj(graph, n, x);
    while(adj != NULL){
        visitcon(visited, n, adj->data, graph);
        adj = adj->next;
    }
    deletelist(adj);
}

//Verifica se um grafo é conexo
//Recebe: O grafo e seu tamanho
//Retorna: 1 caso seja conexo, 0 caso não
int isconex(int graph[][MAXV], int n){
    int i, x, visited[MAXV];
    x = 0;
    for(i = 0; i < n; i++) visited[i] = 0;
    visitcon(visited, n, x, graph);
    for(i = 0; i < n; i++){
        if(visited[i] == 0) return 0;
    }
    return 1;
}

//Desenha o grafo colorido do algoritmo de Kruskal
//Recebe: O grafo, seu tamanho, vetor de arestas e seu tamanho, flag de orientado
//Retorna: Nada
void drawgraphkruskal(int matrix[][MAXV], int n, struct Edge* final, int size, int isoriented){
    FILE *f = fopen("grafo.dot", "w");
    int i, j;
    if(isoriented) fprintf(f, "strict digraph {\n");
    else fprintf(f, "strict graph {\n");
    for(i = 0; i < n; i++) fprintf(f, "  %d\n", i);
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(matrix[i][j]){
                if(isoriented) fprintf(f, "  %d -> %d [label=\"%d\", weight = \"%d\"]\n", i, j, matrix[i][j], matrix[i][j]);
                else fprintf(f, "  %d -- %d [label=\"%d\", weight = \"%d\"]\n", i, j, matrix[i][j], matrix[i][j]);
            }
        }
    }
    for(i = 0; i < size; i++){
        if(isoriented) fprintf(f, "  %d -> %d [color = \"red\"]\n", final[i].u, final[i].v);
        else fprintf(f, "  %d -- %d [color = \"red\"]\n", final[i].u, final[i].v);
    }
    fprintf(f, "}\n");
    fclose(f);
    system("dot -Tpng grafo.dot -o grafo.png");
    system(".\\grafo.png");
}

//Implementação do algoritmo de Kruskal
//Recebe: O grafo, suas arestas, grafo em matriz adjacência, seu tamanho e o flag de orientado
//Retorna: Nada
void kruskal(struct Graph *g, struct Edge *edge, int graph[][MAXV], int tam, int isoriented){
    if(!isconex(graph, tam)){
        printf("O algoritmo de Kruskal nao pode ser executado - grafo nao conexo");
        return;
    }
    if(isoriented){
        printf("O algoritmo de Kruskal nao pode ser executado - grafo orientado");
        return;
    }
    if(hasNegative(graph, tam)){
        printf("O algoritmo de Kruskal nao pode ser executado - grafo possui pesos negativos");
        return;
    }
    int i, n, size, count, u, v, w, totalw, count2;
    n = g->E;
    size = g->V;
    count = 0;
    totalw = 0;
    count2 = 0;
    mergeSort(edge, 0, n - 1);
    struct Edge *aux = (struct Edge *)malloc((n / 2) * sizeof(struct Edge));
    for(i = 0; i < n; i++){
        if(i % 2 == 0){
            aux[count2] = edge[i];
            count2++;
        }
    }
    n = n / 2;
    List* vet[MAXV];
    struct Edge *final = (struct Edge *)malloc(n * sizeof(struct Edge));
    for(i = 0; i < size; i++) vet[i] = NULL;
    for(i = 0; i < size; i++) vet[i] = insertlist(vet[i], i);
    for(i = 0; i < n; i++){
        u = aux[i].u;
        v = aux[i].v;
        w = aux[i].w;
        if(getindex(vet, size, u) != getindex(vet, size, v)){
            unite(vet, size, u, v);
            final[count].u = u;
            final[count].v = v;
            final[count].w = w;
            totalw = totalw + w;
            count = count + 1;
        }
    }
    printf("\npeso total:  %d\n", totalw);
    printf("arestas: ");
    for(i = 0; i < count; i++) printf(" (%d,%d)", final[i].u, final[i].v);
    drawgraphkruskal(graph, tam, final, count, isoriented);
    free(final);
    for(i = 0; i < size; i++){
        deletelist(vet[i]);
        vet[i] = NULL;
    }
    free(aux);
}

//Checa se todos os vértices foram visitados
//Recebe: O vetor de vértices visitados e seu tamanho
//Retorna: 1 caso sim, 0 caso não
int visitedall(int vet[], int n){
    int i;
    for(i = 0; i < n; i++){
        if(vet[i] == 0) return 0;
    }
    return 1;
}

//Procura pela posição do valor de chave mínimo que ainda não tenha sido visitado
//Recebe: Vetor de chaves, vetor de vértices visitados e quantidade de vértices
//Retorna: Posição do valor
int extractmin(int vet[], int vet2[], int n){
    int i, min, minpos;
    min = (int)INFINITY;
    minpos = -1;
    for(i = 0; i < n; i++){
        if(vet[i] <= min && vet2[i] == 0){
            min = vet[i];
            minpos = i;
        }
    }
    return minpos;
}

//Desenha o grafo colorido do algoritmo de Prim
//Recebe: O grafo, seu tamanho, o vetor de predicados e o flag de orientado
//Retorna: Nada
void drawgraphprim(int matrix[][MAXV], int n, int pred[], int isoriented){
    FILE *f = fopen("grafo.dot", "w");
    int i, j;
    if(isoriented) fprintf(f, "strict digraph {\n");
    else fprintf(f, "strict graph {\n");
    for(i = 0; i < n; i++) fprintf(f, "  %d\n", i);
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(matrix[i][j]){
                if(isoriented) fprintf(f, "  %d -> %d [label=\"%d\", weight = \"%d\"]\n", i, j, matrix[i][j], matrix[i][j]);
                else fprintf(f, "  %d -- %d [label=\"%d\", weight = \"%d\"]\n", i, j, matrix[i][j], matrix[i][j]);
            }
        }
    }
    for(i = 0; i < n; i++){
        if(i != pred[i]){
            if(isoriented) fprintf(f, "  %d -> %d [color = \"red\"]\n", pred[i], i);
            else fprintf(f, "  %d -- %d [color = \"red\"]\n", pred[i], i);
        }
    }
    fprintf(f, "}\n");
    fclose(f);
    system("dot -Tpng grafo.dot -o grafo.png");
    system(".\\grafo.png");
}

//Implementação do algoritmo de Prim
//Recebe: O grafo, seu tamanho e o flag de orientado
//Retorna: Nada
void prim(int graph[][MAXV], int tam, int isoriented){
    if(!isconex(graph, tam)){
        printf("O algoritmo de Prim nao pode ser executado - grafo nao conexo");
        return;
    }
    if(isoriented){
        printf("O algoritmo de Prim nao pode ser executado - grafo orientado");
        return;
    }
    if(hasNegative(graph, tam)){
        printf("O algoritmo de Prim nao pode ser executado - grafo possui pesos negativos");
        return;
    }
    int pred[MAXV];
    int key[MAXV];
    int visited[MAXV];
    List *adj, *temp;
    int i, min, totalw, x;
    printf("Insira o vertice de origem: ");
    scanf("%d%*c", &x);
    for(i = 0; i < tam; i++){
        visited[i] = 0;
        key[i] = (int)INFINITY;
    }
    key[x] = 0;
    totalw = 0;
    pred[x] = x;
    while(!visitedall(visited, tam)){
        min = extractmin(key, visited, tam);
        visited[min] = 1;
        adj = getAdj(graph, tam, min);
        temp = adj;
        while(adj != NULL){
            if(visited[adj->data] == 0){
                if(graph[min][adj->data] < key[adj->data]){
                    pred[adj->data] = min;
                    key[adj->data] = graph[min][adj->data];
                }
            }
            adj = adj->next;
        }
        deletelist(temp);
        adj = NULL;
        temp = NULL;
    }
    for(i = 0; i < tam; i++){
        if(key[i] != (int)INFINITY) totalw += key[i];
    }
    printf("\nvertice inicial:  %d\n", x);
    printf("peso total:  %d\n", totalw);
    printf("arestas: ");
    for(i = 0; i < tam; i++){
        if(i != pred[i]) printf(" (%d,%d)", pred[i], i);
    }
    drawgraphprim(graph, tam, pred, isoriented);
}

//Implementação do algoritmo de Dijkstra
//Recebe: O grafo e seu tamanho
//Retorna: Nada
void dijkstra(int graph[][MAXV], int n){
    if(hasNegative(graph, n)){
	    printf("O algoritmo de dijkstra nao pode ser aplicado - grafo possui pesos negativos");
	    return;
	}
    List *adj, *aux;
    int distance[MAXV];
    int pred[MAXV];
    int visited[MAXV];
    int i, min, x;
    printf("Insira o vertice de origem: ");
    scanf("%d%*c", &x);
    for(i = 0; i < n; i++){
        distance[i] = (int)INFINITY;
        pred[i] = (int)INFINITY;
    }
    distance[x] = 0;
    for(i = 0; i < n; i++) visited[i] = 0;
    while(!visitedall(visited, n)){
        min = extractmin(distance, visited, n);
        visited[min] = 1;
        adj = getAdj(graph, n, min);
        aux = adj;
        while(adj != NULL){
            if(distance[adj->data] > distance[min] + graph[min][adj->data]){
                distance[adj->data] = distance[min] + graph[min][adj->data];
                pred[adj->data] = min;
            }
            adj = adj->next;
        }
        free(aux);
        adj = NULL;
        aux = NULL;
    }
    printf("origem:  %d\n", x);
    for(i = 0; i < n; i++){
        printf("destino:  %d ", i);
        if(distance[i] < 200000000 && distance[i] > -200000000){
            printf("dist.:  %d  ", distance[i]);
            printf("caminho: ");
            showpath(pred, x, i);
            printf("\n");
        }else printf("dist.: --  caminho: --\n");
    }
}

//Mostra o caminho de um vértice a outro no algoritmo de Floyd-Warshall
//Recebe: Matriz de distâncias, matriz de precedentes, vértice de início e vértice de fim
//Retorna: Nada
void printpath(int dist[][MAXV], int pred[][MAXV], int x, int y){
    if(dist[x][y] == (int)INFINITY){
        printf("---\n");
        return;
    }
    List *l = NULL;
    while (y != x) {
        l = insertlist(l, y);
        y = pred[x][y];
    }
    l = insertlist(l, x);
    printlist(l);
    printf("\n");
    deletelist(l);
}

//Implementação do algoritmo de Floyd-Warshall
//Recebe: Matriz modificada, estrutura inicial da matriz de predecentes e quantidade de vértices
//Retorna: Nada
void floydw(int graph[][MAXV], int pred[][MAXV], int n){
    int dist[MAXV][MAXV];
    int i, j, k;
    for(i = 0; i < n; i++){
        for (j = 0; j < n; j++) dist[i][j] = graph[i][j];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (dist[i][j] == (int)INFINITY) pred[i][j] = -1; 
            else pred[i][j] = i;
        }
    }
    for(k = 0; k < n; k++){
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++) {
                if(dist[i][k] != (int)INFINITY && dist[k][j] != (int)INFINITY && dist[i][k] + dist[k][j] < dist[i][j]){                 
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }
            }
        }
    }
    for(i = 0; i < n; i++){
        if(dist[i][i] < 0){
            printf("O algoritmo de Floyd-Warshall nao pode ser executado - grafo possui ciclo negativo");
            return;
        }
    }
    printf("Matriz de distancias:\n");
    printf("     ");
    for(i = 0; i < n; i++) printf(" %3d ", i);
    printf("\n");
    for(i = 0; i < n; i++){
        printf(" %3d ", i);
        for(j = 0; j < n; j++){
            if(dist[i][j] == (int)INFINITY) printf(" --- "); 
            else printf(" %3d ", dist[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("caminho de %d para %d: ", i, j);
            printpath(dist, pred, i, j);
        }
    }
}

//Cria a matriz adjacência modificada e envia para o algoritmo de Floyd-Warshall
//Recebe: O grafo e seu tamanho
//Retorna: Nada
void floydwarshall(int graph[][MAXV], int n){
    int aux[MAXV][MAXV], pred[MAXV][MAXV];
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(i == j) aux[i][j] = 0;
            else if(graph[i][j] != 0) aux[i][j] = graph[i][j];
            else aux[i][j] = (int)INFINITY;
            pred[i][j] = -1;
        }
    }
    floydw(aux, pred, n);
}

//Desenha o grafo
//Recebe: Seu tamanho, o grafo e o flag de orientado
//Retorna: Nada
void drawgraph(int matrix[][MAXV], int n, int isoriented){
    FILE *f = fopen("grafo.dot", "w");
    if(isoriented) fprintf(f, "strict digraph {\n");
    else fprintf(f, "strict graph {\n");
    for(int i = 0; i < n; i++) fprintf(f, "  %d\n", i);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(matrix[i][j]){
                if(isoriented) fprintf(f, "  %d -> %d [label=\"%d\", weight = \"%d\"]\n", i, j, matrix[i][j], matrix[i][j]);
                else fprintf(f, "  %d -- %d [label=\"%d\", weight = \"%d\"]\n", i, j, matrix[i][j], matrix[i][j]);
            }
        }
    }
    fprintf(f, "}\n");
    fclose(f);
    system("dot -Tpng grafo.dot -o grafo.png");
    system(".\\grafo.png");
}

//Função principal
//Recebe: Nada
//Retorna: 0
int main(){
    FILE *f;
    char line[25];
    int i, isoriented, vertexnumber, opt, x;
    int graph[MAXV][MAXV];
    int visited[MAXV];
    char filename[30];
    printf("Insira o nome do arquivo: ");
    scanf("%[^\n]%*c", filename);
    f = fopen(filename, "r");
    for(i = 0; fgets(line, 25, f); i++){
        removeSpaces(line);
        if(i == 0){
            if(strcmp("orientado=nao\n", line) == 0) isoriented = 0;
            else isoriented = 1;
        }
        else if(i == 1){
            vertexnumber = getVnumber(line);
            startGraph(graph, vertexnumber);
        }
        else{
            if(*line == '('){
                if(isoriented) loadgraph(graph, line, 1);
                else loadgraph(graph, line, 2);
            }
        }
    }
    fclose(f);
    struct Graph *g = (struct Graph *)malloc(sizeof(struct Graph));
    g->V = vertexnumber;
    g->E = calcEdges(graph, vertexnumber);
    g->edge = getEdges(graph, vertexnumber, g->E);
    opt = 1;
    while(opt){
        opt = showMenu();
        if(opt == 1) deepsearch(graph, vertexnumber);
        if(opt == 2){
            printf("Insira o vertice de origem: ");
            scanf("%d%*c", &x);
            widthsearch(graph, vertexnumber, x, 0, visited);
        }
        if(opt == 3) dijkstra(graph, vertexnumber);
        if(opt == 4) bellmanford(g);
        if(opt == 5) floydwarshall(graph, vertexnumber);
        if(opt == 6) kruskal(g, g->edge, graph, vertexnumber, isoriented);
        if(opt == 7) prim(graph, vertexnumber, isoriented);
        if(opt == 8) drawgraph(graph, vertexnumber, isoriented);
    }
    free(g);
    return 0;
}
