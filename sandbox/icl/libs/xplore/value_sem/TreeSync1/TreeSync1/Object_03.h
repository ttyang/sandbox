#pragma once

#include <string>
#include <iostream>
#include <typeinfo>
#include <boost/smart_ptr/shared_ptr.hpp>

template<class T>
void draw(const T& x, std::ostream& out, size_t pos)
{ 
  out << std::string(pos, ' ') << x << std::endl; 
}

class object 
{
public:
  template<class Model>
  object(const Model& x) : m_object(new model<Model>(x)){ }

  object(const object& x) : m_object(x.m_object->copy()){ }

  object& operator = (const object& x)
  { m_object.reset(x.m_object->copy()); return *this; }

  friend void draw(const object& x, std::ostream& out, size_t pos)
  { 
    x.m_object->draw_(out, pos); 
  }

  friend std::string type_name(const object& x){ return x.m_object->type_name_(); }

private:
  struct concept 
  {   
    virtual ~concept() {}
    virtual concept* copy() = 0;
    virtual void draw_(std::ostream&, size_t)const = 0;
    virtual std::string type_name_()const = 0;
  };

  template<class Model> struct model : concept 
  {
    model( const Model& x) : m_model(x) {}
    concept* copy(){ return new model(*this); }
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
  boost::shared_ptr<concept> m_object;
};


//30:25 operator= via unique_ptr.
//50:10 refactoring: (member) function templates across models
//50:19 refactoring local models structs to a template