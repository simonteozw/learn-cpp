## Access controls
- public: anyone can access
- private: only class can access its private attributes
- using class instead of struct declares members as private by default
- aside from default access control, classes declared with the struct and class keywords are the same

## Pointers
- deference pointer (*) is a unary operator that accesses the object to which a pointer refers
- member-of-pointer performs 2 simultaneous operations: dereferences a pointer, accesses a member of a pointed-to object
- void pointers are used when pointed-to type is irrelevant
- cannot dereference a void pointer, because the pointed-to type has been erased, dereferencing makes no sense
- use std::byte pointer for interacting with raw memory at byte level
- any value that is not nullptr converts implicitly to true, whereas nullptr converts implicitly to false

## Object Life Cycle
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

## Exceptions
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

## Variadic Functions
- declare variadic functions by placing `...` as the final parameter in the function’s argument list
- when a variadic function is invoked, the compiler matches arguments against declared arguments
- any leftovers pack into the variadic arguments represented by the `...` argument

## Function Pointers
- `using alias-name = return-type(*)(arg-type1, arg-type2, ...)`
- `using operation_func = float(*)(float, int);`

## Lambda Expressions
- `[captures] (parameters) modifiers -> return-type { body }`
- captures: member variables of the function object (that is, the partially applied parameters)
- parameters: arguments required to invoke the function object
- body: function object's code
- specifiers: elements like `constexpr, mutable, noexcept`, and `[[noreturn]]`
- return type: type returned by the function object

## Testing
- unit test: focused, cohesive collection of code—a unit, such as a function or a class—behaves exactly as the programmer intended
- integration test: testing a collection of units together
- acceptance test: ensure that your software meets all of your customers’ requirements
- performance test: evaluate whether software meets effectiveness requirements, such as speed of execution or memory/power consumption

## Scoped Pointers
- expresses non-transferable, exclusive ownership over a single dynamic object
- non-transferable means that the scoped pointers cannot be moved from one scope to another
- exclusive ownership means that they can’t be copied, so no other smart pointers can have ownership of a scoped pointer’s dynamic object
- `boost::scoped_ptr<PointedToType> my_ptr{ new PointedToType };`

## Unique Pointers
- transferable, exclusive ownership over a single dynamic object
- can move unique pointers, which makes them transferable
- exclusive ownership, cannot be copied

## Shared Pointers
- transferable, non-exclusive ownership over a single dynamic object
- can move shared pointers, which makes them transfer- able
- can copy them, which makes their ownership non-exclusive

## Weak Pointers
- special kind of smart pointer that has no ownership over the object to which it refers
- allow you to track an object and to convert the weak pointer into a shared pointer only if the tracked object still exists
- generate temporary ownership over an object
- movable and copyable

## File Systems
- inode: database that describes the file/directory attributes such as metadata and the physical location on the hard drive

![aefg](/assets/images/file-link.png)

- inode: essentially the numerical equivalent of a full address
- hard link: directory entry that assigns a name to an existing file
- symbolic link: assigns a name to a path (which might or might not exist)

## Concurrency and Parallelism
- concurrency: 2 or more tasks running in a given time period
- parallelism: 2 or more tasks running at the same instant