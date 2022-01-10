#include <cstdio>

char read_from(char* arr, int idx, int arrsize) {
    // read first char of array
    if (idx < arrsize) {
        return *(arr + (idx * sizeof(char)));
    } else return 'i';
}

void write_to(char* arr, int idx, int arrsize, char add) {
    // write to idx of arr provided within bounds
    if (idx < arrsize) {
        *(arr + (idx * sizeof(char))) = add;
    } else printf("Index out of bounds!");
}

int main() {
    char lower[] = "abc?e";
    char upper[] = "ABC?E";
    char* lower_ptr = lower;
    char* upper_ptr = upper; // Equivalent: &upper[0]
    int lower_size = sizeof(lower) / sizeof(char);
    int upper_size = sizeof(upper) / sizeof(char);
    // lower[3] = 'd'; // lower now contains a b c d e
    write_to(lower_ptr, 3, lower_size, 'd');
    // upper_ptr[3] = 'D'; // upper now contains A B C D E
    write_to(upper_ptr, 3, upper_size, 'D');
    // char letter_d = lower[3]; // letter_d equals 'd' char letter_D = upper_ptr[3]; // letter_D equals 'D'
    char lower_d = read_from(lower_ptr, 3, lower_size);
    char upper_d = read_from(upper_ptr, 3, upper_size);
    printf("lower: %s\nupper: %s\n", lower, upper);
    printf("lower: %c\nupper: %c\n", lower_d, upper_d);
    // lower[7] = 'g'; // Super bad. You must never do this.
    write_to(lower_ptr, 10, lower_size, 'z');
}