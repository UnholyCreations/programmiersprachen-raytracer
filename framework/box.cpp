#include "box.hpp"
#include <string>
Box::Box() : Shape{}, m_min{0,0,0},m_max{1,1,1} // default constructor
{}
Box::Box(std::string const& name,Material const& material,glm::vec3 const& min,glm::vec3 const& max)://user constructor
Shape{name,material},
m_min{min},
m_max{max}
{}

Box::~Box() {}; //desturctor



glm::vec3 const& Box::get_min() const
{
	return m_min;
}
glm::vec3 const& Box::get_max() const
{
	return m_max;
}	

double Box::area() const
{
	return (x*y+x*z+z*y)*2;
}
double Box::volume() const
{
	return x*y*z;
}

std::ostream & Box::print(std::ostream & os) const{

Shape::print(os);

return os<<"Box: \n"<<"min coordinates:"<<m_min.x<<" "<<m_min.y<<" "<<m_min.z<<"\n"
<<"max coordinates:"<<m_max.x<<" "<<m_max.y<<" "<<m_max.z<<"\n";

}
//https://people.csail.mit.edu/amy/papers/box-jgt.pdf
//DID WE MISS SMTH?CONSTRUCTORS KILL BRAINCELLS...Struct/class creations functions more...
//bool hit, float distance, glm::vec3 const& intersect,glm::vec3 const& norm (missing), Shape* shape_ptr
Hit Box::intersect(Ray const& ray ,float& t)
{

    Hit box_hit;

    float tx1 = (m_min.x-ray.m_origin.x)/ray.m_direction.x;
    float tx2 = (m_max.x-ray.m_origin.x)/ray.m_direction.x;
 
    float tfarx=std::max(tx1, tx2);
    float tnearx=std::min(tx1, tx2);

    float ty1 = (m_min.y-ray.m_origin.y)/ray.m_direction.y;
    float ty2 = (m_max.y-ray.m_origin.y)/ray.m_direction.y;
  
    float tfary=std::max(ty1, ty2);
    float tneary=std::min(ty1, ty2);

    float tz1 = (m_min.z-ray.m_origin.z)/ray.m_direction.z;
    float tz2 = (m_max.z-ray.m_origin.z)/ray.m_direction.z;

    float tfarz=std::max(tz1, tz2);
    float tnearz=std::min(tz1, tz2);

    float tfar=std::max(tfarx, tfary);
    float tnear=std::min(tnearx, tneary);

    box_hit.m_distance = sqrt(ray.m_direction.x*ray.m_direction.x+ray.m_direction.y*ray.m_direction.y+ray.m_direction.z*ray.m_direction.z); 
    box_hit.m_intersect = glm::vec3{tnear*ray.m_direction.x, tnear*ray.m_direction.y, tnear*ray.m_direction.z}+ray.m_origin;
    box_hit.m_shape_ptr = this;
   //bool hit:
   if(tfar<tnear)
   {
        box_hit.m_hit=false;
        return box_hit;
   }
 
   tfar=std::min(tfar, tfarz);
   tnear=std::max(tnear, tnearz);

   if((tfar<0) || (tfar<tnear))
   {
       box_hit.m_hit=false;
       return box_hit;
   }

   box_hit.m_hit=true;
   return box_hit;
}