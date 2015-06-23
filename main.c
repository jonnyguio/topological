#include <stdio.h>
#include <stdlib.h>

typedef struct adj {
    int i;
    struct adj *next;
} adj;

typedef struct node {
  int i, size, grau;
  struct node *next;
  struct adj *adjInit;
} node;

void insertNode(node **init, int index, int adj) {
    node **aux;
    if (*init == NULL) {
        *init = (node *) malloc(sizeof(node));
        (*init)->next = NULL;
        (*init)->i = index;
        (*init)->adjInit = NULL;
        (*init)->grau = 0;
        (*init)->size = 0;
    }
    else {
        for (aux = init; (*aux)->next; aux = &((*aux)->next));
        (*aux)->next = (node *) malloc(sizeof(node));
        (*aux)->next->next = (node *) NULL;
        (*aux)->next->i = index;
        (*aux)->next->adjInit = NULL;
        (*aux)->next->grau = 0;
        (*aux)->next->size = 0;
    }

}

void setSize(node **init, int index, int size) {
    node **aux;
    for (aux = init; *aux; aux = &((*aux)->next)) {
        if ((*aux)->i == index) {
            (*aux)->size = size;
            break;
        }
    }
}

int getSize(node *init, int index) {
    node *aux;
    for (aux = init; aux; aux = aux->next) {
        if (aux->i == index)
            return aux->size;
    }
    return -1;
}

void setAdj(adj **init, int index, int val) {
    adj **aux;
    int i = 1;
    aux = init;
    while (i < index) {
        aux = &((*aux)->next);
        i++;
    }
    (*aux)->i = val;
    /*for (aux = init; *aux; aux = &((*aux)->next)) {
        if ((*aux)->i = index) {
            (*aux)->i = val;
            break;
        }
    }*/
}

int getAdj(adj *init, int iterations) {
    int i;
    adj *aux;
    aux = init;
    for (i = 0; i < iterations; i++) {
        aux = aux->next;
    }
    return aux->i;
}

void insertOnAdj(adj **init, int val) {
    adj **aux;
    if (*init != (adj *) NULL) {
        for (aux = init; (*aux)->next != NULL; aux = &((*aux)->next));
        (*aux)->next = (adj *) malloc(sizeof(adj));
        (*aux)->next->next = (adj *) NULL;
        (*aux)->next->i = val;
    }
    else {
        *init = (adj *) malloc(sizeof(adj));
        (*init)->next = (adj *) NULL;
        (*init)->i = val;
    }
}

void insertAdj(node *init, int index, int iadj) {
    node *aux;
    for (aux = init; aux; aux = aux->next) {
        if (aux->i == index) {
            insertOnAdj(&(aux->adjInit), iadj);
            break;
        }
    }
}

void increaseGrau(node **init, int index) {
    node **aux;
    for (aux = init; *aux; aux = &((*aux)->next)) {
        if ((*aux)->i == index) {
            (*aux)->grau++;
        }
    }
}

void decreaseGrau(node **init, int index) {
    node **aux;
    for (aux = init; *aux; aux = &((*aux)->next)) {
        if ((*aux)->i == index) {
            (*aux)->grau--;
        }
    }
}

int getGrau(node *init, int index) {
    node *aux;
    for (aux = init; aux; aux = aux->next) {
        if (aux->i == index) {
            return aux->grau;
        }
    }
    return -1;
}

void printAdj(adj *init) {
    adj *aux;
    for (aux = init; aux; aux = aux->next) {
        printf("%d |", aux->i);
    }
    printf("\n");
}

void printNode(node *init) {
    node *aux;
    for (aux = init; aux; aux = aux->next) {
        printf("%d - %d - %d\n", aux->i, aux->grau, aux->size);
        printAdj(aux->adjInit);
    }
    printf("\n");
}

int getOnAdj(node *init, int index, int indexAdj) {
    node *aux;
    adj *aux2;
    int i;
    for (aux = init; aux; aux = aux->next) {
        if (aux->i == index)
            break;
    }
    if (aux) {
        aux2 = aux->adjInit;
        i = 1;
        while (i < indexAdj) {
            aux2 = aux2->next;
            i++;
        }
    }
    return aux2->i;
}

int main() {
    int i, j, n, m, counter, numbers, add;
    node *init;
    char *name, *s;

    scanf("%d", &n); scanf("%d", &m);
    init = (node *) NULL;
    for (i = 0; i < n; i++) {
    insertNode(&init, i + 1, m);
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
          setSize(&init, i + 1, numbers);
          //g[i].size = numbers;

          char *endPtr;
          endPtr = name;
          for (j = numbers; j > 0; j--) {
            add = (int) strtol(endPtr, &endPtr, 10);
            insertAdj(init, i + 1, add);
            //g[i].adj[(numbers-j)] = (int) strtol(endPtr, &endPtr, 10);
            increaseGrau(&init, add);
            //g[g[i].adj[(numbers-j)]-1].grau++;
          }
        }
        else {
          name[0] = ' ';
          setSize(&init, i + 1, 0);
          //g[i].size = 0;
        }
    }

    adj *q;
    //int *q;
    q = NULL;
    //q = malloc(sizeof(int)*n);

    counter = 0;
    for (i = 0; i < n; i++) {
        //q[i] = 0;
        insertOnAdj(&q, 0);
        //if (g[i].grau == 0) {
        if (getGrau(init, i + 1) == 0) {
            setAdj(&q, counter + 1, i + 1);
            //q[counter] = g[i].i;
            counter++;
        }
    }

    j = 0;
    while (getAdj(q, n - 1) != -1) { // q[n-1]

        //printNode(init);

        printf("%d\n", getAdj(q, j)); // q[j];

        for (i = 0; i < getSize(init, getAdj(q, j)); i++) { // g[q[j]-1].size
            decreaseGrau(&init, getOnAdj(init, getAdj(q, j), i + 1));
            if (getGrau(init, getOnAdj(init, getAdj(q, j), i + 1)) == 0) { // --g[g[q[j]-1].adj[i] - 1].grau
                setAdj(&q, counter + 1, getOnAdj(init, getAdj(q, j), i + 1)); //q[counter] = g[g[q[j]-1].adj[i] - 1].i;
                counter++;
            }
        }

        setAdj(&q, j + 1, -1);
        //q[j] = -1;
        j++;
    }
    puts("");
}
