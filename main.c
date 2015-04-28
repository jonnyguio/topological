#include <stdio.h>
#include <stdlib.h>


typedef struct graph {
  int level;
  int i;
  int *adj;
} graph;


int main() {
  int i, j, n, m, counter, numbers;
  graph *g;
  char *name, *s;

  scanf("%d", &n); scanf("%d", &m);
  g = (graph *) malloc(sizeof(graph)*n);
  for (i = 0; i < n; i++) {
    g[i].i = i;
    g[i].adj = malloc(sizeof(int)*m);
  }

  counter = 0;
  name = malloc(sizeof(char) * (m + (m - 1) + 1)); // + 1 because of null
  for (i = 0; i <= n; i++) {
    //scanf("%d", &number);
    fgets(name, 9, stdin);
    if (i != 0) {
      if (name[0] != '\n') {
        strtok(name, "\n");
        s = name;
        for (numbers = 0; s[numbers] != '\0'; s[numbers] == ' '? numbers++ : *s++);
        numbers++;
        g[i-1].level = numbers;
        printf("i: %d - Line: %s - Level: %d\n", i, name, numbers);
        char *endPtr;
        endPtr = name;
        for (j = numbers; j > 0; j--)
          *(g[i-1].adj+(numbers-j)) = (int) strtol(endPtr, &endPtr, 10);
        puts("");
      }
      else {
        name[0] = ' ';
      }
    }
  }
  for (i = 1; i <= n; i++) {
    printf("%d ", i);
    for (j=0; j < g[i-1].level; j++)
      printf("- %d ", g[i-1].adj[j]);
    puts("");
  }
}
/*
#include <stdio.h>
#include <stdlib.h>

#define NAME_MAX    80
#define NAME_MAX_S "80"

int main(void)
{
    char *name;
    name = malloc(sizeof(char) * (NAME_MAX + 1)); // + 1 because of null
    if(scanf("%80[^\n]", name) != 1)
    {
        fputs("io error or premature end of line\n", stderr);
        return 1;
    }

    printf("Hello %s. Nice to meet you.\n", name);
}
*/
