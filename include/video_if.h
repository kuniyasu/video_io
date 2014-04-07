/*
 * video_if.h
 *
 *  Created on: 2014/04/07
 *      Author: Kuniyasu
 */

#ifndef VIDEO_IF_H_
#define VIDEO_IF_H_

#include<systemc.h>

class PIN{};
class TLM{};
#define TR_NAME(_name) (std::string(name())+"_"+std::string(_name)).c_str()
#define PIN_NAME(bname,_name_) (std::string(bname)+"_"+std::string(_name_)).c_str()

class VideoConfig {
public:
	static const unsigned char VideoDataWidth = 24U;
	typedef sc_uint<VideoDataWidth> video_data_type;
};

template<class CFG>class VideoInterface:public sc_interface{
public:
	virtual void reset() = 0;
	virtual void display(bool v, bool h, bool en, typename CFG::video_data_type data) = 0;
};

template<class CFG=VideoConfig,class L=PIN> class video_sig{
public:
	sc_signal<bool> valid;

	sc_signal<bool> v_sync;
	sc_signal<bool> h_sync;
	sc_signal<bool> video_en;
	sc_signal<typename CFG::video_data_type> data;

	video_sig(const char* name=sc_gen_unique_name("video_sig")){}
};

template<class CFG=VideoConfig,class L=PIN> class video_base_in:public VideoInterface<CFG>{
public:
	sc_in<bool> valid;

	sc_in<bool> v_sync;
	sc_in<bool> h_sync;
	sc_in<bool> video_en;
	sc_in<typename CFG::video_data_type> data;

	video_base_in(const char* name=sc_gen_unique_name("video_base_in")){}

	template<class C> void bind(C& c){
		valid(c.valid);
		v_sync(c.v_sync);
		h_sync(c.h_sync);
		video_en(c.video_en);
		data(c.data);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=VideoConfig,class L=PIN> class video_base_out:public VideoInterface<CFG>{
public:
	sc_in<bool> valid;

	sc_in<bool> v_sync;
	sc_in<bool> h_sync;
	sc_in<bool> video_en;
	sc_in<typename CFG::video_data_type> data;

	video_base_out(const char* name=sc_gen_unique_name("video_base_out")){}

	template<class C> void bind(C& c){
		valid(c.valid);
		v_sync(c.v_sync);
		h_sync(c.h_sync);
		video_en(c.video_en);
		data(c.data);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};


template<class CFG=VideoConfig,class L=PIN> class video_in:public sc_module, public video_base_in<CFG,L>, public VideoInterface<CFG>{
public:
	typedef video_base_in<CFG,L> base_type;
	typedef VideoInterface<CFG> if_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	sc_export<if_type> cb_port;

	SC_HAS_PROCESS(video_in);
	video_in(const sc_module_name& name=sc_gen_unique_name("video_in")):sc_module(name),base_type(name){
		SC_CTHREAD(thread,clk.pos());
		reset_signal_is(nrst,false);
		end_module();
	}

	void reset(){
		cb_port->reset();
	}

	void display(bool v, bool h, bool en, typename CFG::video_data_type data){
		cb_port->display( v, h, en, data);
	}

	void thread(){
		reset();
		wait();

		while( true ){
			do{ wait(); }while( base_type::valid.read() == false );
			display(base_type::v_sync.read(), base_type::h_sync.read(), base_type::video_en.read(), base_type::data.read());
		}
	}

	void set_trace(sc_trace_file* tf){
		sc_trace(tf,	base_type::valid, 		TR_NAME("valid"));
		sc_trace(tf,	base_type::v_sync,		TR_NAME("v_sync"));
		sc_trace(tf,	base_type::h_sync,		TR_NAME("h_sync"));
		sc_trace(tf,	base_type::video_en,	TR_NAME("video_en"));
		sc_trace(tf,	base_type::data,		TR_NAME("data"));
	}

	template<class C> void bind(C& c){
		base_type::valid(c.valid);
		base_type::v_sync(c.v_sync);
		base_type::h_sync(c.h_sync);
		base_type::video_en(c.video_en);
		base_type::data(c.data);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG=VideoConfig,class L=PIN> class video_out:public sc_module, public video_base_out<CFG,L>, public VideoInterface<CFG>{
public:
	typedef video_base_out<CFG,L> base_type;
	typedef VideoInterface<CFG> if_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;

	video_out(const sc_module_name& name=sc_gen_unique_name("video_out")):sc_module(name),base_type(name){
		end_module();
	}

	void reset(){
		base_type::valid = false;
	}

	void display(bool v, bool h, bool en, typename CFG::video_data_type data){
		base_type::valid = true;
		base_type::v_sync = v;
		base_type::h_sync = h;
		base_type::video_en = en;
		base_type::data = data;
		wait();
		base_type::valid = false;
	}

	void set_trace(sc_trace_file* tf){
		sc_trace(tf,	base_type::valid, 		TR_NAME("valid"));
		sc_trace(tf,	base_type::v_sync,		TR_NAME("v_sync"));
		sc_trace(tf,	base_type::h_sync,		TR_NAME("h_sync"));
		sc_trace(tf,	base_type::video_en,	TR_NAME("video_en"));
		sc_trace(tf,	base_type::data,		TR_NAME("data"));
	}

	template<class C> void bind(C& c){
		base_type::valid(c.valid);
		base_type::v_sync(c.v_sync);
		base_type::h_sync(c.h_sync);
		base_type::video_en(c.video_en);
		base_type::data(c.data);
	}

	template<class C> void operator()(C& c){
		bind(c);
	}
};

template<class CFG> class video_base_in<CFG,TLM>:public sc_export<VideoInterface<CFG> >{
public:

};

template<class CFG> class video_base_out<CFG,TLM>:public sc_port<VideoInterface<CFG> >{
public:

};


#endif /* VIDEO_IF_H_ */
