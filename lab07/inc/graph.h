#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <vector>
#include <cstddef>
#include <ostream>

struct Graph {
	std::size_t n_vertices;
	std::vector<std::list<std::size_t> > adj;

	Graph(std::size_t n_vertices);

	void add_edge(std::size_t v, std::size_t w);
	void remove_edge(std::size_t v, std::size_t w);

	void add_vertex();
	void remove_vertex(std::size_t v);
	void swap_vertices(std::size_t v, std::size_t w);

	bool vertex_exists(std::size_t v) const;
	bool edge_exists(std::size_t v, std::size_t w) const;
	bool can_add_edge(std::size_t v, std::size_t w) const;
};

std::ostream& operator<<(std::ostream& os, Graph const& graph);
std::istream& operator>>(std::istream& is, Graph& graph);
std::size_t print_scc(Graph const& graph, std::ostream& os);

#endif // GRAPH_H_
