#include <stdio.h>
#include <stdlib.h>

typedef struct adj {
    int i;
    adj *next;
} adj;

typedef struct node {
  int i, size, grau;
  node *next;
  adj *adjInit;
} node;

void insertNode(node *init, int index, int adj) {
    node *aux;
    if (init == (node *) NULL) {
        init = (node *) malloc(sizeof(node));
        init->next = (node *) NULL;
        init->i = index;
        init->adj = (adj *) NULL;
        init->grau = 0;
    }
    else {
        for (aux = init; aux->next; aux = aux->next);
        aux->next = (node *) malloc(sizeof(node));
        aux->next->next = (node *) NULL;
        aux->next->i = index;
        aux->next->adj = (adj *) NULL;
        aux->next->grau = 0;
    }

}

void setSize(node *init, int index, int size) {
    node *aux;
    for (aux = init; aux; aux = aux->next) {
        if (aux->i == index) {
            aux->size = size;
            break;
        }
    }
}

void insertOnAdj(adj *init, int val) {
    adj *aux;
    if (init != (adj *) NULL) {
        for (aux = init; aux->next; aux = aux->next);
        aux->next = (adj *) malloc(sizeof(adj));
        aux->next->next = (adj *) NULL;
        aux->next->i = val;
    }
    else {
        init = (adj *) malloc(sizeof(adj));
        init->next = (adj *) NULL;
        init->i = val;
    }
}

void insertAdj(node *init, int index, int iadj) {
    node *aux;
    for (aux = init; aux; aux = aux->next) {
        if (aux->i == index) {
            insertOnAdj(aux->adj, iadj);
            break;
        }
    }
}

void increaseGrau(node *init, int index) {
    node *aux;
    for (aux = init; aux; aux = aux->next) {
        if (aux->i == index) {
            aux->grau++;
        }
    }
}

int main() {
  int i, j, n, m, counter, numbers, add;
  node *init;
  char *name, *s;

  scanf("%d", &n); scanf("%d", &m);
  init = (node *) malloc(sizeof(node)*n);
  for (i = 0; i < n; i++) {
    insertNode(init, i + 1, m)
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
      setSize(init, i + 1, numbers);
      //g[i].size = numbers;

      char *endPtr;
      endPtr = name;
      for (j = numbers; j > 0; j--) {
        add = (int) strtol(endPtr, &endPtr, 10);
        insertAdj(init, numbers - j + 1, add);
        //g[i].adj[(numbers-j)] = (int) strtol(endPtr, &endPtr, 10);
        increaseGrau(init, add);
        //g[g[i].adj[(numbers-j)]-1].grau++;
      }
    }
    else {
      name[0] = ' ';
      setSize(init, i + 1, 0);
      //g[i].size = 0;
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
