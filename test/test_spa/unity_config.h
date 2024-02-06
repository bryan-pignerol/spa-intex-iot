#include <unity_config.h>

[env:extra_unity_options]
platform = native
build_flags =
    -D UNITY_INT_WIDTH=16
    -D UNITY_FLOAT_TYPE=float16_t