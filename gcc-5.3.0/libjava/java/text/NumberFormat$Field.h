
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __java_text_NumberFormat$Field__
#define __java_text_NumberFormat$Field__

#pragma interface

#include <java/text/Format$Field.h>
#include <gcj/array.h>

extern "Java"
{
  namespace java
  {
    namespace text
    {
        class NumberFormat$Field;
    }
  }
}

class java::text::NumberFormat$Field : public ::java::text::Format$Field
{

  NumberFormat$Field();
public: // actually protected
  NumberFormat$Field(::java::lang::String *);
  virtual ::java::lang::Object * readResolve();
public: // actually package-private
  static const jlong serialVersionUID = 7494728892700160890LL;
public:
  static ::java::text::NumberFormat$Field * INTEGER;
  static ::java::text::NumberFormat$Field * FRACTION;
  static ::java::text::NumberFormat$Field * EXPONENT;
  static ::java::text::NumberFormat$Field * DECIMAL_SEPARATOR;
  static ::java::text::NumberFormat$Field * SIGN;
  static ::java::text::NumberFormat$Field * GROUPING_SEPARATOR;
  static ::java::text::NumberFormat$Field * EXPONENT_SYMBOL;
  static ::java::text::NumberFormat$Field * PERCENT;
  static ::java::text::NumberFormat$Field * PERMILLE;
  static ::java::text::NumberFormat$Field * CURRENCY;
  static ::java::text::NumberFormat$Field * EXPONENT_SIGN;
private:
  static JArray< ::java::text::NumberFormat$Field * > * allFields;
public:
  static ::java::lang::Class class$;
};

#endif // __java_text_NumberFormat$Field__
