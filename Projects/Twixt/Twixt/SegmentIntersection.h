#pragma once

// A C++ program to check if two given line segments intersect 
// algorithm from https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/

#include "SDL.h"
#include <algorithm>



// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(SDL_Point p, SDL_Point q, SDL_Point r)
{
	if (q.x <= (std::min)(p.x, r.x) && q.x >= (std::min)(p.x, r.x) &&
		q.y <= (std::min)(p.y, r.y) && q.y >= (std::min)(p.y, r.y))
		return true;

	return false;
}

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(SDL_Point p, SDL_Point q, SDL_Point r)
{
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
	// for details of below formula. 
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear 

	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(SDL_Point p1, SDL_Point q1, SDL_Point p2, SDL_Point q2)
{
	// Find the four orientations needed for general and 
	// special cases 
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case 
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases 
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are colinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases 
}