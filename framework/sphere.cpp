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

bool Sphere::intersect(Ray const& ray, float& distance)
{
    
   auto norm_direction = glm::normalize(ray.direction);
    auto result = glm::intersectRaySphere(ray.origin, norm_direction, m_center, m_radius * m_radius, distance);
    return result;
    
}