#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> a;
    vector<int> b = {1, 2, 3};
    a = b;
    cout << a.size();
}
