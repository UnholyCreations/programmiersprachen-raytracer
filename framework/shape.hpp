#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP
#include <string>
#include "color.hpp"
#include "material.hpp"
#include "hit.hpp"
#include "ray.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
struct Hit;
class Shape
{

public:
	//Constructors
  Shape();//default
  Shape(std::string const& name, Material const& material,int const& type);//User 
  virtual ~Shape();//Destructor
  //Virtual Methods
  virtual double area() const = 0;
  virtual double volume() const = 0;
  virtual std::ostream & print (std::ostream & os) const=0;
  virtual Hit intersect(Ray const& ray) = 0;
  //Const Attributes
  std::string get_name() const;
  glm::mat4 get_worldtrans() const;
  glm::mat4 get_worldtrans_inv() const; 
  int get_type() const; 
  Material get_material() const;

  Ray transformRay(glm::mat4 const& mat,Ray const &ray);
  void ShapeScale(glm::vec3 value);
  void ShapeTranslate(glm::vec3 offset);
  void ShapeRotate(float angle,glm::vec3 axis);
protected:
glm::mat4 m_worldtrans;
glm::mat4 m_worldtrans_inv;
std::string m_name;
Material m_material;
int m_type;
};



std::ostream & operator <<(std::ostream & os, Shape const& s);




#endif