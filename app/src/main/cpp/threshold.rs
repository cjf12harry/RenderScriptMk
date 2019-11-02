#pragma version(1)
#pragma rs java_package_name(com.packtpub.renderscriptmk)

float thresholdValue;
static const float3 BLACK = { 0.0, 0.0, 0.0 };
static const float3 LUMINANCE_VECTOR = { 0.2125, 0.7154, 0.0721 };

uchar4 __attribute__((kernel)) threshold(uchar4 in) {
    float4 pixel = rsUnpackColor8888(in);
    float luminance = dot(LUMINANCE_VECTOR, pixel.rgb);
    if (luminance < thresholdValue) {
        pixel.rgb = BLACK;
    }
    return rsPackColorTo8888(pixel);
}
