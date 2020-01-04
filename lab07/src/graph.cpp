#include "graph.h"

#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <string>
#include <stack>

Graph::Graph(std::size_t n_vertices)
	: n_vertices(n_vertices)
	, adj(std::vector<std::list<std::size_t> >(n_vertices))
	{ }

void Graph::add_edge(std::size_t v, std::size_t w) {
	adj[v].push_back(w);
}

void Graph::remove_edge(std::size_t v, std::size_t w) {
	adj[v].remove(w);
}

void Graph::add_vertex() {
	adj.push_back(std::list<std::size_t>());
	++n_vertices;
}

void Graph::remove_vertex(std::size_t v) {
	std::size_t last = n_vertices - 1;
	swap_vertices(v, last);
	for (v = 0; v != last; ++v) {
		adj[v].remove(last);
	}
	adj.pop_back();
	--n_vertices;
}

void Graph::swap_vertices(std::size_t v, std::size_t w) {
	std::swap(adj[v], adj[w]);
	for (std::size_t x = 0; x != n_vertices; ++x) {
		if (x == v || x == w)
			continue;
		for (auto& y : adj[x])
			if (y == v)
				y = w;
			else if (y == w)
				y = v;
	}
}

bool Graph::vertex_exists(std::size_t v) const {
	return v < n_vertices;
}

bool Graph::edge_exists(std::size_t v, std::size_t w) const {
	for (auto const i : adj[v])
		if (i == w)
			return true;
	return false;
}

bool Graph::can_add_edge(std::size_t v, std::size_t w) const {
	return vertex_exists(v) && vertex_exists(w) && !edge_exists(v, w);
}

std::ostream& operator<<(std::ostream& os, Graph const& graph) {
	os << '[' << graph.n_vertices << ']' << std::endl;
	for (std::size_t v = 0; v != graph.n_vertices; ++v) {
		os << v << ": ";
		if (graph.adj[v].empty())
			os << "null";
		else
			for (auto const w : graph.adj[v])
				os << w << ' ';
		os << std::endl;
	}
	return os;
}

struct confirm_input {
	char const* str;
	confirm_input(char const* in) : str(in) { }
	friend std::istream& operator>>(std::istream& s, confirm_input const& o) {
		for (char const* p = o.str; *p; ++p)
			if (std::isspace(*p))
				std::istream::sentry k(s); // discard whitespace
			else if (s.get() != *p)
				s.setstate(std::ios::failbit); // stop extracting
		return s;
	}
};

std::istream& operator>>(std::istream& is, Graph& graph) {
	std::size_t n_vertices;
	is >> confirm_input("[") >> n_vertices >> confirm_input("]\n");
	graph = Graph(n_vertices);
	for (std::size_t v = 0; v != n_vertices; ++v) {
		std::string s;
		std::getline(is, s);
		std::istringstream iss(s);
		std::size_t w;
		iss >> w >> confirm_input(": ");
		while (iss >> w)
			graph.add_edge(v, w);
	}
	return is;
}

Graph transpose(Graph const& graph) {
	Graph t(graph.n_vertices);
	for (std::size_t v = 0; v != graph.n_vertices; ++v)
		for (auto const w : graph.adj[v])
			t.add_edge(w, v);
	return t;
}

void fill_order(Graph const& graph,
                std::size_t v,
                std::vector<bool>& visited,
                std::stack<std::size_t>& stack) {
	visited[v] = true;
	for (auto const w : graph.adj[v])
		if (!visited[w])
			fill_order(graph, w, visited, stack);
	stack.push(v);
}

void print_dfs(Graph const& graph,
               std::size_t v,
               std::vector<bool>& visited,
               std::ostream& os) {
	visited[v] = true;
	os << v << ' ';

	for (auto const w : graph.adj[v])
		if (!visited[w])
			print_dfs(graph, w, visited, os);
}

// strongly connected components
std::size_t print_scc(Graph const& graph, std::ostream& os) {
	std::stack<std::size_t> stack;
	std::vector<bool> visited(graph.n_vertices, false);
	for (std::size_t v = 0; v != graph.n_vertices; ++v)
		if (!visited[v])
			fill_order(graph, v, visited, stack);

	Graph t = transpose(graph);

	std::size_t scc = 0;
	std::fill(visited.begin(), visited.end(), false);
	while (!stack.empty()) {
		std::size_t v = stack.top();
		stack.pop();

		if (!visited[v]) {
			print_dfs(t, v, visited, os);
			os << std::endl;
			++scc;
		}
	}
	return scc;
}
