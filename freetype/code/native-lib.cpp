#include <jni.h>
#include <android/log.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "mtcnnAttribute.h"
#include "CvText.h"

#define TAG "native-lib.cpp"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

// TODO native方法实现

static mtcnn *mtcnn_;
Attribute attribute;

// 模型是否已经初始化
bool detection_init_ok = false;
bool gender_init_ok = false;

CvText *text;

cv::Mat cropFaceForAttr(cv::Mat& image, int x1, int y1, int x2, int y2){
    cv::Size crop_size = cv::Size(224, 224);
    cv::Rect roi;
    cv::Mat crop;
    roi.x = x1;
    roi.y = y1;
    roi.width = x2 - x1 + 1;
    roi.height = y2 - y1 + 1;
    if(0 <= roi.x && 0 <= roi.width && roi.x + roi.width <= image.cols && 0 <= roi.y && 0 <= roi.height && roi.y + roi.height <= image.rows )
    {
        crop = image(roi);
        cv::resize(crop, crop, crop_size, 0, 0, CV_INTER_LINEAR);
    }
    return crop;
}

static int getMaxId(std::vector<float>& arr, float &confidence){
    //assert(arr != NULL);
    int num = arr.size();
    float max_val = arr[0];
    int id = 0;
    for (int i = 1; i < num; i++) {
        if (arr[i] > max_val) {
            //std::cout<<"arr[i] : "<< arr[i] <<std::endl;
            max_val = arr[i];
            id = i;
        }
    }
    //std::cout<<"confidence : "<< max_val <<std::endl;
    confidence = max_val;
    return id;
}

void mRotate90(Mat &img) {
    cv::Point2f center = cv::Point2f(img.rows/2, img.rows/2);
    double angle = 270;
    double scale = 1;
    cv::warpAffine(img, img, cv::getRotationMatrix2D(center, angle, scale), cv::Size(img.rows, img.cols));
}

static unsigned long get_current_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec*1000000 + tv.tv_usec);
}

extern "C"
JNIEXPORT jint
Java_com_faceattributes_NativeFunction_makeFace(JNIEnv *, jobject, jlong jrgbaddr) {
    LOGD("makeFace start");

    cv::Mat &frame = *(cv::Mat *) jrgbaddr;
    LOGD("frame width:%d, height:%d, step:%d", frame.cols, frame.rows, frame.step[0]);


    //unsigned long time1 = get_current_time();
    mRotate90(frame);
    //unsigned long time2 = get_current_time();
    //LOGD("旋转消耗时间：%.3fms", (time2-time1)/1000.0);
    //LOGD("顺时针旋转90度, frame width:%d, height:%d, step:%d", frame.cols, frame.rows, frame.step[0]);


    ncnn::Mat ncnn_img = ncnn::Mat::from_pixels(frame.data, ncnn::Mat::PIXEL_RGBA2RGB, frame.cols,
                                                frame.rows);
    std::vector<Bbox> finalBox;
    mtcnn_->detect(ncnn_img, finalBox);
    const int num_box = finalBox.size();
    std::vector<cv::Rect> bbox;
    bbox.resize(num_box);

    std::vector<float> gender_scores;
    std::vector<float> age_scores;
    float confidence = 0;
    __android_log_print(ANDROID_LOG_DEBUG, "freetype", "载入字体");
    //CvText text("Ubuntu Mono derivative Powerline.ttf");
    __android_log_print(ANDROID_LOG_DEBUG, "freetype", "载入字体结束");
    int total = 0;
    for (vector<Bbox>::iterator it = finalBox.begin(); it != finalBox.end(); it++) {
        if (it->exist) {
            total++;
            cv::Mat attCropImg = cropFaceForAttr(frame, it->x1, it->y1, it->x2, it->y2);
            if (!attCropImg.empty() && attCropImg.rows==224 && attCropImg.cols==224){
                attribute.classify(attCropImg, gender_scores, age_scores);

                int genderID = getMaxId(gender_scores, confidence);
                if (genderID == 0)
                    cv::rectangle(frame, Point((*it).x1, (*it).y1), Point((*it).x2, (*it).y2),
                                  Scalar(255, 0, 255), 2, 8, 0);
                else
                    cv::rectangle(frame, Point((*it).x1, (*it).y1), Point((*it).x2, (*it).y2),
                                  Scalar(255, 255, 0), 2, 8, 0);

                int ageID = getMaxId(age_scores, confidence);
                switch (ageID) {
                    case 0: // 儿童
                        //cv::putText(frame, "child", Point((*it).x1, (*it).y1), cv::FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 255));
                        text->putText(frame, "幼年", Point((*it).x1, (*it).y1), Scalar(0, 255, 255));
                        break;
                    case 1: // 少年
                        //cv::putText(frame, "teenager", Point((*it).x1, (*it).y1), cv::FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 255));
                        text->putText(frame, "少年", Point((*it).x1, (*it).y1), Scalar(0, 255, 255));
                        break;
                    case 2: // 青年
                        //cv::putText(frame, "young", Point((*it).x1, (*it).y1), cv::FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 255));
                        text->putText(frame, "青年", Point((*it).x1, (*it).y1), Scalar(0, 255, 255));
                        break;
                    case 3: // 中年
                        //cv::putText(frame, "middle", Point((*it).x1, (*it).y1), cv::FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 255));
                        text->putText(frame, "中年", Point((*it).x1, (*it).y1), Scalar(0, 255, 255));
                        break;
                    case 4: // 老年
                        //cv::putText(frame, "older", Point((*it).x1, (*it).y1), cv::FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 255));
                        text->putText(frame, "老年", Point((*it).x1, (*it).y1), Scalar(0, 255, 255));
                        break;
                    default:
                        //cv::putText(frame, "unknown", Point((*it).x1, (*it).y1), cv::FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 255));
                        text->putText(frame, "妖寿", Point((*it).x1, (*it).y1), Scalar(0, 255, 255));
                        break;
                }
            }

        }
    }
    /*
    unsigned long time3 = get_current_time();
    LOGD("检测耗时：%.3fms", (time3-time2)/1000.0);
    LOGD("total:%d", total);
     */
    LOGD("makeFace end");
    return 0;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_faceattributes_NativeFunction_ModelInit(JNIEnv *env, jobject instance, jstring path_) {
    LOGD("ModelInit start");

    if (NULL == path_) {
        LOGD("path cannot be null");
        return 0;
    }

    const char *path = env->GetStringUTFChars(path_, 0);

    if (NULL == path) return 0;

    string tFaceModelDir = path;

    string tLastChar = tFaceModelDir.substr(tFaceModelDir.length() - 1, 1);
    LOGD("init, tFaceModelDir last is %s", tLastChar.c_str());

    //目录补齐'/'
    if ("\\" == tLastChar) {
        tFaceModelDir = tFaceModelDir.substr(0, tFaceModelDir.length()-1) + "/";
    } else if (tLastChar != "/") {
        tFaceModelDir += "/";
    }
    LOGD("init, tFaceModelDir=%s", tFaceModelDir.c_str());

    if (detection_init_ok) LOGD("face detection model has been loaded");
    else {
        LOGD("call mtcnn constructor");
        mtcnn_ = new mtcnn(tFaceModelDir);
        detection_init_ok = true;
    }
    if (gender_init_ok) LOGD("gender classification model has been loaded");
    else {
        LOGD("call Attribute.setup() function");
        attribute.setup(tFaceModelDir);
        gender_init_ok = true;
    }

    text = new CvText((tFaceModelDir+"/Ubuntu Mono derivative Powerline.ttf").c_str());

    return 1;
}