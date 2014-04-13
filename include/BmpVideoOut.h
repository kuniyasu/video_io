/*
 * BmpVideoOut.h
 *
 *  Created on: 2014/04/08
 *      Author: Kuniyasu
 */

#ifndef BMPVIDEOOUT_H_
#define BMPVIDEOOUT_H_

#include<systemc.h>
#include "video_if.h"

#ifndef pinConfig
#define pinConfig PIN
#endif

class BITMAPFILEHEADER {
public:
	typedef BITMAPFILEHEADER this_type;

	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;


	void reset(){}

	inline friend std::string getMessage( const this_type& v){
		std::stringstream	ss;

		ss <<  "  [BITMAPFILEHEADER]" << endl;
		ss << "  Size          : " << v.bfSize << " [Byte]" << endl;
		ss << "  bfReserved1   : " << v.bfReserved1  << endl;
		ss << "  bfReserved2   : " << v.bfReserved2  << endl;
		ss << "  OffBits       : " << v.bfOffBits << " [Byte]" << endl;
		ss << endl;

		return ss.str();
	}

    inline bool operator == (const this_type & rhs) const {
      return ( rhs.bfType == bfType)&&( rhs.bfSize == bfSize );
    }

    inline this_type& operator = (const this_type& rhs) {
    	bfType = rhs.bfType;
    	bfSize = rhs.bfSize;
    	bfReserved1 = rhs.bfReserved1;
    	bfReserved2 = rhs.bfReserved2;
    	bfOffBits   = rhs.bfOffBits;

		return *this;
    }

    inline friend void sc_trace(sc_trace_file *tf, const this_type & v, const std::string & NAME ) {
		sc_trace(tf, v.bfSize, NAME + ".bfSize");
		sc_trace(tf, v.bfOffBits, NAME + ".bfOffBits");
    }

    inline friend ostream& operator << ( ostream& os,  const this_type& v ) {
    	os << getMessage(v);
    	return os;
    }

};

class BITMAPCOREHEADER{
public:
	typedef BITMAPCOREHEADER this_type;

    //unsigned long  bcSize;
    short          bcWidth;
    short          bcHeight;
    unsigned short bcPlanes;
    unsigned short bcBitCount;

    void reset(){}

    inline friend std::string getMessage( const this_type& v){
    	std::stringstream msg;

		msg << "  [BITMAPCOREHEADER]" << endl;
		msg << "  Height        : " << v.bcHeight << " [pixel]" << endl;
		msg << "  Width	        : " << v.bcWidth  << " [pixel]" << endl;
		msg << "  BitCount      : " << v.bcBitCount << " [bit]" << endl;

    	return msg.str();
    }

    inline bool operator == (const this_type & rhs) const {
      return ( rhs.bcWidth == bcWidth)&&( rhs.bcHeight == bcHeight )&&( rhs.bcPlanes == bcPlanes)&&( rhs.bcBitCount == bcBitCount );
    }

    inline this_type& operator = (const this_type& rhs) {
    	bcWidth = rhs.bcWidth;
    	bcHeight = rhs.bcHeight;
    	bcPlanes = rhs.bcPlanes;
    	bcBitCount = rhs.bcBitCount;

		return *this;
    }

    inline friend void sc_trace(sc_trace_file *tf, const this_type & v, const std::string & NAME ) {
		sc_trace(tf, v.bcWidth,		NAME + ".bcWidth");
		sc_trace(tf, v.bcHeight,	NAME + ".bcHeight");
		sc_trace(tf, v.bcPlanes, 	NAME + ".bcPlanes");
		sc_trace(tf, v.bcBitCount,	NAME + ".bcBitCount");
    }

    inline friend ostream& operator << ( ostream& os,  const this_type& v ) {
    	os << getMessage(v);
    	return os;
    }
};

class BITMAPINFOHEADER{
public:
	typedef BITMAPINFOHEADER this_type;

    //unsigned long  biSize;
    long           biWidth;
    long           biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned long  biCompression;
    unsigned long  biSizeImage;
    long           biXPixPerMeter;
    long           biYPixPerMeter;
    unsigned long  biClrUsed;
    unsigned long  biClrImporant;

    void reset(){}

    inline friend std::string getMessage( const this_type& v){
    	std::stringstream msg;

		msg << "  [BITMAPINFOHEADER]" << endl;
		msg << "  Width         : " << v.biWidth <<" [pixel]" << endl;
		msg << "  Height        : " << v.biHeight << " [pixel]" << endl;
		msg << "  BitCount      : " << v.biBitCount << " [bit]" << endl;

		if( v.biCompression == 0){
		msg << "  Compression   : 無圧縮" << endl;
		}else if( v.biCompression == 0){
		msg << "  Compression   : BI_RLE8 8bit RunLength" << endl;
		}else if( v.biCompression == 0){
		msg << "  Compression   : BI_RLE4 4bit RunLength" << endl;
		}

		msg << "  SizeImage     : " << v.biSizeImage << " [Byte]" << endl;
		msg << "  XPelsPerMeter : " << v.biXPixPerMeter << " [pixel/m]" << endl;
		msg << "  YPelsPerMeter : " << v.biYPixPerMeter << " [pixel/m]" << endl;
		msg << "  ClrUsed       : " << v.biClrUsed << " [color]" << endl;

    	return msg.str();
    }

    inline bool operator == (const this_type & rhs) const {
      return (( rhs.biWidth == biWidth )&&( rhs.biHeight == biHeight )&&( rhs.biPlanes == biPlanes )&&
    		  ( rhs.biBitCount == biBitCount )&&( rhs.biCompression == biCompression )&&( rhs.biSizeImage == biSizeImage )&&
    		  ( rhs.biXPixPerMeter == biXPixPerMeter )&&( rhs.biYPixPerMeter == biYPixPerMeter )&&( rhs.biClrUsed == biClrUsed )&&
    		  ( rhs.biClrImporant == biClrImporant ));
    }

    inline this_type& operator = (const this_type& rhs) {
    	biWidth = rhs.biWidth;
    	biHeight = rhs.biHeight;
    	biPlanes = rhs.biPlanes;
    	biBitCount = rhs.biBitCount;
    	biCompression = rhs.biCompression;
    	biSizeImage = rhs.biSizeImage;
    	biXPixPerMeter = rhs.biXPixPerMeter;
    	biYPixPerMeter = rhs.biYPixPerMeter;
    	biClrUsed = rhs.biClrUsed;
    	biClrImporant = rhs.biClrImporant;

		return *this;
    }

    inline friend void sc_trace(sc_trace_file *tf, const this_type & v, const std::string & NAME ) {
		sc_trace(tf, v.biWidth, 		NAME + ".biWidth");
		sc_trace(tf, v.biHeight, 		NAME + ".biHeight");
		sc_trace(tf, v.biPlanes, 		NAME + ".biPlanes");
		sc_trace(tf, v.biBitCount, 		NAME + ".biBitCount");
		sc_trace(tf, v.biCompression, 	NAME + ".biCompression");
		sc_trace(tf, v.biSizeImage, 	NAME + ".biSizeImage");
		sc_trace(tf, v.biXPixPerMeter,	NAME + ".biXPixPerMeter");
		sc_trace(tf, v.biYPixPerMeter,	NAME + ".biYPixPerMeter");
		sc_trace(tf, v.biClrUsed,		NAME + ".biClrUsed");
		sc_trace(tf, v.biClrImporant,	NAME + ".biClrImporant");
    }

    inline friend ostream& operator << ( ostream& os,  const this_type& v ) {
    	os << getMessage(v);
    	return os;
    }
};

class RGBTRIPLE{
public:
	typedef RGBTRIPLE this_type;

    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;

    void reset(){}

    inline bool operator == (const this_type & rhs) const {
    	return ((rgbBlue==rhs.rgbBlue)&&(rgbGreen==rhs.rgbGreen)&&(rgbRed==rhs.rgbRed));
    }

    inline this_type& operator = (const this_type& rhs) {
    	this->rgbBlue = rhs.rgbBlue;
    	this->rgbGreen = rhs.rgbGreen;
    	this->rgbRed = rhs.rgbRed;

    	return *this;
    }

    inline friend void sc_trace(sc_trace_file *tf, const this_type & v, const std::string & NAME ) {
		sc_trace(tf, v.rgbBlue, 		NAME + ".rgbBlue");
		sc_trace(tf, v.rgbGreen, 		NAME + ".rgbGreen");
		sc_trace(tf, v.rgbRed, 			NAME + ".rgbRed");
    }

    inline friend std::string getMessage( const this_type& v){
    	std::stringstream msg;
    	msg << "(" << "," << v.rgbRed << "," << v.rgbGreen << "," << v.rgbBlue << ")" << endl;
    	return msg.str();
    }

    inline friend ostream& operator << ( ostream& os,  const this_type& v ) {
    	os << getMessage(v);
    	return os;
    }
};

class RGBQUAD{
public:
	typedef RGBQUAD this_type;

	unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbReserved;

    void reset(){}

    inline bool operator == (const this_type & rhs) const {
    	return ((rgbBlue==rhs.rgbBlue)&&(rgbGreen==rhs.rgbGreen)&&(rgbRed==rhs.rgbRed)&&(rgbReserved==rhs.rgbReserved));
    }

    inline this_type& operator = (const this_type& rhs) {
    	this->rgbBlue = rhs.rgbBlue;
    	this->rgbGreen = rhs.rgbGreen;
    	this->rgbRed = rhs.rgbRed;
    	this->rgbReserved = rhs.rgbReserved;

    	return *this;
    }

    inline friend void sc_trace(sc_trace_file *tf, const this_type & v, const std::string & NAME ) {
		sc_trace(tf, v.rgbBlue, 		NAME + ".rgbBlue");
		sc_trace(tf, v.rgbGreen, 		NAME + ".rgbGreen");
		sc_trace(tf, v.rgbRed, 			NAME + ".rgbRed");
		sc_trace(tf, v.rgbReserved, 	NAME + ".rgbReserved");
    }

    inline friend std::string getMessage( const this_type& v){
    	std::stringstream msg;
    	msg << "(" << v.rgbReserved << "," << v.rgbRed << "," << v.rgbGreen << "," << v.rgbBlue << ")" << endl;
    	return msg.str();
    }

    inline friend ostream& operator << ( ostream& os,  const this_type& v ) {
    	os << getMessage(v);
    	return os;
    }
};

class BMP_Loader{
public:
	typedef BMP_Loader this_type;

	BITMAPFILEHEADER bitmapfileheader;

	unsigned long infosize;
	BITMAPCOREHEADER bitmapcoreheader;
	BITMAPINFOHEADER bitmapinfoheader;

	RGBTRIPLE* bc_color_map;
	RGBQUAD* bi_color_map;

	RGBQUAD** rgbquad;

	FILE* file;
	char filename[256];

	BMP_Loader(){
		cout << "Instance" << endl;
	}

	inline friend ostream& operator << ( ostream& os,  const this_type& v ) {
		os << v.bitmapfileheader << endl;

		if( v.infosize == 12U ){
			cout << v.bitmapcoreheader;
		}

		if( v.infosize == 40U ){
			cout << v.bitmapinfoheader;
		}

		return os;
	}

	void createColorMap(){
		if( infosize==12 && bitmapcoreheader.bcBitCount == 1U ){
			bc_color_map = new RGBTRIPLE[2];
		}else if( infosize==12 && bitmapcoreheader.bcBitCount == 4U ){
			bc_color_map = new RGBTRIPLE[16];
		}else if( infosize==12 && bitmapcoreheader.bcBitCount == 8U ){
			bc_color_map = new RGBTRIPLE[256];
		}else if( infosize==12 && bitmapcoreheader.bcBitCount == 16U ){
			bc_color_map = new RGBTRIPLE[65536];
		}

		if( infosize==40 && bitmapinfoheader.biBitCount == 1U ){
			bi_color_map = new RGBQUAD[2];
		}else if( infosize==40 && bitmapinfoheader.biBitCount == 4U ){
			bi_color_map = new RGBQUAD[16];
		}else if( infosize==40 && bitmapinfoheader.biBitCount == 8U ){
			bi_color_map = new RGBQUAD[256];
		}else if( infosize==40 && bitmapinfoheader.biBitCount == 16U ){
			bi_color_map = new RGBQUAD[65536];
		}
	}

	void createBuffer(){
		int32_t height;
		int32_t width;

		if( infosize == 12U){
			height = bitmapcoreheader.bcHeight;
			width  = bitmapcoreheader.bcWidth;

		}else if( infosize == 40U){
			height = bitmapinfoheader.biHeight;
			width  = bitmapinfoheader.biWidth;
		}

		rgbquad = new RGBQUAD*[height];

		for(short i=0; i<width; i++){
			rgbquad[i] = new RGBQUAD();
		}

	}

	void delateBuffer(){
	}

	void loadBMPFile(const char* filename){
		if( strlen(filename) < 256 ){
			strcpy(this->filename, filename);

			if( (file = fopen(filename,"rb")) == NULL){
				cout << "Not File open." << endl;
				return;
			}

			analysisBMPFileheader();
			analysisBMPCoreheader();
			createBuffer();
			createColorMap();

			fclose(file);

			cout << bitmapfileheader;
			cout << bitmapinfoheader;
		}

		cout << this->filename << endl;

	}

	void analysisBMPFileheader(){
		char s[10];
		uint16_t var_short;
		uint32_t var_long;
		//long var_long;

		// BITMAP 認識文字 "BM"
		if (fread(s, 2, 1, file) == 1) {
			if (memcmp(s, "BM", 2) == 0) {
				//printf("[BM] BITMAP file\n");

				// ファイルサイズ
				if (fread(&var_long, 4, 1, file) == 1) {
					bitmapfileheader.bfSize = var_long;
				}

				// 予約領域 1
				if (fread(&var_short, 2, 1, file) == 1) {
					bitmapfileheader.bfReserved1 = var_short;
				}

				// 予約領域 2
				if (fread(&var_short, 2, 1, file) == 1) {
					bitmapfileheader.bfReserved2 = var_short;
				}

				// ファイルの先頭から画像データまでの位置
				if (fread(&var_long, 4, 1, file) == 1) {
					bitmapfileheader.bfOffBits = var_long;
				}
			}

		}
	}

	void analysisBMPCoreheader(){
		short var_short;
		long var_long;

		// BITMAPINFOHEADER のサイズ
		if (fread(&var_long, 4, 1, file) == 1) {
			infosize = var_long;
		}

		// OS/2 Bitmap
		if (infosize == 12U ) {
			// 画像データの幅
			if (fread(&var_short, 2, 1, file) == 1) {
				bitmapcoreheader.bcWidth = var_short;
			}

			// 画像データの高さ
			if (fread(&var_short, 2, 1, file) == 1) {
				bitmapcoreheader.bcHeight = var_short;
			}

			// プレーン数 (1のみ)
			if (fread(&var_short, 2, 1, file) == 1) {
				bitmapcoreheader.bcPlanes = var_short;
			}

			// 1画素あたりのビット数 (1, 4, 8, 24, 32)
			if (fread(&var_short, 2, 1, file) == 1) {
				bitmapcoreheader.bcBitCount = var_short;
			}

		}else if(infosize == 40U ){
			// 画像データの幅
			if (fread(&var_long, 4, 1, file) == 1) {
				bitmapinfoheader.biWidth = var_long;
			}

		    // 画像データの高さ
		    if (fread(&var_long, 4, 1, file) == 1) {
		    	bitmapinfoheader.biHeight = var_long;
		    }

		    // プレーン数 (1のみ)
		    if (fread(&var_short, 2, 1, file) == 1) {
		    	bitmapinfoheader.biPlanes = var_short;
		    	//count += 2;
		    }

		    // 1画素あたりのビット数 (1, 4, 8, 24, 32)
		    if (fread(&var_short, 2, 1, file) == 1) {
		    	bitmapinfoheader.biBitCount = var_short;
		    }

		    // 圧縮方式  0 : 無圧縮
		    //           1 : BI_RLE8 8bit RunLength 圧縮
		    //           2 : BI_RLE4 4bit RunLength 圧縮
		    if (fread(&var_long, 4, 1, file) == 1) {
		    	bitmapinfoheader.biCompression = var_long;
		    }

		    // 画像データのサイズ
		    if (fread(&var_long, 4, 1, file) == 1) {
		    	bitmapinfoheader.biSizeImage = var_long;
		    }

		    // 横方向解像度 (Pixel/meter)
		    if (fread(&var_long, 4, 1, file) == 1) {
				bitmapinfoheader.biXPixPerMeter = var_long;
		    }

		    // 縦方向解像度 (Pixel/meter)
		    if (fread(&var_long, 4, 1, file) == 1) {
		    	bitmapinfoheader.biYPixPerMeter = var_long;
		    }

		    // 使用色数
		    if (fread(&var_long, 4, 1, file) == 1) {
		    	bitmapinfoheader.biClrUsed = var_long;
		    }

		    // 重要な色の数 0の場合すべての色
		    if (fread(&var_long, 4, 1, file) == 1) {
		    	bitmapinfoheader.biClrImporant = var_long;
		    }
		}
	}

};

class BmpVideoOut:public sc_module, public BMP_Loader{
public:
	typedef BMP_Loader base_type;

	sc_in<bool> clk;
	sc_in<bool> nrst;
	video_out<VideoConfig,pinConfig> out;

	char filename[256];
	FILE* file;
	typename VideoConfig::video_data_type** bmp;


	SC_HAS_PROCESS(BmpVideoOut);

	BmpVideoOut(const sc_module_name& name=sc_gen_unique_name("BmpVideoOut")):sc_module(name)
	,clk(PIN_NAME(name,"clk")),nrst(PIN_NAME(name,"nrst")),out(PIN_NAME(name,"vout")){
		SC_CTHREAD(thread,clk.pos());
		async_reset_signal_is(nrst,false);

		end_module();
	}

	void set_trace(sc_trace_file* tf){
		sc_trace(tf,	clk, 		TR_NAME("clk"));
		sc_trace(tf,	nrst, 		TR_NAME("nrst"));

		out.set_trace(tf);
	}

	void usage(){
		std::cout << "-bmp_in_file <filename>" << endl;
	}

	void analysisArgv(){
		int argc = sc_argc();
		const char* const* argv = sc_argv();

		if( argc < 3 ){
			usage();
			return;
		}


		for(int i=0; i<argc; i++){
			const char* arg0 = argv[i];

			if(0 == strcmp("-bmp_in_file",arg0)){

			}

		}

	}

	void thread(){
		out.reset();
		wait();

		while( true ){

			wait();
		}
	}
};


#endif /* BMPVIDEOOUT_H_ */
