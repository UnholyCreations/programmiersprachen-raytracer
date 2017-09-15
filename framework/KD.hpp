#include "AABB.hpp"
#include "shape.hpp"
#include <vector>
#ifndef KD_HPP
#define KD_HPP
class KDNODE{


	public:
	AABB m_aabb;
	KDNODE* m_left;
	KDNODE* m_right;
	std::vector<std::shared_ptr<Shape>> KDShapeVector;

	//constructor
	KDNODE();
	~KDNODE();
	//funcs

	KDNODE* build(std::vector<std::shared_ptr<Shape>> f_KDShapeVector,int depth);

};


#endif 