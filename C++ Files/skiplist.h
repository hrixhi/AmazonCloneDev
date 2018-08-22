#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>



template <class K, class V> 
struct SkipNode
{
    K key;
    V value;
  
    SkipNode** forward; //array of ptrs

    SkipNode(K& k, V& v, int level)
    {
        key = k; 
        value = v;
        // height = level;
        // end = e;
        forward = new SkipNode*[level+1];
    }
};





template <typename K, typename V, typename Comp = std::less<K> > 
class SkipList {
	
private:
	
	int maxLevel;
	int size_;
	double probability;
	SkipNode<K, V>* end;
	SkipNode<K, V>* head;
	Comp comp;

	int nodeLevel(const std::vector<SkipNode<K, V>* >& v);
	int randomLevel();

public:

	SkipList(const Comp& c = Comp());
    ~SkipList();
    // If the key is already present, update the value
    void insert(const std::pair<const K,V>& item); 
    // Return NULL if the key doesn't exist in the map
    std::pair<const K,V>* find(const K& key); 
    // Do nothing if the key does not exist
    void erase(const K& key); 
    size_t size() const;
    bool empty() const;
    //void print();
    SkipNode<K, V>* internalFind(const K& key);
	
};



template <typename K, typename V, typename Comp> 
SkipList<K, V, Comp>::SkipList(const Comp& c) 
 {

	maxLevel = 20;
	probability = 0.5;
	K key; V val;
	comp = c;
	
	head = new SkipNode<K, V>(key, val, maxLevel); 
	end = new SkipNode<K, V>(key, val, maxLevel);

	for(int i=0; i < maxLevel; i++){
		head->forward[i] = end; 
	}

}

template <typename K, typename V, typename Comp> 
SkipList<K, V, Comp>::~SkipList() 
 {


}


template <typename K, typename V, typename Comp> 
int SkipList<K, V, Comp>::nodeLevel (const std::vector<SkipNode<K, V>* >& v) {
    
    int currentLevel = 1;
    
    int nil = std::numeric_limits<int>::max();

    if (v[0]->key == nil) {
        return currentLevel;
    }

    for (size_t i = 0; i < v.size(); ++i) {

        if (v[i] != NULL && v[i]->key != nil) {
            ++currentLevel;
        } else { 
            break;
        }
    }
    return currentLevel;
    
}



template <typename K, typename V, typename Comp> 
int SkipList<K, V, Comp>::randomLevel () {
    
   int x = 1;

    while ((((double)std::rand() / RAND_MAX)) < probability && std::abs(x) < maxLevel) {

        x += 1;
    }

    return abs(x);

}




template <typename K, typename V, typename Comp> 
void SkipList<K, V, Comp>::insert(const std::pair<const K,V>& item) {
	
	SkipNode<K, V>* tempx = internalFind(item.first);

    if (tempx) {

        tempx->value = item.second;
        return;
    }

    std::vector<SkipNode<K, V>* > update(1 + maxLevel);
    
    SkipNode<K, V>* current = head;
    // search the list 
   for(int i=maxLevel-1; i >= 0; i--){
		while(current->forward[i]!= end &&  comp(current->forward[i]->key, item.first)){ 
			current = current->forward[i];
		} 
		update[i] = current;
	}
	current = current->forward[0];


    int newNodeLevel = 1;
    if (current->key != item.first) {
    	K key=item.first;
    	V value=item.second;

         newNodeLevel = randomLevel();
        SkipNode< K, V>* x = new SkipNode<K, V>(key, value, newNodeLevel);
       
        int currentLevel = nodeLevel(update);

        if (newNodeLevel > currentLevel) {

            for (int i = currentLevel + 1; i < newNodeLevel; ++i) {

                update[i] = head;
            }   
        }



    for (int i = 0; i < newNodeLevel; ++i) {

        x->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = x;
    }
         
    }


    size_++;

}


template <typename K, typename V, typename Comp>  
SkipNode<K,V>* SkipList<K, V, Comp>::internalFind(const K& key) {
	
	SkipNode<K,V>* current = head;

	for(int i=maxLevel-1; i >= 0; i--){
		while(current->forward[i]!= end && comp(current->forward[i]->key , key)) { 
			current = current->forward[i];
		} 
	}
	current = current->forward[0];
		// will always stop on level 0 w/ current=node
		// just prior to the actual target node or End node current = current->forward[0];
	if(current->key == key)  {
		return current;
	} else {
		return NULL; // key is not in the list
	}
	
}


template <typename K, typename V, typename Comp>  
std::pair<const K,V>* SkipList<K, V, Comp>::find(const K& key) {
	
	SkipNode<K,V>* current = head;

	for(int i=maxLevel - 1; i >= 0; i--){
		while(current->forward[i]!= end &&  comp(current->forward[i]->key, key)){ 
			current = current->forward[i];
		} 
	}
	current = current->forward[0];
		// will always stop on level 0 w/ current=node
		// just prior to the actual target node or End node current = current->forward[0];
	if(current->key == key)  {
		std::pair<const K, V> x = std::make_pair(current->key, current->value);
		std::pair<const K, V>* ptr = &x;
		return ptr; 
		
	} else {
		return NULL; // key is not in the list
	}
	
}

template <typename K, typename V, typename Comp > 
void SkipList<K, V, Comp>::erase(const K& key) {
	
	std::vector<SkipNode<K,V>*> update(maxLevel + 1);
    SkipNode<K, V>* x = head;

    //unsigned int cM = nodeLevel(update);
    //std::cout<<"se"<<std::endl;
    // search and update pointers
    //unsigned int currentMaximum = nodeLevel(head->forward);


    for (unsigned int i = maxLevel-1;  i-- > 0;) {

        while (x->forward[i] != end && comp(x->forward[i]->key, key)) {

            // if(x->forward[i]->forward[i] == NULL) {
            //     break;
            // }

            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[0];

    // update pointers and delete node 
    if (x->key == key) {
        for (unsigned int i = 0; i < update.size(); i++) {

            if (update[i]->forward[i] != x) {

                break;
            }
            update[i]->forward[i] = x->forward[i];
        }
        delete x;        
    }    

    size_--;

}


template <typename K, typename V, typename Comp > 
size_t SkipList<K, V, Comp>::size() const {
	
	return size_;
	
}

template <typename K, typename V, typename Comp > 
bool SkipList<K, V, Comp>::empty() const {
	
	if(head == NULL) {
		return true;
	}
	else {
		return false;
	}
}



#endif