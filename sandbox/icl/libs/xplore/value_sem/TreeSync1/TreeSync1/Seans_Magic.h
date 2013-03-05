#pragma once

#include <memory>
#include <string>
#include <iostream>

template<class T>
void draw(const T& x, std::ostream& out, size_t pos)
{ out << std::string(pos, ' ') << x << std::endl; }

class Object 
{
public:
  template<class Model>
  Object(Model const& value) : m_value(new Concept_ModeledBy<Model>(value)){ }

  Object(Object const& value) : m_value(value.m_value->copy()){ }
  Object(Object&& value): m_value(std::move(value.m_value)){};
  Object& operator = (Object value){ m_value = std::move(value.m_value); return *this; }

  friend void draw(const Object& value, std::ostream& out, size_t pos)
  { value.m_value->draw_(out, pos); }

private:
  struct Concept 
  {   
    virtual ~Concept() {}
    virtual Concept* copy() = 0;
    virtual void draw_(std::ostream&, size_t)const = 0;
  };

  template<class Model> struct Concept_ModeledBy : Concept 
  {
    Concept_ModeledBy(Model const& val) : m_model(val) {}
    Concept* copy(){ return new Concept_ModeledBy(*this); }
    void draw_(std::ostream& out, size_t pos)const{ draw(m_model, out, pos); }

    Model m_model;
  };

private:
  std::unique_ptr<Concept> m_value;
};


//  30:13 unsave operator= using delete / new. (defects)
//  30:25 operator= via unique_ptr and reset.
//  34:15 rewrite assignment using pass by value and move. 
//  34:48 Pass sink arguments by value.
//  39:58 Introducing move ctor.
//  50:10 refactoring: (member) function templates across models
//  50:19 refactoring local models structs to a template
//1:06:00 Undo history and copy_on_write

