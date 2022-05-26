#ifndef SEARCHABLE_H
#define SEARCHABLE_H

#include <vector>
#include <memory>
#include <iostream>

using std::vector;
using std::unique_ptr;
using std::ostream;

// Don't edit this file

class Searchable {

public:

    virtual ~Searchable() {}
    
    virtual bool isSolution() const = 0;    
    virtual vector<unique_ptr<Searchable> > successors() const = 0;
    virtual void write(ostream & o) const = 0;
    
    virtual int heuristicValue() const {
        return 0;
    }
    

};

#endif
