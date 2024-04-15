#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

struct KeyValue {
  char key[22];
  char *value;
  int len = 0;
};

size_t DINMEMORY = 1;

void sortCount(KeyValue *arr, int size, int exp) {
  int count[10] = {0}, index, gap, offset;
  struct KeyValue n_arr[size];
  char input;

  for (int i = 0; i < size; ++i) {
    gap = 19 - arr[i].len;
    offset = exp - gap;
    if (offset >= 0) {
      input = (arr[i].key[offset]) & 0xFF;
      if ('0' <= input && input <= '9') {
        ++count[input - '0'];
      } else {
        ++count[0];
      }
    } else {
      ++count[0];
    }
  }

  for (int i = 1; i < 10; ++i) count[i] += count[i - 1];

  for (int i = size - 1; i >= 0; --i) {
    gap = 19 - arr[i].len;
    offset = exp - gap;

    if (offset >= 0) {
      input = (arr[i].key[offset]) & 0xFF;
      if ('0' <= input && input <= '9') {
        index = count[input - '0']--;
      } else {
        index = count['0' - '0']--;
      }
    } else {
      index = count['0' - '0']--;
    }

    n_arr[index - 1] = arr[i];
  }

  memcpy(arr, n_arr, size * sizeof(struct KeyValue));
}

void sortRadix(KeyValue *arr, int size) {
  int byteSize = sizeof(char) * 22;

  for (int i = byteSize - 1; i >= 0; i--) {
    sortCount(arr, size, i);
  }
}


int main() {
  KeyValue *arr = (KeyValue *)malloc(DINMEMORY * sizeof(KeyValue));
  size_t size = 0;
  char buff[2049];

  while (scanf("%s\t%s", arr[size].key, buff) == 2) {
    arr[size].len = strlen(arr[size].key);
    arr[size].value = new char[strlen(buff) + 1];

    for (size_t i = 0; i < strlen(buff); i++) {
      arr[size].value[i] = buff[i];
    }
    arr[size].value[strlen(buff)] = '\0';

    size++;
    if (size == DINMEMORY) {
      DINMEMORY *= 2;
      arr = (KeyValue *)realloc(arr, DINMEMORY * sizeof(KeyValue));
    }
  }

  sortRadix(arr, size);

  for (size_t i = 0; i < size; i++) {
    cout << arr[i].key << "\t" << arr[i].value << "\n";
  }
  
  free(arr);
}
