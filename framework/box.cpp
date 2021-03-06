#include "box.hpp"
#include <string>
Box::Box() : Shape{}, m_min{0,0,0},m_max{1,1,1} // default constructor
{}
Box::Box(std::string const& name,Material const& material,glm::vec3 const& kord1,glm::vec3 const& kord2)://user constructor
Shape{name,material,0},
m_min{std::min(kord1.x,kord2.x),std::min(kord1.y,kord2.y),std::min(kord1.z,kord2.z)},
m_max{std::max(kord1.x,kord2.x),std::max(kord1.y,kord2.y),std::max(kord1.z,kord2.z)}
{
}

Box::~Box() {}; //desturctor



glm::vec3 Box::get_min() const
{  
glm::vec4 q(m_min,1.0f);
glm::vec3 p{m_translate*m_scale*q};
//p.x+=p.x*(float(m_BBOXangle_x)*0.066666667f);
//p.y+=p.y*(float(m_BBOXangle_y)*0.066666667f);
//p.z+=p.z*(float(m_BBOXangle_z)*0.066666667f);

	return p;
}
glm::vec3 Box::get_max() const
{
glm::vec4 q(m_max,1.0f);
glm::vec3 p{m_translate*m_scale*q};

//p.x+=p.x*(float(m_BBOXangle_x)*0.066666667f);
//p.y+=p.y*(float(m_BBOXangle_y)*0.066666667f);
//p.z+=p.z*(float(m_BBOXangle_z)*0.066666667f);
  return p;
}	

double Box::area() const
{
  glm::vec3 seiten=m_max-m_min;
  double x=seiten.x;
  double y=seiten.y;
  double z=seiten.z;
	return (x*y+x*z+z*y)*2;
}
double Box::volume() const
{
  glm::vec3 seiten=m_max-m_min;
  double x=seiten.x;
  double y=seiten.y;
  double z=seiten.z;
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
    tmin = (m_min.x - trans_ray.m_origin.x) * trans_ray.m_inverse.x;
    tmax = (m_max.x - trans_ray.m_origin.x) * trans_ray.m_inverse.x;
}
else {
    tmin = (m_max.x - trans_ray.m_origin.x) * trans_ray.m_inverse.x;
    tmax = (m_min.x - trans_ray.m_origin.x) * trans_ray.m_inverse.x;
}
if (trans_ray.m_direction.y >= 0) {
    tymin = (m_min.y - trans_ray.m_origin.y) * trans_ray.m_inverse.y;
    tymax = (m_max.y - trans_ray.m_origin.y) * trans_ray.m_inverse.y;
} else {
    tymin = (m_max.y - trans_ray.m_origin.y) * trans_ray.m_inverse.y;
    tymax = (m_min.y - trans_ray.m_origin.y) * trans_ray.m_inverse.y;
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
    tzmin = (m_min.z - trans_ray.m_origin.z) * trans_ray.m_inverse.z;
    tzmax = (m_max.z - trans_ray.m_origin.z) * trans_ray.m_inverse.z;
} else {
    tzmin = (m_max.z - trans_ray.m_origin.z) * trans_ray.m_inverse.z;
    tzmax = (m_min.z - trans_ray.m_origin.z) * trans_ray.m_inverse.z;
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
        glm::mat4 M = glm::transpose(m_worldtrans_inv);
        glm::vec4 n{box_hit.m_norm, 0.0f};
        glm::vec3 m(M * n);
        box_hit.m_norm = glm::normalize(m);
        
        glm::vec4 q(box_hit.m_intersect,1.0f);
        glm::vec3 p{m_worldtrans*q};
        box_hit.m_intersect=p;
        
return box_hit;
}