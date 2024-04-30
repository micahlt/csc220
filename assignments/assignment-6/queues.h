#include <iostream>
#include <list>
#include <map>
#include <utility>
using namespace std;

template <typename T> class rpt_queue {
private:
  // Store the queue in a list of pairs (item and count)
  list<pair<T, int>> queue;

public:
  // Push a copy of item onto the queue, grouping as needed
  void push(const T &item) {
    // Iterate over ad check for an existing entry to group with
    for (auto i = queue.begin(); i != queue.end(); ++i) {
      if (i->first == item) {
        // Increment the count of items
        i->second++;
        return;
      }
    }
    // Push a new copy initialized to a count of zero
    queue.push_back(pair<T, int>(item, 1));
  }
  // Pop an item from the queue
  int pop(T &item) {
    // Don't do anything if there aren't any items to pop
    if (queue.empty()) {
      return 0;
    } else {
      pair<T, int> p;
      p = queue.front();
      queue.pop_front();
      item = p.first;
      return p.second;
    }
  }
  // Return whether or not the queue contains items
  bool empty() const { return queue.empty(); }
  // Print out the queue in a pretty format
  void print() {
    cout << "[front] ->" << endl;
    for (auto i = queue.begin(); i != queue.end(); ++i)
      cout << i->first << ": " << i->second << endl;
    cout << "<- [back]" << endl;
  }
};

template <typename T> class expand_queue {
private:
  list<T> queue;

public:
  // push count repetitions of item to queue
  void push(int count, const T &item) {
    if (count < 1) {
      return;
    }
    while (--count) {
      queue.push_back(item);
    }
  }
  // Pop an item from the queue
  bool pop(T &item) {
    if (empty()) {
      return false;
    } else {
      item = queue.front();
      queue.pop_front();
      return true;
    }
  }
  // Return whether or not the queue contains items
  bool empty() const { return queue.empty(); }
  // Print out the queue in a pretty format
  void print() {
    cout << "[front] ->" << endl;
    for (auto i = queue.begin(); i != queue.end(); ++i)
      cout << *i << endl;
    cout << "<- [back]" << endl;
  }
};