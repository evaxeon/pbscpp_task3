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

template <class T, class M>
class MyAlloc {
 public:
   typedef T value_type;
   MyAlloc() noexcept {}
   template <class U> MyAlloc (const MyAlloc<U, U>&) noexcept {}

   T* allocate (size_t num, const void* = 0) {
   		//template with two parameters + static cast trick
       return static_cast<T*>(M::operator new(num*sizeof(T)));
   }

   void deallocate (T* p, size_t num) {
       M::operator delete(p, num);
   }
};

int main() {
	auto sp = std::allocate_shared<A> (MyAlloc<A, A>());
}
