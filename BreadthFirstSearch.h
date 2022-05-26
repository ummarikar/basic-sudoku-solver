#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H

#include "Searchable.h"

#include <memory>
using std::unique_ptr;

#include <deque>
using std::deque;

class BreadthFirstSearch {
protected:
    deque<unique_ptr<Searchable> > q;
    int nodes = 0;

public:
    BreadthFirstSearch(std::unique_ptr<Searchable> && startFrom) {
        q.push_back(std::move(startFrom));
    }

    int getNodesExpanded() const {
        return nodes;
    }

    Searchable* solve() { 
        while (!q.empty()) {
            if (q.front()->isSolution()) {
                return q.front().get(); 
            }
                  
            ++nodes; 
            unique_ptr<Searchable> current(std::move(q.front()));
            q.pop_front();
            vector<unique_ptr<Searchable>> successors = current->successors();
            
            for (auto & successor : successors) {
                q.push_back(std::move(successor));
            }
        }
        
        return nullptr;
    }
};

#endif
