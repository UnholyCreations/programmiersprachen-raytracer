#include "box.hpp"
#include <string>
Box::Box() : Shape{}, m_min{0,0,0},m_max{1,1,1} // default constructor
{}
Box::Box(std::string const& name,Material const& material,glm::vec3 const& min,glm::vec3 const& max)://user constructor
Shape{name,material,0},
m_kord1{min},
m_kord2{max}
{
if (m_kord1.x>m_kord2.x) {m_max.x=m_kord1.x; m_min.x=m_kord2.x;} else {m_max.x=m_kord2.x; m_min.x=m_kord1.x;};
if (m_kord1.y>m_kord2.y) {m_max.y=m_kord1.y; m_min.y=m_kord2.y;} else {m_max.y=m_kord2.y; m_min.y=m_kord1.y;};
if (m_kord1.z>m_kord2.z) {m_max.z=m_kord1.z; m_min.z=m_kord2.z;} else {m_max.z=m_kord2.z; m_min.z=m_kord1.z;};

}

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
//https://tavianator.com/fast-branchless-raybounding-box-intersections-part-2-nans/#cite-1
//DID WE MISS SMTH?CONSTRUCTORS KILL BRAINCELLS...Struct/class creations functions more...
//bool hit, float distance, glm::vec3 const& intersect,glm::vec3 const& norm (missing), Shape* shape_ptr
Hit Box::intersect(Ray const& ray)
{
Hit box_hit;
Ray trans_ray=transformRay(m_worldtrans_inv,ray);
float tmin, tmax, tymin, tymax, tzmin, tzmax;
if (trans_ray.m_direction.x >= 0) {
    tmin = (m_min.x - trans_ray.m_origin.x) / trans_ray.m_direction.x;
    tmax = (m_max.x - trans_ray.m_origin.x) / trans_ray.m_direction.x;
}
else {
    tmin = (m_max.x - trans_ray.m_origin.x) / trans_ray.m_direction.x;
    tmax = (m_min.x - trans_ray.m_origin.x) / trans_ray.m_direction.x;
}
if (trans_ray.m_direction.y >= 0) {
    tymin = (m_min.y - trans_ray.m_origin.y) / trans_ray.m_direction.y;
    tymax = (m_max.y - trans_ray.m_origin.y) / trans_ray.m_direction.y;
} else {
    tymin = (m_max.y - trans_ray.m_origin.y) / trans_ray.m_direction.y;
    tymax = (m_min.y - trans_ray.m_origin.y) / trans_ray.m_direction.y;
}
if ((tmin > tymax) || (tymin > tmax)) {
  box_hit.m_hit=false;
    return box_hit;
}
if (tymin > tmin) {
    tmin = tymin;
}
if (tymax < tmax) {
    tmax = tymax;
}
if (trans_ray.m_direction.z >= 0) {
    tzmin = (m_min.z - trans_ray.m_origin.z) / trans_ray.m_direction.z;
    tzmax = (m_max.z - trans_ray.m_origin.z) / trans_ray.m_direction.z;
} else {
    tzmin = (m_max.z - trans_ray.m_origin.z) / trans_ray.m_direction.z;
    tzmax = (m_min.z - trans_ray.m_origin.z) / trans_ray.m_direction.z;
}
if ((tmin > tzmax) || (tzmin > tmax)) {
  box_hit.m_hit=false;
    return box_hit;
}
if (tzmin > tmin) {
    tmin = tzmin;
}
if (tzmax < tmax) {
    tmax = tzmax;
}

if (tmax > std::max(tmin, 0.0f))
{
  box_hit.m_hit=true;
  box_hit.m_shape_ptr = this;
  
  box_hit.m_intersect=trans_ray.m_origin+glm::normalize(trans_ray.m_direction)*tmin; 
   box_hit.m_distance=glm::length(trans_ray.m_origin-box_hit.m_intersect);
   if ((box_hit.m_intersect.x)==Approx(m_max.x))
        {
           box_hit.m_norm=glm::vec3(1.0f,0.0f,0.0f);  
        }else if ((box_hit.m_intersect.x)==Approx(m_min.x))
        {
          box_hit.m_norm=glm::vec3(-1.0f,0.0f,0.0f); 
        }else if ((box_hit.m_intersect.y)==Approx(m_max.y))
        {
          box_hit.m_norm=glm::vec3(0.0f,1.0f,0.0f);
        }else if ((box_hit.m_intersect.y)==Approx(m_min.y))
        {
          box_hit.m_norm=glm::vec3(0.0f,-1.0f,0.0f); 
        }else if ((box_hit.m_intersect.z)==Approx(m_max.z))
        {
          box_hit.m_norm=glm::vec3(0.0f,0.0f,1.0f); 
        }else
        {
          box_hit.m_norm=glm::vec3(0.0f,0.0f,-1.0f);
        }    
}


return box_hit;
}