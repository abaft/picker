#include <stdlib.h>
#include <stdio.h>

struct person
{
  char name[50];
  int priority;
};

int main()
{
  int seed;
  scanf("%i", &seed);
  srand(seed);
  struct person people[] =
  {
    {"Ben", rand()},
    {"Kavan", rand()},
    {"Josh B", rand()},
    {"Gypsy", rand()},
    {"Josh K", rand()},
    {"Dirty Perv", rand()}
  };

  for (int j = 0; j < sizeof(people)/sizeof(struct person); ++j)
  {
    struct person* max = people;
    for (int i = 0; i < sizeof(people)/sizeof(struct person); ++i)
    {
      if (people[i].priority > max->priority) max = people + i;
    }
    printf("%i) %s %i\n", j + 1, max->name, max->priority);
    max->priority = -1;
  }
}
