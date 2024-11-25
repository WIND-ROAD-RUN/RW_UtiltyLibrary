##在Windows额外构建
if(${CMAKE_SYSTEM_NAME}  STREQUAL "Windows")
    #add_subdirectory(oulq)
endif()

add_subdirectory(cdm) #Common data models
add_subdirectory(oso) 
#add_subdirectory(cfgr)
add_subdirectory(dsl)
add_subdirectory(tdp)
add_subdirectory(extra)