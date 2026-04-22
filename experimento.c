#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void insertionSort(int arr[], int n) {
  for(int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;

    while(j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }

    arr[j + 1] = key;
  }
}

static void merge(int arr[], int left, int mid, int right) {
  int leftSize = mid - left + 1;
  int rightSize = right - mid;

  int* leftArr = (int*)malloc(leftSize * sizeof(int));
  int* rightArr = (int*)malloc(rightSize * sizeof(int));

  if(leftArr == NULL || rightArr == NULL) {
    fprintf(stderr, "Error: no se pudo reservar memoria en merge()\n");
    free(leftArr);
    free(rightArr);
    exit(EXIT_FAILURE);
  }

  for(int i = 0; i < leftSize; i++) {
    leftArr[i] = arr[left + i];
  }

  for(int j = 0; j < rightSize; j++) {
    rightArr[j] = arr[mid + 1 + j];
  }

  int i = 0;
  int j = 0;
  int k = left;

  while(i < leftSize && j < rightSize) {
    if(leftArr[i] <= rightArr[j]) {
      arr[k++] = leftArr[i++];
    } else {
      arr[k++] = rightArr[j++];
    }
  }

  while(i < leftSize) {
    arr[k++] = leftArr[i++];
  }

  while(j < rightSize) {
    arr[k++] = rightArr[j++];
  }

  free(leftArr);
  free(rightArr);
}

static void mergeSortRecursive(int arr[], int left, int right) {
  if(left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  mergeSortRecursive(arr, left, mid);
  mergeSortRecursive(arr, mid + 1, right);
  merge(arr, left, mid, right);
}

static void mergeSort(int arr[], int n) {
  if(n > 1) {
    mergeSortRecursive(arr, 0, n - 1);
  }
}

static void generateRandomArray(int arr[], int n, int maxValue) {
  for(int i = 0; i < n; i++) {
    arr[i] = rand() % maxValue;
  }
}

static long long elapsedNanoseconds(struct timespec start, struct timespec end) {
  long long seconds = (long long)(end.tv_sec - start.tv_sec);
  long long nanoseconds = (long long)(end.tv_nsec - start.tv_nsec);
  return seconds * 1000000000LL + nanoseconds;
}

static double measureInsertionSort(int baseArr[], int n) {
  struct timespec start;
  struct timespec end;

  clock_gettime(CLOCK_MONOTONIC, &start);
  insertionSort(baseArr, n);
  clock_gettime(CLOCK_MONOTONIC, &end);

  return (double)elapsedNanoseconds(start, end) / 1000.0;
}

static double measureMergeSort(int baseArr[], int n) {
  struct timespec start;
  struct timespec end;

  clock_gettime(CLOCK_MONOTONIC, &start);
  mergeSort(baseArr, n);
  clock_gettime(CLOCK_MONOTONIC, &end);

  return (double)elapsedNanoseconds(start, end) / 1000.0;
}

int main(void) {
  srand((unsigned int)time(NULL));

  printf("# n insertion_us merge_us\n");
  int rep = 10; // repeticiones para promedio

  for(int n = 2; n <= 1200; n *= 2) {
    int* baseArr = malloc(n * sizeof(int));
    int* copy1   = malloc(n * sizeof(int));
    int* copy2   = malloc(n * sizeof(int));

    if(baseArr == NULL || copy1 == NULL || copy2 == NULL) {
      fprintf(stderr, "Error de memoria para n=%d\n", n);
      return EXIT_FAILURE;
    }

    generateRandomArray(baseArr, n, 100000);

    double totalInsertion = 0.0;
    double totalMerge     = 0.0;

    for(int r = 0; r < rep; r++) {

    memcpy(copy1, baseArr, n * sizeof(int));
    memcpy(copy2, baseArr, n * sizeof(int));

    totalInsertion += measureInsertionSort(copy1, n);
    totalMerge     += measureMergeSort(copy2, n);

    }

    double insertionTime = totalInsertion / rep;
    double mergeTime     = totalMerge / rep;

    printf("%d %.3f %.3f\n", n, insertionTime, mergeTime);

    free(baseArr);
    free(copy1);
    free(copy2);
  }

  return EXIT_SUCCESS;
}
