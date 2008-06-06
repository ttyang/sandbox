#ifndef BOOST_DSEARCH_TRIE_HPP
#define BOOST_DSEARCH_TRIE_HPP

#include<limits>
#include<memory>
#include<stack>
#include<algorithm>
#include<assert.h>
#include<boost/dsearch/node_cursor.hpp>
#include<boost/dsearch/trie_iterator.hpp>
#include<vector>

namespace boost{
namespace dsearch{

template<class Key,class Mapped,
template<class K,class M,class K_t,class A > class trie_node, 
class Key_traits,
class Alloc=std::allocator<char> > //wonder allocator<char> is correct
class trie
{
	private:
	typedef trie_node<Key,Mapped,Key_traits,Alloc> node_type;
	friend class trie_node<Key,Mapped,Key_traits,Alloc>;
	typedef typename Alloc::template rebind<node_type>::other node_allocator_type;
	node_allocator_type node_allocator;
	node_type *node_root;
	public:
	typedef Key key_type;
	typedef Mapped data_type;
	typedef std::pair<Key,Mapped> value_type;
	typedef trie<Key,Mapped,trie_node,Key_traits,Alloc> type;

	//need to define an iterator before that will need to define cursor for trie_node
	//TODO iterator, const_iterator, reverse_iterator, const_reverse_iterator, begin(), end()
	//rbegin(),size(),trie(trie &), overload =, lots of other things

	typedef typename Alloc::template rebind<value_type>::other allocator_type;
    	typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer        const_pointer;
	typedef typename allocator_type::reference            reference;
	typedef typename allocator_type::const_reference      const_reference;
	typedef typename allocator_type::size_type            size_type;//should actually depend on iterator(.|?)
	typedef typename allocator_type::difference_type      difference_type; //should actually depend on iterator(.|?)
	
	typedef trie_cursor<key_type,data_type,node_type> cursor;
	typedef trie_iterator<key_type,data_type,cursor> iterator;
	typedef trie_iterator<key_type,const data_type,cursor> const_iterator;

	trie()
	{
		node_root=node_allocator.allocate(1);
		new(node_root) node_type();
	}

	trie(const type &other)
	{
		std::cout<<"in copy constructor"<<std::endl;

		copy_trie_preserve(const_cast<node_type *>(other.node_root) );
	}
	
	type &operator = ( const type other )
	{
		if(node_root==other.node_root) return *this;
		clear();
		node_allocator.destroy(node_root);
		node_allocator.deallocate(node_root,1);
		copy_trie(other.node_root);
		return *this;
	}

	data_type &operator [] (const key_type &k) 
	{
		return	insert_(k)->get_value_ref();
	}

	void insert(const value_type &v)
	{
		this->operator[](v.first)=v.second;
	}

	std::size_t size()
	{
		return 0; //for now
	}

	std::size_t max_size()
	{
		return  std::numeric_limits<std::size_t>::max();
	}

	bool empty()
	{
		return node_root->empty();
	}

	void erase(const key_type &key) 
	{
		typename Key_traits::const_iterator it=Key_traits::begin(key),
			end_it=Key_traits::end(key),temp_it=it;
		typename node_type::iterator fit;

		node_type* cur=node_root,*par=node_root,*temp_cur=node_root;

		if(it==end_it) 
		{
			if(node_root->has_value())
				node_root->erase_value();
			return;
		}
		fit=cur->find(*it);
		if(fit==cur->end())
			return;
		cur=*fit;

		it++;
		while(!(it==end_it))
		{
			
			fit=cur->find(*it);
			if(fit==cur->end()) 
			{
				return;
			}
			if(cur->size()!=1 || cur->has_value()) //should we delete things backwards?
			{
				temp_cur=cur;
				temp_it=it;
			}
			cur=*fit;
			it++;
		}

		cur->erase_value();
		if(!cur->empty()) return;

		fit=temp_cur->find(*temp_it);
		cur=*fit;
		std::cout<<"deleting:"<<*temp_it<<std::endl;
		temp_cur->erase(fit);

		it=temp_it;
		++it;

		while(it!=end_it)
		{
			std::cout<<"deleting:"<<*it<<std::endl;
			par=cur;
			cur=*cur->find(*it);
			node_allocator.deallocate(par,1);
			it++;
		}
		node_allocator.deallocate(cur,1);		
	}

	//make use of iterator iterator.push();
	iterator find(const key_type &key) const //make this iterator instead of bool;
	{
		typename Key_traits::const_iterator it=Key_traits::begin(key),
					end_it=Key_traits::end(key);
		iterator ret_it;
		cursor cur,next;
		cur=root();
		while(!(it==end_it))
		{
			ret_it.push(cur);
			next=cur.find(*it);
			if ( next == cur.end() ) return end();
			cur=next;
			it++;
		}
		ret_it.push(cur);
		if(cur->has_value())
		{
			return ret_it;
		}
		return end();
	}

	iterator upper_bound(const key_type &key)
	{
		typename Key_traits::const_iterator it=Key_traits::begin(key),
					end_it=Key_traits::end(key);
		iterator ret_it;
		bool not_found=false;
		cursor cur,next,r=root();
		cur=r;
		ret_it.push(cur);
		std::cout<<"UPPER BOUND"<<std::endl;
		while(it!=end_it)
		{
			if(cur.empty())
			{
				ret_it++;
				return ret_it;
			}
			std::cout<<"finding "<<*it<<std::endl;
			next=cur.find(*it);
			if ( next == cur.end() )
			{
				not_found=true;
				break;
			}
			std::cout<<"found "<<*it<<std::endl;
			cur=next;
			ret_it.push(cur);
			it++;
		}
		//ret_it.push(cur);
		if( not_found )
		{
			next=cursor(cur.get_node(),cur.get_node()->lower_bound(*it));
			if(next==ret_it.top().end())
				next=cursor ( cur.get_node(), cur.get_node()->begin());
			else
				next++;
			while(next==ret_it.top().end())
			{
				std::cout<<"popping "<<std::endl;
				next=ret_it.top();
				if(next==r)
					return end();
				ret_it.pop();
				next++;
			}
			ret_it.push(next);
		}
		ret_it.to_left_most(); //if ret_it.top().hash_value() then this does nothing
		return ret_it;
	}

	iterator lower_bound(const key_type &key)
	{
		typename Key_traits::const_iterator it=Key_traits::begin(key),
				end_it=Key_traits::end(key);
		iterator ret_it;
		bool not_found=false;
		cursor cur,next,r=root();
		cur=r;
		ret_it.push(cur);
		std::cout<<"LOWER BOUND"<<std::endl;
		while(it!=end_it)
		{
			if(cur.empty())
				break;
			std::cout<<"finding "<<*it<<std::endl;
			next=cur.find(*it);
			if ( next == cur.end() )
			{
				not_found=true;
				break;
			}
			std::cout<<"found "<<*it<<std::endl;
			cur=next;
			ret_it.push(cur);
			it++;
		}

		if(not_found)
		{
			next=cursor(cur.get_node(),cur.get_node()->lower_bound(*it));
			if(next!=cur.end()) 
			{
				ret_it.push(next);
				ret_it.to_right_most();
				return ret_it;
			}
		}

		do
		{
			next=ret_it.top();
			ret_it.pop();
			if(next.has_value())
			{
				ret_it.push(next);
				return ret_it;
			}
			if(next==r)
			{
				return end();
			}
		}
		while(next==ret_it.top().begin());

		next--;
		ret_it.push(next);
		ret_it.to_right_most();
		return ret_it;
	}

	std::pair<iterator,iterator> prefix_range(const key_type &key)
	{
		typename Key_traits::const_iterator it=Key_traits::begin(key),
				end_it=Key_traits::end(key);
		iterator ret_it,right;
		cursor cur,next;
		cur=root();
		ret_it.push(cur);
		while(it!=end_it)
		{
			if(cur.empty()) return std::make_pair(end(),end());
			next=cur.find(*it);
			if(cur.end()==next)
				return std::make_pair(end(),end());
			cur=next;
			ret_it.push(cur);
		}
		right=ret_it;
		ret_it.to_left_most();
		right.to_right_most();
		return std::make_pair(ret_it,++right);
	}

	void clear()
	{
		typedef typename node_type::iterator node_it;
		std::stack< std::pair<node_type*,node_it> > node_stack; 
		int size=1;
		node_stack.push(std::make_pair(node_root,node_root->begin()));
		while(1)
		{		
			if(node_stack.top().first->end()==node_stack.top().second)
			{
				if(size==1) break;
				node_allocator.destroy(node_stack.top().first);
				node_allocator.deallocate(node_stack.top().first,1);
				node_stack.pop();
				size--;
				node_stack.top().second++;
				continue;
			}
			node_stack.push( std::make_pair(*(node_stack.top().second)
			,(*(node_stack.top().second))->begin()) );
			size++;
		}
		node_stack.pop();
		node_allocator.destroy(node_root);
		node_allocator.deallocate(node_root,1);
		node_root=node_allocator.allocate(1);
		new(node_root) node_type();
	}
	
	//linear iteration to find where the pointer is grr...
	//otherwise i will need to add one more function to the node
	void erase(const iterator &it)
	{
		iterator iter=it;
		node_type *n_t;
		cursor cur_it;
		typename node_type::iterator node_it;
		if ( iter.top().begin()==iter.top().end() )
		{
			node_allocator.destroy( n_t = iter.top().get_node() );
			node_allocator.deallocate( iter.top().get_node() , 1 );
			iter.pop();
		}
		else
		{
			iter.top().get_node()->erase_value();
			return;
		}
		if ( iter.empty() )
		if( iter.empty() ) //deallocated the root node so reallocate it.
		{
			node_root=node_allocator.allocate(1);
			new(node_root) node_type();
			return;
		}
			
		cur_it=iter.top().begin();
		while((++cur_it)==iter.top().end())
		{
			node_allocator.destroy ( n_t = iter.top().get_node() );
			node_allocator.deallocate ( iter.top().get_node() , 1 );
			iter.pop();
			if( iter.empty() ) //deallocated the root node so reallocate it.
			{
				node_root=node_allocator.allocate(1);
				new(node_root) node_type();
				return;
			}
			if(iter.top().has_value())
				break;
			cur_it=iter.top().begin();
		}
		node_it=iter.top().get_node()->begin();

		//here is the linear iteration
		while( (*node_it)!=n_t )
		{
			++node_it;
			assert(iter.top().get_node()->end()!=node_it);
		}
		iter.top().get_node()->erase(node_it);
	}

	void swap(type &other)
	{
		std::swap(other.node_root,node_root);
	}

	iterator begin() const
	{
		return iterator(root(),false);
	}

	iterator end() const
	{
		return iterator(root(),true);
	}

	cursor root() const
	{
		return cursor(node_root);
	}
	
	~trie()
	{
		std::cout<<"trie class destructor"<<std::endl;
		this->clear();
		node_allocator.deallocate(node_root,1);
	}
	private:

	//get reference to the leaf node of the key
	node_type *insert_(const key_type &key)
	{
		typename Key_traits::const_iterator it=Key_traits::begin(key),
			end_it=Key_traits::end(key);
		node_type *cur=node_root,*next;
		typename node_type::iterator fit;
		int i=0;
		while(it!=end_it)
		{
			fit=cur->find(*it);
			if(fit==cur->end())
				break;
			cur=*fit;
			it++;
			assert(i!=10);
		}
		i=0;
		while(it!=end_it)
		{
			i++;
			next=node_allocator.allocate(1);
			std::cout<<"Allocating:"<<*it<<std::endl;
			new(next) node_type();
			cur->insert(*it,next);
			cur=next;
			assert(i!=10);
			it++;
		}
		return cur;
	}

	bool exist(const key_type &key) const //make this iterator instead of bool;
	{
		typename Key_traits::const_iterator it=Key_traits::begin(key),
					end_it=Key_traits::end(key);
		typename node_type::iterator fit;
		node_type *cur=node_root;
		while(!(it==end_it))
		{
			fit=cur->find(*it);
			if(fit == cur->end() ) return false;
			cur=*fit;
			it++;
		}
		if(cur->has_value())
		{
			return true;
		}
		return false;
	}

	void copy_trie_preserve(node_type*other_root)
	{
		node_type *prev,*temp_node;
		typedef typename node_type::iterator node_iterator;
		std::stack<node_iterator> st;
		std::stack<node_iterator> this_st;
		node_iterator cur_it=other_root->begin();

		node_root=node_allocator.allocate(1);
		node_allocator.construct(node_root,*other_root);
		
		if ( other_root->end() == other_root->begin() )
			return;
		this_st.push(node_root->begin());

		while(true)
		{
			if(st.empty())
				prev=other_root;
			else
				prev=*st.top();

			if( cur_it == prev->end() )
			{
				if(st.empty())  return;
				cur_it=++st.top();
				st.pop();
				this_st.pop();
				++this_st.top();
				continue;
			}

			temp_node=node_allocator.allocate(1);
			node_allocator.construct( temp_node , **cur_it );
			*(this_st.top())=temp_node;

			/*if((*cur_it)->has_value())
				temp_node->get_value_ref()=(*cur_it)->get_value_ref();*/
			this_st.push(temp_node->begin());
			st.push(cur_it);

			cur_it=(*cur_it)->begin();
		}
	}

	//this does not preserve the stucture of tst.
	void copy_trie(node_type*other_root)
	{
		node_type *prev,*this_prev,*temp_node;
		typedef typename node_type::iterator node_iterator;
		std::stack<node_iterator> st;
		std::stack<node_type *> this_st;

		node_iterator cur_it=other_root->begin();

		node_root=node_allocator.allocate(1);
		new(node_root) node_type;
		if(other_root->has_value())
			node_root->get_value_ref()=other_root->get_value_ref();

		while(true)
		{
			if(st.empty())
			{
				prev=other_root;
				this_prev=node_root;
			}
			else
			{
				prev=*st.top();
				this_prev=this_st.top();
			}

			if(cur_it==prev->end())
			{
				std::cout<<"reached end"<<std::endl;
				if(st.empty())  return;
				this_st.pop();
				cur_it=++st.top();
				st.pop();
				continue;
			}
			else
				std::cout<<"going to:"<<prev->get_element(cur_it)<<std::endl;

			temp_node=node_allocator.allocate(1);
			new(temp_node) node_type();
			this_prev->insert(prev->get_element(cur_it),temp_node);

			if((*cur_it)->has_value())
				temp_node->get_value_ref()=(*cur_it)->get_value_ref();
			this_st.push(temp_node);
			st.push(cur_it);
			cur_it=(*cur_it)->begin();
		}
	}
};

}
}
#endif //BOOST_DSEARCH_TRIE_HPP

