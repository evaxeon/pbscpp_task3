#include <iostream>
#include <memory>

class A {
public:
	// ...
	static void * operator new(size_t size) {
		std::cout << "operator new!" << std::endl;
		return ::operator new(size);
	}

	static void operator delete(void *p, size_t size) {
		std::cout << "operator delete!" << std::endl;
		return ::operator delete(p);
	}
};

template <class T>
class MyAlloc {
 public:
   typedef T        value_type;
   typedef T*       pointer;
   typedef const T* const_pointer;
   typedef T&       reference;
   typedef const T& const_reference;
   typedef std::size_t    size_type;
   typedef std::ptrdiff_t difference_type;

   template <class U>
   struct rebind {
       typedef MyAlloc<U> other;
   };

   pointer address (reference value) const {
       return &value;
   }
   const_pointer address (const_reference value) const {
       return &value;
   }

   MyAlloc() throw() {
   }
   MyAlloc(const MyAlloc&) throw() {
   }
   template <class U>
     MyAlloc (const MyAlloc<U>&) throw() {
   }
   ~MyAlloc() throw() {
   }

   pointer allocate (size_type num, const void* = 0) {
       pointer ret = (pointer) A::operator new(num);
       return ret;
   }

   void deallocate (pointer p, size_type num) {
       ::operator delete((void*)p);
   }
};

int main() {
	auto sp = std::allocate_shared<A> (MyAlloc<A>());
}
