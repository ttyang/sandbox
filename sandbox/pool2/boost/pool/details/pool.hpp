#ifndef __BOOST_POOL_DETAILS
#define __BOOST_POOL_DETAILS

/* -------------------------------------------------------------------------- */
/* -- boost::pool::list_t                                                  -- */
/* -------------------------------------------------------------------------- */

template<typename T>
class list_t
{
	public :
		list_t() { _node.buffer = NULL; }
		list_t(T *buffer, list_t list = list_t()) { _node.buffer = buffer; if (_node.next) *_node.next = list; }

	public :
		inline void push(T *buffer)
			{ *this = list_t(buffer, *this); }		
		inline T *pop()
			{ T *buffer = front(); *this = next(); return buffer; }

		inline T *front() const
			{ return _node.buffer; }
		inline bool empty() const
			{ return !_node.buffer; }

		inline list_t next() const
			{ return _node.next ? *_node.next : *this; }
		inline void next(list_t list)
			{ if (_node.next) *_node.next = list; }

		inline bool operator<(const list_t& list) const
			{ return front() < list.front(); }

	public :
		bool contains(T *buffer) const
		{
			for (list_t list = *this; !list.empty(); list = list.next())
				if (list.front() == buffer)
					return true;

			return false;
		}

		void sort()
		{
			*this = sort(*this);
		}

    static list_t sort(list_t list)
    {
      if (list.empty() || list.next().empty())
        return list;

      list_t listA, listB;
      split(list, &listA, &listB);

      return merge(sort(listA), sort(listB));
    }

    static list_t merge(list_t listA, list_t listB)
    {
      if (listA.empty()) return listB;
      if (listB.empty()) return listA;

      if (listB < listA)
        std::swap(listA, listB);

      list_t list = listA; listA = listA.next();
      list_t last = list;

      while (!listA.empty())
      {
        if (listB < listA)
          std::swap(listA, listB);

        last.next(listA);
        last = last.next();
        listA = listA.next();
      }

      last.next(listB);
      return list;
    }
  
    static void split(list_t list, list_t *listA, list_t *listB)
    {
      list_t half = list;
      list_t full = list.next();

      while (!full.empty())
      {
        full = full.next();
        if (!full.empty())
        {
          half = half.next();
          full = full.next();
        }
      }

      *listA = list;
      *listB = half.next();

      half.next(list_t());
    }

	private :
		union
		{
			T *buffer;       // Buffer pointer.
			list_t *next;    // Linked list pointer.

		} _node;    // Linked list node 
};

/* -------------------------------------------------------------------------- */

#endif