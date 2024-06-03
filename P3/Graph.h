#pragma once
#include "Vector.h"

class Graph
{
private:
	long long int number_of_vertices; // degree_sequence.size()
	Vector<int> degree_sequence;
	Vector<Vector<int>> graph;

private:
	bool assignColorsDfs(Vector<int>& colors, int vertex, int color) const {
		colors[vertex] = color; // Przypisanie koloru wierzcho³kowi

		// Przypisanie przeciwnego koloru dla s¹siadów
		for (int i = 0; i < graph[vertex].getSize(); i++) {
			int neighbour = graph[vertex][i] - 1; // Indeksowanie od 0
			if (colors[neighbour] == color) {
				// Konflikt - ten sam kolor dla wierzcho³ka i s¹siada
				return false;
			}
			// Jeœli s¹siad nie ma jeszcze przypisanego koloru, rekurencyjnie przypiszmy mu przeciwny kolor
			if (colors[neighbour] == 0 && !assignColorsDfs(colors, neighbour, -color)) {
				return false; // Jeœli rekurencja zwróci³a false, to zakoñcz dzia³anie z b³êdem
			}
		}
		return true; // Uda³o siê przypisaæ kolory wierzcho³kom
	}

	void dfs(long long int start, Vector<bool>& visited) const {
		visited[start] = true;

		for (int i = 0; i < graph[start].getSize(); i++) {
			int neighbour = graph[start][i] - 1;
			if (!visited[neighbour]) {
				dfs(neighbour, visited);
			}
		}
	}

public:
	Graph() : number_of_vertices(0), degree_sequence(), graph() {
	}

	Graph(long long int& number_of_vertices, Vector<int>& degree_sequence, Vector<Vector<int>>& graph)
		: number_of_vertices(number_of_vertices) {
		this->degree_sequence = degree_sequence;
		this->graph = graph;
	}

	void setDegreeSequence(Vector<int>& degree_sequence) {
		this->degree_sequence = degree_sequence;
	}

	void setNumberOfVertices(long long int& amount) {
		this->number_of_vertices = amount;
	}

	void setGraph(Vector<Vector<int>>& graph) {
		this->graph = graph;
	}
	
	int componentsCounter() const {
		int counter = 0;

		Vector<bool> visited(number_of_vertices);
		visited.fill(false);

		for (int i = 0; i < number_of_vertices; i++) {
			if (!visited[i]) {
				dfs(i, visited);
				counter++;
			}
		}

		return counter;
	}

	bool isBipartited() const {
		Vector<int> colors(number_of_vertices); // Tablica przechowuj¹ca kolory wierzcho³ków
		colors.fill(0); // Domyœlny kolor (0) - nieprzypisany

		// Przechodzimy przez wszystkie wierzcho³ki, by sprawdziæ dwudzielnoœæ grafu
		for (long long int i = 0; i < number_of_vertices; i++) {
			if (colors[i] == 0 && !assignColorsDfs(colors, i, 1)) {
				// Jeœli wierzcho³ek nie ma jeszcze przypisanego koloru i nie uda³o siê przypisaæ kolorów DFS-em, zwróæ false
				return false;
			}
		}
		return true; // Jeœli uda³o siê przypisaæ kolory wierzcho³kom zgodnie z regu³ami, zwróæ true
	}

	long long int countComplementEdges() const {
		long long int complement_edges = (number_of_vertices * (number_of_vertices - 1)) / 2;
		long long int edges = 0;

		for (int i = 0; i < number_of_vertices; i++) {
			edges += degree_sequence[i];
		}

		edges /= 2;
		complement_edges -= edges;

		return complement_edges;
	}

	~Graph() {
	}
};

