#ifndef VECTOR_VECTOR_H_
#define	VECTOR_VECTOR_H_

#include<memory>

template<typename T>
T max(T val1,T val2){
	return val1 > val2?val1:val2;
}

template<class T>class Vector/*different the standart vector*/{
public:
	//this class typename
	typedef T* iterator;
	typedef T const* const_iterator;
	/**/
	Vector():elements(0) , first_free(0),end(0) {  }
	void push_back(const T& t)
	{
		//are we out of the space?
		if(first_free == end)
			reallocate();
		alloc.construct(first_free,t);
		//construct low choose
		//new(first_free)T(t);
		++first_free;
	}
	void resize(std::size_t n)
	{
		if(elements + n > first_free){
			//new size over the capacity
			if(elements + n >= end){
				//add new capacity and recall this function
				for(T *t = first_free ; t != end; ++t)
					*t = 0;
				first_free = end;
				reallocate();
				resize(n);
				return;
			}
			else{
				for(T *p = first_free;p != elements + n;++p)
					*p = 0;
				first_free = elements + n;
			}
		}else{
			for(T *p = first_free ; p != elements + n ;/*empty*/)
				alloc.destroy( --p);
			first_free = elements + n;
		}
	}
	void resize(std::size_t n,T t)
	{
		if(elements + n > first_free){
			//new size over the capacity
			if(elements + n >= end){
				//add new capacity and recall this function
				for(T *p = first_free ; p != end; ++p)
					*p = t;
				first_free = end;
				reallocate();
				resize(n,t);
				return;
			}
			else{
				for(T *p = first_free;p != elements + n;++p)
					*p = t;
				first_free = elements + n;
			}
		}else{
			for(T *p = first_free ; p != elements + n ;/*empty*/)
				alloc.destroy( --p);
			first_free = elements + n;
		}
	}
	void reserve(std::size_t n)
	{
		if(elements + n <= end)
			return;
		//compute size of current array and allocate space for twice as many element
		std::ptrdiff_t size = first_free - elements;
		std::ptrdiff_t newcapacity = n;
		//allocate space to hold newcapacity number of elements of type T
		T *newelements = alloc.allocate(newcapacity);

		//construct copies of the existing elements in the new space
		std::uninitialized_copy(elements,first_free,newelements);
		//destory the old elements in reverse order
		for(T *p = first_free; p != elements; /* empty */)
			alloc.destroy(--p);
		//deallocate cannot be called on a 0 pointer
		if(elements)
			//return the memory that held the elements
			alloc.deallocate(elements,end - elements);
		//make our data structure that held the elements
		elements = newelements;
		first_free = newelements + size;
		end = newelements + newcapacity;
	}
	T& operator[](std::size_t n)
	{
		return *(elements + n);
	}
	const T& operator[](std::size_t n)const
	{
		return *(elements + n);
	}
	inline std::size_t size()
	{
		return first_free - elements;
	}
	inline std::size_t capacity()
	{
		return end - elements;
	}
private:
	static std::allocator<T> alloc; //object to get raw memory
	void reallocate()	// get more space and copy existing(mean:now have) elements
	{
		//compute size of current array and allocate space for twice as many element
		std::ptrdiff_t size = first_free - elements;
		std::ptrdiff_t newcapacity = 2 * max(size,1);
		//allocate space to hold newcapacity number of elements of type T
		T *newelements = alloc.allocate(newcapacity);
		//allow other way of writing
		/*T* newelements = static_cast<T*>
								(operator new[](newcapacity *sizeof(T)));*/

		//construct copies of the existing elements in the new space
		std::uninitialized_copy(elements,first_free,newelements);
		//destory the old elements in reverse order
		for(T *p = first_free; p != elements; /* empty */)
			alloc.destroy(--p);
		//deallocate cannot be called on a 0 pointer
		if(elements)
			//return the memory that held the elements
			alloc.deallocate(elements,end - elements);
			//other way of writing
			/*operator delete[](elements);*/
		//make our data structure that held the elements
		elements = newelements;
		first_free = newelements + size;
		end = newelements + newcapacity;
		
	}
	
	T *elements;		// pointer to first element in the array(mean:number list)
	T *first_free;		//pointer to first free element int the array
	T *end;				//pointer to one past the end of the array
};
//define static member
template<class T> std::allocator<T> Vector<T>::alloc;

#endif