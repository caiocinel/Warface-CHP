#pragma once

//#define _SECURE_SCL 0

#ifndef _WIN32_WINNT    

#define _WIN32_WINNT 0x0500     
#endif
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include "stdafx.h"
#include"XorStr.h"
#include < Windows.h >
#include < Iostream >
#include < Assert.h >
#include < Fstream >
#include < Vector >
#include < Stdio.h >
#include <d3dx9.h>
#include < String >
#include <d3d9.h>
#include < Time.h >
#include < List >
#include < Map >
#include <math.h>
#include <process.h>
#include <tlhelp32.h>
#include "Classes.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "Draw.h"
#include "Menu.h"
#include <dinput.h>
#define DIRECTINPUT_VERSION 0x0800


using namespace std;

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")


//#pragma comment( lib, "ddraw.lib" )
//#pragma comment( lib, "dxguid.lib" )

#include < algorithm >
#include "Detour/include/detours.h"
#pragma comment (lib,"Detour\\lib.X86\\detours.lib")

#include <intrin.h>
#pragma intrinsic(_ReturnAddress)

using namespace std;


//SOME USEFULL THINGS, SOME OF IT IS USELESS RIGHT NOW BUT IF YOU NEED TO EXPAND AT LEAST ITS ALREADY HERE :)

#define ILINE __forceinline
typedef float f32;
typedef double f64;
typedef unsigned short  uint16;
typedef unsigned __int64 uint64;
typedef unsigned int     uint32;
typedef unsigned char  uint8;
typedef signed __int64 int64;
typedef signed __int32 int32;
typedef signed __int8 int8;

template<typename T >
T ReadOffset(PVOID pBase, DWORD dwIndex)
{
    return *(T*)((DWORD)pBase + dwIndex);
}
extern long  CryInterlockedIncrement( int volatile *lpAddend );
extern long  CryInterlockedDecrement( int volatile *lpAddend );
template <class _I> class _smart_ptr 
{
private:
  _I* p;
public:
  _smart_ptr() : p(NULL) {}
#if defined(LINUX64)
	_smart_ptr(typeof(__null)) : p(NULL) {}
#endif
	_smart_ptr(int Null) : p(NULL) {}
  _smart_ptr(_I* p_)
	{
		p = p_;
		if (p)
			p->AddRef();
	}
	
  _smart_ptr(const _smart_ptr &p_)
	{
		p = p_.p;
		if (p)
			p->AddRef();
	}
	~_smart_ptr()
	{
		if (p)
			p->Release();
	}
  operator _I*() const { return p; } 
  _I& operator*() const { return *p; }
  _I* operator->() const { return p; }
	_I* operator+() const { return p; }
	_I* get() const { return p; }
  _smart_ptr&  operator=(_I* newp)
	{
		if (newp)
			newp->AddRef();
		if (p)
			p->Release();
		p = newp;
		return *this;
	}

	void reset()
	{
		_smart_ptr<_I>().swap(*this);
	}

	void reset(_I* p)
	{
		_smart_ptr<_I>(p).swap(*this);
	}

	_smart_ptr&  operator=(const _smart_ptr &newp)
	{
		if (newp.p)
			newp.p->AddRef();
		if (p)
			p->Release();
		p = newp.p;
		return *this;
	}
	bool operator !() const 
	{
		return p == NULL;
	};

	// set our contained pointer to null, but don't call Release()
	// useful for when we want to do that ourselves, or when we know that
	// the contained pointer is invalid
	friend _I* ReleaseOwnership( _smart_ptr<_I>& ptr )
	{
		_I * ret = ptr.p;
		ptr.p = 0;
		return ret;
	}
	void swap(_smart_ptr<_I>& other)
	{
		std::swap(p, other.p);
	}

};

template <typename T>
__forceinline void swap(_smart_ptr<T>& a, _smart_ptr<T>& b)
{
	a.swap(b);
}


// reference target for smart pointer
// implements AddRef() and Release() strategy using reference counter of the specified type
template <typename Counter> class _reference_target
{
public:
	_reference_target():
		m_nRefCounter (0)
	{
	}

	virtual ~_reference_target()
	{
		//assert (!m_nRefCounter);
	}
	
	void AddRef()
	{
		++m_nRefCounter;
	}

	void Release()
	{
		if (--m_nRefCounter == 0)
		{
			delete this;
		}
		else if (m_nRefCounter < 0)
		{
			assert(0);
		}
	}
	// Warning: use for debugging/statistics purposes only!
	Counter NumRefs()
	{
		return m_nRefCounter;
	}
protected:
	Counter m_nRefCounter;
};

// default implementation is int counter - for better alignment
typedef _reference_target<int> _reference_target_t;


// reference target for smart pointer with configurable destruct function 
// implements AddRef() and Release() strategy using reference counter of the specified type
template <typename T, typename Counter = int> class _cfg_reference_target
{
public:

  typedef void (*DeleteFncPtr)(void*);

	_cfg_reference_target():
		m_nRefCounter (0), 
    m_pDeleteFnc(operator delete)
	{
	}

	explicit _cfg_reference_target(DeleteFncPtr pDeleteFnc):
		m_nRefCounter (0), 
    m_pDeleteFnc(pDeleteFnc)
	{
	}

	virtual ~_cfg_reference_target()
	{
	}
	
	void AddRef()
	{
		++m_nRefCounter;
	}

	void Release()
	{
		if (--m_nRefCounter == 0)
		{
      assert(m_pDeleteFnc);
      static_cast<T*>(this)->~T();
      m_pDeleteFnc(this);
		}
		else if (m_nRefCounter < 0)
		{
			assert(0);
		}
	}

  // Sets the delete function with which this object is supposed to be deleted 
  void SetDeleteFnc(DeleteFncPtr pDeleteFnc) { m_pDeleteFnc = pDeleteFnc; }

	// Warning: use for debugging/statistics purposes only!
	Counter NumRefs()
	{
		return m_nRefCounter;
	}
protected:
	Counter m_nRefCounter;
  DeleteFncPtr m_pDeleteFnc; 
};


// base class for interfaces implementing reference counting
// derive your interface from this class and the descendants won't have to implement
// the reference counting logic
template <typename Counter> class _i_reference_target
{
public:
	_i_reference_target():
		m_nRefCounter (0)
	{
	}

	virtual ~_i_reference_target()
	{
	}

	virtual void AddRef()
	{
		++m_nRefCounter;
	}

	virtual void Release()
	{
		if (--m_nRefCounter == 0)
		{
			delete this;
		}
		else if (m_nRefCounter < 0)
		{
			assert(0);
		}
	}

	// Warning: use for debugging/statistics purposes only!
	Counter NumRefs()	const
	{
		return m_nRefCounter;
	}
protected:
	Counter m_nRefCounter;
};

class CMultiThreadRefCount
{
public:
	CMultiThreadRefCount() : m_cnt(0) {}
	virtual ~CMultiThreadRefCount() {}

	inline int AddRef()
	{
		return CryInterlockedIncrement(&m_cnt);
	}
	inline int Release()
	{
		const int nCount = CryInterlockedDecrement(&m_cnt);
		assert(nCount >= 0);
		if (nCount == 0)
		{
			delete this;
		}
		else if (nCount < 0)
		{
			assert(0);
		}
		return nCount;
	}

	inline int GetRefCount()	const { return m_cnt; }

private:
	volatile int m_cnt;
};

typedef _i_reference_target<int> _i_reference_target_t;

typedef unsigned int                uint;
typedef signed char                    int8;
typedef signed short                int16;
typedef signed int                    int32;
typedef signed __int64                int64;
typedef unsigned char                uint8;
typedef unsigned char                BYTE;
typedef unsigned short                uint16;
typedef unsigned int                uint32;
typedef unsigned __int64            uint64;
typedef float                        f32;
typedef double                        f64;
typedef double                        real;

enum type_zero { ZERO };
enum type_min { VMIN };
enum type_max { VMAX };
enum type_identity { IDENTITY };

#define FloatU32(x)						(alias_cast<uint32, float>(x))
#define FloatU32ExpMask				(0xFF << 23)
#define FloatU32FracMask			((1 << 23) - 1)
#define FloatU32SignMask			(1 << 31)
#define F32NAN								(0x7F800001)					// Produces rock solid fp-exceptions.
#define F32NAN_SAFE						(FloatU32ExpMask | FloatU32FracMask) // This one is not triggering an fp-exception.

#define DoubleU64(x)					(*( (uint64*) &(x) ))
#define DoubleU64ExpMask			((uint64)255 << 55)
#define DoubleU64FracMask			(((uint64)1 << 55) - (uint64)1)
#define DoubleU64SignMask			((uint64)1 << 63)
#if defined(__GNUC__)
	#define F64NAN								(0x7FF0000000000001ULL)	// Produces rock solid fp-exceptions.
#else
	#define F64NAN								(0x7FF0000000000001)	// Produces rock solid fp-exceptions.
#endif
#define F64NAN_SAFE						(DoubleU64ExpMask | DoubleU64FracMask)  // This one is not triggering an fp-exception.
template<typename DestinationType, typename SourceType>
ILINE DestinationType alias_cast( SourceType pPtr )
{
	//STATIC_CHECK(sizeof(DestinationType) == sizeof(SourceType), ALIAS_CAST_BOTH_TYPES_NEED_TO_BE_OF_THE_SAME_SIZE );
#if defined(__SPU__)
	return reinterpret_cast<DestinationType>(pPtr);
#else
	union { 
		SourceType pSrc;
		DestinationType pDst;
	} conv_union;
	conv_union.pSrc = pPtr;
	return conv_union.pDst;
#endif
}