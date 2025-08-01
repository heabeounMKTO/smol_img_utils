// #include "common_img_utils.h"
// #include <stdlib.h>

// /* [DEBUG] test_keypoints:
//  *[{
//  'left_eye': (631.6034545898438, 230.62551879882812),
//  'right_eye': (759.8145141601562, 210.94581604003906)
//  }]
//  */

// int
// main()
// {
//   StbImage img;
//   StbImage rot_img;
//   HbImgUtilsStatus status;

//   StbImage cropped_image2;
//   StbImage eye_rot;
//   load_image("./debug/testf3.jpg", &img, &status);
//   load_image("./debug/raw_crop1.png", &cropped_image2, &status);
//   // rotate_image_by_deg(&img, &rot_img, 128.0f, &status);
//   float left_eye[2] = { 631.6034545898438, 230.62551879882812 };
//   float right_eye[2] = { 759.81451416015625, 210.94581604003906 };
//   hb_img_rotate_image_by_keypoint_pair(
//     &cropped_image2, &eye_rot, left_eye, right_eye, &status);

//   // if(status == HB_IMG_UTILS_OK) {
//   //   printf("rotate sucessful!\n");
//   // } else {
//   //   hb_img_util_get_error_message(&status);
//   // }
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_img_utils.h"

// Test helper function to check if two images are approximately equal
int compare_images(const StbImage *img1, const StbImage *img2, float tolerance) {
    if (img1->width != img2->width || img1->height != img2->height || img1->channels != img2->channels) {
        return 0;
    }
    
    int total_pixels = img1->width * img1->height * img1->channels;
    for (int i = 0; i < total_pixels; i++) {
        if (abs(img1->image[i] - img2->image[i]) > tolerance) {
            return 0;
        }
    }
    return 1;
}

// Test loading an image
void test_load_image() {
    printf("Testing image loading...\n");
    StbImage img;
    HbImgUtilsStatus status;
    
    load_image("debug/raw_crop1.png", &img, &status);
    
    if (status == HB_IMG_UTILS_OK) {
        printf("✓ Image loaded successfully: %dx%d, %d channels\n", img.width, img.height, img.channels);
        // Clean up
        stbi_image_free(img.image);
    } else {
        printf("✗ Failed to load image\n");
    }
}

// Test rotation by 0 degrees (should be identical)
void test_rotate_0_degrees() {
    printf("Testing 0-degree rotation...\n");
    StbImage src_img, dst_img;
    HbImgUtilsStatus status;
    
    // Load test image
    load_image("debug/raw_crop1.png", &src_img, &status);
    if (status != HB_IMG_UTILS_OK) {
        printf("✗ Failed to load test image\n");
        return;
    }
    
    // Rotate by 0 degrees
    hb_img_rotate_image_by_deg(&src_img, &dst_img, 0.0f, &status);
    
    if (status == HB_IMG_UTILS_OK) {
        printf("✓ 0-degree rotation successful\n");
        // Clean up
        free(dst_img.image);
        stbi_image_free(src_img.image);
    } else {
        printf("✗ 0-degree rotation failed\n");
        stbi_image_free(src_img.image);
    }
}

// Test rotation by 90 degrees
void test_rotate_90_degrees() {
    printf("Testing 90-degree rotation...\n");
    StbImage src_img, dst_img;
    HbImgUtilsStatus status;
    
    // Load test image
    load_image("debug/raw_crop1.png", &src_img, &status);
    if (status != HB_IMG_UTILS_OK) {
        printf("✗ Failed to load test image\n");
        return;
    }
    
    // Rotate by 90 degrees
    hb_img_rotate_image_by_deg(&src_img, &dst_img, 90.0f, &status);
    
    if (status == HB_IMG_UTILS_OK) {
        printf("✓ 90-degree rotation successful: %dx%d -> %dx%d\n", 
               src_img.width, src_img.height, dst_img.width, dst_img.height);
        // Clean up
        free(dst_img.image);
        stbi_image_free(src_img.image);
    } else {
        printf("✗ 90-degree rotation failed\n");
        stbi_image_free(src_img.image);
    }
}

// Test rotation by 180 degrees
void test_rotate_180_degrees() {
    printf("Testing 180-degree rotation...\n");
    StbImage src_img, dst_img;
    HbImgUtilsStatus status;
    
    // Load test image
    load_image("debug/raw_crop1.png", &src_img, &status);
    if (status != HB_IMG_UTILS_OK) {
        printf("✗ Failed to load test image\n");
        return;
    }
    
    // Rotate by 180 degrees
    hb_img_rotate_image_by_deg(&src_img, &dst_img, 180.0f, &status);
    
    if (status == HB_IMG_UTILS_OK) {
        printf("✓ 180-degree rotation successful: %dx%d -> %dx%d\n", 
               src_img.width, src_img.height, dst_img.width, dst_img.height);
        // Clean up
        free(dst_img.image);
        stbi_image_free(src_img.image);
    } else {
        printf("✗ 180-degree rotation failed\n");
        stbi_image_free(src_img.image);
    }
}

// Test path validation
void test_path_validation() {
    printf("Testing path validation...\n");
    int result = check_path_valid("debug/raw_crop1.png");
    
    if (result == HB_IMG_UTILS_OK) {
        printf("✓ Path validation successful - file exists\n");
    } else {
        printf("✗ Path validation failed - file does not exist\n");
    }
}

// Test error handling
void test_error_handling() {
    printf("Testing error handling...\n");
    StbImage img;
    HbImgUtilsStatus status;
    
    // Try to load non-existent file
    load_image("non_existent_file.png", &img, &status);
    
    if (status == HB_IMG_UTILS_FAILURE_TO_LOAD_IMAGE) {
        printf("✓ Error handling works correctly for missing file\n");
    } else {
        printf("✗ Error handling failed\n");
    }
}

// Test keypoint rotation (basic)
void test_keypoint_rotation() {
    printf("Testing keypoint rotation...\n");
    StbImage src_img, dst_img;
    HbImgUtilsStatus status;
    
    // Load test image
    load_image("debug/raw_crop1.png", &src_img, &status);
    if (status != HB_IMG_UTILS_OK) {
        printf("✗ Failed to load test image\n");
        return;
    }
    
    // Define fake eye positions (center of image)
    float left_eye[2] = {src_img.width * 0.25f, src_img.height * 0.5f};
    float right_eye[2] = {src_img.width * 0.75f, src_img.height * 0.5f};
    
    // Rotate by keypoint pair (should be close to 0 degrees)
    hb_img_rotate_image_by_keypoint_pair(&src_img, &dst_img, left_eye, right_eye, &status);
    
    if (status == HB_IMG_UTILS_OK) {
        printf("✓ Keypoint rotation successful\n");
        // Clean up
        free(dst_img.image);
        stbi_image_free(src_img.image);
    } else {
        printf("✗ Keypoint rotation failed\n");
        stbi_image_free(src_img.image);
    }
}

// Test all functions
int main() {
    printf("Running unit tests for hb_img_utils...\n\n");
    
    test_path_validation();
    test_load_image();
    test_error_handling();
    test_rotate_0_degrees();
    test_rotate_90_degrees();
    test_rotate_180_degrees();
    test_keypoint_rotation();
    
    printf("\nUnit tests completed.\n");
    return 0;
}


