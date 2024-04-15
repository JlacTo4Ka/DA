#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

int max(int left, int right) {
    return left >= right? left: right;
}

int min(int left, int right) {
    return left >= right? right: left;
}


const int max_size = 90000000;

size_t sample_size = 0;
size_t input_size = 0;
char input_text[max_size + 1] = "";
char sample[max_size + 1] = "";

int* build_z_function(const char* merged_text) {
    size_t length = sample_size + input_size + 2;
    int* z_func = new int[length + 1];
    int left = 0, right = 0;
    for (int current_index = 0; merged_text[current_index] != 0; ++current_index) {
        z_func[current_index] = max(0, min(right-current_index, z_func[current_index - left]));
        while (current_index + z_func[current_index] < length && merged_text[z_func[current_index]] == merged_text[z_func[current_index] + current_index])
        {
            ++z_func[current_index];
        }
        if (current_index + z_func[current_index] > right) {
            left = current_index;
            right = current_index + z_func[current_index];
        }
    }
    return z_func;
}

void str_find() {
    ios:: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);


    if (sample_size > input_size) {
        return;
    }
    char* merged_text = new char[input_size + sample_size + 2];

    strcpy(merged_text, sample);
    merged_text[sample_size] = '#';
    for (size_t index = sample_size + 1; index < sample_size + input_size + 2; ++index) {
        merged_text[index] = input_text[index - sample_size - 1];
    }
    int* z_func = build_z_function(merged_text);

    for (int z_func_index = sample_size + 1; z_func_index < input_size + sample_size + 2; ++z_func_index) {
        if (z_func[z_func_index] == sample_size) {
            cout << z_func_index - sample_size - 1 << endl;
        }
    }
    delete z_func;
}

int main() {
    ios:: sync_with_stdio(false);
    ifstream input("input.txt");
    input.getline(input_text, max_size);
    input.getline(sample, max_size);
    input_size = strlen(input_text);
    sample_size = strlen(sample);
    if (input_size == 0 || sample_size == 0 || sample_size > input_size)
    {
        return 0;
    }
    str_find();
    return 0;
}
