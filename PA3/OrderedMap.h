#ifndef ORDERED_MAP_H
#define ORDERED_MAP_H
#include <vector>

using namespace std;

// OrderedMap class
template <class Key, class Value>
class OrderedMap
{
  public:
    /**
     * Default constructor for the map
     */
    OrderedMap( ) : root_key{ new KeyNode(-1, nullptr, nullptr) }
    { }

    OrderedMap( int map_size) : root_key{ new KeyNode(-1, nullptr, nullptr) }, MAP_MAX_SIZE{ map_size }
    { }
    
    /**
     * Destructor for the map
     */
    ~OrderedMap( )
    { makeEmpty( ); }

    /**
     * Copy assignment
     */
    OrderedMap & operator=( const OrderedMap & rhs )
    {
        OrderedMap copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    OrderedMap & operator=( OrderedMap && rhs )
    {
        std::swap( root_key, rhs.root_key );
        return *this;
    }

    /**
     * Insert a key value pair in the map.
     */
    void insert( const Key & key, const Value & value )
    {
        int key_hash = hashFunction(key);
        return insert( key_hash, key, value, root_key );
    }

    /**
     * Print the map content in sorted order.
     */
    void printMap( ostream & out = cout ) const
    {
        printMap( root_key, out );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    { makeEmpty( root_key ); }



  private:
    
    struct ValueNode
    {
        Key key;
        Value value;
        ValueNode* right;

        ValueNode
            ( const Key & theKey, const Value & theValue, ValueNode *rt)
          : key{ theKey }, value{ theValue }, right{ rt } { }

        ValueNode
            ( Key && theKey, Value && theValue, ValueNode *rt)
          : key{ std::move( theKey ) }, value{ std::move( theValue ) }, right{ rt } { }
    };

    struct KeyNode
    {
        int hash_key;
        ValueNode* right;
        KeyNode* down;

        KeyNode
            (int hash, ValueNode *rt, KeyNode* dn)
          : hash_key{ hash }, right{ rt }, down{ dn } { }
    };

    KeyNode *root_key;
    int MAP_MAX_SIZE;
    vector<Key> keys;

    /** Q 4.1
     *
     * Implement your own hash function that will convert the Key into an integer.
     *
     * Note: Return value of this function should be between 0 than MAP_MAX_SIZE - 1.
     */
    int hashFunction( const Key & key ) {
        
        // Remove below line after your implementation
       bool find = false;
            for (int i = 0; i < keys.size() && !find; i++){  // Search if hash key already existed.
                if (key == keys.at(i)){
                    return i;
                    find = true;
                }
            }
            if(!find){
                if (keys.size() < MAP_MAX_SIZE - 1){    // the number of hash key is less than max size
                    keys.push_back(key);
                    return keys.size() - 1;
                }
            }
        return -1; //The number of hash key is larger than the max size
    }

    /** Q 4.2
     *
     * Implement method to insert a key, value pair in a map.
     *
     * Note: Since this is ordered map, insert key in sorted order of hash_key.
     *       In case there is already a key node with given hash_key, insert the
     *       value node in the end.
     */
    void insert( int hash_key, const Key & key, const Value & value, KeyNode* t )
    {
        // Remove below line after your implementation
        bool ins = false;
        while(!ins){
            if (t->down == nullptr){  // the list for keyNode is empty
                KeyNode* k = new KeyNode(hash_key, nullptr, nullptr);
                ValueNode* v = new ValueNode(key, value, nullptr);
                k->right = v;
                t->down = k;
                ins = true;
            }
            else if (hash_key < t->down->hash_key){  //hash_key < next
                KeyNode* k = new KeyNode(hash_key, nullptr, nullptr);
                ValueNode* v = new ValueNode(key, value, nullptr);
                k->right = v;
                KeyNode* aft = t->down;
                t->down = k;
                k->down = aft;
                ins = true;
            }
            else if (hash_key == t->down->hash_key){ //hash_key = next
                ValueNode* idx = new ValueNode(key, value, nullptr);
                ValueNode* ind = t->down->right;
                bool repeat = false;
                while (ind->right != nullptr){
                    if (key == ind->key && value == ind->value){
                        repeat = true;
                        break;
                    }
                    ind = ind->right;
                }
                if (!repeat){
                    ind->right = idx;
                }
                ins = true;
            }
            else{ //hash_key > next
                t = t->down;
            }
        }
    }


    /**
     * Internal method to make a map empty.
     */
    void makeEmpty( KeyNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty_row( t->right );
            makeEmpty( t->down );
            delete t;
        }
        t = nullptr;
    }

    void makeEmpty_row( ValueNode * & v )
    {
        if( v != nullptr )
        {
            makeEmpty_row( v->right );
            delete v;
        }
        v = nullptr;
    }

    /**
     * Internal method to print the map.
     */
    void printMap( KeyNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            out << t->hash_key << "\t->";
            if(t->hash_key == -1) {
                out << " Root KeyNode of Map";
            } else {
                printMap_row( t->right, out );
            }
            out << endl;
            printMap( t->down, out );
        }
    }

    void printMap_row( ValueNode *v, ostream & out ) const
    {
        if( v != nullptr )
        {
            out << " ( " <<v->key << " , " << v->value << " ) ";
            printMap_row( v->right, out );
        }
    }
};

#endif
