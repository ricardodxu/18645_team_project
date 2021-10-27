#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POPULATION_SIZE 10
#define INDIVIDUAL_SIZE 10

static __inline__ unsigned long long rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
  return ((unsigned long long)lo) | (((unsigned long long)hi) << 32);
}

int *crossover(int *father, int *mother);

double fitness(int *base, int *target);

int **selection(int **population, int *target);

int **init();
int *generate_individual();

void free_population(int **population);
void free_individual(int *individual);

void print_population(int **population);
void print_individual(int *individual);

int main(int argc, char const *argv[]) {
  /* code */
  srand(time(NULL));
  int **population = init();
  int *target = generate_individual();
  printf("target & init population: \n");
  print_individual(target);
  printf("\n");

  print_population(population);

  uint64_t start = rdtsc();
  int** new_population = selection(population, target);
  uint64_t end = rdtsc();

  uint64_t latency = end - start;

  printf("Verify: %ld\n",
         latency); // required to prevent the compiler from optimizing it out
  // printf("Latency: %lf\n", MAX_FREQ/BASE_FREQ * latency);   //find the
  // average latency over multiple runs

  free_population(new_population);
  free_population(population);
  free_individual(target);
  return 0;
}

int **init() {
  int **population = (int **)malloc(POPULATION_SIZE * sizeof(int *));
  for (int i = 0; i < POPULATION_SIZE; ++i) {
    population[i] = generate_individual();
  }
  return population;
}

int *generate_individual() {
  int *individual = (int *)malloc(INDIVIDUAL_SIZE * sizeof(int));
  for (int j = 0; j < INDIVIDUAL_SIZE; ++j) {
    individual[j] = rand() % 10; /* generate a number from 0 - 9 */
  }
  return individual;
}

void free_population(int **population) {
  for (int i = 0; i < POPULATION_SIZE; ++i) {
    free_individual(population[i]);
  }
  free(population);
}
void free_individual(int *individual) { free(individual); }

void print_individual(int *individual) {
  for (int j = 0; j < INDIVIDUAL_SIZE; ++j) {
    printf("%d ", individual[j]);
  }
  printf("\n");
}

void print_population(int **population) {
  for (int i = 0; i < POPULATION_SIZE; ++i) {
    print_individual(population[i]);
  }
}

int *crossover(int *father, int *mother) {
  int crs_idx = INDIVIDUAL_SIZE / 2;
  int *child = (int *)malloc(INDIVIDUAL_SIZE * sizeof(int));
  for (int i = 0; i < crs_idx; ++i)
    child[i] = father[i];

  for (int i = crs_idx; i < INDIVIDUAL_SIZE; ++i)
    child[i] = mother[i];
  return child;
}

double fitness(int *base, int *target) {
  double correct = 0.0;
  for (int i = 0; i < INDIVIDUAL_SIZE; i++) {
    if (base[i] == target[i]) {
      correct += 1;
    }
  }
  return correct / INDIVIDUAL_SIZE;
}

int **selection(int **population, int *target) {
  int *mating_pool = (int *)malloc(sizeof(int *) * POPULATION_SIZE);
  int idx = 0;
  for (int i = 0; i < POPULATION_SIZE; i++) {
    int score = fitness(population[i], target);
    for (int j = 0; j < score; j++) {
      mating_pool[idx] = i;
      idx = idx + 1;
    }
  }
  int **new_population = (int **)malloc(sizeof(int *) * POPULATION_SIZE);
  for (int i = 0; i < POPULATION_SIZE; i++) {
    int *mother = (int *)malloc(sizeof(int *) * INDIVIDUAL_SIZE);
    int *father = (int *)malloc(sizeof(int *) * INDIVIDUAL_SIZE);
    int *child = crossover(mother, father);
    new_population[i] = child;
  }

  free(mating_pool);
  //print_population(new_population);
  return new_population;
}