/* Copyright Joaqu�n M L�pez Mu�oz 2003. Use, modification, and distribution
 * are subject to the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/indexed_set for library home page.
 */

#ifndef BOOST_INDEXED_SET_INDEX_HPP
#define BOOST_INDEXED_SET_INDEX_HPP

#include <boost/config.hpp> /* keep it first to prevent some nasty warnings in MSVC */
#include <algorithm>
#include <boost/call_traits.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/indexed_set/access_specifier.hpp>
#include <boost/indexed_set/index_fwd.hpp>
#include <boost/indexed_set/index_iterator.hpp>
#include <boost/indexed_set/index_node.hpp>
#include <boost/indexed_set/modify_key_adaptor.hpp>
#include <boost/indexed_set/prevent_eti.hpp>
#include <boost/indexed_set/safe_mode.hpp>
#include <boost/indexed_set/scope_guard.hpp>
#include <boost/indexed_set/unbounded.hpp>
#include <boost/indexed_set/value_compare.hpp>
#include <boost/iterator_adaptors.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/ref.hpp>
#include <boost/tuple/tuple.hpp>

#if defined(BOOST_INDEXED_SET_ENABLE_INVARIANT_CHECKING)
#define BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT \
  detail::scope_guard BOOST_JOIN(check_invariant_,__LINE__)=\
    detail::make_obj_guard(*this,&index::check_invariant_);\
  BOOST_JOIN(check_invariant_,__LINE__).touch();
#else
#define BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT
#endif

namespace boost{

namespace indexed_sets{

namespace detail{

/* index adds a layer of indexing to a given Super */

/* Most of the implementation of unique and non-unique indices is
 * shared. We tell from one another on instantiation time by using
 * these tags.
 */

struct unique_index_tag{};
struct non_unique_index_tag{};

template<
  typename KeyFromValue,typename Compare,typename Allocator,
  typename Super,typename TagList,typename Category
>

#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)
#if BOOST_WORKAROUND(BOOST_MSVC,<1300)
class index:
  BOOST_INDEXED_SET_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS Super,
  public index_proxy<index_node<typename Super::node_type> >
#else
class index:
  BOOST_INDEXED_SET_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS Super,
  public safe_container<index<KeyFromValue,Compare,Allocator,Super,TagList,Category> >
#endif
#else
class index:BOOST_INDEXED_SET_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS Super
#endif

{ 
protected:
  typedef index_node<typename Super::node_type> node_type;

public:
  /* types */

  typedef typename KeyFromValue::result_type         key_type;
  typedef typename node_type::value_type             value_type;
  typedef KeyFromValue                               key_from_value;
  typedef Compare                                    key_compare;
  typedef value_comparison<
    value_type,KeyFromValue,Compare>                 value_compare;
  typedef tuple<key_from_value,key_compare>          ctor_args;
  typedef Allocator                                  allocator_type;
  typedef typename Allocator::reference              reference;
  typedef typename Allocator::const_reference        const_reference;

#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)
#if BOOST_WORKAROUND(BOOST_MSVC,<1300)
  typedef index_iterator<node_type>                  iterator;
  typedef index_iterator<node_type>                  const_iterator;
#else
  typedef index_iterator<node_type,index>            iterator;
  typedef index_iterator<node_type,index>            const_iterator;
#endif
#else
  typedef index_iterator<node_type>                  iterator;
  typedef index_iterator<node_type>                  const_iterator;
#endif

  typedef std::size_t                                size_type;      
  typedef std::ptrdiff_t                             difference_type;
  typedef typename Allocator::pointer                pointer;
  typedef typename Allocator::const_pointer          const_pointer;
  typedef typename
    reverse_iterator_generator<iterator>::type       reverse_iterator;
  typedef typename
    reverse_iterator_generator<const_iterator>::type const_reverse_iterator;
  typedef typename TagList::type                     tag_list;

protected:
  typedef typename Super::final_node_type               final_node_type;
  typedef tuples::cons<
    ctor_args, 
    typename Super::ctor_args_list>                     ctor_args_list;
  typedef typename mpl::push_front<
    typename Super::index_type_list,index>::type        index_type_list;
  typedef typename mpl::push_front<
    typename Super::iterator_type_list,iterator>::type  iterator_type_list;
  typedef typename mpl::push_front<
    typename Super::const_iterator_type_list,
    const_iterator>::type                               const_iterator_type_list;

private:
#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)
#if BOOST_WORKAROUND(BOOST_MSVC,<1300)
  typedef index_proxy<index_node<typename Super::node_type> > safe_super;
#else
  typedef safe_container<index>                               safe_super;
#endif
#endif

  typedef typename call_traits<value_type>::param_type        value_param_type;
  typedef typename call_traits<key_type>::param_type          key_param_type;

public:

  /* construct/copy/destroy
   * Default and copy ctors are in the protected section as indices are
   * not supposed to be created on their own. No range ctor either.
   */

  index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& operator=(
    const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& x)
  {
    BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT;
    final()=x.final();
    return *this;
  }

  allocator_type get_allocator()const
  {
    return final().get_allocator();
  }

  /* iterators */

  iterator               begin(){return make_iterator(leftmost());}
  const_iterator         begin()const{return make_iterator(leftmost());}
  iterator               end(){return make_iterator(header());}
  const_iterator         end()const{return make_iterator(header());}
  reverse_iterator       rbegin(){return make_reverse_iterator(end());}
  const_reverse_iterator rbegin()const{return make_reverse_iterator(end());}
  reverse_iterator       rend(){return make_reverse_iterator(begin());}
  const_reverse_iterator rend()const{return make_reverse_iterator(begin());}
 
  /* capacity */

  bool      empty()const{return final_empty_();}
  size_type size()const{return final_size_();}
  size_type max_size()const{return final_max_size_();}

  /* modifiers */

  std::pair<iterator,bool> insert(value_param_type x)
  {
    BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=final_insert_(x);
    return std::pair<iterator,bool>(make_iterator(p.first),p.second);
  }

  iterator insert(iterator position,value_param_type x)
  {
    BOOST_INDEXED_SET_CHECK_VALID_ITERATOR(position);
    BOOST_INDEXED_SET_CHECK_IS_OWNER(position,*this);
    BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT;
    std::pair<final_node_type*,bool> p=final_insert_(
      x,static_cast<final_node_type*>(position.get_node()));
    return make_iterator(p.first);
  }
    
#if !defined(BOOST_NO_MEMBER_TEMPLATES)||defined(BOOST_MSVC6_MEMBER_TEMPLATES)
  template<typename InputIterator>
  void insert(InputIterator first,InputIterator last)
  {
    BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT;
    iterator hint=end();
    for(;first!=last;++first)hint=insert(hint,*first);
  }
#endif

  void erase(iterator position)
  {
    BOOST_INDEXED_SET_CHECK_VALID_ITERATOR(position);
    BOOST_INDEXED_SET_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_INDEXED_SET_CHECK_IS_OWNER(position,*this);
    BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT;

#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)
    /* MSVC++ 6.0 optimizer on safe mode code chokes if this
     * this is not added. Left it for all compilers as it does no
     * harm.
     */

    position.detach();
#endif

    final_erase_(static_cast<final_node_type*>(position.get_node()));
  }
  
  size_type erase(key_param_type x)
  {
    BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT;
    std::pair<iterator,iterator> p=equal_range(x);
    size_type s=0;
    while(p.first!=p.second){
      erase(p.first++);
      ++s;
    }
    return s;
  }

  void erase(iterator first,iterator last)
  {
    BOOST_INDEXED_SET_CHECK_VALID_ITERATOR(first);
    BOOST_INDEXED_SET_CHECK_VALID_ITERATOR(last);
    BOOST_INDEXED_SET_CHECK_IS_OWNER(first,*this);
    BOOST_INDEXED_SET_CHECK_IS_OWNER(last,*this);
    BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT;
    while(first!=last){
      erase(first++);
    }
  }

  bool update(iterator position,value_param_type x)
  {
    BOOST_INDEXED_SET_CHECK_VALID_ITERATOR(position);
    BOOST_INDEXED_SET_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_INDEXED_SET_CHECK_IS_OWNER(position,*this);
    BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT;
    return final_update_(x,static_cast<final_node_type*>(position.get_node()));
  }

#if !defined(BOOST_NO_MEMBER_TEMPLATES)||defined(BOOST_MSVC6_MEMBER_TEMPLATES)
  template<typename Modifier>
  bool modify(iterator position,Modifier mod)
  {
    BOOST_INDEXED_SET_CHECK_VALID_ITERATOR(position);
    BOOST_INDEXED_SET_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_INDEXED_SET_CHECK_IS_OWNER(position,*this);
    BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT;

#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)
    /* MSVC++ 6.0 optimizer on safe mode code chokes if this
     * this is not added. Left it for all compilers as it does no
     * harm.
     */

    position.detach();
#endif

    return final_modify_(mod,static_cast<final_node_type*>(position.get_node()));
  }

  template<typename Modifier>
  bool modify_key(iterator position,Modifier mod)
  {
    BOOST_INDEXED_SET_CHECK_VALID_ITERATOR(position);
    BOOST_INDEXED_SET_CHECK_DEREFERENCEABLE_ITERATOR(position);
    BOOST_INDEXED_SET_CHECK_IS_OWNER(position,*this);
    BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT;
    return modify(position,modify_key_adaptor<Modifier,value_type,KeyFromValue>(mod,key));
  }
#endif

  void swap(index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& x)
  {
    BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT;
    final_swap_(x.final());
  }

  void clear()
  {
    BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT;
    erase(begin(),end());
  }

  /* observers */

  key_from_value key_extractor()const{return key;}
  key_compare    key_comp()const{return comp;}
  value_compare  value_comp()const{return value_compare(key,comp);}

#if !defined(BOOST_NO_MEMBER_TEMPLATES)||defined(BOOST_MSVC6_MEMBER_TEMPLATES)

  /* set operations */

  /* no need to provide non-const versions as index::iterator==index::const_iterator */

  template<typename CompatibleKey>
    const_iterator find(const CompatibleKey& x)const
  {
    return find(x,comp);
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  const_iterator find(const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    node_type* y=header();
    node_type* z=root();
      
    while (z){
      if(!comp(key(z->value),x)){
        y=z;
        z=node_type::from_impl(z->left());
      }
      else z=node_type::from_impl(z->right());
    }
      
    const_iterator j=make_iterator(y);   
    return (j==end()||comp(x,key(*j)))?end():j;
  }

  template<typename CompatibleKey>
  size_type count(const CompatibleKey& x)const
  {
    return count(x,comp);
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  size_type count(const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    std::pair<const_iterator, const_iterator> p=equal_range(x,comp);
    size_type n=std::distance(p.first,p.second);
    return n;
  }

  template<typename CompatibleKey>
  const_iterator lower_bound(const CompatibleKey& x)const
  {
    return lower_bound(x,comp);
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  const_iterator lower_bound(const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    node_type* y=header();
    node_type* z=root();

    while(z){
      if(!comp(key(z->value),x)){
        y=z;
        z=node_type::from_impl(z->left());
      }
      else z=node_type::from_impl(z->right());
    }

    return make_iterator(y);
  }

  template<typename CompatibleKey>
  const_iterator upper_bound(const CompatibleKey& x)const
  {
    return upper_bound(x,comp);
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  const_iterator upper_bound(const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    node_type* y=header();
    node_type* z=root();

    while(z){
      if(comp(x,key(z->value))){
        y=z;
        z=node_type::from_impl(z->left());
      }
      else z=node_type::from_impl(z->right());
    }

    return make_iterator(y);
  }

  template<typename CompatibleKey>
  std::pair<const_iterator,const_iterator> equal_range(const CompatibleKey& x)const
  {
    return equal_range(x,comp);
  }

  template<typename CompatibleKey,typename CompatibleCompare>
  std::pair<const_iterator,const_iterator> equal_range(
    const CompatibleKey& x,const CompatibleCompare& comp)const
  {
    return std::pair<const_iterator,const_iterator>(lower_bound(x,comp),upper_bound(x,comp));
  }

#else /* no member templates, most of the fun goes out */

  /* set operations */

  /* no need to provide non-const versions as index::iterator==index::const_iterator */

  const_iterator find(key_param_type x)const
  {
    node_type* y=header();
    node_type* z=root();
      
    while (z){
      if(!comp(key(z->value),x)){
        y=z;
        z=node_type::from_impl(z->left());
      }
      else z=node_type::from_impl(z->right());
    }
      
    const_iterator j=make_iterator(y);   
    return (j==end()||comp(x,key(*j)))?end():j;
  }

  size_type count(key_param_type x)const
  {
    std::pair<const_iterator, const_iterator> p=equal_range(x,comp);
    size_type n=std::distance(p.first,p.second);
    return n;
  }

  const_iterator lower_bound(key_param_type x)const
  {
    node_type* y=header();
    node_type* z=root();

    while(z){
      if(!comp(key(z->value),x)){
        y=z;
        z=node_type::from_impl(z->left());
      }
      else z=node_type::from_impl(z->right());
    }

    return make_iterator(y);
  }


  const_iterator upper_bound(key_param_type x)const
  {
    node_type* y=header();
    node_type* z=root();

    while(z){
      if(comp(x,key(z->value))){
        y=z;
        z=node_type::from_impl(z->left());
      }
      else z=node_type::from_impl(z->right());
    }

    return make_iterator(y);
  }

  std::pair<const_iterator,const_iterator> equal_range(key_param_type x)const
  {
    return std::pair<const_iterator,const_iterator>(lower_bound(x),upper_bound(x));
  }

#endif

#if !defined(BOOST_NO_MEMBER_TEMPLATES)||defined(BOOST_MSVC6_MEMBER_TEMPLATES)
  /* range */

  /* no need to provide non-const version as index::iterator==index::const_iterator */

  template<typename LowerBounder,typename UpperBounder>
  std::pair<const_iterator,const_iterator>
  range(LowerBounder lower,UpperBounder upper)const
  {
    std::pair<const_iterator,const_iterator> p(lower_range(lower),upper_range(upper));
    if(p.second!=end()&&(p.first==end()||comp(key(*p.second),key(*p.first))))p.second=p.first;
    return p;
  }
#endif

  /* Create an iterator given a node pointer. This should be protected,
   * but it is not simple to do so in a reasonable manner as it gets called
   * by global project().
   */

#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)
  iterator       make_iterator(node_type* node){return iterator(node,this);}
  const_iterator make_iterator(node_type* node)const
    {return const_iterator(node,const_cast<index*>(this));}
#else
  iterator       make_iterator(node_type* node){return iterator(node);}
  const_iterator make_iterator(node_type* node)const{return const_iterator(node);}
#endif

protected:
  index(const ctor_args_list& args_list,const Allocator& al):
    Super(args_list.get_tail(),al),

#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)&&BOOST_WORKAROUND(BOOST_MSVC,<1300)
    safe_super(final_header()),
#endif

    key(tuples::get<0>(args_list.get_head())),
    comp(tuples::get<1>(args_list.get_head()))
  {
    empty_initialize();
  }

  index(const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& x):
    Super(x),

#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)&&BOOST_WORKAROUND(BOOST_MSVC,<1300)
    safe_super(final_header()),
#endif

    key(x.key),
    comp(x.comp)
  {
    /* Copy ctor just takes the compare objects from x. The rest is done by
     * the indexed_set class ctor.
     */
    empty_initialize();
  }

  std::pair<node_type*,bool> insert_(value_param_type v,node_type* x)
  {
    std::pair<node_type*,bool> p=link2(key(v),x,Category());
    if(!p.second)return p;

    scope_guard undo=make_guard(
      &index_node_impl::rebalance_for_erase,
      x->impl(),ref(header()->parent()),ref(header()->left()),ref(header()->right()));

    typedef typename Super::node_type super_node_type;
    std::pair<super_node_type*,bool> p2=Super::insert_(v,x);
    if(!p2.second){
      return std::pair<node_type*,bool>(static_cast<node_type*>(p2.first),false);
    }

    undo.dismiss();
    return p;
  }

  std::pair<node_type*,bool> insert_(value_param_type v,node_type* position,node_type* x)
  {
    std::pair<node_type*,bool> p=link3(key(v),position,x,Category());
    if(!p.second)return p;

    scope_guard undo=make_guard(
      &index_node_impl::rebalance_for_erase,
      x->impl(),ref(header()->parent()),ref(header()->left()),ref(header()->right()));

    typedef typename Super::node_type super_node_type;
    std::pair<super_node_type*,bool> p2=Super::insert_(v,position,x);
    if(!p2.second){
      return std::pair<node_type*,bool>(static_cast<node_type*>(p2.first),false);
    }

    undo.dismiss();
    return p;
  }

  void erase_(node_type* x)
  {
    Super::erase_(x);
    index_node_impl::rebalance_for_erase(
      x->impl(),header()->parent(),header()->left(),header()->right());

#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)
    detach_iterators(x);
#endif
  }

  void swap_(index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& x)
  {
    std::swap(key,x.key);
    std::swap(comp,x.comp);

#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)
    safe_super::swap(x);
#endif

    Super::swap_(x);
  }

  bool update_(value_param_type v,node_type* x)
  {
    if(!comp(key(v),key(x->value))&&
       !comp(key(x->value),key(v))){
      return Super::update_(v,x);
    }

    node_type* prior=x;
    node_type::decrement(prior);
    node_type* next=x;
    node_type::increment(next);

    index_node_impl::rebalance_for_erase(
      x->impl(),header()->parent(),header()->left(),header()->right());
    scope_guard undo_rebalance=make_guard(
      &index_node_impl::restore,
      x->impl(),prior->impl(),next->impl(),header()->impl());

    if(!link2(key(v),x,Category()).second)return false;
    scope_guard undo_link=make_guard(
      &index_node_impl::rebalance_for_erase,
      x->impl(),ref(header()->parent()),ref(header()->left()),ref(header()->right()));

    if(!Super::update_(v,x))return false;

    undo_link.dismiss();
    undo_rebalance.dismiss();
    return true;
  }

#if !defined(BOOST_NO_MEMBER_TEMPLATES)||defined(BOOST_MSVC6_MEMBER_TEMPLATES)
  bool modify_(node_type* x)
  {
    scope_guard eraser=make_obj_guard(*this,&index::erase_,x);
    bool b=in_place(x,Category());
    eraser.dismiss();

#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)
    scope_guard detacher=make_obj_guard(*this,&index::detach_iterators,x);
#endif

    if(!b){
      index_node_impl::rebalance_for_erase(
        x->impl(),header()->parent(),header()->left(),header()->right());

      scope_guard super_eraser=make_obj_guard(static_cast<Super&>(*this),&Super::erase_,x);
      if(!link2(key(x->value),x,Category()).second)return false;
      super_eraser.dismiss();
    }

    scope_guard local_eraser=make_guard(
      &index_node_impl::rebalance_for_erase,
      x->impl(),ref(header()->parent()),ref(header()->left()),ref(header()->right()));
    if(!Super::modify_(x))return false;
    local_eraser.dismiss();

#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)
    detacher.dismiss();
#endif

    return true;
  }
#endif

#if defined(BOOST_INDEXED_SET_ENABLE_INVARIANT_CHECKING)
  /* invariant stuff */

  bool invariant_()const
  {
    if(size()==0||begin()==end()){
      if(size()!=0||begin()!=end()||
         header()->left()!=header()->impl()||
         header()->right()!=header()->impl())return false;
    }
    else{
      if((size_type)std::distance(begin(),end())!=size())return false;

      std::size_t len=index_node_impl::black_count(leftmost()->impl(),root()->impl());
      for(const_iterator it=begin();it!=end();++it){
        node_type* x=it.get_node();
        node_type* left_x=node_type::from_impl(x->left());
        node_type* right_x=node_type::from_impl(x->right());

        if(x->color()==red){
          if((left_x&&left_x->color()==red)||(right_x&&right_x->color()==red))return false;
        }
        if(left_x&&comp(key(x->value),key(left_x->value)))return false;
        if(right_x&&comp(key(right_x->value),key(x->value)))return false;
        if(!left_x&&!right_x&&
           index_node_impl::black_count(x->impl(),root()->impl())!=len)return false;
      }
    
      if(leftmost()->impl()!=index_node_impl::minimum(root()->impl()))return false;
      if(rightmost()->impl()!=index_node_impl::maximum(root()->impl()))return false;
    }

    return Super::invariant_();
  }

  
  /* This forwarding function eases things for the boost::mem_fn construct
   * in BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT. Actually, final_check_invariant
   * is already an inherited member function of index.
   */
  void check_invariant_()const{final_check_invariant_();}
#endif

private:
  node_type* header()const{return final_header();}
  node_type* root()const{return node_type::from_impl(header()->parent());}
  node_type* leftmost()const{return node_type::from_impl(header()->left());}
  node_type* rightmost()const{return node_type::from_impl(header()->right());}

  void empty_initialize()
  {
    header()->color()=red; /* used to distinguish header() from root, in iterator.operator++ */
    header()->parent()=0;
    header()->left()=header()->impl();
    header()->right()=header()->impl();
  }

  node_type* link4(key_param_type k,node_type* x,node_type* y,node_type* z)
  {
    if(y==header()||x!=0||comp(k,key(y->value))){
      y->left()=z->impl();           /* also makes leftmost()=z when y==header() */
      if (y==header()){
        header()->parent()=z->impl();
        header()->right()=z->impl();
      }
      else if(y==leftmost()){
        header()->left()=z->impl();  /* maintain leftmost() pointing to min node */
      }
    }
    else{
      y->right()=z->impl();
      if(y==rightmost()){
        header()->right()=z->impl(); /* maintain rightmost() pointing to max node */
      }
    }
    z->parent()=y->impl();
    z->left()=0;
    z->right()=0;
    index_node_impl::rebalance(z->impl(),header()->parent());
    return z;
  }

  std::pair<node_type*,bool> link2(key_param_type k,node_type* z,unique_index_tag)
  {
    node_type* y=header();
    node_type* x=root();
    bool c=true;
    while(x){
      y=x;
      c=comp(k,key(x->value));
      x=node_type::from_impl(c?x->left():x->right());
    }
    iterator j=make_iterator(y);   
    if(c){
      if(j==begin())return std::pair<node_type*,bool>(link4(k,x,y,z),true);
      else --j;
    }

    if(comp(key(*j),k))return std::pair<node_type*,bool>(link4(k,x,y,z),true);
    else return std::pair<node_type*,bool>(j.get_node(),false);
  }

  std::pair<node_type*,bool> link2(key_param_type k,node_type* z,non_unique_index_tag)
  {
    node_type* y=header();
    node_type* x=root();
    while (x){
     y=x;
     x=node_type::from_impl(comp(k,key(x->value))?x->left():x->right());
    }
    return std::pair<node_type*,bool>(link4(k,x,y,z),true);
  }

  std::pair<node_type*,bool> link3(
    key_param_type k,node_type* position,node_type* z,unique_index_tag)
  {
    if(position->impl()==header()->left()){ 
      if(size()>0&&comp(k,key(position->value))){
        return std::pair<node_type*,bool>(link4(k,position,position,z),true);
      }
      else return link2(k,z,unique_index_tag());
    } 
    else if(position==header()){ 
      if(comp(key(rightmost()->value),k)){
        return std::pair<node_type*,bool>(link4(k,0,rightmost(),z),true);
      }
      else return link2(k,z,unique_index_tag());
    } 
    else{
      node_type* before=position;
      node_type::decrement(before);
      if(comp(key(before->value),k)&&comp(k,key(position->value))){
        if(before->right()==0)return std::pair<node_type*,bool>(link4(k,0,before,z),true); 
        else return std::pair<node_type*,bool>(link4(k,position,position,z),true);
      } 
      else return link2(k,z,unique_index_tag());
    }
  }

  std::pair<node_type*,bool> link3(
    key_param_type k,node_type* position,node_type* z,non_unique_index_tag)
  {
    if(position->impl()==header()->left()){ 
      if(size()>0&&!comp(key(position->value),k)){
        return std::pair<node_type*,bool>(link4(k,position,position,z),true);
      }
      else return link2(k,z,non_unique_index_tag());
    } 
    else if(position==header()){
      if(!comp(k,key(rightmost()->value))){
        return std::pair<node_type*,bool>(link4(k,0,rightmost(),z),true);
      }
      else return link2(k,z,non_unique_index_tag());
    } 
    else{
      node_type* before=position;
      node_type::decrement(before);
      if (!comp(k,key(before->value))&&!comp(key(position->value),k)){
        if(before->right()==0)return std::pair<node_type*,bool>(link4(k,0,before,z),true); 
        else return std::pair<node_type*,bool>(link4(k,position,position,z),true);
      } 
      else return link2(k,z,non_unique_index_tag());
    }
  }

  bool in_place(node_type* x,unique_index_tag)
  {
    node_type* y=x;
    node_type::decrement(y);
    if(y!=header()&&!comp(key(y->value),key(x->value)))return false;

    y=x;
    node_type::increment(y);
    return y==header()||comp(key(x->value),key(y->value));
  }

  bool in_place(node_type* x,non_unique_index_tag)
  {
    node_type* y=x;
    node_type::decrement(y);
    if(y!=header()&&comp(key(x->value),key(y->value)))return false;

    y=x;
    node_type::increment(y);
    return y==header()||!comp(key(y->value),key(x->value));
  }

#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)
  void detach_iterators(node_type* x)
  {
    iterator it=make_iterator(x);
    safe_mode::detach_equivalent_iterators(it);
  }
#endif

#if !defined(BOOST_NO_MEMBER_TEMPLATES)||defined(BOOST_MSVC6_MEMBER_TEMPLATES)
  template<typename LowerBounder>
  const_iterator lower_range(LowerBounder lower)const
  {
    node_type* y=header();
    node_type* z=root();

    while(z){
      if(lower(key(z->value))){
        y=z;
        z=node_type::from_impl(z->left());
      }
      else z=node_type::from_impl(z->right());
    }

    return make_iterator(y);
  }

  const_iterator lower_range(unbounded_type)const
  {
    return begin();
  }

  template<typename UpperBounder>
  const_iterator upper_range(UpperBounder upper)const
  {
    node_type* y=header();
    node_type* z=root();

    while(z){
      if(!upper(key(z->value))){
        y=z;
        z=node_type::from_impl(z->left());
      }
      else z=node_type::from_impl(z->right());
    }

    return make_iterator(y);
  }

  const_iterator upper_range(unbounded_type)const
  {
    return end();
  }

#endif

  key_from_value key;
  key_compare    comp;
};

/* comparison */

template<
  typename KeyFromValue,typename Compare,typename Allocator,
  typename Super,typename TagList,typename Category
>
bool operator==(
  const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& x,
  const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& y)
{
  return x.size()==y.size()&&std::equal(x.begin(),x.end(),y.begin());
}

template<
  typename KeyFromValue,typename Compare,typename Allocator,
  typename Super,typename TagList,typename Category
>
bool operator<(
  const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& x,
  const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& y)
{
  return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}

template<
  typename KeyFromValue,typename Compare,typename Allocator,
  typename Super,typename TagList,typename Category
>
bool operator!=(
  const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& x,
  const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& y)
{
  return !(x==y);
}

template<
  typename KeyFromValue,typename Compare,typename Allocator,
  typename Super,typename TagList,typename Category
>
bool operator>(
  const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& x,
  const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& y)
{
  return y<x;
}

template<
  typename KeyFromValue,typename Compare,typename Allocator,
  typename Super,typename TagList,typename Category
>
bool operator>=(
  const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& x,
  const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& y)
{
  return !(x<y);
}

template<
  typename KeyFromValue,typename Compare,typename Allocator,
  typename Super,typename TagList,typename Category
>
bool operator<=(
  const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& x,
  const index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& y)
{
  return !(x>y);
}

/*  specialized algorithms */

template<
  typename KeyFromValue,typename Compare,typename Allocator,
  typename Super,typename TagList,typename Category
>
void swap(
  index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& x,
  index<KeyFromValue,Compare,Allocator,Super,TagList,Category>& y)
{
  x.swap(y);
}

} /* namespace indexed_sets::detail */

/* index specifiers */

template<typename Arg1,typename Arg2,typename Arg3>
struct unique
{
  typedef typename detail::index_args<Arg1,Arg2,Arg3> index_args;
  typedef typename index_args::tag_list_type          tag_list_type;
  typedef typename index_args::key_from_value_type    key_from_value_type;
  typedef typename index_args::compare_type           compare_type;

  template<typename Super>
  struct node_type
  {
    typedef detail::index_node<Super> type;
  };

  template<typename Allocator,typename Super>
  struct index_class_type
  {
    typedef detail::index<
      key_from_value_type,compare_type,Allocator,
      Super,tag_list_type,detail::unique_index_tag> type;
  };
};

template<typename Arg1,typename Arg2,typename Arg3>
struct non_unique
{
  typedef detail::index_args<Arg1,Arg2,Arg3>       index_args;
  typedef typename index_args::tag_list_type       tag_list_type;
  typedef typename index_args::key_from_value_type key_from_value_type;
  typedef typename index_args::compare_type        compare_type;

  template<typename Super>
  struct node_type
  {
    typedef detail::index_node<Super> type;
  };

  template<typename Allocator,typename Super>
  struct index_class_type
  {
    typedef detail::index<
      key_from_value_type,compare_type,Allocator,
      Super,tag_list_type,detail::non_unique_index_tag> type;
  };
};

} /* namespace indexed_sets */

} /* namespace boost */

#undef BOOST_INDEXED_SET_INDEX_CHECK_INVARIANT

#endif
