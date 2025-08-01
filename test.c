#include "common_img_utils.h"
#include <stdlib.h>



/* [DEBUG] test_keypoints: 
 * [{'left_eye': (233.89254760742188, 552.4268798828125),
 * 'right_eye': (346.468017578125, 542.976806640625)}] */

int main() {
  StbImage img;
  StbImage rot_img;
  HbImgUtilsStatus status;

  StbImage cropped_image2;
  StbImage eye_rot;
  load_image("./debug/testf3.jpg", &img, &status);
  load_image("./debug/raw_crop1.png", &cropped_image2, &status);
  // rotate_image_by_deg(&img, &rot_img, 128.0f, &status); 
  float left_eye[2] = { 233.89, 552.42 };
  float right_eye[2] = {346.468017578125, 542.976806640625};
  rotate_image_by_keypoint_pair(&cropped_image2,
                      &eye_rot,
                      left_eye,
                      right_eye,
                      &status 
                      );
  
  // if(status == HB_IMG_UTILS_OK) {
  //   printf("rotate sucessful!\n");
  // } else {
  //   hb_img_util_get_error_message(&status);
  // }
}
