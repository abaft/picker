#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <assert.h>

struct person
{
  char* name;
  unsigned long int priority;
  RSA* key;
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
  char c;
  while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
  int num;
  printf("Enter the number of people: ");
  scanf("%i", &num);

  struct person* people;
  people = malloc(sizeof(struct person) * num);
  clear_input_buffer();
  printf("Enter your name: ");
  people->name = read_the_line();

  //// RSA GENERATION

  RSA* localKey = NULL;
  RSA* pact = NULL;
  BIGNUM* bne = NULL;
  bne = BN_new();
  BN_set_word(bne, RSA_F4);
  people->key = RSA_new();

  printf("Please seed the srng used for the key generation. Keep this hidden\n"
      ">>> ");
  char* seed = read_the_line();
  RAND_seed(seed, strlen(seed));

  if (RSA_generate_key_ex(people->key, 4096, bne, NULL) == 0)
    printf("%s\n",  ERR_reason_error_string(ERR_get_error()));
  printf("This is your public key, give it to your friends:\n");
  PEM_write_RSAPublicKey(stdout, people->key);

  printf("Fill in friends details:\n");
  for (int i = 1; i < num; ++i)
  {
    printf("Name (%i/%i): ", i, num - 1);
    people[i].name = read_the_line(); 
    printf("Public Key:\n");
    PEM_read_RSAPublicKey(stdin, &(people[i].key), NULL, NULL);
  }

  for(int i = 0; i < num; ++i)
  {
    printf("%i) %s \n", i + 1, people[i].name);
    PEM_write_RSAPublicKey(stdout, people[i].key);
  }

/*
  for (int j = 0; j < num; ++j)
  {
    struct person* max = people;
    for (int i = 0; i < num; ++i)
    {
      if (people[i].priority > max->priority) max = people + i;
    }
    printf("%i) %s %lu\n", j + 1, max->name, max->priority);
    max->priority = 0;
  }
  */
}
