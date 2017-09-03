#include "sphere.hpp"
#include <string>
Sphere::Sphere() : Shape{},m_center{0,0,0},m_radius{1.0}  // default constructor
{//std::cout<< "sphere default constructor\n";
}



Sphere::Sphere(std::string const& name, Material const& material,glm::vec3 const& center,double const& radius)://user constructor
Shape{name,material},
m_center{center},
m_radius{radius}
{//std::cout<< "sphere user constructor\n";
}






Sphere::~Sphere()//destructor
{//std::cout<< "sphere destrcutor\n";
};






glm::vec3 const& Sphere::get_center() const{

	return m_center;
}

double const& Sphere::get_radius() const{

	return m_radius;
}

//area
double Sphere::area() const
{
		return 12.56*m_radius*m_radius;
	}

//volume
double Sphere::volume() const
{
		return m_radius*m_radius*m_radius*4.186;
}
std::ostream & Sphere::print(std::ostream & os) const{

Shape::print(os);

return os<<"\n"<<"Sphere: \n"<<"center:"<<m_center.x<<" "<<m_center.y<<" "<<m_center.z<<"\n"
<<"radius:"<<m_radius<<"\n";
}


Hit Sphere::intersect(Ray const& ray)
{
	
 	Hit sphere_hit;   
 	
    sphere_hit.m_hit = glm::intersectRaySphere(
    ray.m_origin, glm::normalize(ray.m_direction),
     m_center,m_radius, 
     sphere_hit.m_intersect,sphere_hit.m_norm);

    if (sphere_hit.m_hit==true)
    {

  	sphere_hit.m_distance = glm::distance(sphere_hit.m_intersect,ray.m_origin);
	sphere_hit.m_shape_ptr = this;
	sphere_hit.m_norm=glm::normalize(m_center-sphere_hit.m_intersect);
		
	}
	

	/*
	float a=glm::dot(ray.m_direction,ray.m_direction);
	float b=2.0f*glm::dot(ray.m_direction,ray.m_origin-m_center);
	float c=glm::dot(ray.m_origin-m_center,ray.m_origin-m_center)-m_radius*m_radius;
	
	float d = b*b - 4.0f*a*c;
	
	if (d>0)
	{
		float t1=(-b - sqrt(d))/(2*a);
		sphere_hit.m_hit=true;
		sphere_hit.m_shape_ptr = this;
		sphere_hit.m_intersect=ray.m_origin+t1*ray.m_direction;
		sphere_hit.m_distance = glm::distance(ray.m_origin, sphere_hit.m_intersect);
		sphere_hit.m_norm=glm::normalize(m_center-sphere_hit.m_intersect);
	}
	*/
    return sphere_hit;
    
}


