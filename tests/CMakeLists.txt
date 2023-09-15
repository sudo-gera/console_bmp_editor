
add_test(NAME same_test8_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/test8.bmp" "--same" "result.bmp")
add_test(NAME same_test8_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/test8.bmp.sum.txt" "result.bmp")


add_test(NAME same_trans_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/trans.bmp" "--same" "result.bmp")
add_test(NAME same_trans_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/trans.bmp.sum.txt" "result.bmp")


add_test(NAME same_greenland_grid_velo_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/greenland_grid_velo.bmp" "--same" "result.bmp")
add_test(NAME same_greenland_grid_velo_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/greenland_grid_velo.bmp.sum.txt" "result.bmp")


add_test(NAME same_test32bf_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/test32bf.bmp" "--same" "result.bmp")
add_test(NAME same_test32bf_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/test32bf.bmp.sum.txt" "result.bmp")


add_test(NAME same_test32v5_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/test32v5.bmp" "--same" "result.bmp")
add_test(NAME same_test32v5_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/test32v5.bmp.sum.txt" "result.bmp")


add_test(NAME same_test32_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/test32.bmp" "--same" "result.bmp")
add_test(NAME same_test32_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/test32.bmp.sum.txt" "result.bmp")


add_test(NAME same_snail_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/snail.bmp" "--same" "result.bmp")
add_test(NAME same_snail_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/snail.bmp.sum.txt" "result.bmp")


add_test(NAME same_test24_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/test24.bmp" "--same" "result.bmp")
add_test(NAME same_test24_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/test24.bmp.sum.txt" "result.bmp")


add_test(NAME same_index_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/index.bmp" "--same" "result.bmp")
add_test(NAME same_index_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/index.bmp.sum.txt" "result.bmp")


add_test(NAME same_all_gray_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/all_gray.bmp" "--same" "result.bmp")
add_test(NAME same_all_gray_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/all_gray.bmp.sum.txt" "result.bmp")


add_test(NAME same_lena_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/lena.bmp" "--same" "result.bmp")
add_test(NAME same_lena_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/lena.bmp.sum.txt" "result.bmp")


add_test(NAME same_test16_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/test16.bmp" "--same" "result.bmp")
add_test(NAME same_test16_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/test16.bmp.sum.txt" "result.bmp")


add_test(NAME same_test1_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/test1.bmp" "--same" "result.bmp")
add_test(NAME same_test1_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/test1.bmp.sum.txt" "result.bmp")


add_test(NAME same_blackbuck_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/blackbuck.bmp" "--same" "result.bmp")
add_test(NAME same_blackbuck_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/blackbuck.bmp.sum.txt" "result.bmp")


add_test(NAME same_bmp_24_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/bmp_24.bmp" "--same" "result.bmp")
add_test(NAME same_bmp_24_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/bmp_24.bmp.sum.txt" "result.bmp")


add_test(NAME same_test32bfv4_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/test32bfv4.bmp" "--same" "result.bmp")
add_test(NAME same_test32bfv4_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/test32bfv4.bmp.sum.txt" "result.bmp")


add_test(NAME same_dots_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/dots.bmp" "--same" "result.bmp")
add_test(NAME same_dots_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/dots.bmp.sum.txt" "result.bmp")


add_test(NAME same_bmp_08_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/bmp_08.bmp" "--same" "result.bmp")
add_test(NAME same_bmp_08_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/bmp_08.bmp.sum.txt" "result.bmp")


add_test(NAME same_test4_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/test4.bmp" "--same" "result.bmp")
add_test(NAME same_test4_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/test4.bmp.sum.txt" "result.bmp")

add_test(NAME same_food_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/food.bmp" "--same" "result.bmp")
add_test(NAME same_food_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/same/food.bmp.sum.txt" "result.bmp")

add_test(NAME negative_food_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/food.bmp" "--negative" "result.bmp")
add_test(NAME negative_food_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/negative/food.bmp.sum.txt" "result.bmp")

add_test(NAME scale_food_5000_7000_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/food.bmp" "--scale" "5000" "7000" "result.bmp")
add_test(NAME scale_food_5000_7000_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/scale/food_5000_7000.bmp.sum.txt" "result.bmp")

add_test(NAME scale_food_7000_5000_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/food.bmp" "--scale" "7000" "5000" "result.bmp")
add_test(NAME scale_food_7000_5000_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/scale/food_7000_5000.bmp.sum.txt" "result.bmp")

add_test(NAME scale_food_700_500_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/food.bmp" "--scale" "700" "500" "result.bmp")
add_test(NAME scale_food_700_500_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/scale/food_700_500.bmp.sum.txt" "result.bmp")

add_test(NAME scale_food_70_50_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/food.bmp" "--scale" "70" "50" "result.bmp")
add_test(NAME scale_food_70_50_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/scale/food_70_50.bmp.sum.txt" "result.bmp")

add_test(NAME scale_food_7_5_create COMMAND bmp "${PROJECT_SOURCE_DIR}/tests/sources/food.bmp" "--scale" "7" "5" "result.bmp")
add_test(NAME scale_food_7_5_check  COMMAND "bash" "${PROJECT_SOURCE_DIR}/tests/checker.sh" "${PROJECT_SOURCE_DIR}/tests/scale/food_7_5.bmp.sum.txt" "result.bmp")

