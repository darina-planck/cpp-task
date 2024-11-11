#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cout << "Введите число N: ";
    cin >> n;
    int random[n][n];
    int start = 0;
    int end = 9;

    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= n; j++) {
            random[i][j] = rand() % (end - start + 1) + start;
        }
    }
    for (int i = 0;i <= n; i++){
        for (int j = 0; j <= n; j++) {
            cout << random[i][j] << " ";
        }
        cout << "\n";
    }
    
    
    return 0;
}