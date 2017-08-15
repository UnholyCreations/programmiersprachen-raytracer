#ifndef SCENE_HPP
#define SCENE_HPP
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "material.hpp"
#include <map>
#include <iostream>
#include <ostream>
#include <string>
#include <memory>
struct Scene
{
    int x_resolution;
    int y_resolution;

	std::map<std::string,Material> MaterialMap;
	std::vector<std::shared_ptr<Shape>> ShapeVector;
	const void Print_Shapes()
	{
	for (int i=0;i<ShapeVector.size();i++) //if i dont mess the indices after a month pause its not me... :D
        {   
            //std::static_pointer_cast
            //std::const_pointer_cast
            //std::dynamic_pointer_cast
        	(*ShapeVector[i]).print(std::cout);
            //std::cout<<(*ShapeVector[i]);
        	//ShapeVector[i]->print(std::cout);
            //(*ShapeVector[i]).print(std::cout);
        };
    }
};



#endif 