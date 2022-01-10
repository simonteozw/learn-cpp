Access controls:
- public: anyone can access
- private: only class can access its private attributes
- using class instead of struct declares members as private by default
- aside from default access control, classes declared with the struct and class keywords are the same

Pointers:
- deference pointer (*) is a unary operator that accesses the object to which a pointer refers
- member-of-pointer performs 2 simultaneous operations: dereferences a pointer, accesses a member of a pointed-to object
- void pointers are used when pointed-to type is irrelevant
- cannot dereference a void pointer, because the pointed-to type has been erased, dereferencing makes no sense
- use std::byte pointer for interacting with raw memory at byte level
- any value that is not nullptr converts implicitly to true, whereas nullptr converts implicitly to false