file(GLOB_RECURSE SRC "*.cpp" "*.c" "*.cxx")
set(EXCLUDE_PATHS
    "CMakeFiles"
)

foreach(TMP_PATH ${SRC})
    foreach(EXCLUDE_PATH ${EXCLUDE_PATHS})
        string(FIND ${TMP_PATH} ${EXCLUDE_PATH} RESULT)
        if(NOT ${RESULT} EQUAL -1)
            list(REMOVE_ITEM SRC ${TMP_PATH})
        endif()
    endforeach(EXCLUDE_PATH)
endforeach(TMP_PATH)

add_library(lib STATIC ${SRC})