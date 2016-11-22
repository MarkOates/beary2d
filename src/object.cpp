



#include <beary2d/object.h>




Object::Object()
   : x(0)
   , y(0)
   , w(0)
   , h(0)
   , velocity_x(0)
   , velocity_y(0)
{}




Object::~Object()
{}




float Object::get_left_edge() { return x; }




float Object::get_right_edge() { return x + w; }




float Object::get_top_edge() { return y; }




float Object::get_bottom_edge() { return y + h; }




void Object::set_left_edge(float x) { this->x = x; }




void Object::set_right_edge(float x) { this->x = x - w; }




void Object::set_top_edge(float y) { this->y = y; }




void Object::set_bottom_edge(float y) { this->y = y - h; }




void Object::push(float force_x, float force_y)
{
   velocity_x += force_x;
   velocity_y += force_y;
}




bool Object::collides(Object &other)
{
   if (other.x > x+w) return false;
   if (other.y > y+h) return false;
   if (x > other.x+other.w) return false;
   if (y > other.y+other.h) return false;
   return true;
}




