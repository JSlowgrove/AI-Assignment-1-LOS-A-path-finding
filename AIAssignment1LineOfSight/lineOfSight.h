#pragma once

#include <time.h>
#include "vec2.h"
#include "SDL.h"
#include "map.h"

namespace LOS
{
	/**
	Check if two positions can see each other
	@param Vec2 Position a
	@param Vec2 Position b
	@param Map * A pointer to the map 
	@return bool If the position can see each other
	*/
	bool lineOfSight(Vec2 a, Vec2 b, Map* map);

	/**
	Check if two lines intersect
	@param Vec2 Position a (line 1)
	@param Vec2 Position b (line 1)
	@param Vec2 Position c (line 2)
	@param Vec2 Position c (line 2)
	@param char Axis that the second line being tested is on
	@return bool If the lines intersect
	*/
	bool lineLineIntersectionCheck(Vec2 a, Vec2 b, Vec2 c, Vec2 d, char axis);

	/**
	Check if two positions can see each other and draw the tested tiles
	@param Vec2 Position a
	@param Vec2 Position b
	@param Map * A pointer to the map
	@param SDL_Renderer * A pointer to the renderer
	*/
	void drawLineOfSight(Vec2 a, Vec2 b, Map* map, SDL_Renderer* renderer);

	/**
	Find a new target position to go to
	@param Vec2 Position a
	@param Map * A pointer to the map
	@return Vec2 The new target position
	*/
	Vec2 getNewTarget(Vec2 a, Map* map);
}