#include <stdlib.h>
#include <stdio.h>
#include <openssl/rsa.h>

struct person
{
  char* name;
  int priority;
};

char* read_the_line()
{
  size_t c = 0;
  char* s = NULL, * i;
  char e = 1;
  do
  {
    s = realloc(s, sizeof(char) * c + 50);
    for(i = s + c; (e = (*i = fgetc(stdin)) != EOF && *i != '\n') && (++c)%51 == 50; ++i);
  }while(e);
  return (*i = '\0', realloc(s, sizeof(char) * c + 1));
}

void clear_input_buffer()
{
  char i;
  while((i = fgetc(stdin)) != EOF && i != '\n');
}

int main()
{
  int seed;
  int num;
  printf("Enter the number of people: ");
  scanf("%i", &num);

  struct person* people;
  people = malloc(sizeof(struct person) * num);
  clear_input_buffer();
  for (int i = 0; i < num; ++i)
  {
    printf("%i) ", i + 1);
    people[i].name = read_the_line();
  }

  scanf("%i", &seed);
  srand(seed);

  for (int i = 0; i < num; ++i)
    people[i].priority = rand();

  for (int j = 0; j < num; ++j)
  {
    struct person* max = people;
    for (int i = 0; i < num; ++i)
    {
      if (people[i].priority > max->priority) max = people + i;
    }
    printf("%i) %s %i\n", j + 1, max->name, max->priority);
    max->priority = -1;
  }
}
