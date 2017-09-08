#include "shape.hpp"
//constructors
Shape::Shape(): m_name {"Default Shape"}, m_material{},m_type{-1}  {//std::cout<< "shape default constructor\n";
} //Default

Shape::Shape(std::string const&  name, Material const& material,int const& type): //User 
	m_name{name},
m_material{material},
m_type{type},
  m_worldtrans{
  1.0f,0.0f,0.0f,0.0f,
  0.0f,1.0f,0.0f,0.0f,
  0.0f,0.0f,1.0f,0.0f,
  0.0f,0.0f,0.0f,1.0f},
  m_worldtrans_inv{glm::inverse(m_worldtrans)}
 {//std::cout<< "shape user constructor\n";
}
Shape::~Shape() {//std::cout<< "shape destructor\n";
} //destuctor



std::ostream & Shape::print(std::ostream & os) const{
	os << m_name << std::endl << m_material ; 
	return os; 
}

std::ostream & operator <<(std::ostream & os, Shape const& s){
	return s.print(os);
}

std::string Shape::get_name() const
{
	return m_name;
}

Material Shape::get_material() const
{
	return m_material;
}
int Shape::get_type() const
{
	return m_type;
}
Ray Shape::transformRay(glm::mat4 const& mat,Ray const &ray )
	{
	  glm::vec4 temp_org {ray.m_origin, 1.0f};
	  glm::vec4 temp_dir {ray.m_direction, 0.0f};
	  glm::vec3 new_org {mat * temp_org };
	  glm::vec3 new_dir {mat * temp_dir};
	  Ray NewRay{new_org, new_dir};
	  return NewRay;	
	}
void Shape::ShapeScale(float value)
{
glm::mat4 ShapeScale;  
ShapeScale[0] = glm::vec4 {value,0.0f,0.0f,0.0f};
ShapeScale[1] = glm::vec4 {0.0f,value,0.0f,0.0f};
ShapeScale[2] = glm::vec4 {0.0f,0.0f,value,0.0f};
ShapeScale[3] = glm::vec4 {0.0f,0.0f,0.0f,1.0f};
m_worldtrans=m_worldtrans*ShapeScale;
m_worldtrans_inv=glm::inverse(m_worldtrans);
}