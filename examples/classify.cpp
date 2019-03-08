/* 
 *  
 * ncnn Classification Benchmark Demo  
 * 
 * v1.0/BUG1989/2017.12.26 
 */

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sys/time.h>
#include <float.h>

#include "net.h"

using namespace std;

static unsigned long get_current_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    
    return (tv.tv_sec*1000000 + tv.tv_usec);
}

static int ncnn_classify(char *pParamPath, char *pBinPath, int width, int height, int count, int threads)
{
    ncnn::Net classify;
    classify.load_param(pParamPath);
    classify.load_model(pBinPath);

    ncnn::Mat in;
    in.create(width, height, 3);

    const float mean_vals[3] = {104.f, 117.f, 123.f};
    in.substract_mean_normalize(mean_vals, 0);

    ncnn::Mat out;

    double total_time = 0.;
    double min_time = DBL_MAX;
    double max_time = 0.0;
    double temp_time = 0.0;   
    unsigned long time_0, time_1;

    for(int i =0 ;i < count; i++)
    {
        time_0 = get_current_time();

        ncnn::Extractor ex = classify.create_extractor();
        ex.set_light_mode(true);
        ex.set_num_threads(threads);
        ex.input("data", in);
        ex.extract("prob", out);

        time_1 = get_current_time();
        temp_time = ((time_1 - time_0)/1000.0);
        if(temp_time < min_time)
        {
            min_time = temp_time;
        }
        if(temp_time > max_time)
        {
            max_time = temp_time;
        }
        total_time += temp_time;

        printf("iter %d/%d cost: %.3f ms\n", i+1, count, temp_time);
    }

    
    std::cout << "Time cost: Max " << max_time << \
                       " ms, Min " << min_time << \
                       " ms, Avg " << total_time/count << \
                       " ms." << std::endl;
}

void usage(void)
{
    std::cout << "Input params illegal." << std::endl; 
    std::cout << "./ncnn_classify <param file> <bin file> <width> <height> <loops num> <threads num>"
              << std::endl;
}

/* 
 * Param:
 *      input:<param file> <bin file> <width> <height> <loops num> <threads num>
 */
int main(int argc, char** argv)
{
    char *imagePath = NULL;
    char *paramPath = NULL;
    char *binPath = NULL;
    char *scalePath = NULL;
    int loopsNum = 1;
    int threadsNum = 1;
    int width,height;

    if(argc != 7)
    {
        usage();
        return -1;
    }
    else    //user params
    {
        paramPath = argv[1];
        binPath = argv[2];
        width = atoi(argv[3]);
        height = atoi(argv[4]);
        loopsNum = atoi(argv[5]);
        threadsNum = atoi(argv[6]);
    }  

    std::cout << "--- NCNN Classification Benchmark Demo --- " << __TIME__ << " " << __DATE__ << std::endl;
    std::cout << "Loops   : " << loopsNum << std::endl;
    std::cout << "Threads : " << threadsNum << std::endl;

    ncnn_classify(paramPath, binPath, width, height, loopsNum, threadsNum);

    return 0;
}

