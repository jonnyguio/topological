#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
  int i, *adj, size, grau;
} graph;

int main() {
  int i, j, n, m, counter, numbers;
  graph *g;
  char *name, *s;

  scanf("%d", &n); scanf("%d", &m);
  g = (graph *) malloc(sizeof(graph)*n);
  for (i = 0; i < n; i++) {
    g[i].i = i + 1;
    g[i].adj = malloc(sizeof(int)*m);
    g[i].grau = 0;
  }

  counter = 0;
  name = malloc(sizeof(char) * (m + (m - 1) + 1)); // + 1 because of null
  fgets(name, 9, stdin); // forcing to jump one line
  for (i = 0; i < n; i++) {
    name[0] = '\n';
    fgets(name, 9, stdin);
    if (name[0] != '\n') {
      strtok(name, "\n");
      s = name;
      for (numbers = 0; s[numbers] != '\0'; s[numbers] == ' '? numbers++ : *s++);
      numbers++;
      g[i].size = numbers;
      char *endPtr;
      endPtr = name;
      for (j = numbers; j > 0; j--) {
        g[i].adj[(numbers-j)] = (int) strtol(endPtr, &endPtr, 10);
        g[g[i].adj[(numbers-j)]-1].grau++;
      }
    }
    else {
      name[0] = ' ';
      g[i].size = 0;
    }
  }

  int *q, *result;
  q = malloc(sizeof(int)*n);

  counter = 0;
  for (i = 0; i < n; i++) {
    q[i] = 0;
    if (g[i].grau == 0) {
      q[counter] = g[i].i;
      counter++;
    }
  }

  j = 0;
  while (q[n-1] != -1) {
    
    printf("%d ", q[j]);

    for (i = 0; i < g[q[j]-1].size; i++) {
      if (--g[g[q[j]-1].adj[i] - 1].grau == 0) {
        q[counter] = g[g[q[j]-1].adj[i] - 1].i;
        counter++;
      }
    }

    q[j] = -1;
    j++;
  }
  puts("");
}
