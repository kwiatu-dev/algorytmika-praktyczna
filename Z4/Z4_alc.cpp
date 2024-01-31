#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#define GRAPH unordered_map<int, vector<Edge>>
#define PRIORITY priority_queue<Node, vector<Node>, Compare>

using namespace std;

class Node {
public:
	int index;
	int dist;

	Node(int index, int dist) : index(index), dist(dist) {};
};

class Edge {
public:
	int to;
	int cost;

	Edge(int to, int cost) : to(to), cost(cost) {};
};

class Compare {
public: 
	bool operator()(Node a, Node b) {
		if (a.dist > b.dist) {
			return true;
		}

		return false;
	}
};

int n, m;
const float duty = 0.5;
int* metal_costs;
GRAPH transformations_graph;
GRAPH reverse_transformations_graph;

vector<int> dijkstra(GRAPH g, int start) {
	PRIORITY pq;
	vector<bool> visited(n + 1, false);
	vector<int> dist(n + 1, INT_MAX);

	dist[start] = 0;
	pq.push(Node(start, 0));

	while (pq.size() != 0) {
		Node node = pq.top();	pq.pop();
		visited[node.index] = true;
		if (dist[node.index] < node.dist) continue;

		for (Edge edge : g[node.index]) {
			if (visited[edge.to]) continue;
			int new_dist = dist[node.index] + edge.cost;

			if (new_dist < dist[edge.to]) {
				dist[edge.to] = new_dist;
				pq.push(Node(edge.to, new_dist));
			}
		}
	}

	return dist;
}

void load() {
	int from, to, cost;
	cin >> n;
	metal_costs = new int[n + 1];

	for (int i = 1; i <= n; i++) {
		cin >> metal_costs[i];
	}

	cin >> m;

	for (int i = 0; i < m; i++) {
		cin >> from >> to >> cost;
		transformations_graph[from].push_back(Edge(to, cost));
		reverse_transformations_graph[to].push_back(Edge(from, cost));
	}
}

void del() {
	transformations_graph.clear();
	reverse_transformations_graph.clear();
	delete metal_costs;
}

void result() {
	int min_costs = INT_MAX, alchemy_cost, metal_cost;
	vector<int> dist_to = dijkstra(transformations_graph, 1);
	vector<int> dist_from = dijkstra(reverse_transformations_graph, 1);

	for (int i = 1; i <= n; i++) {
		alchemy_cost = dist_to[i] == INT_MAX ? 0 : dist_to[i];
		alchemy_cost += dist_from[i] == INT_MAX ? 0 : dist_from[i];
		metal_cost = metal_costs[i] / 2;
		min_costs = min(min_costs, alchemy_cost + metal_cost);
	}

	cout << min_costs << endl;
}

void test() {
	load();
	result();
	del();
}

int main() {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		test();
	}

	return 0;
}