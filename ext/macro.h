#ifndef EXT__MACRO_H
#define EXT__MACRO_H


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

#endif