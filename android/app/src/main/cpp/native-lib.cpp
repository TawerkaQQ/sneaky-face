#include "log.h"
#include "camera_capture.h"

#include <jni.h>
#include <string>

#include <android_native_app_glue.h>
#include <android/native_window.h>
#include <camera/NdkCameraDevice.h>
#include <camera/NdkCameraError.h>
#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraMetadataTags.h>
#include <android/looper.h>

std::shared_ptr<CameraCapture> camera_capture_;

extern "C" JNIEXPORT void JNICALL
Java_com_example_objectdetection_MainActivity_initObjectDetection(
        JNIEnv *env,
        jobject /* this */,
        jstring camId) {
    auto camera_id = env->GetStringUTFChars(camId, nullptr);
    LOGI("Camera ID: %s", camera_id);
    if (camera_capture_) {
        camera_capture_->allow_camera_session(camera_id);
        camera_capture_->configure_resources();
    } else
        LOGE("CameraCapture object is missed!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_objectdetection_MainActivity_stopObjectDetection(
        JNIEnv *,
        jobject /* this */) {
    camera_capture_->release_resources();
}

static void process_android_cmd(struct android_app */*app*/, int32_t cmd) {
    if (camera_capture_) {
        switch (cmd) {
            case APP_CMD_INIT_WINDOW:
                camera_capture_->configure_resources();
                break;
            case APP_CMD_TERM_WINDOW:
                camera_capture_->release_resources();
                break;
        }
    }
}

static int32_t process_android_input(struct android_app * /*app*/, AInputEvent *event) {
    if (camera_capture_ && event) {
        camera_capture_->change_detector();
    }
    return 0;
}

extern "C" void android_main(struct android_app *app) {
    LOGI("Native entry point");
    camera_capture_ = std::make_shared<CameraCapture>(app);
    app->onAppCmd = process_android_cmd;
    app->onInputEvent = process_android_input;

    while (!app->destroyRequested) {
        struct android_poll_source *source = nullptr;
        auto result = ALooper_pollOnce(0, nullptr, nullptr, (void **) &source);
        ASSERT(result != ALOOPER_POLL_ERROR, "ALooper_pollOnce returned an error");
        if (source != nullptr) {
            source->process(app, source);
        }
        if (camera_capture_)
            camera_capture_->draw_frame();
    }

    // application is closing ...
    camera_capture_.reset();
}