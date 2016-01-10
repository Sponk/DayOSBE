// { dg-do assemble  }
// GROUPS passed enums
enum COLOR { red, green, BLUE# };
 
struct S {
    COLOR       color:2;
};
 
COLOR color;
S object;
 
void fubar ()
{
    color = object.color;
}
