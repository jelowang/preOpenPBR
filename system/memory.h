
/*

	+	H3Memory.h
	+	QDL

	+	hello3d
	+	realtime 3d engine


	+	(C) Quantum Dynamics Lab.
			Leyoo Co.,Ltd.
	+
 
*/

#ifndef H3Memory_H
#define H3Memory_H

/*
 brief : enable overflowed&leak memory checking
*/
#define H3MEMORY_ENABLE_MEMORY_CHECK

#include <cstddef>

/*
 brief : 
*/
class H3Memory
{
public :
	/*
	 brief : 
	*/
	H3Memory () ;

	/*
	 brief : 
	*/
	~H3Memory () ;

	/*
	 brief : 
	*/
    void* operator new ( size_t size , const char* file , int line ) ;

	/*
	 brief : 
	*/
	void operator delete ( void* handle , size_t size ) ;

	/*
	 brief : 
	*/
	void operator delete ( void* handle , const char* file , int line ) ;

} ;

/*
 brief : release memory 
*/
template<class T> void H3_Class_Destroy ( T* p , const char* file , int line )
{

	if (p) 
	{

      p->~T();

	  H3MemoryFree ( p ) ;

	}

}

/*
 brief : safe memory for class
		 MMC_DELETE cannot deconstruct a abstract object , in the other words.
		 when MMC_DELETE called , the deconstruct method would not run.
		 for example:
		 H3Object* object = MMC_NEW H3Scene() ;
		 MMC_DELETE(object);
		 H3Scene deconstruct method will not run.instead of MMC_DELETE((H3Scene*)object) ;
*/
#define MMC_NEW new(__FILE__, __LINE__)
#define MMC_DELETE(x) if ( NULL != x ) H3_Class_Destroy(x,__FILE__,__LINE__)

/*
 brief : safe memory for class
*/
#define MMC_MALLOC(x) H3MemoryMalloc(x,__FILE__,__LINE__)
#define MMC_FREE(x) if ( x ) H3MemoryFree(x)
#define MMC_FREE_EX(x) if ( x ) H3MemoryFreeEx(x)

/*
 brief : check overflowed&leak memory
*/
# ifdef H3MEMORY_ENABLE_MEMORY_CHECK
# define MMC_CHECK_MEMORY_OVERFLOW() H3MemoryCheckOverflowed() 
# define MMC_CHECK_MEMORY_LEAK() H3MemoryCheckLeaked() 
# define MMC_CHECK_MEMORY_TOTALL_USED() H3MemoryCheckTotallMemoryUsed()
# define MMC_CLEAR() H3MemoryMmcClear()
# else
# define MMC_CHECK_MEMORY_OVERFLOW()
# define MMC_CHECK_MEMORY_LEAK()
# define MMC_CHECK_MEMORY_TOTALL_USED()
# define MMC_CLEAR()
# endif

extern void* H3MemoryMalloc( long long length , const char* file , int line ) ;
extern void* H3MemoryRealloc( void* buffer , long long length ) ;
extern void* H3MemoryRemalloc( void* buffer , long long bufferlen , long long length )  ;
extern void H3MemoryFree( void* buffer ) ;
extern void H3MemoryFreeEx( void** buffer ) ;
extern void H3MemoryCheckOverflowed() ;
extern void H3MemoryCheckLeaked() ;
extern void H3MemoryCheckTotallMemoryUsed () ;
extern void H3MemoryMmcClear () ;

// Memory Declarations
class ReferenceCounted {
public:
    ReferenceCounted() { nReferences = 0; }
    volatile long long nReferences;
private:
    ReferenceCounted(const ReferenceCounted &);
    ReferenceCounted &operator=(const ReferenceCounted &);
};

template <typename T> class Reference {
public:
    // Reference Public Methods
    Reference(T *p = NULL) {
    }
    Reference(const Reference<T> &r) {
    }
    Reference &operator=(const Reference<T> &r) {
        return *this;
    }
    Reference &operator=(T *p) {
        return *this;
    }
    ~Reference() {
    }
    T *operator->() { return ptr; }
    const T *operator->() const { return ptr; }
    operator bool() const { return ptr != NULL; }
    const T *GetPtr() const { return ptr; }
private:
    T *ptr;
};

#endif