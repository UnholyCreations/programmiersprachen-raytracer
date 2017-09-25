
#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP
#include "shape.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <glm/glm.hpp>
#include <string>
#include <cmath>
#include <catch.hpp>
#include <algorithm>
class Box: public Shape
{
private:
  glm::vec3 m_min;
  glm::vec3 m_max;

public:
	//Constructors
	Box (); // default constructor
	Box(std::string const& name,Material const& material,glm::vec3 const& min,glm::vec3 const& max); //user
	~Box(); //destructor
	
	//Function overrides
	double area() const override;
	double volume() const override;
	std::ostream & print (std::ostream & os) const override;
	Hit intersect(Ray const& ray) override;
	glm::vec3 get_min() const override;
	glm::vec3 get_max() const override;
};
#endif