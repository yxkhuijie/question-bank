#include <iostream>

void bubble_sort(int* d, int l) {
  for (int i = 0; i < l - 1; i++) {
    for (int j = 0; j < l - 1 - i; j++) {
      if (d[j] > d[j + 1]) {
        int t = d[j];
        d[j] = d[j + 1];
        d[j + 1] = t;
      }
    }
  }
}

void select_sort(int* d, int l) {
  for (int i = 0; i < l - 1; i++) {
    int min = i;
    for (int j = i + 1; j < l; j++) {
      if (d[j] < d[min]) {
        min = j;
      }
    }

    if (min != i) {
      int t = d[i];
      d[i] = d[min];
      d[min] = t;
    }
  }
}

void quick_sort(int* d, int l, int r) {
  if (l >= r) return;
  int i = l;
  int j = r;
  int key = d[i];
  while(i < j) {
    while(i < j && key <= d[j]) {
      j--;
    }

    d[i] = d[j];

    while(i < j && key >= d[i]) {
      i++;
    }

    d[j] = d[i];
  }

  d[i] = key;
  quick_sort(d, l, i - 1);
  quick_sort(d, i + 1, r);
}

void merge_sort_merge(int* d, int l, int mid, int r, int* tmp) {
  int i = l;
  int j = mid + 1;
  int t = 0;
  while (i <= mid && j <= r) {
    if (d[i] <= d[j]) {
      tmp[t] = d[i];
      t++;
      i++;
    } else {
      tmp[t] = d[j];
      t++;
      j++;
    }
  }

  while (i <= mid) {
    tmp[t] = d[i];
    t++;
    i++;
  }

  while (j <= r) {
    tmp[t] = d[j];
    t++;
    j++;
  }

  t = 0;
  while(l <= r) {
    d[l] = tmp[t];
    l++;
    t++;
  }
}

void merge_sort(int* d, int l, int r, int* tmp) {
  if (l >= r) return;
  int* t = tmp;
  if (t == NULL) {
    t = new int[r - l + 1];
  }

  int mid = (l + r) / 2;
  merge_sort(d, l, mid, t);
  merge_sort(d, mid + 1, r, t);
  merge_sort_merge(d, l, mid, r, t);
}

void print(int* d, int l) {
  for (int i = 0; i < l; i++) {
    std::cout << d[i] << " ";
  }
  std::cout << std::endl;
}

void copy(int* src, int l, int* dst) {
  for (int i = 0; i < l; i++) {
    dst[i] = src[i];
  } 
}

int main(int argc, char** argv) {
  int data[] = {3,2,6,7,4,9,10,1};
  int size = sizeof(data)/sizeof(data[0]);
  int* d1 = new int[size];
  copy(data, size, d1);
  bubble_sort(d1, size);
  print(d1, size);

  copy(data, size, d1);
  select_sort(d1, size);
  print(d1, size);

  copy(data, size, d1);
  quick_sort(d1, 0, size - 1);
  print(d1, size);

  copy(data, size, d1);
  merge_sort(d1, 0, size - 1, NULL);
  print(d1, size);
}

