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
    Camera SceneCamera;
	std::map<std::string,Material> MaterialMap;
	std::vector<std::shared_ptr<Shape>> ShapeVector;
    std::vector<Light> LightVector;
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
    void Print_Lights()
    {
    for (Light l:LightVector)
        {
            l.print();
        }
    }
    void Print_Ambience()
    {
        std::cout<<"col:"<<SceneAmbience.r<<" "<<SceneAmbience.g<<" "<<SceneAmbience.b<<"\n";
    }
};



#endif 