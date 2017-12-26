//
//
//
#ifndef _HELP_UTILS_H
#define _HELP_UTILS_H

#include <iostream>
#include <string>
#include <sstream>  
#include <string>
#include <fstream>  
#include <stdlib.h>  
#include <vector>
#include "mat.h"
#include "help.h"

void cpuStartTimer(void);
float cpuStopTimer(void);

namespace ncnn {

/*
 * Extract the layer kernel weight value
 */
void extract_kernel_f32(int layer_index, const char* layer_name, const Mat& _kernel,  const Mat& _bias, int num_input, int num_output, const int _kernel_size);
void extract_kernel_s16(int layer_index, const char* layer_name, const Mat& _kernel, const Mat& _bias, int num_input, int num_output, const int _kernel_size);
void extract_kernel_s16(int layer_index, const char* layer_name, const short *_kernel, const Mat& _bias, int num_input, int num_output, const int _kernel_size);
void extract_kernel_s8(int layer_index, const char* layer_name, const Mat& _kernel, const Mat& _bias, int num_input, int num_output, const int _kernel_size);
/*
 * Extract the layer bottom blob and top blob 2 feature maps
 */
void extract_feature_in_f32(int layer_index, const char* layer_name, const Mat& bottom_blob, const Mat& top_blob);
void extract_feature_in_f32_v1(int layer_index, const char* layer_name, const Mat& bottom_blob, const int count);
void extract_feature_in_s16(int layer_index, const char* layer_name, const Mat& bottom_blob, const Mat& top_blob);
void extract_feature_in_s8(int layer_index, const char* layer_name, const Mat& bottom_blob, const Mat& top_blob);

void extract_feature_out_f32(int layer_index, const char* layer_name, const Mat& bottom_blob, const Mat& top_blob);
void extract_feature_out_f32_v1(int layer_index, const char* layer_name, const Mat& top_blob, const int count);
/*
 * Create the blob's data from files
 */
void loaddata(ncnn::Mat& blob, const int weight, const int height, const int channels,const char *blobpath);
}

/*
 * Return the current system time ,return unit us
 */
long long get_current_time(void);

/*
 * Convert string type to need type
 */
template <class Type>
Type stringToNum(const std::string& str)
{
	std::istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

typedef struct _quantizeParams
{
	std::string name;
	float  dataScale;
	float  weightScale;
	float  biasScale;
	float  reshapeScale;
	float  anchorsScale;
}stQuantizeParams;

typedef struct _quantizeParamsBin
{
	int index;
	float  dataScale;
	float  weightScale;
	float  biasScale;
	float  reshapeScale;
	float  anchorsScale;
}stQuantizeParamsBin;

typedef enum _convModel
{
	CONV_DIRECT = 0,
	CONV_WINOGRAD = 1,
	CONV_QUANTIZE = 2,
}enConvModel;

#endif //_HELP_UTILS_H

