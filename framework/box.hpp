
#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP
#include "shape.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <glm/vec3.hpp>
#include <string>
class Box: public Shape
{
private:
  glm::vec3 m_min;
  glm::vec3 m_max;
  glm::vec3 seiten=m_max-m_min;
  double x=seiten.x;
  double y=seiten.y;
  double z=seiten.z;
public:
	//Constructors
	Box (); // default constructor
	Box(std::string const& name,Material const& material,glm::vec3 const& min,glm::vec3 const& max); //user
	~Box(); //destructor
	
	//Function overrides
	double area() const override;
	double volume() const override;
	std::ostream & print (std::ostream & os) const override;
	Hit intersect(Ray const& ray, float distance) override;
	
	//Functions
	glm::vec3 const& get_min() const;
	glm::vec3 const& get_max() const;
};
#endif