message(STATUS "Retrieve compatible Qt environments")

#检查QT_ROOT环境变量并设置qt路径

if(DEFINED ENV{QT_ROOT})
	message("QT_ROOT：$ENV{QT_ROOT}")

	# 查找符合条件的Qt路径
    file(GLOB QT_PATHS "$ENV{QT_ROOT}/[56]*/msvc2019_64")
    if(QT_PATHS)
        list(GET QT_PATHS 0 QT_PATH) # 获取第一个匹配的路径
        set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${QT_PATH}") # 添加到CMAKE_PREFIX_PATH
        message("Found QT path: ${QT_PATH}")
    else()
     message(FATAL_ERROR "No QT path found that meets the criteria (Qt major version should be 5 or 6)")
    endif()

else()
	message(FATAL_ERROR "QT_ROOT environment variable undefined")
	message("Please define QT_ROOT in the system (which should be the root directory of qt)")
endif()