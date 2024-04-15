#include <iostream>
#include <vector>

const long long ALPHABET = 3;

using namespace std;

long long Solve(vector<long long int> &sequence, long long N, long long swap) {
    int borders[ALPHABET] = {0, 0, 0};

    for (int elem = 0; elem < N; elem++) {    
        if (sequence[elem] == 1) {
            borders[0]++;
        }
        if (sequence[elem] == 2) {
            borders[1]++;
        }
    }

    int one_in_second = 0;
    for (int elem = borders[0]; elem < (borders[0] + borders[1]); elem++) {    
        if (sequence[elem] == 1) {
            one_in_second++;
        }
    }

    int swap_three_to_second_field = 0;
    for (int elem = 0; elem < borders[0]; elem++) {
        if (sequence[elem] == 2) {
            swap++;
        }
        if (sequence[elem] == 3) {
            swap++;
            swap_three_to_second_field++;
        }
    }

    int swap_two_to_second_field = swap - swap_three_to_second_field;

    int add_swaps = one_in_second - swap_two_to_second_field;

    swap += add_swaps;

    for (int elem = borders[0]; elem < (borders[0] + borders[1]); elem++) {
        if (sequence[elem] == 3) {
            swap++;
        }
    }

    return swap;
}

int main() {
    long long int N;
    cin >> N;
    vector<long long int> sequence(N);

    for (int elem = 0; elem < N; ++elem) {
        cin >> sequence[elem];
    }

    long long swap = 0;
    long long swaps = Solve(sequence, N, swap);    

    cout << swaps << endl;
    
    return 0;
}

