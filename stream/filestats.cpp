#include <fstream>
#include <exception>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

ifstream open(const char* path, ios_base::openmode mode = ios_base::in) {
    ifstream file{ path, mode };
    if (!file.is_open()) {
        string err{ "Unable to open file " };
        err.append(path);
        throw runtime_error{ err };
    }
    file.exceptions(ifstream::badbit);
    return file;
}

int main() {
    try {
        auto file = open("intro.txt");
        cout << "Contents: " << file.rdbuf() << endl;
        file.seekg(-1, ios_base::end);
        cout << "Length of text: " << (int) file.tellg() + 1<< endl;
        file.seekg(0);
        char c;
        int vowels = 0;
        unordered_set<char> us{ 'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u' };
        while (file >> c) {
            if (us.find(c) != us.end()) vowels++;
        }
        cout << "No. of vowels: " << vowels << endl;
    } catch (const exception& e) {
        cerr << e.what();
    }
}