#ifndef HB_IMG_UTILS
#define HB_IMG_UTILS

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// maths constants 
#ifndef M_PI_F
#  define M_PI_F (3.1415926535897932f) /* pi */
#endif
#ifndef M_PI_2_F
#  define M_PI_2_F (1.5707963267948966f) /* pi/2 */
#endif
#ifndef M_PI_3_F
#  define M_PI_3_F (1.0471975511965976f) /* pi/3 */
#endif
#ifndef M_2PI_3_F
#  define M_2PI_3_F (2.0943951023931953f) /* 2pi/3 */
#endif

#ifndef M_PI_6_F
#  define M_PI_6_F (0.5235987755982988f) /* pi/6 */
#endif

#ifndef M_7PI_6_F
#  define M_7PI_6_F (3.665191429188092f) /* 7pi/6 */
#endif

#ifndef M_4PI_3_F
#  define M_4PI_3_F (4.1887902047863905f) /* 4pi/3 */
#endif

#ifndef M_3PI_2_F
#  define M_3PI_2_F (4.71238898038469f) /* 3pi/2 */
#endif


#ifndef M_5PI_6_F
#  define M_5PI_6_F (2.6179938779914944f) /* 5pi/6 */
#endif

#ifndef M_11PI_6_F
#  define M_11PI_6_F (5.759586531581287f) /* 11pi/6 */
#endif


#ifndef M_PI_4_F
#  define M_PI_4_F (0.7853981633974830f) /* pi/4 */
#endif
#ifndef M_1_PI_F
#  define M_1_PI_F (0.3183098861837067f) /* 1/pi */
#endif
#ifndef M_2_PI_F
#  define M_2_PI_F (0.6366197723675813f) /* 2/pi */
#endif
#ifndef M_1_2PI_F
#  define M_1_2PI_F (0.1591549430918953f) /* 1/(2*pi) */
#endif
#ifndef M_1_4PI_F
#  define M_1_4PI_F (0.0795774715459476f) /* 1/(4*pi) */
#endif
#ifndef M_SQRT_PI_8_F
#  define M_SQRT_PI_8_F (0.6266570686577501f) /* sqrt(pi/8) */
#endif
#ifndef M_LN_2PI_F
#  define M_LN_2PI_F (1.8378770664093454f) /* ln(2*pi) */
#endif

/* Multiplication */
#ifndef M_2PI_F
#  define M_2PI_F (6.2831853071795864f) /* 2*pi */
#endif
#ifndef M_4PI_F
#  define M_4PI_F (12.566370614359172f) /* 4*pi */
#endif
#ifndef M_PI_4F
#  define M_PI_4F 0.78539816339744830962f /* pi/4 */
#endif

/* Float sqrt variations */
#ifndef M_SQRT2_F
#  define M_SQRT2_F (1.4142135623730950f) /* sqrt(2) */
#endif
#ifndef M_CBRT2_F
#  define M_CBRT2_F 1.2599210498948732f /* cbrt(2) */
#endif
#ifndef M_SQRT1_2F
#  define M_SQRT1_2F 0.70710678118654752440f /* sqrt(1/2) */
#endif
#ifndef M_SQRT3_F
#  define M_SQRT3_F (1.7320508075688772f) /* sqrt(3) */
#endif
#ifndef M_LN2_F
#  define M_LN2_F (0.6931471805599453f) /* ln(2) */
#endif
#ifndef M_LN10_F
#  define M_LN10_F (2.3025850929940457f) /* ln(10) */
#endif



#define DEG2RAD(x) ((x) * M_PI_F / 180.0)
#define RAD2DEG(x) ((x) * 180.0 / M_PI_F)


typedef struct {
  unsigned char* image;
  int width, height, channels;
} StbImage;



typedef enum {
  HB_IMG_UTILS_OK,
  HB_IMG_UTILS_FAILURE_TO_LOAD_IMAGE,
  HB_IMG_UTILS_FAILURE_TO_ALLOCATE_IMAGE_MEMORY
} HbImgUtilsStatus;

static inline void hb_img_util_get_error_message(const HbImgUtilsStatus* status) {

  switch(*status) {
    case HB_IMG_UTILS_OK:
    fprintf(stdout, "everything ok");
    break;
    case HB_IMG_UTILS_FAILURE_TO_LOAD_IMAGE:
    fprintf(stderr, "image loading failed!");
    break;
    case HB_IMG_UTILS_FAILURE_TO_ALLOCATE_IMAGE_MEMORY:
    fprintf(stderr, "memory allocation failed");
    break;
  }
}

static inline void load_image(const char* filename, StbImage* img, HbImgUtilsStatus* status) {
  int width, height, channels;
  unsigned char* _img = stbi_load(filename, &width, &height, &channels, 0);  
  if (!_img) {
    fprintf(stderr, "[ERROR] falied to load image!");
    *status = HB_IMG_UTILS_FAILURE_TO_LOAD_IMAGE;
    return;
  }
  img->image = _img;
  img->width = width;
  img->channels =  channels;
  img->height = height;
  *status = HB_IMG_UTILS_OK;
}


static inline void rotate_image_by_eye(const StbImage* src_image, StbImage* dst_image, const float left_eye[2], const float right_eye[2], HbImgUtilsStatus* status) {

}

static inline void rotate_image_by_deg(const StbImage* src_image, StbImage* dst_image, const float rotation_degree, HbImgUtilsStatus* status) {
  float angle_rad;
  switch((int) rotation_degree) {
    case 360:
    angle_rad = M_PI_2_F;
    break;
    case 0:
    angle_rad = M_PI_2_F;
    break;
    case 30:
    angle_rad = M_PI_6_F;
    break;
    case 60:
    angle_rad = M_PI_3_F;
    break;
    case 90:
    angle_rad = M_PI_2_F;
    break;
    case 120:
    angle_rad = M_2PI_3_F;
    break;
    case 150:
    angle_rad = M_5PI_6_F;
    break; 
    case 180:
    angle_rad = M_PI_F;
    break;
    case 210:
    angle_rad = M_7PI_6_F;
    break;
    case 240:
    angle_rad = M_4PI_3_F;
    break;
    case 270:
    angle_rad = M_3PI_2_F;
    break;
    case 300:
    angle_rad = M_5PI_6_F;
    break;
    case 330:
    angle_rad = M_11PI_6_F;
    break;
    default:
    angle_rad = DEG2RAD(rotation_degree);
    break;
  }


  float cos_theta = cosf(angle_rad);
  float sin_theta = sinf(angle_rad);
  float new_width = (int)(fabs(src_image->width * cos_theta) + fabs(src_image->height * sin_theta));
  float new_height = (int)(fabs(src_image->width * sin_theta) + fabs(src_image->height * cos_theta));
  // unsigned char* rotated = calloc(new_width * new_height * src_image->channels, 1);
  dst_image->image = calloc(new_width * new_height * src_image->channels, 1);
  if (!dst_image->image) {
    *status = HB_IMG_UTILS_FAILURE_TO_ALLOCATE_IMAGE_MEMORY;
    return;
  }
  float cx = src_image->width / 2.0f;
  float cy = src_image->height / 2.0f;
  float ncx = new_width / 2.0f;
  float ncy = new_height / 2.0f;
  for (int y = 0; y < new_height; y++) {
    for (int x = 0; x < new_width; x++) {
            // Translate to origin
            float dx = x - ncx;
            float dy = y - ncy;

            // Rotate backward
            float src_x = cos_theta * dx + sin_theta * dy + cx;
            float src_y = -sin_theta * dx + cos_theta * dy + cy;

            // Nearest-neighbor lookup
            int isrc_x = (int)(src_x + 0.5f);
            int isrc_y = (int)(src_y + 0.5f);

            if (isrc_x >= 0 && isrc_x < src_image->width && isrc_y >= 0 && isrc_y < src_image->height) {
              for (int c = 0; c < src_image->channels; c++) {
                int dst_index = (y * new_width + x) * src_image->channels + c;
                int src_index = (isrc_y * src_image->width + isrc_x) * src_image->channels + c;
                dst_image->image[dst_index] = src_image->image[src_index];}
            }
        }
  }
  dst_image->channels = src_image->channels;
  dst_image->width = (int) new_width;
  dst_image->height = (int) new_height;
  stbi_write_png("./debug/rotated_51deg.png", new_width, new_height, src_image->channels, dst_image->image, new_width * src_image->channels);
  *status = HB_IMG_UTILS_OK;
}



#endif //HB_IMG_UTILS END
