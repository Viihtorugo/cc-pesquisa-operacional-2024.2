#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    double val[n];

    for (int i = 0; i < n; i++)
    {
        cin >> val[i];
        val[i] /= 200;
    }

    ofstream arquivo("2.in");
    arquivo << n << " " << k << "\n";

    if (arquivo.is_open()) 
    {
        for (int i = 0; i < n; i++) 
        {
            arquivo << val[i] << "\n";
        }

        arquivo.close();
    }

    return 0;
}
