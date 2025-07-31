#include "common_img_utils.h"
#include <stdlib.h>

int main() {
  StbImage img;
  StbImage rot_img;
  HbImgUtilsStatus status;
  load_image("./debug/testf3.jpg", &img, &status);
  rotate_image_by_deg(&img, &rot_img, 128.0f, &status); 
  if(status == HB_IMG_UTILS_OK) {
    printf("rotate sucessful!\n");
  } else {
    hb_img_util_get_error_message(&status);
  }
}
