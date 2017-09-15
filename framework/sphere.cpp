#include "sphere.hpp"
#include <string>
Sphere::Sphere() : Shape{},m_center{0,0,0},m_radius{1.0}  // default constructor
{//std::cout<< "sphere default constructor\n";
}



Sphere::Sphere(std::string const& name, Material const& material,glm::vec3 const& center,double const& radius)://user constructor
Shape{name,material,1},
m_center{center},
m_radius{radius}
{//std::cout<< "sphere user constructor\n";
}






Sphere::~Sphere()//destructor
{//std::cout<< "sphere destrcutor\n";
};




glm::vec3 Sphere::get_max() const
{
	glm::vec3 max=m_center+glm::vec3{m_radius,m_radius,m_radius};
	glm::vec4 q(max,1.0f);
	glm::vec3 p{m_translate*m_scale*q};
	return p;
}
glm::vec3 Sphere::get_min() const
{
	glm::vec3 min=m_center+glm::vec3{-m_radius,-m_radius,-m_radius};
	glm::vec4 q(min,1.0f);
	glm::vec3 p{m_translate*m_scale*q};
	return p;
}	

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
  	Ray trans_ray=transformRay(m_worldtrans_inv,ray);
    sphere_hit.m_hit = glm::intersectRaySphere(
    trans_ray.m_origin, glm::normalize(trans_ray.m_direction),
     m_center,m_radius, 
     sphere_hit.m_intersect,sphere_hit.m_norm);

    if (sphere_hit.m_hit==true)
    {

    sphere_hit.m_distance = glm::length(trans_ray.m_origin-sphere_hit.m_intersect);
  sphere_hit.m_shape_ptr = this;
  sphere_hit.m_norm=glm::normalize(sphere_hit.m_intersect-m_center);
         glm::mat4 M = glm::transpose(m_worldtrans_inv);
        glm::vec4 n{sphere_hit.m_norm, 0.0f};
        glm::vec3 m(M * n);
		sphere_hit.m_norm = glm::normalize(m);


        glm::vec4 q(sphere_hit.m_intersect,1.0f);
        glm::vec3 p{m_worldtrans*q};
        sphere_hit.m_intersect=p;
        
		/*
		   glm::vec4 q(sphere_hit.m_intersect,1.0f);
        glm::vec3 p{m_worldtrans_inv*q};
        sphere_hit.m_intersect=p;
		*/
  }

	

	/*
	float a=glm::dot(ray.m_direction,ray.m_direction);
	float b=2.0f*glm::dot(ray.m_direction,ray.m_origin-m_center);
	float c=glm::dot(ray.m_origin-m_center,ray.m_origin-m_center)-m_radius*m_radius;
	
	float d = b*b - 4.0f*a*c;
	
	if (d>0)
	{
		float inverse=1/(2*a);
		float t1=(-b - sqrt(d))*inverse;
		float t2=(-b + sqrt(d))*inverse;
		float tfinal=std::min(t1,t2);



		sphere_hit.m_hit=true;
		sphere_hit.m_shape_ptr = this;
		sphere_hit.m_intersect=ray.m_origin+t1*glm::normalize(ray.m_direction);
		sphere_hit.m_distance = glm::distance(ray.m_origin, sphere_hit.m_intersect);
		sphere_hit.m_norm=glm::normalize(sphere_hit.m_intersect-m_center);

	}
*/
    return sphere_hit;
    
}


