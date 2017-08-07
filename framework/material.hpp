#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include <string>

struct Material{

    std::string m_name;
    Color m_ka;
    Color m_kd;
    Color m_ks;
    float m_m;

    Material();
    Material(std::string const& nm, Color const& ka, Color const& kd, Color const& ks, float m);

    friend std::ostream& operator<<(std::ostream& ost, Material const& m);
    
};



#endif