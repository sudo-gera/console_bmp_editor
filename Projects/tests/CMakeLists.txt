
add_test(NAME same_test8_create COMMAND bmp_cli "str" "infile" "../../tests/sources/test8.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_test8_check  COMMAND "diff" "../../tests/same/test8.bmp" "result.bmp")


add_test(NAME same_trans_create COMMAND bmp_cli "str" "infile" "../../tests/sources/trans.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_trans_check  COMMAND "diff" "../../tests/same/trans.bmp" "result.bmp")


add_test(NAME same_greenland_grid_velo_create COMMAND bmp_cli "str" "infile" "../../tests/sources/greenland_grid_velo.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_greenland_grid_velo_check  COMMAND "diff" "../../tests/same/greenland_grid_velo.bmp" "result.bmp")


add_test(NAME same_test32bf_create COMMAND bmp_cli "str" "infile" "../../tests/sources/test32bf.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_test32bf_check  COMMAND "diff" "../../tests/same/test32bf.bmp" "result.bmp")


add_test(NAME same_test32v5_create COMMAND bmp_cli "str" "infile" "../../tests/sources/test32v5.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_test32v5_check  COMMAND "diff" "../../tests/same/test32v5.bmp" "result.bmp")


add_test(NAME same_test32_create COMMAND bmp_cli "str" "infile" "../../tests/sources/test32.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_test32_check  COMMAND "diff" "../../tests/same/test32.bmp" "result.bmp")


add_test(NAME same_snail_create COMMAND bmp_cli "str" "infile" "../../tests/sources/snail.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_snail_check  COMMAND "diff" "../../tests/same/snail.bmp" "result.bmp")


add_test(NAME same_test24_create COMMAND bmp_cli "str" "infile" "../../tests/sources/test24.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_test24_check  COMMAND "diff" "../../tests/same/test24.bmp" "result.bmp")


add_test(NAME same_index_create COMMAND bmp_cli "str" "infile" "../../tests/sources/index.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_index_check  COMMAND "diff" "../../tests/same/index.bmp" "result.bmp")


add_test(NAME same_all_gray_create COMMAND bmp_cli "str" "infile" "../../tests/sources/all_gray.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_all_gray_check  COMMAND "diff" "../../tests/same/all_gray.bmp" "result.bmp")


add_test(NAME same_lena_create COMMAND bmp_cli "str" "infile" "../../tests/sources/lena.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_lena_check  COMMAND "diff" "../../tests/same/lena.bmp" "result.bmp")


add_test(NAME same_wallpaperflare_create COMMAND bmp_cli "str" "infile" "../../tests/sources/wallpaperflare.com_wallpaper.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_wallpaperflare_check  COMMAND "diff" "../../tests/same/wallpaperflare.com_wallpaper.bmp" "result.bmp")


add_test(NAME same_test16_create COMMAND bmp_cli "str" "infile" "../../tests/sources/test16.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_test16_check  COMMAND "diff" "../../tests/same/test16.bmp" "result.bmp")


add_test(NAME same_test1_create COMMAND bmp_cli "str" "infile" "../../tests/sources/test1.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_test1_check  COMMAND "diff" "../../tests/same/test1.bmp" "result.bmp")


add_test(NAME same_blackbuck_create COMMAND bmp_cli "str" "infile" "../../tests/sources/blackbuck.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_blackbuck_check  COMMAND "diff" "../../tests/same/blackbuck.bmp" "result.bmp")


add_test(NAME same_bmp_24_create COMMAND bmp_cli "str" "infile" "../../tests/sources/bmp_24.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_bmp_24_check  COMMAND "diff" "../../tests/same/bmp_24.bmp" "result.bmp")


add_test(NAME same_test32bfv4_create COMMAND bmp_cli "str" "infile" "../../tests/sources/test32bfv4.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_test32bfv4_check  COMMAND "diff" "../../tests/same/test32bfv4.bmp" "result.bmp")


add_test(NAME same_dots_create COMMAND bmp_cli "str" "infile" "../../tests/sources/dots.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_dots_check  COMMAND "diff" "../../tests/same/dots.bmp" "result.bmp")


add_test(NAME same_bmp_08_create COMMAND bmp_cli "str" "infile" "../../tests/sources/bmp_08.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_bmp_08_check  COMMAND "diff" "../../tests/same/bmp_08.bmp" "result.bmp")


add_test(NAME same_test4_create COMMAND bmp_cli "str" "infile" "../../tests/sources/test4.bmp" "str" "outfile" "result.bmp" "bmp" "=" "read" "[" "infile" "]" "write" "[" "bmp" "outfile" "]")
add_test(NAME same_test4_check  COMMAND "diff" "../../tests/same/test4.bmp" "result.bmp")

