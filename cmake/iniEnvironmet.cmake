message("检索符合的qt环境....")

#检查QT_ROOT环境变量并设置qt路径

if(DEFINED ENV{QT_ROOT})
	message("QT_ROOT：$ENV{QT_ROOT}")

	# 查找符合条件的Qt路径
    file(GLOB QT_PATHS "$ENV{QT_ROOT}/[56]*/msvc2019_64")
    if(QT_PATHS)
        list(GET QT_PATHS 0 QT_PATH) # 获取第一个匹配的路径
        set(CMAKE_PREFIX_PATH ${QT_PATH} PARENT_SCOPE)
        message("找到的QT路径: ${QT_PATH}")
        set(CMAKE_PREFIX_PATH ${QT_PATH})
    else()
     message(FATAL_ERROR "未找到符合条件的QT路径(qt版本应该为5或6)")
    endif()

else()
	message(FATAL_ERROR "QT_ROOT环境变量未定义")
	message("请在系统中定义QT_ROOT（应该为qt的根目录）")
endif()