#include <iostream>
#include <random>
#include <chrono>

using namespace std;

const int W = 1e5;

int par[2500];

int main()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    int n = 2500;
    vector<pair<int, pair<int, int>>> adj;
    // make tree
    for (int a = 1; a < n; a++)
    {
        par[a] = (int)(gen() % a);
        int w = (int)(gen() % W) + 1;
        adj.push_back({a, {par[a], w}});
    }
    int m = n - 1;
    // probability of new edge
    int prob = (int)(gen() % 15) + 5;
    // get new edges
    for (int a = 0; a < n; a++)
    {
        for (int b = a + 1; b < n; b++)
        {
            if (par[a] == b || par[b] == a)
                continue;
            int here = (int)(gen() % 100);
            if (here <= prob)
            {
                m++;
                int w = (int)(gen() % W) + 1;
                adj.push_back({a, {b, w}});
            }
            if (m >= W)
                break;
        }
        if (m >= W)
            break;
    }
    cout << n << " " << adj.size() << "\n";
    for (int a = 0; a < adj.size(); a++)
        cout << adj[a].first + 1 << " " << adj[a].second.first + 1 << " " << adj[a].second.second << "\n";
    return 0;
}