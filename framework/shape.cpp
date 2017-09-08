#include "shape.hpp"
//constructors
Shape::Shape(): m_name {"Default Shape"}, m_material{},m_type{-1}  {//std::cout<< "shape default constructor\n";
} //Default

Shape::Shape(std::string const&  name, Material const& material,int const& type): //User 
	m_name{name},
m_material{material},
m_type{type},
  m_worldtrans{
  1.0f},
  m_worldtrans_inv{glm::inverse(m_worldtrans)}
 {}
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

glm::mat4 Shape::get_worldtrans() const
{
	return m_worldtrans;
}

glm::mat4 Shape::get_worldtrans_inv() const
{
	return m_worldtrans_inv;
}

Ray Shape::transformRay(glm::mat4 const& mat,Ray const &ray )
	{
	  glm::vec4 temp_org {ray.m_origin, 1.0f};
	  glm::vec4 temp_dir {ray.m_direction, 0.0f};
	  glm::vec3 new_org {mat * temp_org };
	  glm::vec3 new_dir {mat * temp_dir};
	  Ray NewRay{new_org, glm::normalize(new_dir)};
	  return NewRay;	
	}
void Shape::ShapeScale(glm::vec3 value)
{
glm::mat4 ShapeScale;
if (value.z==1) {value.z=-1.0f;}  
ShapeScale[0] = glm::vec4 {value.x,0.0f,0.0f,0.0f};
ShapeScale[1] = glm::vec4 {0.0f,value.y,0.0f,0.0f};
ShapeScale[2] = glm::vec4 {0.0f,0.0f,value.z,0.0f};
ShapeScale[3] = glm::vec4 {0.0f,0.0f,0.0f,1.0f};
m_worldtrans=m_worldtrans*ShapeScale;
m_worldtrans_inv=glm::inverse(m_worldtrans);
}

void Shape::ShapeRotate(float angle,glm::vec3 axis)
{
  angle=angle*M_PI/180;
  //https://math.stackexchange.com/questions/134741/a-4x4-homogeneous-matrix-for-a-90-degree-rotation-about-y-axis
  glm::mat4 ShapeRotate;
  if (axis.x!=0)
  {
  ShapeRotate[0] = glm::vec4 {1.0, 0.0,0.0,0.0};
  ShapeRotate[1] = glm::vec4 {0, cos(angle),sin(angle),0.0};
  ShapeRotate[2] = glm::vec4 {0, -sin(angle),cos(angle),0.0};
  ShapeRotate[3] = glm::vec4 {0.0, 0.0,0.0,1.0};
  m_worldtrans=m_worldtrans*ShapeRotate;
  m_worldtrans_inv=glm::inverse(m_worldtrans);
  }
  if (axis.y!=0)
  {
  ShapeRotate[0] = glm::vec4 {cos(angle), 0.0, -sin(angle), 0.0};
  ShapeRotate[1] = glm::vec4 {0.0, 1.0, 0.0, 0.0};
  ShapeRotate[2] = glm::vec4 {sin(angle), 0.0, cos(angle), 0.0};
  ShapeRotate[3] = glm::vec4 {0.0, 0.0, 0.0, 1.0};
  m_worldtrans=m_worldtrans*ShapeRotate;
  m_worldtrans_inv=glm::inverse(m_worldtrans);
  }
  if (axis.z!=0)
  {
  ShapeRotate[0] = glm::vec4 {cos(angle), -sin(angle), 0.0, 0.0};
  ShapeRotate[1] = glm::vec4 {sin(angle), cos(angle), 0.0, 0.0};
  ShapeRotate[2] = glm::vec4 {0.0, 0.0, 1.0, 0.0};
  ShapeRotate[3] = glm::vec4 {0.0, 0.0, 0.0, 1.0};  
  m_worldtrans=m_worldtrans*ShapeRotate;
  m_worldtrans_inv=glm::inverse(m_worldtrans);
  }

}

void Shape::ShapeTranslate(glm::vec3 offset)
{
glm::mat4 ShapeTranslate;
ShapeTranslate[0] = glm::vec4 {1.0f,0.0f,0.0f,0.0f};
ShapeTranslate[1] = glm::vec4 {0.0f,1.0f,0.0f,0.0f};
ShapeTranslate[2] = glm::vec4 {0.0f,0.0f,1.0f,0.0f};
ShapeTranslate[3] = glm::vec4 {offset.x,offset.y,offset.z,1.0f};
m_worldtrans=m_worldtrans*ShapeTranslate;
m_worldtrans_inv=glm::inverse(m_worldtrans);
}