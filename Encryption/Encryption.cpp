#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void Encrypt(string& input, int rows, int columns) {
    char array[rows][columns];
    int index = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            array[i][j] = (index < input.size()) ? input[index++] : '\0';
        }
    }
    for (int j = 0; j < columns; ++j) {
        for (int i = 0; i < rows; ++i) {
            if (array[i][j] != '\0') cout << array[i][j];
        }
        cout << " ";
    }
}

int main() {
    string input;
    cin >> input;
    double sqrtlen = sqrt(input.size());
    int sqrtintlen = sqrt(input.size());
    int width  = floor(sqrtlen);
    int height = ceil(sqrtlen);
    //cout << width << ":" << height << ":" << sqrtintlen << endl;
    if (sqrtintlen*sqrtintlen == input.size()) {
        Encrypt(input, sqrtintlen, sqrtintlen);
    } else {
        while (width*height < input.size()) {
            if ( width < height ) ++width;
            else height++;
        }
        Encrypt(input, width, height);
    }
    
    return 0;
}
