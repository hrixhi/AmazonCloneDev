#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>

template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double priority, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double priority, const T& item);

private:
    /// Add whatever helper functions you need below

    void heapify(int idx);
    void trickleUp(int loc);

    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickleUp(int loc)
{
    int parent = (loc-1)/m_;
    while(parent >= 0 && c_(store_[loc].first, store_[parent].first) ) { 
        // std::swap(store_[parent], store_[loc]); 
        // keyToLocation_[store_[loc].second] = parent;
        // keyToLocation_[store_[index].second] = loc;
        // loc = parent;
        // parent = (loc-1)/m_;

    std::pair<double, T> temp = store_[parent];
      store_[parent] = store_[loc];
      keyToLocation_[store_[loc].second] = parent;
      store_[loc] = temp;
      keyToLocation_[store_[loc].second] = loc;
      loc = parent;
      parent = (loc-1)/m_;
  }

}

//  PUSH FUNCTION
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    // You complete.

    store_.push_back(std::make_pair(priority, item));
    keyToLocation_.insert(std::make_pair(item, store_.size() - 1));
    trickleUp(store_.size()-1);

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    // You complete
    store_[keyToLocation_[item]].first = priority;
    trickleUp(keyToLocation_[item]);

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }

    // You complete
    return store_[0].second;
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::heapify(int idx)
{
   
    std::vector<std::pair<double, T> > temp;

    for(int i = 1; i<=m_; i++) {
        if(m_*idx + i < store_.size()) {
            temp.push_back(store_[m_*idx + i]);
        }
    }

    if(temp.size() == 0) { return; }

    int child = 0;

    for(int i = 0; i<temp.size(); i++) {
        if(c_(temp[i].first, temp[child].first)) {
            child = i;
        }
    }

    if(temp.size() == 0) { return; } 
    
    child = m_*idx + 1 + child;

    if(c_(store_[child].first, store_[idx].first)) {
        // T t = items_[child];
        std::pair<double, T> tempx = store_[idx];
         store_[idx] = store_[child];
         keyToLocation_[store_[idx].second] = idx;
         store_[child] = tempx;
         keyToLocation_[store_[child].second] = child;

    }

    heapify(child);

}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    // You complete
    store_[0] = store_[store_.size() - 1];
    keyToLocation_[store_[0].second] = 0;
    
    //keyToLocation_.erase(store[]);
    //std::cout<<"Before"<<std::endl;
    store_.pop_back();
    heapify(0); 
    //

}

/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}


#endif