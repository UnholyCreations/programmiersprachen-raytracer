#include "material.hpp"

Material::Material():
    m_name{"no_mat"},
    m_ka{Color{0, 0, 0}},
    m_kd{Color{0, 0, 0}},
    m_ks{Color{0, 0, 0}},
    m_m{0}{}


Material::Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks, float m):
    m_name{name},
    m_ka{ka},
    m_kd{kd},
    m_ks{ks},
    m_m{m}{}

std::ostream& operator<<(std::ostream& ost, Material const& m){
    ost <<"\n"<< "Name:" << m.m_name << "\n ka:" << m.m_ka << "\n kd:" << m.m_kd << "\n ks:" << m.m_ks
       << "\n m:" << m.m_m << "\n";

    return ost;

}