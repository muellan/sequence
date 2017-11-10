AM sequence
==========

Header-only collection of sequence generators for C++14.


## Quick Overview

### Sequences
 - ```linear_sequence```
 - ```ascending_sequence```
 - ```descending_sequence```
 - ```geometric_sequence```
 - ```fibonacci_sequence```

 - ```replica_sequence``` 
      sequence of n times the same element

 - ```interleaved_bit_sequence``` 
      interleaved 1s/true values with an initial offset
      e.g. {.........1....1....1....1....1....1}


### Sequence Decorators
 - ```repeated<Sequence>``` repeats an underlying sequence several times
 - ```combined<Sequence1,Sequence2>``` concatenates two sequences
 



## Interfaces

A sequence generator acts similar to ```InputIterator``` and ```InputRange```.
Minimum common interface:
```cpp
//current value
value_type Sequence::operator * ();

//forward to next value
Sequence& Sequence::operator ++ ();

//range adaption
auto Sequence::begin();  //at current value
auto Sequence::end();    //one after the last value
```


## Requirements
Requires C++14 conforming compiler.
Tested with g++ 6.1

