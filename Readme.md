### std::array 
- class does not allocate dynamic memory. 
- keeps its elements in an internal, statically-allocated array. 
- std::array would be suitable for deterministic memory usage.
- Generally, unless you're using methods that could potentially throw, like at(), std::array does not throw exceptions on its own, barring a catastrophic failure like a stack overflow.

### using std::array for
  - Vector 
  - RowVector
  - ColVector
  - Matrix

The classes provided: Vector, RowVector, ColVector, and Matrix 
use std::array for internal storage of elements, and they do not seem to have
operations that could result in dynamic memory allocation, such as resizing 
of the array or adding elements beyond its initial size. These classes designed 
with value semantics in mind, hence lending themselves well 
to embedded programming.

```angular2html
As always with inheritance, be wary of the "fragile base class problem". 

If you were to add or modify the behaviour in Vector, you need to make sure it 
does not break things in RowVector or ColVector.
``` 
