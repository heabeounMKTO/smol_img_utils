#include "common_img_utils.h"
#include <stdlib.h>

/* [DEBUG] test_keypoints:
 *[{
 'left_eye': (631.6034545898438, 230.62551879882812), 
 'right_eye': (759.8145141601562, 210.94581604003906)
 }]
 */

int main() {
  StbImage img;
  StbImage rot_img;
  HbImgUtilsStatus status;

  StbImage cropped_image2;
  StbImage eye_rot;
  load_image("./debug/testf3.jpg", &img, &status);
  load_image("./debug/raw_crop1.png", &cropped_image2, &status);
  // rotate_image_by_deg(&img, &rot_img, 128.0f, &status);
  float left_eye[2] = {631.6034545898438, 230.62551879882812};
  float right_eye[2] = {759.81451416015625, 210.94581604003906};
  rotate_image_by_keypoint_pair(&cropped_image2, &eye_rot, left_eye, right_eye,
                                &status);

  // if(status == HB_IMG_UTILS_OK) {
  //   printf("rotate sucessful!\n");
  // } else {
  //   hb_img_util_get_error_message(&status);
  // }
}
