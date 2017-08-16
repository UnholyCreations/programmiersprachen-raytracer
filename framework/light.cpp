#include "light.hpp"
//Light(std::string const& name, glm::vec3 const& pos, Color const& color,int brightness)


Light::Light():
m_name{"Default Light"},
m_pos{-2,2,-2},
m_color{1,0,0},
m_brightness{0.5}
{};

Light::Light(std::string const& name, glm::vec3 const& pos, Color const& color,float brightness):
m_name{name},
m_pos{pos},
m_color{color},
m_brightness{brightness}
 {};

Light::~Light(){};

void Light::print() 
{
        std::cout<<"\nname:"<<m_name<<"\n";
        std::cout<<"pos:"<<m_pos.x<<" "<<m_pos.y<<" "<<m_pos.z<<"\n";
        std::cout<<"col:"<<m_color.r<<" "<<m_color.g<<" "<<m_color.b<<"\n";
        std::cout<<"brightness:"<<m_brightness<<"\n";
}
