
#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>
#include "ray.hpp"
#include "hit.hpp"
#include <string>
class Sphere: public Shape
{
protected:
  glm::vec3 m_center;
  float m_radius;
public:
	//Constructors
	Sphere(); // default constructor
	Sphere(std::string const& name, Material const& material,glm::vec3 const& center,double const& radius); //user
	~Sphere();//destructor
	//Function Overrides
	double area() const override;
	double volume() const override;
	glm::vec3 get_min() const override;
	glm::vec3 get_max() const override;
	std::ostream & print (std::ostream & os) const override;
	Hit intersect(Ray const& ray) override;

	//Functions
	double const& get_radius() const; 
	glm::vec3 const& get_center() const; 
};


#endif