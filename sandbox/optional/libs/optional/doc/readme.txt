================================================================================

-----------------
improved optional
-----------------

a) the lifetime management bool was changed into a properly typed pointer (this
   actually takes the same amount of space while it provides a no-op get_ptr()
   member function as well as easier debugging as the contents of optional can
   now clearly be seen through the pointer, as opposed to gibberish in an opaque
   storage array)
b) added another conditional constructor that accepts an in-place factory
c) uses the safe bool idiom implementation from Boost.Range (which generates
   better code on pre MSVC10 compilers)
d) skips redundant/dead stores of marking itself as uninitialised [including but
   limited to, in its destructor (if it has one)]
e) streamlined internal assign paths to help the compiler avoid unnecessary
   branching
f) added direct_create() and direct_destroy() member functions that allow the
   user to bypass the internal lifetime management (they only assert correct
   usage) in situations where the user's own external logic already implicitly
   knows the state of the optional
g) optional now declares and defines a destructor only if the contained type has
   a non-trivial destructor (this prevents the compiler from detecting false EH
   states and thus generating bogus EH code)
h) extracted the "placeholder" functionality into a standalone class (basically
   what would be left of optional<> if the lifetime management "bool" member and
   logic was removed) so that it can be reused (e.g. for singleton like classes,
   or when more complex custom lifetime management is required)
i) added compiler specific "aids" to workaround situations when the compiler is
   unable to detect that placement new will never return a nullptr (and then
   generates bogus branching)   
j) the lifetime management pointer is now stored after the actual contained
   object (this helps in avoiding more complex/offset addressing when accessing
   optionals through pointers w/o checking whether they are initialised)
k) removed support for antediluvian compilers (MSVC6, BCB5)

todo:

l) lifetime management policy: bool, pointer, reference count...

m) zero size overhead for optional references (requires (l))

n) avoid branching in assignment and copy construction of optionals that hold
   PODs smaller than N * sizeof( void * ) where N is some small number

   
 - temporarily renamed to optional2 to avoid collision with the original
   optional
 - passes all optional unit tests (after being renamed back to optional) with
   MSVC10 SP1 and Apple Clang 3.0 (from Xcode 4.2.1)


  Copyright © 2012. Domagoj Saric (dsarit@gmail.com). All rights reserved.

================================================================================
