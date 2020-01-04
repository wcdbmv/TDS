#include "vizualize.h"

#include <cstdlib>
#include <sstream>
#include <string>

std::string convert_to_dot(const Graph& graph) {
	std::ostringstream oss;
	oss << "digraph{";
	for (std::size_t v = 0; v != graph.n_vertices; ++v) {
		if (graph.adj[v].empty())
			oss << v << ';';
		else
			for (auto const w : graph.adj[v])
				oss << v << "->" << w << ';';
	}
	oss << '}';
	return oss.str();
}

void download_image(const std::string& url) {
	std::ostringstream oss;
	oss << "wget -O tmp/digraph.png \"" << url << "\" 2>tmp/log";
	system(oss.str().c_str());
}

void show_image() {
	system("eog tmp/digraph.png");
}

void vizualize(const Graph& graph) {
	std::ostringstream oss;
	const std::string api = "http://chart.apis.google.com/chart?cht=gv&chl=";
	oss << api << convert_to_dot(graph);
	download_image(oss.str());
	show_image();
}
