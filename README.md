# ncnn-benchmark
The benchmark of ncnn that is a high-performance neural network inference framework optimized for the mobile platform
https://github.com/Tencent/ncnn
## Hardware Platform
|Device|System|CPU-Family|CPU-Num|Freq|
|------|------|----------|-------|----|
|RK3288|Android 5.1|Cortex-A17|4|1.8GHz|
|Qualcomm820|Android 6.0|Kryo(Cortex-A72)|2+2|2.15GHz/1.6GHz|
## Runtime Environment
1.Using the cpu working in performance model.  
```
echo performance > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
2.Loop a hundred times to take the minimum value of Inference time-consuming
## Result
|Devices|Models|Input Size|Single-Thread(ms)|Multi-Threads(ms)|
|-------|------|----------|-----------------|-----------------|
|RK3288|SqueezeNet v1.1|227x227x3|194|80|
|       |MobileNet v1.0|224x224x3|324|115|
|       |ResNet18|224x224x3|807|291|
|       |GoogleNet v1.0|224x224x3|740|261|
|       |VGG16|224x224x3|
|       |MobileNet-SSD|300x300x3|652|245|
|Qualcomm820|SqueezeNet v1.1|227x227x3|91|47|
|       |MobileNet v1.0|224x224x3|150|70|
|       |ResNet18|224x224x3|356|171|
|       |GoogleNet v1.0|224x224x3|371|161|
|       |VGG16|224x224x3|2583|971|
|       |MobileNet-SSD|300x300x3|330|160|
## The End
Thanks to ncnn's author nihui and all the contributors for sharing this framework.
