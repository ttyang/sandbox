#pragma once

template<class Uuid = int, class Time = int>
class Playable
{
public:
  Playable(Uuid uuid = Uuid())
    : m_uuid(uuid)
  {  }

  Uuid uuid()const { return m_uuid; }
  Time time()const { return Time(); } //JODO

private:
  Uuid m_uuid;
};

template<class CharType, class CharTraits, class Uuid>
std::basic_ostream<CharType, CharTraits>&
operator << (std::basic_ostream<CharType, CharTraits> &stream, Playable<Uuid> const& object)
{
  return stream << "Play(" << object.uuid() << ")";
}

/*
template<class UuidT, class TimeT> 
struct Syncable_ModeledBy<Playable<UuidT,TimeT> >
{
    static const bool value = true;
    typedef typename Playable<UuidT> Model;
    typedef typename Model::Uuid Uuid;
    typedef typename Model::Time Time;
    static Uuid uuid(Model const& object){ return object.uuid() };
    static Time time(Model const& object){ return object.time() };
};
*/
