find_package(Git REQUIRED)

if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
	option(GIT_SUBMODULE "Check submodules during build" ON)
	if(GIT_SUBMODULE)
		message(STATUS "updating submodules")
		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
		if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}")
        endif()
	endif()
endif()