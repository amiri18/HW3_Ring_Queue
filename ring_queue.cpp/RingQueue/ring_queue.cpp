#include <iostream>

/**
 The RingQueue class stores objects in a circular fashion. Once the queue operates at full capacity, the newest element is overwritten by the oldest element.
 @tparam ItemType , data type of the items that the queue (array) stores
 @tparam MAX_SIZE , capacity of the (array) queue
 */
template <typename ItemType, int MAX_SIZE>
class RingQueue;

// Definition of RingQueue
template <typename ItemType, int MAX_SIZE>
class RingQueue{
    
// Nested Forward declaration of RingQueue<ItemType,MAX_SIZE>::iterator
public:
    class iterator;
    
// Definition of RingQueue<ItemType,MAX_SIZE>::iterator
public:
    class iterator{
    private:
        // A link to the parent container
        RingQueue* parent;
        
        // The position within the RingQueue is determined by how
        // far ahead we are from the begining of the queue.
        int offset;
        
        /**
         private iterator constructor:
         @param _parent , pointer to the RingQueue
         @param _offset , position in queue (from the beginning)
         */
        iterator(RingQueue* _parent, int _offset = 0) : parent(_parent), offset(_offset) { }
        
        // convenient for the container and iterator classes to be granted friendship
        friend class RingQueue<ItemType,MAX_SIZE>;
        
    public:
        /**
         dereference overload:
         @return a referenec to the object that the RingQueue is storing at the correct index
         */
        ItemType& operator*() {
            return parent->buffer[(parent->begin_index + offset) % MAX_SIZE] ;
        }
        
        /**
         pre-increment overlad:
         @return a reference to the iterator
         */
        iterator& operator++(){
            // only need to increase offset in order to advance the array
            ++offset;
            return *this;
        }
        
        /**
         post-increment overload:
         @return a copy of the iterator
         */
        iterator operator++(int unused){
           iterator copy(*this);
            ++(*this);
            return copy;
        }
        
        /**
         equivalence overload:
         @param rhs , iterator to check
         @return true if they are equal, false if they are unequal
         */
        bool operator==(const iterator& rhs) const {
            return ((parent == rhs.parent) && (offset = rhs.offset));
        }
        
        /**
         inequivalence overload:
         @param rhs , iterator to check
         @return true if they are not equal, false if they are equal
         */
        bool operator!=( const iterator& rhs ) const {
            if ((parent == rhs.parent) && (offset == rhs.offset)){
                return false;
            }
            else {
                return true;
            }
        }
        
    };

    
    /**
     class const_iterator{
     private:
     RingQueue* parent;
     int offset;
     
     private:
     // Only RingQueue objects can create const_iterators...
     const_iterator() ;
     
     public:
     // ... however, const_iterators can be 'copied'.
     const_iterator( const const_iterator& ) ;
     
     friend class RingQueue<ItemType,MAX_SIZE>;
     };
     */
    

    // Friendship goes both ways
    friend class iterator;
    // friend class const_iterator;  // not implemented... yet.
    
    
    
private:
    // A fixed-size static array with constant capacity that represents the RingQueue
    ItemType buffer[MAX_SIZE];
    
    // The starting index
    int begin_index;
    
    // The actual size of the RingQueue
    int ring_size;
    
public:
    /** RingQueue constructor:
     */
    RingQueue() : begin_index(0), ring_size(0) {
        // default initialize object types
        for (int i = 0; i < MAX_SIZE; ++i)
            buffer[i] = ItemType();
    }
    
    /**
     front access:
     @return the object stored at the beginning index
     */
    ItemType front() const {
        if ( ring_size == 0 ) std::cerr<< "Warning: Empty ring!\n" ;
        return buffer[begin_index];
    }
    
    /**
     back access:
     @return the object stored at the last index
     */
    ItemType back() const {
        if ( ring_size == 0 ) std::cerr<< "Warning: Empty ring!\n" ;
        return buffer[(begin_index+ring_size-1)%MAX_SIZE];
    }
    
    /**
     adds an object to the queue:
     @param value , object to be added
     */
    void push_back( const ItemType& value ){
        // if the ring_size has not reached capacity
        if (ring_size < MAX_SIZE){
            // insert the object at the next available index
            buffer[(begin_index+ring_size)%MAX_SIZE] = value;
            // increase the size
            ++ring_size;
        }
        else { // if the size has reached capacity
            // overwrite the beginning element with the object
            buffer[(begin_index+ring_size)%MAX_SIZE] = value;
            
            // if the object was added at the literal end of the array
            if (begin_index == MAX_SIZE-1 &&((begin_index+ring_size)%MAX_SIZE) == begin_index){
                // set the beginning index back to 0
                begin_index = 0;
            }
            // if the object was not added at the end
            if (((begin_index+ring_size)%MAX_SIZE) == begin_index){
                // increase the beginning index
                ++begin_index;
            }
        }
    }
    /**
     removes the object at the front:
     */
    void pop_front(){
        if (ring_size == 0) { // don't remove on an empty array
            std::cerr << "Don't pop_front on an empty ring!\n";
        }
        else {
            --ring_size; // decrease the size
            
            // if the "front" is the end
            if (begin_index == MAX_SIZE-1) {
                // set the beginning index to the literal front of the array
                begin_index = 0;
            }
            else { // increase the beginning index
                ++begin_index;
                
            }
        }
    }
    
    /**
     iterator to the beginning:
     @return an iterator that points to the beginning of the queue
     */
    iterator begin() { // remember that offset = 0 here
        return iterator(this,0);
    }
    
    /**
     iterator to (beyond) the end:
     @return an iterator points past the end
     */
    iterator end() { // remember that this is not an accurate index
        return iterator(this,ring_size);
    }
    
   /**
    size accessor:
    @return the ring size
    */
    size_t size() const {
        return ring_size;
    }
    
    /**
     displays everything stored in the array:
     */
    void dump_queue() const {
        std::cout << "Raw queue...\n";
        for (int i = 0 ; i < MAX_SIZE ; ++i ) {
            std::cout << "Val: " << buffer[i] << ", at: " << buffer+i << '\n';
        }
        std::cout << '\n';
        return;
    }
    
};

int main(){
    RingQueue<int,7> rq;
    rq.dump_queue();
    
    for ( int i = 0 ; i < 8 ; ++i ){
        rq.push_back(i+1);
    }
    rq.dump_queue();
    rq.pop_front();
    
    std::cout << "Queue via size: \n";
    
    // RingQueue<int,7>::iterator it = rq.begin() ;
    auto it = rq.begin();
    for ( size_t i = 0 ; i < rq.size() ; ++i ) {
        std::cout << "Value: " << *it << ", address: " << &(*it) << '\n';
        ++it;
    }
    
     std::cout << '\n' << "Queue via iterators: \n";
     for ( auto it = rq.begin() ; it != rq.end() ; ++it ) {
     std::cout << "Value: " << *it << ", address: " << &(*it) << '\n';
     }
     std::cout << '\n';
    
    rq.dump_queue();
    
    return 0;
}

/**
 +++++++++++++++++++++++++++++++++++++++++++++++
 The output of your program [once the missing
 code is added] should look more or less like
 the output below.
 
 Note:
 It is dependent on the device where
 this driver is executed. However, it
 should be clear that the difference
 between consecutive memory addresses
 is equal to the number reported by
 'size_of( int )'.
 +++++++++++++++++++++++++++++++++++++++++++++++
 
 Raw queue...
 Val: 2, at: 0x7ffcdeeaab40
 Val: 0, at: 0x7ffcdeeaab44
 Val: 4198285, at: 0x7ffcdeeaab48
 Val: 0, at: 0x7ffcdeeaab4c
 Val: 0, at: 0x7ffcdeeaab50
 Val: 0, at: 0x7ffcdeeaab54
 Val: 0, at: 0x7ffcdeeaab58
 
 Raw queue...
 Val: 8, at: 0x7ffcdeeaab40
 Val: 2, at: 0x7ffcdeeaab44
 Val: 3, at: 0x7ffcdeeaab48
 Val: 4, at: 0x7ffcdeeaab4c
 Val: 5, at: 0x7ffcdeeaab50
 Val: 6, at: 0x7ffcdeeaab54
 Val: 7, at: 0x7ffcdeeaab58
 
 Queue via size:
 Value: 3, address: 0x7ffcdeeaab48
 Value: 4, address: 0x7ffcdeeaab4c
 Value: 5, address: 0x7ffcdeeaab50
 Value: 6, address: 0x7ffcdeeaab54
 Value: 7, address: 0x7ffcdeeaab58
 Value: 8, address: 0x7ffcdeeaab40
 
 Queue via iterators:
 Value: 3, address: 0x7ffcdeeaab48
 Value: 4, address: 0x7ffcdeeaab4c
 Value: 5, address: 0x7ffcdeeaab50
 Value: 6, address: 0x7ffcdeeaab54
 Value: 7, address: 0x7ffcdeeaab58
 Value: 8, address: 0x7ffcdeeaab40
 
 Raw queue...
 Val: 8, at: 0x7ffcdeeaab40
 Val: 2, at: 0x7ffcdeeaab44
 Val: 3, at: 0x7ffcdeeaab48
 Val: 4, at: 0x7ffcdeeaab4c
 Val: 5, at: 0x7ffcdeeaab50
 Val: 6, at: 0x7ffcdeeaab54
 Val: 7, at: 0x7ffcdeeaab58
 */
