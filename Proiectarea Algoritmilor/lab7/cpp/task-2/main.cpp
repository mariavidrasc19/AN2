#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<int> adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
		}
		fin.close();
	}

	vector<int> TopSort(vector<int> &tsort) {
		vector<int> nodes(n + 1);
		queue<int> q;
		int node;

		for (const auto& u : adj) {
		    for (int i : u) {
		        nodes[i] ++;
		    }
		}

		for (int i = 1; i <= n; ++i) {
		    if (nodes[i] == 0) {
		        q.push(i);
		    }
		}

		while (!q.empty()) {
            node = q.front();
            tsort.emplace_back(node);
            q.pop();

            for (int nextNode : adj[node]) {
                if (nodes[nextNode] >= 0) {
                    q.push(nextNode);
                }
            }
		}
		return tsort;
	}

	vector<int> get_result() {
		vector<int> tsort;
		/*
		TODO: Faceti sortarea topologica a grafului stocat cu liste de
		adiacenta in adj.
		*******
		ATENTIE: nodurile sunt indexate de la 1 la n.
		*******
		*/
		
		return TopSort(tsort);
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i] << ' ';
		}
		fout << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
