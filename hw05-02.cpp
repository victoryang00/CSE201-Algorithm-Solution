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
  dfs(&c, 0);
  std::cout << a.currState << " " << a.id << " " << a.entrytime << " "
            << a.finishTime << "\n";
  std::cout << b.currState << " " << b.id << " " << b.entrytime << " "
            << b.finishTime << "\n";
  std::cout << c.currState << " " << c.id << " " << c.entrytime << " "
            << c.finishTime << "\n";
  std::cout << d.currState << " " << d.id << " " << d.entrytime << " "
            << d.finishTime << "\n";
  std::cout << e.currState << " " << e.id << " " << e.entrytime << " "
            << e.finishTime << "\n";
  std::cout << "-----------------------\n";
  dfs(&a, 0);
  std::cout << a.currState << " " << a.id << " " << a.entrytime << " "
            << a.finishTime << "\n";
  std::cout << b.currState << " " << b.id << " " << b.entrytime << " "
            << b.finishTime << "\n";
  std::cout << c.currState << " " << c.id << " " << c.entrytime << " "
            << c.finishTime << "\n";
  std::cout << d.currState << " " << d.id << " " << d.entrytime << " "
            << d.finishTime << "\n";
  std::cout << e.currState << " " << e.id << " " << e.entrytime << " "
            << e.finishTime << "\n";
}