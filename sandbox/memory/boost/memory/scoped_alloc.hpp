//
//  boost/memory/scoped_alloc.hpp
//
//  Copyright (c) 2004 - 2008 xushiwei (xushiweizh@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/memory/index.htm for documentation.
//
#ifndef BOOST_MEMORY_SCOPED_ALLOC_HPP
#define BOOST_MEMORY_SCOPED_ALLOC_HPP

#ifndef BOOST_MEMORY_BASIC_HPP
#include "basic.hpp"
#endif

#ifndef BOOST_MEMORY_AUTO_ALLOC_HPP
#include "auto_alloc.hpp"
#endif

#ifndef BOOST_MEMORY_THREAD_TLS_HPP
#include "thread/tls.hpp"
#endif

#if !defined(_CLIMITS_) && !defined(_CLIMITS)
#include <climits> // INT_MAX
#endif

NS_BOOST_MEMORY_BEGIN

// -------------------------------------------------------------------------
// class proxy_alloc

template <class AllocT, class TlsAllocT>
class proxy_alloc
{
private:
	AllocT* m_alloc;

public:
	proxy_alloc(AllocT& alloc) : m_alloc(&alloc) {}
	proxy_alloc() : m_alloc(&TlsAllocT::instance()) {}

public:
	enum { Padding = AllocT::Padding };

public:
	void* BOOST_MEMORY_CALL allocate(size_t cb)	{ return m_alloc->allocate(cb); }
	void BOOST_MEMORY_CALL deallocate(void* p) { m_alloc->deallocate(p); }
	void BOOST_MEMORY_CALL swap(proxy_alloc& o)	{ std::swap(m_alloc, o.m_alloc); }
	size_t BOOST_MEMORY_CALL alloc_size(void* p) const { return m_alloc->alloc_size(p); }
};

// -------------------------------------------------------------------------
// class block_pool

template <class PolicyT>
class block_pool_
{
private:
	typedef typename PolicyT::alloc_type AllocT;
	enum { m_cbBlock = PolicyT::MemBlockBytes - AllocT::Padding };

#pragma pack(1)
	struct Block {
		Block* next;
	};
#pragma pack()

	Block* m_freeList;

	int m_nFree;
	const int m_nFreeLimit;

private:
	block_pool_(const block_pool_&);
	void operator=(const block_pool_&);

public:
	block_pool_(int cbFreeLimit = INT_MAX)
		: m_freeList(NULL), m_nFree(0),
		  m_nFreeLimit(cbFreeLimit / m_cbBlock + 1)
	{
	}
	~block_pool_()
	{
		clear();
	}

public:
	enum { Padding = AllocT::Padding };

public:
	void* BOOST_MEMORY_CALL allocate(size_t cb)
	{
		BOOST_MEMORY_ASSERT(cb >= (size_t)m_cbBlock);

		if (cb > (size_t)m_cbBlock)
			return AllocT::allocate(cb);
		else
		{
			if (m_freeList)
			{
				BOOST_MEMORY_ASSERT(AllocT::alloc_size(m_freeList) >= cb);
				Block* blk = m_freeList;
				m_freeList = blk->next;
				--m_nFree;
				return blk;
			}
			return AllocT::allocate(m_cbBlock);
		}
	}

	void BOOST_MEMORY_CALL deallocate(void* p)
	{
		if (m_nFree >= m_nFreeLimit) {
			AllocT::deallocate(p);
		}
		else {
			Block* blk = (Block*)p;
			blk->next = m_freeList;
			m_freeList = blk;
			++m_nFree;
		}
	}

	static size_t BOOST_MEMORY_CALL alloc_size(void* p)
	{
		return AllocT::alloc_size(p);
	}

	void BOOST_MEMORY_CALL clear()
	{
		while (m_freeList)
		{
			Block* blk = m_freeList;
			m_freeList = blk->next;
			AllocT::deallocate(blk);
		}
		m_nFree = 0;
	}
};

typedef block_pool_<NS_BOOST_MEMORY_POLICY::sys> block_pool;

// -------------------------------------------------------------------------
// class tls_block_pool

typedef tls_object<block_pool> tls_block_pool_t;

STDAPI_(tls_block_pool_t*) _boost_TlsBlockPool();

template <class Unused>
class tls_block_pool_
{
private:
	static tls_block_pool_t* _tls_blockPool;
	
public:
	tls_block_pool_() {
		_tls_blockPool->init();
	}
	~tls_block_pool_() {
		_tls_blockPool->term();
	}

	static block_pool& BOOST_MEMORY_CALL instance() {
		return _tls_blockPool->get();
	}
};

template <class Unused>
tls_block_pool_t* tls_block_pool_<Unused>::_tls_blockPool = _boost_TlsBlockPool();

typedef tls_block_pool_<int> tls_block_pool;

// -------------------------------------------------------------------------
// class pool

typedef proxy_alloc<block_pool, tls_block_pool> proxy_block_pool;

NS_BOOST_MEMORY_POLICY_BEGIN

class pool : public sys
{
public:
	typedef proxy_block_pool alloc_type;
};

NS_BOOST_MEMORY_POLICY_END

// -------------------------------------------------------------------------
// class scoped_alloc

#if 0 // defined(_MSC_VER) && (_MSC_VER <= 1200) // VC++ 6.0

class scoped_alloc
{
private:
	region_alloc<NS_BOOST_MEMORY_POLICY::pool> m_impl;
	
public:
	scoped_alloc() {}
	explicit scoped_alloc(scoped_alloc&) {}
	
	__forceinline void BOOST_MEMORY_CALL swap(scoped_alloc& o) {
		m_impl.swap(o.m_impl);
	}
	
	__forceinline void BOOST_MEMORY_CALL clear() {
		m_impl.clear();
	}
	
	__forceinline void* BOOST_MEMORY_CALL allocate(size_t cb) {
		return m_impl.allocate(cb);
	}
	
#if defined(BOOST_MEMORY_NO_STRICT_EXCEPTION_SEMANTICS)
	__forceinline void* BOOST_MEMORY_CALL allocate(size_t cb, int fnZero) {
		return m_impl.allocate(cb);
	}
	
	__forceinline void* BOOST_MEMORY_CALL allocate(size_t cb, destructor_t fn) {
		return m_impl.allocate(cb, fn);
	}
#endif
	
	__forceinline void* BOOST_MEMORY_CALL unmanaged_alloc(size_t cb, destructor_t fn) {
		return m_impl.unmanaged_alloc(cb, fn);
	}
	
	__forceinline void BOOST_MEMORY_CALL manage(void* p, destructor_t fn) {
		m_impl.manage(p, fn);
	}
	
	__forceinline void* BOOST_MEMORY_CALL unmanaged_alloc(size_t cb, int fnZero) {
		return m_impl.allocate(cb);
	}
	
	__forceinline void BOOST_MEMORY_CALL manage(void* p, int fnZero) {
		// no action
	}
	
	void* BOOST_MEMORY_CALL reallocate(void* p, size_t oldSize, size_t newSize) {
		return m_impl.reallocate(p, oldSize, newSize);
	}
	
	void BOOST_MEMORY_CALL deallocate(void* p, size_t cb) {
		// no action
	}
	
	template <class Type>
		void BOOST_MEMORY_CALL destroy(Type* obj) {
		// no action
	}
	
	template <class Type>
		void BOOST_MEMORY_CALL destroyArray(Type* array, size_t count) {
		// no action
	}
};

#else

typedef region_alloc<NS_BOOST_MEMORY_POLICY::pool> scoped_alloc;

#endif

// -------------------------------------------------------------------------
// $Log: $

NS_BOOST_MEMORY_END

#endif /* BOOST_MEMORY_SCOPED_ALLOC_HPP */
