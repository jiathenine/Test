#ifndef TEST_CACHEDOBJ_H_
#define TEST_CACHEDOBJ_H_
#include<memory>
#include<string>

template<class T>class CachedObj{
public:
	struct iterator{
		//function
		iterator(T *type):t(type){  }
		
		iterator operator+(std::size_t sz)const
		{
			iterator it = *this;
			for(std::size_t i = 0;i != sz;++i)
				it.t = it->CachedObj<T>::next;
			return it
		}
		iterator operator+=(std::size_t sz)
		{
			for(std::size_t i = 0;i != sz;++i)
				t = t->CachedObj<T>::next;
			return *this;
		}
		T& operator*()
		{
			return *t;
		}
		T* operator->()
		{
			return t;
		}
		//member
		T *t;
		
	};
	struct const_iterator{
		//function
		const_iterator(T const* type):t(type){  }
		
		const_iterator operator+(std::size_t sz)
		{
			const_iterator it = *this;
			for(std::size_t i = 0;i != sz;++i)
				it.t = it->CachedObj<T>::next;
			return it;
		}
		const_iterator operator+=(std::size_t sz)
		{
			T const* type = this->t;
			for(std::size_t i = 0;i != sz;++i)
				t = t->CachedObj<T>::next;
			
			return *this;
		}
		T const& operator*()const
		{
			return *t;
		}
		T const* operator->()const
		{
			return t;
		}
		//member
		T const* t;
		
	};

	void* operator new(std::size_t sz)
	{
		
		//new should only asked to build a T,not an object
		//derived from T;check that right size is requested
		if(sz != sizeof(T))
			throw std::runtime_error
			( "CacheObj:wrong size object in operator new" );
		 if(  (! freeStore) || (! freeStore->CachedObj<T>::next) ){
			//the list is empty:grab a new chunk of memory
			//allocate allocates chunk number of object of type T
			T *array = alloc_mem.allocate(chunk);
			//test
			T *frontFreeStore = freeStore;
			freeStore = NULL;
			//now set the next pointers in each object in the allocated memory
			for(std::size_t i = 0;i != chunk ; ++i){
				add_to_freelist(&array[i]);
			}
			if(begin){//if this class is init
				//link the last member of the front memory and first member of the next memory
				frontFreeStore->CachedObj<T>::next = &array[chunk -1];
				freeStore = frontFreeStore;
			}
		}
		T *p = freeStore;
		freeStore = freeStore->CachedObj<T>::next;
		if(! begin)//set a start point
			begin = p;
		++size;//compute type num
		return p;//constructor of T will construct the T part of the object
	}
	void operator delete(void *p,std::size_t sz)
	{
		if( p )//p != 0
			//put the "delete" object back at head of freelist
			add_to_freelist(static_cast<T*>(p));
	}
	T const* getNext()const{ return next;}
	//get function
	T* getNext(){ return next;}
	static T const* getBegin() {return begin;}
	static std::size_t getSize(){ return size;}
	static T const* getFreeStore(){return freeStore;}
	//unconstractor
	virtual ~CachedObj() {  }
protected:
	T *next;
private:
	static void add_to_freelist(T* p)
	{
		p->CachedObj<T>::next = freeStore;
		freeStore = p;
		
	}
	
	static std::allocator<T> alloc_mem;
	static std::size_t const chunk;
	static T *begin;
	static T *freeStore;
	static std::size_t size;
public:
	
};
template<class T> std::allocator<T> CachedObj<T>::alloc_mem ;
template<class T> T *CachedObj<T>::freeStore = 0;
template<class T> std::size_t const CachedObj<T>::chunk = 24;

template<class T> T *CachedObj<T>::begin = 0;
template<class T> std::size_t CachedObj<T>::size = 0;
#endif