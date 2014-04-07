/*
 * TOP.h
 *
 *  Created on: 2014/04/08
 *      Author: Kuniyasu
 */

#ifndef TOP_H_
#define TOP_H_

#include <systemc.h>
#include "video_if.h"

class TOP:public sc_module{
public:
	video_in<VideoConfig,PIN> inf;

	TOP(const char* name):sc_module(name){
		end_module();
	}
};



#endif /* TOP_H_ */
