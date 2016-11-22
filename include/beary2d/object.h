#pragma once



class Object
{
public:
   int type;

   float x;
   float y;
   float w;
   float h;
   float velocity_x;
   float velocity_y;

   float get_left_edge();
   float get_right_edge();
   float get_top_edge();
   float get_bottom_edge();

   void set_left_edge(float x);
   void set_right_edge(float x);
   void set_top_edge(float y);
   void set_bottom_edge(float y);

   void push(float force_x, float force_y);

   bool collides(Object &other);

   Object();
   virtual ~Object();
};




