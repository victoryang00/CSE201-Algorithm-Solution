#include <bits/stdc++.h>
#include <type_traits>
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
  template <typename... Rest> void addEdge(Node *e, Rest &&...args) {
    static_assert((std::is_constructible_v<Node *, Rest &&> && ...));
    this->neighbors->push_back(e);
    (this->neighbors->push_back(std::forward<Rest>(args)), ...);
  };
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
  a.addEdge(&b,&c);
  b.addEdge(&e);
  c.addEdge(&d);
  d.addEdge(&e);
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