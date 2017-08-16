#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <glm/glm.hpp>
#include "color.hpp"


class Light{

public:
  Light();
  Light(std::string const& name, glm::vec3 const& pos, Color const& color,float brightness);
  ~Light();
  void print();
  std::string m_name;
  glm::vec3 m_pos;
  Color m_color;
  float m_brightness;
};

#endif
