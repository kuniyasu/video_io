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
#include "BmpVideoOut.h"

class TOP:public sc_module{
public:
	//video_in<VideoConfig,PIN> inf;
	BMP_Loader bmp_loader;

	SC_HAS_PROCESS(TOP);
	TOP(const sc_module_name& name):sc_module(name),bmp_loader(){

		bmp_loader.loadBMPFile("SMPTE_COLOR_BAR.bmp");

		SC_THREAD(thread);
		end_module();
	}


	void thread(){
		wait(100,SC_MS);
		sc_stop();
	}
};



#endif /* TOP_H_ */
