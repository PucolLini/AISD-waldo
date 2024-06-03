#include <iostream>
#include "Vector.h"
#include "MString.h"
#include "Queue.h"
using namespace std;

void dfs(const Vector<Vector<int>>& graph, long long int start, Vector<bool>& visited) {
	visited[start] = true;

	for (int i = 0; i < graph[start].getSize(); i++) {
		int neighbour = graph[start][i] - 1;
		if (!visited[neighbour]) {
			dfs(graph, neighbour, visited);
		}
	}
}

int componentsCounter(Vector<Vector<int>>& graph, long long int& graph_order) {
	int counter = 0;
	
	Vector<bool> visited(graph_order); // liczba wierzcholkow odwiedzonych
	visited.fill(false);

	for (int i = 0; i < graph_order; i++) {
		if (!visited[i]) {
			dfs(graph, i, visited);
			counter++;
		}
	}

	return counter;
}

bool assignColorsDFS(Vector<Vector<int>>& graph, Vector<int>& colors, int vertex, int color) {
	colors[vertex] = color; // Przypisanie koloru wierzchołkowi

	// Przypisanie przeciwnego koloru dla sąsiadów
	for (int i = 0; i < graph[vertex].getSize(); i++) {
		int neighbour = graph[vertex][i] - 1; // Indeksowanie od 0
		if (colors[neighbour] == color) {
			// Konflikt - ten sam kolor dla wierzchołka i sąsiada
			return false;
		}
		// Jeśli sąsiad nie ma jeszcze przypisanego koloru, rekurencyjnie przypiszmy mu przeciwny kolor
		if (colors[neighbour] == 0 && !assignColorsDFS(graph, colors, neighbour, -color)) {
			return false; // Jeśli rekurencja zwróciła false, to zakończ działanie z błędem
		}
	}
	return true; // Udało się przypisać kolory wierzchołkom
}

bool isBipartited(Vector<Vector<int>>& graph, long long int& graph_order) {
	Vector<int> colors(graph_order); // Tablica przechowująca kolory wierzchołków
	colors.fill(0); // Domyślny kolor (0) - nieprzypisany

	// Przechodzimy przez wszystkie wierzchołki, by sprawdzić dwudzielność grafu
	for (long long int i = 0; i < graph_order; i++) {
		if (colors[i] == 0 && !assignColorsDFS(graph, colors, i, 1)) {
			// Jeśli wierzchołek nie ma jeszcze przypisanego koloru i nie udało się przypisać kolorów DFS-em, zwróć false
			return false;
		}
	}
	return true; // Jeśli udało się przypisać kolory wierzchołkom zgodnie z regułami, zwróć true
}

long long int countComplementEdges(Vector<int>& degrees, long long int& vertices) {
	long long int complement_edges = (vertices*(vertices-1))/2;
	long long int edges = 0;

	for (int i = 0; i < vertices ; i++) {
		edges += degrees[i];
	}

	edges /= 2;
	complement_edges -= edges;

	return complement_edges;
}

//geeksforgeeks.org
int bfs(const Vector<Vector<int>>& graph, int start) {
	Vector<int> distances(graph.getSize(), 0);
	Vector<bool> visited(graph.getSize(), false);
	Queue<int> queue;
	
	visited[start] = true;
	queue.push(start);

	while (!queue.isEmpty()) {
		int current = queue.getFront();
		queue.pop();

		//cout << current << "-";
		
		for (int i = 0; i < graph[current].getSize(); i++) {
			int neighbour = graph[current][i] - 1;
			if (!visited[neighbour]) {
				visited[neighbour] = true;
				queue.push(neighbour);
				distances[neighbour] = distances[current] + 1;
			}
		}
		
	}
	//cout << endl;

	int max_distance = 0;
	for (int i = 0; i < distances.getSize(); i++) {
		if (distances[i] > max_distance) {
			max_distance = distances[i];
		}
	}

	return max_distance;
}

void eccentricity(const Vector<Vector<int>>& graph) {
	for (int i = 0; i < graph.getSize(); i++) {
		cout << bfs(graph, i) << " ";
		//bfs(graph, i);
	}
	cout << endl;
}

int main()
{
	int number_of_graphs;
	cin >> number_of_graphs;

	while (number_of_graphs--) {
		//pobranie liczby wierzcholkow grafu (rząd grafu)
		long long int graph_order;
		cin >> graph_order;
        cin.ignore();

		Vector<Vector<int>> graph(graph_order);
		Vector<int> degree_sequence;

        for (int i = 0; i < graph_order; i++) {
            int number_of_neighbours;

			cin >> number_of_neighbours;
			degree_sequence.push_back(number_of_neighbours);
            
            Vector<int> neighbours;//lista sasiadow
            int vertex;

            while (number_of_neighbours--) {
                cin >> vertex;
				neighbours.push_back(vertex);
            }
			
            graph[i] = std::move(neighbours);
        }

		//1. ciag stopniowy
		degree_sequence.reverseSort();
		for (int i = 0; i < degree_sequence.getSize(); i++) {
			cout << degree_sequence[i] << " ";
		}
		cout << endl;

		//2. Liczba składowych spójności
		int number_of_components = componentsCounter(graph, graph_order);
		cout << number_of_components << endl;

		//3. Dwudzielność grafu
		if (isBipartited(graph, graph_order)) {
			cout << "T";
		}
		else {
			cout << "F";
		}
		cout << endl;

		//4. Acentryczność wierzchołków
		cout << "?\n";
		//eccentricity(graph);

		//5. Planarność grafu
		cout << "?\n";

		//6. Kolory wierzchołków a,b,c
		cout << "?\n";
		cout << "?\n"; 
		cout << "?\n";

		//7. Liczba różnych podgrafów C4
		cout << "?\n";

		//8. Liczba krawędzi dopełnienia grafu
		cout << countComplementEdges(degree_sequence, graph_order)<<endl;
	}
	
	return 0;
}
