#pragma once

#include <string>
#include <iostream>
#include <typeinfo>
#include <memory>

template<class T>
void draw(const T& x, std::ostream& out, size_t pos)
{ 
  out << std::string(pos, ' ') << x << std::endl; 
}

class object 
{
public:
  template<class Model>
  object(Model const& value) : m_value(new model<Model>(value)){ }

  object(object const& value) : m_value(value.m_value->copy()){ }

  object(object&& value): m_value(std::move(value.m_value)){};

  object& operator = (object value)
  { m_value = std::move(value.m_value); return *this; }

  friend void draw(const object& value, std::ostream& out, size_t pos)
  { 
    value.m_value->draw_(out, pos); 
  }

  friend std::string type_name(object const& value){ return value.m_value->type_name_(); }

  friend bool is_less(object const& lhs, object const& rhs)
  {
    return lhs.m_value->is_less_(*rhs.m_value->as_model()); 
  }

private:
  struct concept 
  {   
    virtual ~concept() {}
    virtual concept* copy() = 0;
    virtual concept* as_model() = 0;

    virtual bool is_less_(concept const& rhs)const = 0;
    virtual void draw_(std::ostream&, size_t)const = 0;
    virtual std::string type_name_()const = 0;

  };

  template<class Model> struct model : concept 
  {
    model(Model const& val) : m_model(val) {}
    concept* copy(){ return new model(*this); }

    concept* as_model() { return this; }

    bool is_less_(concept const& rhs)const 
    { 
     //return is_less(m_model, dynamic_cast<model const&>(rhs).m_model);
     return m_model < dynamic_cast<model const&>(rhs).m_model;
    }

    void draw_(std::ostream& out, size_t pos)const
    { 
      //out << std::string(pos, ' ') << "{ " << type_name() << " }"; 
      draw(m_model, out, pos); 
    }

    //std::string type_name()const { return typeid(m_model).name(); }
    std::string type_name_()const{ return type_name(m_model); }

    Model m_model;
  };

private:
  std::unique_ptr<concept> m_value;
};

//                                     friend enabled gate to polymorphic objects
bool operator < (object const& lhs, object const& rhs){ return is_less(lhs, rhs); }


//  30:13 unsave operator= using delete / new. (defects)
//  30:25 operator= via unique_ptr and reset.
//  34:15 rewrite assignment using pass by value and move. 
//  34:48 Pass sink arguments by value.
//  39:58 Introducing move ctor.
//  50:10 refactoring: (member) function templates across models
//  50:19 refactoring local models structs to a template
//1:06:00 Undo history and copy_on_write

