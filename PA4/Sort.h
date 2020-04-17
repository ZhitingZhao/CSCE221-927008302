#ifndef SORT_H
#define SORT_H

/**
 * Several sorting routines.
 * Arrays are rearranged with smallest item first.
 */

#include <vector>
#include <functional>
using namespace std;

/**
 * Simple insertion sort.
 */
template <typename Comparable>
void insertionSort( vector<Comparable> & a )
{
    for( int p = 1; p < a.size( ); ++p )
    {
        Comparable tmp = std::move( a[ p ] );

        int j;
        for( j = p; j > 0 && tmp < a[ j - 1 ]; --j )
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}


/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
    for( int p = left + 1; p <= right; ++p )
    {
        Comparable tmp = std::move( a[ p ] );
        int j;

        for( j = p; j > left && tmp < a[ j - 1 ]; --j )
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}



/**
 * Shellsort, using Shell's (poor) increments.
 */
template <typename Comparable>
void shellsort( vector<Comparable> & a )
{
    for( int gap = a.size( ) / 2; gap > 0; gap /= 2 )
        for( int i = gap; i < a.size( ); ++i )
        {
            Comparable tmp = std::move( a[ i ] );
            int j = i;

            for( ; j >= gap && tmp < a[ j - gap ]; j -= gap )
                a[ j ] = std::move( a[ j - gap ] );
            a[ j ] = std::move( tmp );
        }
}

/**
 * Standard heapsort.
 */
template <typename Comparable>
void percDown( vector<Comparable> & a, int i, int n );

template <typename Comparable>
void heapsort( vector<Comparable> & a )
{
    for( int i = a.size( ) / 2 - 1; i >= 0; --i )  /* buildHeap */
        percDown( a, i, a.size( ) );
    for( int j = a.size( ) - 1; j > 0; --j )
    {
        std::swap( a[ 0 ], a[ j ] );               /* deleteMax */
        percDown( a, 0, j );
    }
}

/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild( int i )
{
    return 2 * i + 1;
}

/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
template <typename Comparable>
void percDown( vector<Comparable> & a, int i, int n )
{
    int child;
    Comparable tmp;

    for( tmp = std::move( a[ i ] ); leftChild( i ) < n; i = child )
    {
        child = leftChild( i );
        if( child != n - 1 && a[ child ] < a[ child + 1 ] )
            ++child;
        if( tmp < a[ child ] )
            a[ i ] = std::move( a[ child ] );
        else
            break;
    }
    a[ i ] = std::move( tmp );
}

/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void merge( vector<Comparable> & a, vector<Comparable> & tmpArray,
            int leftPos, int rightPos, int rightEnd );

template <typename Comparable>
void mergeSort( vector<Comparable> & a,
                vector<Comparable> & tmpArray, int left, int right )
{
    if( left < right )
    {
        int center = ( left + right ) / 2;
        mergeSort( a, tmpArray, left, center );
        mergeSort( a, tmpArray, center + 1, right );
        merge( a, tmpArray, left, center + 1, right );
    }
}

/**
 * Mergesort algorithm (driver).
 */
template <typename Comparable>
void mergeSort( vector<Comparable> & a )
{
    vector<Comparable> tmpArray( a.size( ) );

    mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}


/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
template <typename Comparable>
void merge( vector<Comparable> & a, vector<Comparable> & tmpArray,
            int leftPos, int rightPos, int rightEnd )
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while( leftPos <= leftEnd && rightPos <= rightEnd )
        if( a[ leftPos ] <= a[ rightPos ] )
            tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );
        else
            tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

    while( leftPos <= leftEnd )    // Copy rest of first half
        tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );

    while( rightPos <= rightEnd )  // Copy rest of right half
        tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

    // Copy tmpArray back
    for( int i = 0; i < numElements; ++i, --rightEnd )
        a[ rightEnd ] = std::move( tmpArray[ rightEnd ] );
}


/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right )
{
    int center = ( left + right ) / 2;
    
    if( a[ center ] < a[ left ] )
        std::swap( a[ left ], a[ center ] );
    if( a[ right ] < a[ left ] )
        std::swap( a[ left ], a[ right ] );
    if( a[ right ] < a[ center ] )
        std::swap( a[ center ], a[ right ] );

        // Place pivot at position right - 1
    std::swap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void quicksort( vector<Comparable> & a, int left, int right )
{
    if( left + 10 <= right )
    {
        const Comparable & pivot = median3( a, left, right );

            // Begin partitioning
        int i = left, j = right - 1;
        for( ; ; )
        {
            while( a[ ++i ] < pivot ) { }
            while( pivot < a[ --j ] ) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot

        quicksort( a, left, i - 1 );     // Sort small elements
        quicksort( a, i + 1, right );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}

/**
 * Quicksort algorithm (driver).
 */
template <typename Comparable>
void quicksort( vector<Comparable> & a )
{
    quicksort( a, 0, a.size( ) - 1 );
}


/**
 * Internal selection method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect( vector<Comparable> & a, int left, int right, int k )
{
    if( left + 10 <= right )
    {
        const Comparable & pivot = median3( a, left, right );

            // Begin partitioning
        int i = left, j = right - 1;
        for( ; ; )
        {
            while( a[ ++i ] < pivot ) { }
            while( pivot < a[ --j ] ) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot

            // Recurse; only this part changes
        if( k <= i )
            quickSelect( a, left, i - 1, k );
        else if( k > i + 1 )
            quickSelect( a, i + 1, right, k );
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}

/**
 * Quick selection algorithm.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect( vector<Comparable> & a, int k )
{
    quickSelect( a, 0, a.size( ) - 1, k );
}


template <typename Comparable>
void SORT( vector<Comparable> & items )
{
    if( items.size( ) > 1 )
    {
        vector<Comparable> smaller;
        vector<Comparable> same;
        vector<Comparable> larger;
        
        auto chosenItem = items[ items.size( ) / 2 ];
        
        for( auto & i : items )
        {
            if( i < chosenItem )
                smaller.push_back( std::move( i ) );
            else if( chosenItem < i )
                larger.push_back( std::move( i ) );
            else
                same.push_back( std::move( i ) );
        }
        
        SORT( smaller );     // Recursive call!
        SORT( larger );      // Recursive call!
        
        std::move( begin( smaller ), end( smaller ), begin( items ) );
        std::move( begin( same ), end( same ), begin( items ) + smaller.size( ) );
        std::move( begin( larger ), end( larger ), end( items ) - larger.size( ) );

/*
        items.clear( );
        items.insert( end( items ), begin( smaller ), end( smaller ) );
        items.insert( end( items ), begin( same ), end( same ) );
        items.insert( end( items ), begin( larger ), end( larger ) );
*/
    }
}

/*
 * This is the more public version of insertion sort.
 * It requires a pair of iterators and a comparison
 * function object.
 */
template <typename RandomIterator, typename Comparator>
void insertionSort( const RandomIterator & begin,
                    const RandomIterator & end,
                    Comparator lessThan )
{
    if( begin == end )
        return;
        
    RandomIterator j;

    for( RandomIterator p = begin+1; p != end; ++p )
    {
        auto tmp = std::move( *p );
        for( j = p; j != begin && lessThan( tmp, *( j-1 ) ); --j )
            *j = std::move( *(j-1) );
        *j = std::move( tmp );
    }
}

/*
 * The two-parameter version calls the three parameter version, using C++11 decltype
 */
template <typename RandomIterator>
void insertionSort( const RandomIterator & begin,
                    const RandomIterator & end )
{
    insertionSort( begin, end, less<decltype(*begin )>{ } );
}

/**
 * Q 1.c - Implement selection sort algorithm
 */
template <typename Comparable>
void selectionSort( vector<Comparable> & a )
{
    // Remove below line after your implementation
    for (int b = 0; b < a.size() - 1; b++){
        auto &i = a.at(b);
        Comparable max = a.at(b+1);
        int pos = b+1;
        for (int c = b+1 ; c < a.size(); c++){
            auto &j = a.at(c);
            if (j > max){
                max = j;
                pos = c;
            }
        }
        auto &j = a.at(pos);
        if (j > i){
            swap(i, j);
        }
    }
}

/**
 * Q 1.b - Implement bubble sort algorithm
 */
template <typename Comparable>
void bubbleSort( vector<Comparable> & a )
{
    // Remove below line after your implementation
    for (auto & i : a){
        for (auto & j : a){
            if (i > j){
                std::swap(i,j);
            }
        }
    }
}

/**
 * Q 1.a - Implement the isSorted function that will chceck if the
 * vector is sorted of not.
 */
template <typename Comparable>
bool isSorted( vector<Comparable> & a )
{
    // Remove below line after your implementation
    auto first = a.at(0);
    auto second = a.at(1);
    if (first < second){
        for (int i = 1; i < a.size() - 1; i++){
            first = a.at(i);
            second = a.at(i+1);
            if (first > second){
                return false;
            }
        }
        return true;
    }
    else{
        for (int i = 1; i < a.size() - 1; i++){
            first = a.at(i);
            second = a.at(i+1);
            if (first < second){
                return false;
            }
        }
        return true;
    }
    return false;
}

/**
 * Q 1.d - Implement hybrid sort algorithm
 */
template <typename Comparable>
int insertFour (vector<Comparable> & a, vector<Comparable> & b, vector<Comparable> & c, vector<Comparable> & d, vector<Comparable> & result){
    while (a.size() > 0 && b.size() > 0 && c.size() > 0 && d.size() > 0){
        if (a.at(0) < b.at(0) && a.at(0) < c.at(0) && a.at(0) < d.at(0)){
            result.push_back(a.at(0));
            a.erase(a.begin());
        }
        else if (b.at(0) < c.at(0) && b.at(0) < d.at(0)){
            result.push_back(b.at(0));
            b.erase(b.begin());
        }
        else if (c.at(0) < d.at(0)){
            result.push_back(c.at(0));
            c.erase(c.begin());
        }
        else{
            result.push_back(d.at(0));
            d.erase(d.begin());
        }
    }
    if (a.size() == 0){
        return 1;
    }
    if (b.size() == 0){
        return 2;
    }
    if (c.size() == 0){
        return 3;
    }
    if (d.size() == 0){
        return 4;
    }
    return -1;
}

template <typename Comparable>
int insertThree(vector<Comparable> & a, vector<Comparable> & b, vector<Comparable> & c, vector<Comparable> & result){
    while (a.size() > 0 && b.size() > 0 && c.size() > 0){
        if (a.at(0) < b.at(0) && a.at(0) < c.at(0)){
            result.push_back(a.at(0));
            a.erase(a.begin());
        }
        else if (b.at(0) < c.at(0)){
            result.push_back(b.at(0));
            b.erase(b.begin());
        }
        else{
            result.push_back(c.at(0));
            c.erase(c.begin());
        }
    }
    if (a.size() == 0){
        return 1;
    }
    if (b.size() == 0){
        return 2;
    }
    if (c.size() == 0){
        return 3;
    }
    return -1;
}


template <typename Comparable>
void hybridSort( vector<Comparable> & a )
{
    // Remove below line after your implementation
    vector<Comparable> first;
    vector<Comparable> sec;
    vector<Comparable> thi;
    vector<Comparable> four;
    int size = a.size();
    for (int i = 0; i < size; i++){
        if (i < size / 4){
            first.push_back(a.at(i));
        }
        else if (i < size / 2){
            sec.push_back(a.at(i));
        }
        else if (i < size * 3 / 4){
            thi.push_back(a.at(i));
        }
        else{
            four.push_back(a.at(i));
        }
    }
    
    quicksort(first, 0, first.size()-1);
    
    quicksort(sec, 0, sec.size()-1);
    
    quicksort(thi, 0, thi.size()-1);
    
    quicksort(four, 0, four.size()-1);
    
    vector<Comparable> result;
    int fin = 0;
    fin = insertFour(first, sec, thi, four, result);
    
    if (fin == 1){
        first = four;
    }
    else if (fin == 2){
        sec = four;
    }
    else if (fin == 3){
        thi = four;
    }
    fin = insertThree(first, sec, thi, result);
    
    if (fin == 1){
        first = thi;
    }
    else if (fin == 2){
        sec = thi;
    }
    
    while (first.size() > 0 && sec.size() > 0){
        if (first.at(0) < sec.at(0)){
            result.push_back(first.at(0));
            first.erase(first.begin());
        }
        else {
            result.push_back(sec.at(0));
            sec.erase(sec.begin());
        }
    }
    if (first.size() == 0){
        for (int i = 0; i < sec.size(); i++){
            result.push_back(sec.at(i));
        }
    }
    else {
        for (int i = 0; i < sec.size(); i++){
            result.push_back(first.at(i));
        }
    }
    
    a = result;
}



#endif
