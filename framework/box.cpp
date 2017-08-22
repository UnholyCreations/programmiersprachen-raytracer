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
//https://tavianator.com/fast-branchless-raybounding-box-intersections-part-2-nans/#cite-1
//DID WE MISS SMTH?CONSTRUCTORS KILL BRAINCELLS...Struct/class creations functions more...
//bool hit, float distance, glm::vec3 const& intersect,glm::vec3 const& norm (missing), Shape* shape_ptr
Hit Box::intersect(Ray const& ray)
{
Hit box_hit;
float tmin = -INFINITY, tmax = INFINITY;

//stepX
float t1=(m_min.x-ray.m_origin.x)*ray.m_inverse.x;
float t2=(m_max.x-ray.m_origin.x)*ray.m_inverse.x;
tmin = std::max(tmin, std::min(t1, t2));
tmax = std::min(tmax, std::max(t1, t2));
//stepY
t1=(m_min.y-ray.m_origin.y)*ray.m_inverse.y;
t2=(m_max.y-ray.m_origin.y)*ray.m_inverse.y;
tmin = std::max(tmin, std::min(t1, t2));
tmax = std::min(tmax, std::max(t1, t2));
//stepZ
t1=(m_min.z-ray.m_origin.z)*ray.m_inverse.z;
t2=(m_max.z-ray.m_origin.z)*ray.m_inverse.z;
tmin = std::max(tmin, std::min(t1, t2));
tmax = std::min(tmax, std::max(t1, t2));
if (tmax > std::max(tmin, 0.0f))
{
  box_hit.m_hit=true;
  box_hit.m_shape_ptr = this;
  box_hit.m_distance = sqrt((tmin*tmin)*(ray.m_direction.x*ray.m_direction.x+ray.m_direction.y*ray.m_direction.y+ray.m_direction.z*ray.m_direction.z));
  box_hit.m_intersect=glm::vec3{tmin*ray.m_direction.x, tmin*ray.m_direction.y, tmin*ray.m_direction.z}+ray.m_origin;
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