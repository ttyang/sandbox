//
//  boost/memory/gc_alloc.hpp
//
//  Copyright (c) 2004 - 2008 xushiwei (xushiweizh@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/memory/index.htm for documentation.
//
#ifndef BOOST_MEMORY_GC_ALLOC_HPP
#define BOOST_MEMORY_GC_ALLOC_HPP

#pragma warning(disable:4786)

#ifndef BOOST_MEMORY_SCOPED_ALLOC_HPP
#include "scoped_alloc.hpp"
#endif

#ifndef BOOST_MEMORY_STL_QUEUE_HPP
#include "stl/queue.hpp" // NS_BOOST_MEMORY::priority_queue
#endif

#if !defined(_DEQUE_) && !defined(_DEQUE)
#include <deque> // std::deque
#endif

NS_BOOST_MEMORY_BEGIN

// -------------------------------------------------------------------------
// class gen_alloc

#ifndef MAX
#define MAX(a, b)		((a) < (b) ? (b) : (a))
#endif

#ifndef MIN
#define MIN(a, b)		((a) < (b) ? (a) : (b))
#endif

template <class PolicyT>
class gen_alloc
{
private:
	typedef typename PolicyT::allocator_type AllocT;
	typedef typename PolicyT::huge_gc_allocator HugeGCAllocT;
	typedef size_t HeaderSizeT;

public:
	enum { MemBlockSize = PolicyT::MemBlockSize };
	enum { IsGCAllocator = TRUE };

	typedef AllocT allocator_type;
	typedef HugeGCAllocT huge_gc_allocator;

#pragma pack(1)
private:
	enum MemNodeType {
		nodeFree = 0,
		nodeAlloced = 1,
		nodeAllocedWithDestructor = 3,
	};
	
	struct MemHeader
	{
		HeaderSizeT cbSize	 : 30;
		HeaderSizeT blkType : 2;
	};

	struct MemHeaderEx;
	struct DestroyInfo
	{
		MemHeaderEx* pPrev;
		destructor_t fnDestroy;
	};

	struct MemHeaderEx // = MemHeader + DestroyInfo
	{
		HeaderSizeT cbSize	 : 30;
		HeaderSizeT blkType : 2;
		
		MemHeaderEx* pPrev;
		destructor_t fnDestroy;

		void BOOST_MEMORY_CALL destruct() {
			if (blkType == nodeAllocedWithDestructor) {
				blkType = nodeFree;
				fnDestroy(this + 1);
			}
		}
	};

	friend struct MemHeaderEx;

	struct FreeMemHeader
	{
		HeaderSizeT cbSize;
		HeaderSizeT BOOST_MEMORY_CALL getBlockType() const {
			return ((MemHeader*)this)->blkType;
		}
		char* BOOST_MEMORY_CALL getData() const {
			return (char*)(this + 1);
		}
	};

	struct MemBlock
	{
		MemBlock* pPrev;
		char buffer[1];
		
		class Enumerator
		{
		private:
			char* m_start;
			char* m_last;

		public:
			Enumerator(AllocT& alloc, MemBlock* block) {
				m_start = block->buffer;
				m_last = (char*)block + alloc.alloc_size(block);
			}
			MemHeader* BOOST_MEMORY_CALL first() const {
				return (MemHeader*)m_start;
			}
			MemHeader* BOOST_MEMORY_CALL current() const {
				return (MemHeader*)m_start;
			}
			MemHeader* BOOST_MEMORY_CALL next() {
				BOOST_MEMORY_ASSERT(!done());
				m_start += sizeof(MemHeader) + ((MemHeader*)m_start)->cbSize;
				return (MemHeader*)m_start;
			}
			bool BOOST_MEMORY_CALL done() const {
				return m_start >= m_last;
			}
		};
	};
#pragma pack()

	struct Pred : std::binary_function<FreeMemHeader*, FreeMemHeader*, bool>
	{
		bool operator()(FreeMemHeader* a, FreeMemHeader* b) const {
			return a->cbSize < b->cbSize;
		}
	};
	typedef std::deque<FreeMemHeader*> Container;
	typedef NS_BOOST_MEMORY::priority_queue<FreeMemHeader*, Container, Pred> PriorityQ;
	
	char* m_begin;
	char* m_end;
	AllocT m_alloc;
	MemHeaderEx* m_destroyChain;
	MemBlock* m_blockList;
	PriorityQ m_freeList;
	HugeGCAllocT m_hugeAlloc;
	size_t m_freeSize, m_GCLimitSize;
	static FreeMemHeader _null;

private:
	enum { HeaderSize = sizeof(void*) };
	enum { BlockSize = MemBlockSize - HeaderSize };
	enum { AllocSizeBigDef_ = MAX(PolicyT::AllocSizeBig, BlockSize/4) };
	enum { AllocSizeHugeDef_ = MAX(PolicyT::AllocSizeHuge, 64*1024) };
	enum { GCLimitSizeDef_ = MAX(PolicyT::GCLimitSizeDef, 64*1024) };
	enum { AllocSizeBig = MIN(AllocSizeBigDef_, BlockSize/2) };
	enum { AllocSizeHuge = MIN(AllocSizeHugeDef_, (1 << 29)) };
	enum { GCLimitSizeDef = MIN(GCLimitSizeDef_, (1 << 29)) };
	enum { RecycleSizeMin = MAX(PolicyT::RecycleSizeMin, 128) };

private:
	const gen_alloc& operator=(const gen_alloc&);
	
	static bool BOOST_MEMORY_CALL _isEqual(size_t cbAlloc, size_t cb)
	{
		return cbAlloc >= cb && cb + 64 > cbAlloc;
	}

	static bool BOOST_MEMORY_CALL _isValid(void* obj, size_t cb, destructor_t fn)
	{
		MemHeaderEx* node = (MemHeaderEx*)obj - 1;
		BOOST_MEMORY_ASSERT(node->fnDestroy == fn);
		BOOST_MEMORY_ASSERT(_isEqual(node->cbSize, cb + sizeof(DestroyInfo)));
		BOOST_MEMORY_ASSERT(node->blkType == nodeAllocedWithDestructor);
		return node->fnDestroy == fn &&
			_isEqual(node->cbSize, cb + sizeof(DestroyInfo)) &&
			node->blkType == nodeAllocedWithDestructor;
	}

	static bool BOOST_MEMORY_CALL _isValid(void* obj, size_t cb, int fnZero)
	{
		MemHeader* node = (MemHeader*)obj - 1;
		BOOST_MEMORY_ASSERT(_isEqual(node->cbSize, cb));
		BOOST_MEMORY_ASSERT(node->blkType == nodeAlloced);
		return _isEqual(node->cbSize, cb) && node->blkType == nodeAlloced;
	}

	template <class Type>
	static bool BOOST_MEMORY_CALL _isValid(Type* obj)
	{
		return _isValid(obj, sizeof(Type), destructor_traits<Type>::destruct);
	}

	template <class Type>
	static bool BOOST_MEMORY_CALL _isValidArray(Type* array, size_t count)
	{
		void* buf = destructor_traits<Type>::getArrayBuffer(array);
		size_t cb = destructor_traits<Type>::getArrayAllocSize(count);
		if (buf == array)
		{
			return _isValid(buf, cb, 0);
		}
		else
		{
			size_t count1 = destructor_traits<Type>::getArraySize(array);
			BOOST_MEMORY_ASSERT(count1 == count);
			bool fValid = _isValid(buf, cb, destructor_traits<Type>::destructArray);
			return count1 == count && fValid;
		}
	}

public:
	void BOOST_MEMORY_CALL force_gc()
	{
		// 0. Prepare

		// 0.1. Commit current block:
		_commitCurrentBlock();
		m_begin = m_end = _null.getData();

		// 0.2. Clear destroy chain
		m_destroyChain = NULL;

		// 0.3. Clear free list
		m_freeList.clear();
		m_freeSize = 0;

		// 1. Collect free nodes
		MemBlock* pHeader = m_blockList;
		while (pHeader)
		{
			typename MemBlock::Enumerator coll(m_alloc, pHeader);
			pHeader = pHeader->pPrev;
			for (;;)
			{
				if (coll.done())
					break;
				MemHeader* it = coll.current();
				if (it->blkType == nodeFree)
				{
					// merge nodes marked with nodeFree
					UINT cbFree = it->cbSize;
					for (;;) {
						MemHeader* it2 = coll.next();
						if (coll.done() || it2->blkType != nodeFree)
							break;
						cbFree += it2->cbSize;
					}
					it->cbSize = cbFree;
					if (cbFree >= RecycleSizeMin)
						m_freeList.push((FreeMemHeader*)it);
					if (coll.done())
						break;
					it = coll.current();
				}
				if (it->blkType == nodeAllocedWithDestructor)
				{
					MemHeaderEx* itEx = (MemHeaderEx*)it;
					itEx->pPrev = m_destroyChain;
					m_destroyChain = itEx;
				}
				// skip nodes marked with nodeAlloced
				coll.next();
			}
		}
	}
	
	void BOOST_MEMORY_CALL try_gc()
	{
		if (m_freeSize >= m_GCLimitSize)
			force_gc();
	}

	size_t BOOST_MEMORY_CALL get_free_size() const
	{
		return m_freeSize;
	}

	void BOOST_MEMORY_CALL set_gclim(size_t gcLimit)
	{
		m_GCLimitSize = gcLimit;
	}

private:
	void BOOST_MEMORY_CALL _commitCurrentBlock()
	{
		FreeMemHeader* old = (FreeMemHeader*)m_begin - 1;
		BOOST_MEMORY_ASSERT(old->getBlockType() == nodeFree);
		old->cbSize = (m_end - m_begin);
	}

	MemHeader* BOOST_MEMORY_CALL _newBlock(size_t cbBlock)
	{
		MemBlock* pBlock = (MemBlock*)m_alloc.allocate(cbBlock);
		pBlock->pPrev = m_blockList;
		m_blockList = pBlock;

		MemHeader* pNew = (MemHeader*)pBlock->buffer;
		pNew->blkType = nodeFree;
		pNew->cbSize = m_alloc.alloc_size(pBlock) - (sizeof(MemHeader) + HeaderSize);
		return pNew;
	}

	void BOOST_MEMORY_CALL _init()
	{
		m_blockList = NULL;
		m_destroyChain = NULL;
		m_freeSize = 0;
		m_GCLimitSize = GCLimitSizeDef;

		MemHeader* pNew = _newBlock(MemBlockSize);
		m_begin = (char*)(pNew + 1);
		m_end = m_begin + pNew->cbSize;
	}

public:
	gen_alloc() {
		_init();
	}
	explicit gen_alloc(AllocT alloc) : m_alloc(alloc) {
		_init();
	}
	explicit gen_alloc(gen_alloc& owner) : m_alloc(owner.m_alloc) {
		_init();
	}

	~gen_alloc()
	{
		clear();
	}

	void BOOST_MEMORY_CALL swap(gen_alloc& o)
	{
		std::swap(m_begin, o.m_begin);
		std::swap(m_end, o.m_end);
		std::swap(m_blockList, o.m_blockList);
		std::swap(m_destroyChain, o.m_destroyChain);
		std::swap(m_freeSize, o.m_freeSize);
		std::swap(m_GCLimitSize, o.m_GCLimitSize);
		m_alloc.swap(o.m_alloc);
		m_freeList.swap(o.m_freeList);
		m_hugeAlloc.swap(o.m_hugeAlloc);
	}

	void BOOST_MEMORY_CALL clear()
	{
		m_hugeAlloc.clear();
		while (m_destroyChain)
		{
			MemHeaderEx* curr = m_destroyChain;
			m_destroyChain = m_destroyChain->pPrev;
			curr->destruct();
		}
		MemBlock* pHeader = m_blockList;
		while (pHeader)
		{
			MemBlock* curr = pHeader;
			pHeader = pHeader->pPrev;
			m_alloc.deallocate(curr);
		}
		m_begin = m_end = _null.getData();
		m_blockList = NULL;
		m_freeList.clear();
		m_freeSize = 0;
	}

	void* BOOST_MEMORY_CALL allocate(size_t cbData)
	{
		const size_t cb = cbData + sizeof(MemHeader);
		if ((size_t)(m_end - m_begin) < cb)
		{
			MemHeader* pNew;
			if (cb >= AllocSizeBig)
			{
				if (cb >= BlockSize)
				{
					if (cbData >= AllocSizeHuge)
						return m_hugeAlloc.allocate(cbData);

					pNew = _newBlock(cb + HeaderSize);
					pNew->blkType = nodeAlloced;
					return pNew + 1;
				}
				pNew = _newBlock(MemBlockSize);
			}
			else
			{
				try_gc();
				FreeMemHeader* p;
				if (m_freeList.empty() || (p = m_freeList.top())->cbSize < cb) {
					pNew = _newBlock(MemBlockSize);
				}
				else {
					pNew = (MemHeader*)p;
					m_freeList.pop();
				}
			}
			_commitCurrentBlock();
			m_begin = (char*)(pNew + 1);
			m_end = m_begin + pNew->cbSize;
		}

		BOOST_MEMORY_ASSERT(m_end - m_begin >= cb);

		MemHeader* pAlloc = (MemHeader*)(m_end -= cb);
		pAlloc->blkType = nodeAlloced;
		pAlloc->cbSize = cbData;
		return pAlloc + 1;
	}

	void* BOOST_MEMORY_CALL allocate(size_t cb, destructor_t fn)
	{
		if (cb >= AllocSizeHuge)
			return m_hugeAlloc.allocate(cb, fn);
		
		DestroyInfo* pNode = (DestroyInfo*)allocate(sizeof(DestroyInfo) + cb);
		pNode->fnDestroy = fn;
		pNode->pPrev = m_destroyChain;
		m_destroyChain = (MemHeaderEx*)((char*)pNode - sizeof(MemHeader));
		m_destroyChain->blkType = nodeAllocedWithDestructor;
		return pNode + 1;
	}

	void* BOOST_MEMORY_CALL allocate(size_t cb, int fnZero)
	{
		return allocate(cb);
	}

	void BOOST_MEMORY_CALL deallocate(void* pData, size_t cbData)
	{
		if (cbData >= AllocSizeHuge)
		{
			m_hugeAlloc.deallocate(pData, cbData);
		}
		else
		{
			MemHeader* p = (MemHeader*)pData - 1;
			BOOST_MEMORY_ASSERT(p->cbSize == cbData);
			BOOST_MEMORY_ASSERT(p->blkType == nodeAlloced);

			p->blkType = nodeFree;
			m_freeSize += cbData + sizeof(MemHeader);
		}
	}

private:
	template <class Type>
	void BOOST_MEMORY_CALL _destroy(Type* obj, destructor_t)
	{
		obj->~Type();
		MemHeaderEx* p = (MemHeaderEx*)obj - 1;
		p->blkType = nodeFree;
		m_freeSize += sizeof(Type) + sizeof(MemHeaderEx);
	}

	template <class Type>
	void BOOST_MEMORY_CALL _destroy(Type* obj, int)
	{
		MemHeader* p = (MemHeader*)obj - 1;
		p->blkType = nodeFree;
		m_freeSize += sizeof(Type) + sizeof(MemHeader);
	}

	template <class Type>
	void BOOST_MEMORY_CALL _destroyArray(Type* array, size_t count, destructor_t)
	{
		typedef destructor_traits<Type> Traits;

		Traits::destructArrayN(array, count);
		void* pData = Traits::getArrayBuffer(array);
		MemHeaderEx* p = (MemHeaderEx*)pData - 1;
		p->blkType = nodeFree;
		m_freeSize += Traits::getArrayAllocSize(count) + sizeof(MemHeaderEx);
	}

	template <class Type>
	void BOOST_MEMORY_CALL _destroyArray(Type* array, size_t count, int)
	{
		MemHeader* p = (MemHeader*)array - 1;
		p->blkType = nodeFree;
		m_freeSize += sizeof(Type) * count + sizeof(MemHeader);
	}

public:
	template <class Type>
	void BOOST_MEMORY_CALL destroy(Type* obj)
	{
		BOOST_MEMORY_ASSERT( _isValid(obj) );
		BOOST_MEMORY_ASSERT( sizeof(Type) < AllocSizeHuge );

		_destroy(obj, destructor_traits<Type>::destruct);
	}

	template <class Type>
	Type* BOOST_MEMORY_CALL newArray(size_t count, Type* zero)
	{
		size_t cb = destructor_traits<Type>::getArrayAllocSize(count);
		if (cb >= AllocSizeHuge)
			return m_hugeAlloc.newArray(count, zero);

		Type* array = (Type*)destructor_traits<Type>::allocArray(*this, count);
		return constructor_traits<Type>::constructArray(array, count);
	}

	template <class Type>
	void BOOST_MEMORY_CALL destroyArray(Type* array, size_t count)
	{
		BOOST_MEMORY_ASSERT( _isValidArray(array, count) );

		size_t cb = destructor_traits<Type>::getArrayAllocSize(count);
		if (cb >= AllocSizeHuge)
		{
			m_hugeAlloc.destroyArray(array, count);
		}
		else
		{
			_destroyArray(array, count, destructor_traits<Type>::destruct);
		}
	}

	BOOST_MEMORY_FAKE_DBG_ALLOCATE_();
};

template <class PolicyT>
typename gen_alloc<PolicyT>::FreeMemHeader gen_alloc<PolicyT>::_null;

// -------------------------------------------------------------------------
// class gc_alloc

typedef gen_alloc<policy::pool> gc_alloc;

// -------------------------------------------------------------------------
// $Log: gc_alloc.hpp,v $

NS_BOOST_MEMORY_END

#endif /* BOOST_MEMORY_GC_ALLOC_HPP */
