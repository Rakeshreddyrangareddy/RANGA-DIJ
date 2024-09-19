#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cctype> // For tolower or toupper

using namespace std;

// Define a structure for edges
struct Edge {
    int dest;    // Destination node
    int weight;  // Weight of the edge
};

// Define the graph as an adjacency list
unordered_map<char, vector<Edge>> graph = {
    {'A', {{'B', 10}, {'E', 3}}},
    {'B', {{'C', 2}, {'E', 4}}},
    {'C', {{'D', 9}}},
    {'D', {{'C', 7}}},
    {'E', {{'B', 1}, {'C', 8}}}
};

// Dijkstra's Algorithm
void dijkstra(char start, char end) {
    // Create a priority queue to store the nodes to explore
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
    // Map to store the minimum distance to each node
    unordered_map<char, int> minDistance;
    // Map to store the previous node in the path
    unordered_map<char, char> previous;

    // Initialize distances
    for (const auto& node : graph) {
        minDistance[node.first] = numeric_limits<int>::max(); // Set all distances to infinity
    }
    minDistance[start] = 0; // Distance to the start node is 0

    // Push the start node into the priority queue
    pq.push({0, start});

    while (!pq.empty()) {
        // Get the node with the smallest distance
        char currentNode = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        // If the current node is the end node, we can stop
        if (currentNode == end) break;

        // Explore the neighbors of the current node
        for (const auto& edge : graph[currentNode]) {
            char neighbor = edge.dest;
            int weight = edge.weight;

            // Calculate the new distance to the neighbor
            int newDistance = currentDistance + weight;

            // If the new distance is less than the previously recorded distance, update it
            if (newDistance < minDistance[neighbor]) {
                minDistance[neighbor] = newDistance;
                previous[neighbor] = currentNode;
                pq.push({newDistance, neighbor});
            }
        }
    }

    // Output the result
    if (minDistance[end] == numeric_limits<int>::max()) {
        cout << "There is no path from " << start << " to " << end << "." << endl;
    } else {
        // Output the cost
        cout << "The cost of the shortest path from " << start << " to " << end << " is: " << minDistance[end] << endl;

        // Output the path
        vector<char> path;
        for (char at = end; at != 0; at = previous[at]) {
            path.push_back(at);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        cout << "The shortest path from " << start << " to " << end << " is: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

int main() {
    // Ask the user for the starting and ending nodes
    char startNode, endNode;
    cout << "Enter the start node: ";
    cin >> startNode;
    cout << "Enter the end node: ";
    cin >> endNode;

    // Convert input to uppercase to make it case-insensitive
    startNode = toupper(startNode);
    endNode = toupper(endNode);

    // Check if the entered nodes are valid
    if (graph.find(startNode) == graph.end()) {
        cout << "Start node " << startNode << " is not present in the graph." << endl;
        return 1;
    }
    if (graph.find(endNode) == graph.end()) {
        cout << "End node " << endNode << " is not present in the graph." << endl;
        return 1;
    }

    // Run Dijkstra's algorithm
    dijkstra(startNode, endNode);

    return 0;
}
