## Access controls:
- public: anyone can access
- private: only class can access its private attributes
- using class instead of struct declares members as private by default
- aside from default access control, classes declared with the struct and class keywords are the same

## Pointers:
- deference pointer (*) is a unary operator that accesses the object to which a pointer refers
- member-of-pointer performs 2 simultaneous operations: dereferences a pointer, accesses a member of a pointed-to object
- void pointers are used when pointed-to type is irrelevant
- cannot dereference a void pointer, because the pointed-to type has been erased, dereferencing makes no sense
- use std::byte pointer for interacting with raw memory at byte level
- any value that is not nullptr converts implicitly to true, whereas nullptr converts implicitly to false

## Object Life Cycle:
- reserve storage for objects in a process called allocation
- release the object’s storage in a process called deallocation
- storage duration begins when the object is allocated and ends when the object is deallocated
- lifetime of an object is a runtime property that is bound by the object’s storage duration
- object’s lifetime begins once its constructor completes, and it ends just before a destructor is invoked
- summary of life cycle:
    1. The object’s storage duration begins, and storage is allocated
    2. The object’s constructor is called
    3. The object’s lifetime begins
    4. You can use the object in your program
    5. The object’s lifetime ends
    6. The object’s destructor is called
    7. The object’s storage duration ends, and storage is deallocated
- automatic object is allocated at the beginning of an enclosing code block, and it’s deallocated at the end (eg. function parameters)
- static variables are declared with the `static` keyword
- static variable's lifetime is the program lifetime
- dynamic objects (aka allocated objects) are allocated an deallocated on request (using `new` keyword)
- `int* my_int_ptr = new int{ 42 };`
- `delete my_int_ptr`
- lvalue = value that has a name
- rvalue = value that is not an lvalue
- rvalue references are a C++11 extension
- cast an lvalue reference to an rvalue reference using the std::move function from the <utility> header
- move constructors look like copy constructors except they take rvalue refer- ences instead of lvalue references
- std::move calls the move constructor of an object

## Exceptions:
- `noexcept` means that a function cannot possibly throw an exception
- `bool is_odd(int x) noexcept { return 1 == x % 2; }`
- as a general rule, treat destructors as if they were noexcept

## Runtime polymorphism
- private members are not inherited by derived class
- use the `virtual` keyword to permit a derived class to override a base class’s methods
- achieve interface inheritance through deriving from base classes that contain only pure­virtual methods

## Templates
- declare tem- plate parameters using either the typename or class keywords followed by an identifier
- template<typename T> declares that the template takes a template parameter T
- c++ suppoorts template type detection

## Type Aliasing
- `using type-alias = type-id;`

## Const Expressions
- aka `constexpr`
- evaluated at compile time
- code blocks that correspond to true conditions get emitted, and the rest is ignored
