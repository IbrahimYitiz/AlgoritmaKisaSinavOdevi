#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <functional>
#include <set>

using namespace std;

void mergeSort(int arr[], int low, int high);
void merge(int arr[], int low, int mid, int high);
int kadanesAlgorithm(int arr[], int n);
vector<vector<int>> dijkstraAlgorithm(const vector<vector<pair<int, int>>> &graph, int n);

int main() {
    int arr[] = {10, 80, 30, 90, 40, 50, 70};
    int n = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, n - 1);

    cout << "Siralanmis Dizi: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int arr2[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    int max_sum = kadanesAlgorithm(arr2, n2);
    cout << "Maximum ardisik toplam: " << max_sum << endl;

    vector<vector<pair<int, int>>> graph = {
        {{1, 10}},
        {{0, 10}, {2, 5}},
        {{1, 5}, {3, 20}, {4, 1}},
        {{2, 20}, {4, 2}},
        {{2, 1}, {3, 2}},
        {}
    };
    int n3 = graph.size();

    vector<vector<int>> shortest_distances = dijkstraAlgorithm(graph, n3);

    cout << "En kisa mesafeler:" << endl;

    for (int i = 0; i < n3; i++) {
        for (int j = 0; j < n3; j++) {
            if (shortest_distances[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << shortest_distances[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[low + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

int kadanesAlgorithm(int arr[], int n) {
    int max_so_far = 0, max_ending_here = 0;
    for (int i = 0; i < n; i++) {
        max_ending_here = max_ending_here + arr[i];
        if (max_ending_here < 0) {
            max_ending_here = 0;
        }
       
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
        }
    }
    return max_so_far;
}

vector<vector<int>> dijkstraAlgorithm(const vector<vector<pair<int, int>>> &graph, int n) {
    vector<vector<int>> shortest_distances(n, vector<int>(n, INT_MAX));
    for (int source = 0; source < n; ++source) {
        set<pair<int, int>> pq;
        pq.insert({0, source});
        while (!pq.empty()) {
            int u = pq.begin()->second;
            int dist_u = pq.begin()->first;
            pq.erase(pq.begin());
            if (shortest_distances[source][u] != INT_MAX)
                continue;

            shortest_distances[source][u] = dist_u;

           for (const auto &p : graph[u]) {
    int v = p.first;
    int weight = p.second; {
                int alt_distance = dist_u + weight;
                if (shortest_distances[source][v] > alt_distance) {
                    pq.insert({alt_distance, v});
                }
            }
        }
    }
    return shortest_distances;
}
}
