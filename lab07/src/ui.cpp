#include "ui.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "colors.h"
#include "vizualize.h"

//—————————————————————————————————————————————————————————————————————— static

static Graph graph(1);

static std::string const& menu_info = \
	"Menu:\n"
	"1. Create digraph\n"
	"2. Load digraph\n"
	"3. Remove digraph\n"
	"4. List digraphs\n"
	"0. Exit\n\n"
;

static std::string const& dg_menu_info = \
	"Digraph menu:\n"
	"1. Display\n"
	"2. Add vertex\n"
	"3. Add edge\n"
	"4. Remove vertex\n"
	"5. Remove edge\n"
	"6. Count SCC\n"
	"7. Save as\n"
	"0. Exit\n\n"
;

//—————————————————————————————————————————————————————————————————————— common

void cls() {
	std::cout << CLS;
}

int clear_input() {
	char c;
	int symbols = 0;
	while ((c = std::cin.get()) != '\n' && c != EOF)
		++symbols;
	return symbols;
}

void press_enter() {
	print_flashing("\n<press Enter to continue>");
	if (getchar() != '\n')
		clear_input();
	cls();
}

void print_exit() {
	print_bold("I hope I was helpful. Thank you for using.");
	press_enter();
	cls();
}

void print_error(std::string const& msg) {
	print_red(msg);
	press_enter();
}

void print_good(std::string const& msg) {
	print_green(msg);
	press_enter();
}

void display(std::string const& msg) {
	cls();
	std::cout << msg;
}

int read_action() {
	std::cout << ">>> ";
	char c = std::cin.get();
	if (c != '\n')
		if (clear_input())
			return -1;
	return c - '0';
}

int input_unsigned(std::string const& prompt) {
	int d = -1;
	std::cout << "\nInput " << prompt << "\n>>> ";
	int rc1 = scanf("%d", &d);
	int rc2 = clear_input();
	if (rc1 != 1 || rc2)
		return -1;
	return d;
}

//—————————————————————————————————————————————————————————————————— filesystem

std::string get_filename() {
	std::string filename;
	std::cout << "\nInput filename\n>>> ";
	std::getline(std::cin, filename);
	return "dgf/" + filename;
}

bool file_exists(std::string const& filename) {
	std::ifstream ifs(filename.c_str());
	return ifs.good();
}

void init_file(std::string const& filename) {
	std::ofstream ofs(filename.c_str());
	ofs << "[1]\n0: null\n";
}

//—————————————————————————————————————————————————————————————————— digraph ui

void dg_save_as() {
	std::string filename = get_filename();
	std::ofstream ofs(filename.c_str());
	ofs << graph;
	print_good("Graph saved successful");
}

void dg_count_scc() {
	std::cout << "Strongly connected components:\n";
	std::size_t scc = print_scc(graph, std::cout);
	if (scc == 1)
		print_good("Graph is strongly connected");
	else
		print_error("Graph isn't strongly connected");
}

void dg_remove_edge() {
	int v = input_unsigned("start vertex");
	if (v < 0 || !graph.vertex_exists(v)) {
		print_error("Invalid vertex");
		return;
	}
	int w = input_unsigned("finish vertex");
	if (w < 0 || !graph.vertex_exists(w)) {
		print_error("Invalid vertex");
		return;
	}
	if (!graph.edge_exists(v, w)) {
		print_error("There is no such edge");
		return;
	}
	graph.remove_edge(v, w);
	print_good("Edge deleted successful");
}

void dg_remove_vertex() {
	if (graph.n_vertices == 1) {
		print_error("Can't delete 1 vertex");
		return;
	}
	int v = input_unsigned("vertex");
	if (v < 0 || !graph.vertex_exists(v)) {
		print_error("Invalid vertex");
		return;
	}
	graph.remove_vertex(v);
	print_good("Vertex deleted successful");
}

void dg_add_edge() {
	int v = input_unsigned("start vertex");
	if (v < 0 || !graph.vertex_exists(v)) {
		print_error("Invalid vertex");
		return;
	}
	int w = input_unsigned("finish vertex");
	if (w < 0 || !graph.vertex_exists(w)) {
		print_error("Invalid vertex");
		return;
	}
	if (graph.edge_exists(v, w)) {
		print_error("Edge already exists");
		return;
	}
	graph.add_edge(v, w);
	print_good("Edge added successful");
}

void dg_add_vertex() {
	graph.add_vertex();
	print_good("Vertex added successful");
}

void dg_display() {
	std::cout << "\nAdjacency list:\n" << graph;
	vizualize(graph);
	press_enter();
}

//————————————————————————————————————————————————————————————————————— file ui

void dg_list() {
	// lazy
	std::cout << "\nList of digraphs:\n";
	system("ls -1 dgf");
	press_enter();
}

void dg_fremove() {
	std::string filename = get_filename();
	if (!file_exists(filename)) {
		print_error("There is no such file");
		return;
	}
	remove(filename.c_str());
	print_good("File deleted successful");
}

bool dg_fload() {
	std::string filename = get_filename();
	if (!file_exists(filename)) {
		print_error("There is no such file");
		return false;
	}
	std::ifstream ifs(filename.c_str());
	ifs >> graph;
	return true;
}

void dg_fcreate() {
	std::string filename = get_filename();
	if (file_exists(filename)) {
		print_error("File already exists");
		return;
	}
	init_file(filename);
	print_good("File created successful");
}

//———————————————————————————————————————————————————————————————————————— menu

bool dg_menu() {
	display(dg_menu_info);
	int action = read_action();
	switch (action) {
	case 1:
		dg_display();
		return true;
	case 2:
		dg_add_vertex();
		return true;
	case 3:
		dg_add_edge();
		return true;
	case 4:
		dg_remove_vertex();
		return true;
	case 5:
		dg_remove_edge();
		return true;
	case 6:
		dg_count_scc();
		return true;
	case 7:
		dg_save_as();
		return true;
	case 0:
		print_exit();
		return false;
	default:
		print_error("No such action");
		return true;
	}
}

bool menu() {
	display(menu_info);
	int action = read_action();
	switch (action) {
	case 1:
		dg_fcreate();
		return true;
	case 2:
		if (dg_fload())
			while (true)
				if (!dg_menu())
					return true;
	case 3:
		dg_fremove();
		return true;
	case 4:
		dg_list();
		return true;
	case 0:
		print_exit();
		return false;
	default:
		print_error("No such action");
		return true;
	}
}
