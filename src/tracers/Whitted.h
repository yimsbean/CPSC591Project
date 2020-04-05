#pragma once

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Tracer.h"

namespace Engine{
class Whitted: public Tracer {
	public:
		
		Whitted(int maxDepth);
		
		Whitted(World* _worldPtr, int maxDepth);
		
		virtual											
		~Whitted(void);
	
		virtual Color	
		trace_ray(const Ray ray, const int depth) const;

		virtual Color	
		trace_ray(const Ray ray, float& tmin, const int depth) const;
    private:
        int maxDepth;
};

}