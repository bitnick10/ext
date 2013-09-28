#ifndef EXT__MACRO_H
#define EXT__MACRO_H

#define NS_EXT_BEGIN namespace ext {
#define NS_EXT_END }

#define error()   

#define PRIVATE_FILED_PUBLIC_PROPERTY(type, name, getter, setter)\
private: type name;\
public:  type getter() const { return this->name; }\
public:  void setter(type value){ this->name = value; }

#define PROTECTED_FILED_PUBLIC_PROPERTY(type, name, getter, setter)\
protected: type name;\
public:  type getter() const { return this->name; }\
public:  void setter(type value){ this->name = value; }

#define PRIVATE_FILED_PUBLIC_GETTER(type, name, getter)\
private: type name;\
public:  type getter() const { return this->name; }

#define PROTECTED_FILED_PUBLIC_GETTER(type, name, getter)\
protected: type name;\
public:  type getter() const { return this->name; }

#define FOR(times) for(int i=0;i<times;i++)

#endif