# Utility function to find all sources and headers in a list of directories
function(find_sources_and_headers result_var)
    set(sources_and_headers)
    foreach(path IN LISTS ARGN)
        file(GLOB_RECURSE headers "${path}/*.h")
        file(GLOB_RECURSE sources "${path}/*.cpp")
        list(APPEND sources_and_headers ${headers} ${sources})
    endforeach()
    set(${result_var} ${sources_and_headers} PARENT_SCOPE)
endfunction()

# Utility function to find all sources and headers in a list of directories and group them
function(group_sources_and_headers group_name)
    set(SOURCESFILES)
    set(HEADERSFILES)
    foreach(path IN LISTS ARGN)
        file(GLOB_RECURSE headers "${path}/*.h")
        file(GLOB_RECURSE sources "${path}/*.cpp")
        list(APPEND HEADERSFILES ${headers})
        list(APPEND SOURCESFILES ${sources})
    endforeach()
    
    # Create source group
    source_group("${group_name}/include" FILES ${HEADERSFILES})
    source_group("${group_name}/src" FILES ${SOURCESFILES})
endfunction()

# Utility function to find all sources and headers in a list of directories and group them
function(group_interface_sources_and_headers)
    set(SOURCESFILES)
    set(HEADERSFILES)
    foreach(path IN LISTS ARGN)
        file(GLOB_RECURSE headers "${path}/*.h")
        file(GLOB_RECURSE sources "${path}/*.cpp")
        list(APPEND HEADERSFILES ${headers})
        list(APPEND SOURCESFILES ${sources})
    endforeach()
    
    # Create source group
    source_group("Header Files" FILES ${HEADERSFILES})
    source_group("Source Files" FILES ${SOURCESFILES})
endfunction()

