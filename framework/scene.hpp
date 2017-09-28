#ifndef SCENE_HPP
#define SCENE_HPP
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "light.hpp"
#include <map>
#include <iostream>
#include <ostream>
#include <string>
#include <memory>
#include <vector>
struct Scene
{
    std::string file_name;
    unsigned int x_resolution;
    unsigned int y_resolution;
    float dof_focal=0.0f;
    Camera SceneCamera;
	std::map<std::string,Material> MaterialMap;
	std::vector<std::shared_ptr<Shape>> ShapeVector;
    std::vector<std::shared_ptr<Light>> LightVector;
    Color SceneAmbience{0,0,0};
	void Print_Shapes()
	{
	for (int i=0;i<ShapeVector.size();i++) //if i dont mess the indices after a month pause its not me... :D
        {   

        	(*ShapeVector[i]).print(std::cout);

        };
    }
    void Print_Materials()
    {
        //for (const auto &p : m) 
        for (auto &i: MaterialMap)
        {
        std::cout<<i.second;
        }  
    }
    void Print_Camera()
    {
        SceneCamera.print();
    }
    void Print_Focal()
    {
        std::cout<<"DOF focal:"<<dof_focal<<"\n";
    }
    void Print_Lights()
    {
    for (int i=0;i<LightVector.size();i++) //if i dont mess the indices after a month pause its not me... :D
    {   

    (*LightVector[i]).print();

     };
    }

    
    void Print_Ambience()
    {
        std::cout<<"col:"<<SceneAmbience.r<<" "<<SceneAmbience.g<<" "<<SceneAmbience.b<<"\n";
    }
    void Print_max_min()
    {
    /* 
    for (int i=0;i<ShapeVector.size();i++)
    {   
    std::string name=ShapeVector[i]->get_name();
    glm::vec3 print_max= ShapeVector[i]->get_max();
    glm::vec3 print_min= ShapeVector[i]->get_min();
    /
    std::cout<<"-----------------------------------\n";
    std::cout<<"name: "<<name<<"\n";
    std::cout<<"m_max: "<<print_max.x<<" "<<print_max.y<<" "<<print_max.z<<"\n";
    std::cout<<"m_min: "<<print_min.x<<" "<<print_min.y<<" "<<print_min.z<<"\n";
    std::cout<<"-----------------------------------\n";
    
    }
    */
    glm::vec3 print_max=get_max();
    glm::vec3 print_min=get_min();
    std::cout<<"Scene max: "<<print_max.x<<" "<<print_max.y<<" "<<print_max.z<<"\n";
    std::cout<<"Scene min: "<<print_min.x<<" "<<print_min.y<<" "<<print_min.z<<"\n";
    }


    glm::vec3 get_max()
    {
    glm::vec3 max{0.0f,0.0f,0.0f};
    glm::vec3 temp;
    for (int i=ShapeVector.size()-1;i>=0;i--)
    {
    temp=ShapeVector[i]->get_max();
    if (temp.x>max.x) {max.x=temp.x;};
    if (temp.y>max.y) {max.y=temp.y;};
    if (temp.z>max.z) {max.z=temp.z;};
    }
    return max;
    }

    glm::vec3 get_min()
    {
    glm::vec3 min{0.0f,0.0f,0.0f};
    glm::vec3 temp;
    for (int i=ShapeVector.size()-1;i>=0;i--)
    {
    temp=ShapeVector[i]->get_min();
    if (temp.x<min.x) {min.x=temp.x;};
    if (temp.y<min.y) {min.y=temp.y;};
    if (temp.z<min.z) {min.z=temp.z;};
    }
    return min;
    }


};



#endif 