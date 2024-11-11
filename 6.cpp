#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 0;
    cout << "Введите число N: ";
    cin >> n;
    int start = 0;
    int end = 10;
    int x = rand() % (end - start + 1) + start;
    cout << x << endl;
    cout << x << endl;
    return 0;
}