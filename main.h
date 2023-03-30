#define MAXV 200

typedef struct no{
  int data;
  struct no* next;
}List;

typedef struct{
  struct no* start;
  struct no* end;
}Queue;

struct Edge {
  int u;
  int v;
  int w;
};

struct Graph {
  int V;
  int E;
  struct Edge *edge;
};

//Remove espaços em branco de uma string
//Recebe: String de entrada
//Retorna: String sem espaços em branco
void removeSpaces(char *str);

//Lê o número de vértices do grafo
//Recebe: A linha do f contendo o número
//Retorna: O número
int getVnumber(char *str);

//Inicializa o grafo preenchendo a matriz com 0
//Recebe: O grafo e seu tamanho
//Retorna: Nada
void startGraph(int graph[][MAXV], int n);

//Remove o primeiro caractere de uma string
//Recebe: String de entrada
//Retorna: String sem o primeiro caractere
char* removeFirst(char *str);

//Carrega as arestas do grafo
//Recebe: O grafo, a linha da aresta no f de texto e a opção (orientado ou não)
//Retorna: Nada
void loadgraph(int graph[][MAXV], char *str, int opt);

//Verifica se o grafo contem pesos negativos
//Recebe: O grafo e seu tamanho
//Retorna: 0 ou 1
int hasNegative(int graph[][MAXV], int n);

//Limpa todos os nós da lista
//Recebe: A cabeça da lista
//Retorna: Nada
void deletelist(List* start);

//Mostra o menu da aplicação
//Recebe: Nada
//Retorna: A opção escolhida
int showMenu();

//Mostra os valores de uma lista
//Recebe: A cabeça da lista
//Retorna: Nada
void printlist(List *l);

//Insere valores na lista em ordem crescente
//Recebe: Referência da cabeça da lista e o valor a ser inserido
//Retorna: Nada
void sortedInsert(struct no** head, int x);

//Verifica quais são os vértices adjacentes a um vértice
//Recebe: O grafo, seu tamanho e o vértice de origem
//Retorna: Lista de vértices adjacentes
List* getAdj(int graph[][MAXV], int n, int x);

//Visita um vértice na busca em profundidade
//Recebe: Vetor de vértices visitados, quantidade de vértices, vértice a ser visitado e o grafo
//Retorna: Nada
void visit(int visited[], int n, int x, int graph[][MAXV]);

//Faz a busca em profundidade
//Recebe: O grafo e seu tamanho
//Retorna: Nada
void deepsearch(int graph[][MAXV], int n);

//Cria uma fila vazia
//Recebe: Nada
//Retorna: A fila vazia
Queue* createQueue();

//Insere um valor na fila
//Recebe: A fila e o valor
//Retorna: Nada
void enqueue(Queue *q, int x);

//Retira um valor da fila
//Recebe: A fila
//Retorna: Nada
void dequeue(Queue *q);

//Faz a busca em largura
//Recebe: O grafo, seu tamanho, vértice de origem, opt(chamada inicial ou recursiva), vetor de vértices visitados
//Retorna: Nada
void widthsearch(int graph[][MAXV], int n, int x, int opt, int visited[]);

//Calcula a quantidade de arestas no grafo
//Recebe: O grafo e seu tamanho
//Retorna: A quantidade de arestas
int calcEdges(int graph[][MAXV], int n);

//Lê as arestas do grafo
//Recebe: O grafo, seu tamanho e a quantidade de arestas
//Retorna: Vetor de arestas
struct Edge* getEdges(int graph[][MAXV], int n, int e);

//Insere um valor na lista
//Recebe: A lista e o valor a ser inserido
//Retorna: A lista com o valor inserido
List* insertlist(List *l, int x);

//Mostra o caminho percorrido de um vértice até outro
//Recebe: Vetor de precedentes, vértice de início e vértice de fim
//Retorna: Nada
void showpath(int arr[], int start, int end);

//Mostra os resultados do algoritmo de bellman-ford
//Recebe: Vetor de distâncias, de precedentes, quantidade de vértices e vértice de início
//Retorna: Nada
void showbellman(int distance[], int p[], int n, int start);

//Algoritmo de bellman-ford
//Recebe: Grafo e vértice de origem
//Retorna: Nada
void bellmanford(struct Graph *g);

//Função auxiliar do mergesort
//Recebe:O array, posições da esquerda, meio e direita
//Retorna: Nada
void merge(struct Edge *arr, int l, int m, int r);

//Ordena um vetor de arestas
//Recebe: Vetor de arestas, 0 e o tamanho do vetor - 1
//Retorna: Nada
void mergeSort(struct Edge *arr, int l, int r);

//Calcula a posição de um item no vetor de listas
//Recebe: O vetor de listas, seu tamanho e o item
//Retorna: A posição do item
int getindex(List* vet[], int n, int x);

//Junta duas listas
//Recebe: As duas listas
//Retorna: Lista unida
List* append(List *l1, List *l2);

//Faz a operação de união entre os conjuntos do algoritmo de Kruskal
//Recebe: O vetor de listas, seu tamanho, e dois vértices
//Retorna: Nada
void unite(List* vet[], int n, int u, int v);

//Remove metade das arestas, usado pra não ter arestas duplicadas no caso de grafo não orientado
//Recebe: Vetor de arestas e seu tamanho
//Retorna: Vetor de arestas com tamanho modificado
struct Edge* removehalf(struct Edge *e, int n);

//Visita um vértice no grafo
//Recebe: Vetor de vértices visitados, quantidade de vértices, vértice a ser visitado e o grafo
//Retorna: Nada
void visitcon(int visited[], int n, int x, int graph[][MAXV]);

//Verifica se um grafo é conexo
//Recebe: O grafo e seu tamanho
//Retorna: 1 caso seja conexo, 0 caso não
int isconex(int graph[][MAXV], int n);

//Implementação do algorítmo de Kruskal
//Recebe: O grafo, suas arestas, grafo em matriz adjacência, seu tamanho e o flag de orientado
//Retorna: Nada
void kruskal(struct Graph *g, struct Edge *edge, int graph[][MAXV], int tam, int isoriented);

//Checa se todos os vértices foram visitados
//Recebe: O vetor de vértices visitados e seu tamanho
//Retorna: 1 caso sim, 0 caso não
int visitedall(int vet[], int n);

//Procura pela posição do valor de chave mínimo que ainda não tenha sido visitado
//Recebe: Vetor de chaves, vetor de vértices visitados e quantidade de vértices
//Retorna: Posição do valor
int extractmin(int vet[], int vet2[], int n);

//Implementação do algorítmo de Prim
//Recebe: O grafo, seu tamanho e o flag de orientado
//Retorna: Nada
void prim(int graph[][MAXV], int tam, int isoriented);

//Implementação do algoritmo de Dijkstra
//Recebe: O grafo e seu tamanho
//Retorna: Nada
void dijkstra(int graph[][MAXV], int n);

//Mostra o caminho de um vértice a outro no algoritmo de Floyd-Warshall
//Recebe: Matriz de distâncias, matriz de precedentes, vértice de início e vértice de fim
//Retorna: Nada
void printpath(int dist[][MAXV], int pred[][MAXV], int x, int y);

//Implementação do algoritmo de Floyd-Warshall
//Recebe: Matriz modificada, estrutura inicial da matriz de predecentes e quantidade de vértices
//Retorna: Nada
void floydw(int graph[][MAXV], int pred[][MAXV], int n);

//Cria a matriz adjacência modificada e envia para o algorítmo de Floyd-Warshall
//Recebe: O grafo e seu tamanho
//Retorna: Nada
void floydwarshall(int graph[][MAXV], int n);

//Desenha o grafo
//Recebe: Seu tamanho, o grafo e o flag de orientado
//Retorna: Nada
void drawgraph(int matrix[][MAXV], int n, int isoriented);

//Desenha o grafo colorido do algoritmo de Kruskal
//Recebe: O grafo, seu tamanho, vetor de arestas e seu tamanho, flag de orientado
//Retorna: Nada
void drawgraphkruskal(int matrix[][MAXV], int n, struct Edge* final, int size, int isoriented);

//Desenha o grafo colorido do algoritmo de Prim
//Recebe: O grafo, seu tamanho, o vetor de predicados e o flag de orientado
//Retorna: Nada
void drawgraphprim(int matrix[][MAXV], int n, int pred[], int isoriented);

//Função principal
//Recebe: Nada
//Retorna: 0
int main();
