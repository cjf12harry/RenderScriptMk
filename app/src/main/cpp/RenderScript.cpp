//
// Created by cjf12 on 2019-10-28.
//

#include <android/bitmap.h>
#include <jni.h>
#include <RenderScript.h>

using namespace android::RSC;

void lockBitmap(JNIEnv *pEnv, jobject pImage, AndroidBitmapInfo *pInfo, uint32_t **pContent) {
    if (AndroidBitmap_getInfo(pEnv, pImage, pInfo) < 0) abort();
    if (pInfo->format != ANDROID_BITMAP_FORMAT_RGBA_8888) abort();
    if (AndroidBitmap_lockPixels(pEnv, pImage, (void **) pContent) < 0) abort();
}

void unlockBitmap(JNIEnv *pEnv, jobject pImage) {
    if (AndroidBitmap_unlockPixels(pEnv, pImage) < 0) abort();
}

extern "C" {
JNIEXPORT void JNICALL
Java_com_packtpub_renderscriptmk_RenderScriptActivity_blur(
        JNIEnv *pEnv, jobject pClass, jstring pCacheDir, jobject pSrcImage,
        jobject pDstImage, jfloat pRadius) {
    const char *cacheDir = pEnv->GetStringUTFChars(pCacheDir, NULL);

    sp<RS> rs = new RS();
    rs->init(cacheDir);
    pEnv->ReleaseStringUTFChars(pCacheDir, cacheDir);

    AndroidBitmapInfo srcInfo;
    uint32_t *srcContent;
    AndroidBitmapInfo dstInfo;
    uint32_t *dstContent;
    lockBitmap(pEnv, pSrcImage, &srcInfo, &srcContent);
    lockBitmap(pEnv, pDstImage, &dstInfo, &dstContent);

    sp<const Type> srcType = Type::create(rs, Element::RGBA_8888(rs),
                                          srcInfo.width, srcInfo.height, 0);
    sp<Allocation> srcAlloc = Allocation::createTyped(rs, srcType,
                                                      RS_ALLOCATION_MIPMAP_NONE,
                                                      RS_ALLOCATION_USAGE_SHARED |
                                                      RS_ALLOCATION_USAGE_SCRIPT,
                                                      srcContent);

    sp<const Type> dstType = Type::create(rs, Element::RGBA_8888(rs),
                                          dstInfo.width, dstInfo.height, 0);
    sp<Allocation> dstAlloc = Allocation::createTyped(rs, dstType,
                                                      RS_ALLOCATION_MIPMAP_NONE,
                                                      RS_ALLOCATION_USAGE_SHARED |
                                                      RS_ALLOCATION_USAGE_SCRIPT,
                                                      dstContent);

    sp<ScriptIntrinsicBlur> blurIntrinsic = ScriptIntrinsicBlur::create(rs, Element::RGBA_8888(rs));
    blurIntrinsic->setRadius(pRadius);

    blurIntrinsic->setInput(srcAlloc);
    blurIntrinsic->forEach(dstAlloc);
    dstAlloc->copy2DRangeTo(0, 0, dstInfo.width, dstInfo.height, dstContent);

    unlockBitmap(pEnv, pSrcImage);
    unlockBitmap(pEnv, pDstImage);
}

/*
JNIEXPORT void JNICALL
Java_com_packtpub_renderscript_RenderScriptActivity_threshold
        (JNIEnv *pEnv, jobject pClass, jstring pCacheDir, jobject pSrcImage,
         jobject pDstImage, jfloat pThreshold) {
    const char *cacheDir = pEnv->GetStringUTFChars(pCacheDir, NULL);
    sp<RS> rs = new RS();
    rs->init(cacheDir);
    pEnv->ReleaseStringUTFChars(pCacheDir, cacheDir);

    AndroidBitmapInfo srcInfo;
    uint32_t *srcContent;
    AndroidBitmapInfo dstInfo;
    uint32_t *dstContent;
    lockBitmap(pEnv, pSrcImage, &srcInfo, &srcContent);
    lockBitmap(pEnv, pDstImage, &dstInfo, &dstContent);

    sp<const Type> srcType = Type::create(rs, Element::RGBA_8888(rs),
                                          srcInfo.width, srcInfo.height, 0);
    sp<Allocation> srcAlloc = Allocation::createTyped(rs, srcType,
                                                      RS_ALLOCATION_MIPMAP_NONE,
                                                      RS_ALLOCATION_USAGE_SHARED |
                                                      RS_ALLOCATION_USAGE_SCRIPT,
                                                      srcContent);

    sp<const Type> dstType = Type::create(rs, Element::RGBA_8888(rs),
                                          dstInfo.width, dstInfo.height, 0);
    sp<Allocation> dstAlloc = Allocation::createTyped(rs, dstType,
            RS_ALLOCATION_MIPMAP_NONE,
            RS_ALLOCATION_USAGE_SHARED| RS_ALLOCATION_USAGE_SCRIPT,
            dstContent);
    sp<ScriptC_threshold> thresholdKernel = new ScriptC_threshold(rs);
    thresholdKernel->set_thresholdValue(pThreshold);

    thresholdKernel->forEach_threshold(srcAlloc, dstAlloc);
    dstAlloc->copy2DRangeTo(0,0, dstInfo.width, dstInfo.height, dstContent);

    unlockBitmap(pEnv, pSrcImage);
    unlockBitmap(pEnv, pDstImage);
}
 */
}




