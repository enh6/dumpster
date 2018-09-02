#include "test.h"
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// qsort
int cmp(const void *a, const void *b) {
  const int aa = *(const int *)a;
  const int bb = *(const int *)b;
  return aa - bb;
}

void libc_qsort(int A[], int N) { qsort(A, N, sizeof(int), cmp); }

// bubble sort
void bubble_sort(int A[], int N) {
  int swapped = 1;
  while (swapped) {
    swapped = 0;
    for (int j = 0; j < N - 1; j++) {
      if (A[j] > A[j + 1]) {
        swap(&A[j], &A[j + 1]);
        swapped = 1;
      }
    }
    N--;
  }
}

// insertion sort
void insertion_sort(int A[], int N) {
  for (int i = 1; i < N; i++) {
    int tmp = A[i], j;
    for (j = i; j > 0 && A[j - 1] > tmp; j--)
      A[j] = A[j - 1];
    A[j] = tmp;
  }
}

// shell sort
void shell_sort(int A[], int N) {
  for (int increment = N / 2; increment > 0;
       increment /= 2) { // we can also use other increment sequences
    for (int i = increment; i < N;
         i++) { // this loop is the same as insertion sort loop
      int tmp = A[i], j;
      for (j = i; j >= increment && A[j - increment] > tmp; j -= increment)
        A[j] = A[j - increment];
      A[j] = tmp;
    }
  }
}

// heap sort
void percolate_down(int A[], int i, int N) {
  int child, tmp;
  for (tmp = A[i]; 2 * i + 1 < N; i = child) {
    child = 2 * i + 1;
    if (child != N - 1 && A[child + 1] > A[child])
      child++;
    if (tmp < A[child])
      A[i] = A[child];
    else
      break;
  }
  A[i] = tmp;
}

void heap_sort(int A[], int N) {
  for (int i = N / 2; i >= 0; i--) // build heap
    percolate_down(A, i, N);
  for (int i = N - 1; i > 0; i--) {
    swap(&A[0], &A[i]); // delete max
    percolate_down(A, 0, i);
  }
}

// merge sort
void merge(int A[], int B[], int lpos, int rpos, int rend) {
  int lend = rpos - 1;
  int b_pos = lpos;
  int n = rend - lpos + 1;
  while (lpos <= lend && rpos <= rend)
    if (A[lpos] <= A[rpos])
      B[b_pos++] = A[lpos++];
    else
      B[b_pos++] = A[rpos++];
  while (lpos <= lend)
    B[b_pos++] = A[lpos++];
  while (rpos <= rend)
    B[b_pos++] = A[rpos++];
  for (int i = 0; i < n; i++, rend--)
    A[rend] = B[rend];
}

void msort(int A[], int B[], int left, int right) {
  if (left < right) {
    int center = (left + right) / 2;
    msort(A, B, left, center);
    msort(A, B, center + 1, right);
    merge(A, B, left, center + 1, right);
  }
}

void merge_sort(int A[], int N) {
  int *B = (int *)malloc(N * sizeof(int));
  msort(A, B, 0, N - 1);
  free(B);
}

// quick sort
int median(int A[], int left, int right) { // median of three pivot selection
  int center = (left + right) / 2;
  // after 3 swaps: A[left] <= A[center] <= A[right]
  if (A[left] > A[center])
    swap(&A[left], &A[center]);
  if (A[center] > A[right])
    swap(&A[center], &A[right]);
  if (A[left] > A[center])
    swap(&A[left], &A[center]);
  swap(&A[center], &A[right - 1]);
  return A[right - 1];
}

void q_sort(int A[], int left, int right) {
  int cutoff = 10; // switch to insertion sort if #element below 10
  if (left + cutoff <= right) {
    int pivot = median(A, left, right);
    int i = left, j = right - 1;
    for (;;) {
      while (A[++i] < pivot) {
      }
      while (A[--j] > pivot) {
      }
      if (i < j)
        swap(&A[i], &A[j]);
      else
        break;
    }
    swap(&A[i], &A[right - 1]);
    q_sort(A, left, i - 1);
    q_sort(A, i + 1, right);
  } else {
    insertion_sort(A + left, right - left + 1);
  }
}

void quick_sort(int A[], int N) { q_sort(A, 0, N - 1); }

/*******************************
      Test sort functions
*******************************/

void test_sort_1(void (*sort)()) {
  int A[] = {2, 3, 1, 0};
  sort(A, 4);
  ASSERT(A[0] == 0);
  ASSERT(A[1] == 1);
  ASSERT(A[2] == 2);
  ASSERT(A[3] == 3);
}

void test_sort_2(void (*sort)()) {
  int B[100];
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      B[j] = rand();
    }
    for (int j = 0; j < 100; j++) {
      int B1[100], B2[100];
      memcpy(B1, B, sizeof(int) * j);
      memcpy(B2, B, sizeof(int) * j);
      sort(B1, j);
      libc_qsort(B2, j);
      for (int k = 0; k < j; k++) {
        ASSERT(B1[k] == B2[k]);
      }
    }
  }
}

int main() {
  TEST_CASE(libc_qsort) { test_sort_1(libc_qsort); }
  TEST_CASE(bubble_sort) { test_sort_1(bubble_sort); }
  TEST_CASE(bubble_sort_2) { test_sort_2(bubble_sort); }
  TEST_CASE(shell_sort) { test_sort_1(shell_sort); }
  TEST_CASE(shell_sort_2) { test_sort_2(shell_sort); }
  TEST_CASE(insertion_sort) { test_sort_1(insertion_sort); }
  TEST_CASE(insertion_sort_2) { test_sort_2(insertion_sort); }
  TEST_CASE(heap_sort) { test_sort_1(heap_sort); }
  TEST_CASE(heap_sort_2) { test_sort_2(heap_sort); }
  TEST_CASE(merge_sort) { test_sort_1(merge_sort); }
  TEST_CASE(merge_sort_2) { test_sort_2(merge_sort); }
  TEST_CASE(quick_sort) { test_sort_1(quick_sort); }
  TEST_CASE(quick_sort_2) { test_sort_2(quick_sort); }
  TEST_END();
  return 0;
}
