#include "Entity.hpp"
void Entity::rotate(float x, float y){
	float angle = std::atan2(y + 0.00000000000001f, x + 0.00000000000001f) * 180.f / 3.1415926535f;
    rec.setRotation(angle);
}