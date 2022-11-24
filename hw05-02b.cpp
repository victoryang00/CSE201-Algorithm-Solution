#include <bits/stdc++.h>
using namespace std;

class Node {
public:
  int entrytime;
  int finishTime;
  enum state { unvisited, in_progress, all_done };
  state currState;
  list<Node *> *neighbors;
  int id;

  Node(int id) {
    this->neighbors = new list<Node *>();
    this->currState = unvisited;
    this->id = id;
  };
  void addEdge(Node *e) { this->neighbors->push_back(e); };
};

int dfs(Node *u, int currentTime) {
  u->entrytime = currentTime;
  currentTime++;
  u->currState = Node::in_progress;
  for (auto v : *u->neighbors) {
    if (v->currState == Node::unvisited) {
      currentTime = dfs(v, currentTime);
      currentTime++;
    }
  }
  u->finishTime = currentTime;
  u->currState = Node::all_done;
  return currentTime;
}

int main() {
  auto a = Node(1);
  auto b = Node(2);
  auto c = Node(3);
  auto d = Node(4);
  auto e = Node(5);
  a.addEdge(&b);
  a.addEdge(&c);
  b.addEdge(&e);
  c.addEdge(&d);
  d.addEdge(&e);
  auto time = dfs(&c, 0);
  std::vector<Node *> vs = {&b, &a, &c, &d, &e};
  while (true) {
    int v;
    for (v = 0; v < vs.size(); v++) {
      if (vs.at(v)->currState == Node::state::unvisited) {
        time = dfs(vs[v], time);
        continue;
      }
    }
    if (v == vs.size()) {
      break;
    }
  }
  std::cout << time << "\n";
}