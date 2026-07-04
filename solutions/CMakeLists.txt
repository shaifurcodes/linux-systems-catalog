cmake_minimum_required(VERSION 3.18)

# Force CMake to generate the compile_commands.json configuration database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(canonical_linux_devices C CXX)

# --- 1. Platform Validation -------------------------------------------------
if(NOT UNIX AND NOT APPLE)
    message(FATAL_ERROR "Unsupported Operating System. This project only supports Linux and macOS.")
endif()

enable_testing()

# --- 2. macOS Homebrew Path Fix ------------------------------------------------
if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew" "/usr/local")
endif()

# --- 3. Explicit File Arguments / Defaults ----------------------------------
set(SRC_FILE "" CACHE STRING "Optional: Path to a single C source file")
set(TEST_FILE "" CACHE STRING "Optional: Path to a single C++ test file")

# --- 4. Compiler Settings ---------------------------------------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND COMMON_FLAGS "-Wall" "-Wextra" "-Wpedantic")
list(APPEND COMMON_SANITIZERS "-fsanitize=address,undefined")

# --- 5. Find Dependencies ---------------------------------------------------
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# --- 6. Resolve Targets Dynamically -----------------------------------------

# Determine Source Files
if(SRC_FILE)
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_FILE}")
        message(FATAL_ERROR "Source file not found: ${SRC_FILE}")
    endif()
    set(ALL_SOURCES "${SRC_FILE}")
    message(STATUS "Building Single Source Target: ${SRC_FILE}")
else()
    # Fallback: Collect EVERY .c file inside the src directory
    file(GLOB_RECURSE ALL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
    if(NOT ALL_SOURCES)
        message(FATAL_ERROR "No .c source files found in the src/ directory.")
    endif()
    message(STATUS "No explicit source specified. Compiling all discovered files in src/")
endif()

# Compile the active source library
add_library(active_solution STATIC ${ALL_SOURCES})
target_include_directories(active_solution PUBLIC include)
target_compile_options(active_solution PRIVATE ${COMMON_FLAGS} ${COMMON_SANITIZERS})
target_link_options(active_solution INTERFACE ${COMMON_SANITIZERS})

# Determine Test Files
if(TEST_FILE)
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${TEST_FILE}")
        message(FATAL_ERROR "Test file not found: ${TEST_FILE}")
    endif()
    
    message(STATUS "Building Single Test Target: ${TEST_FILE}")
    add_executable(run_tests ${TEST_FILE})
    
    # Force explicit GTest include path injection into the single file compilation command strings
    target_include_directories(run_tests PRIVATE ${GTEST_INCLUDE_DIRS})
    
    target_compile_options(run_tests PRIVATE ${COMMON_FLAGS} ${COMMON_SANITIZERS})
    target_link_options(run_tests PRIVATE ${COMMON_SANITIZERS})
    target_link_libraries(run_tests PRIVATE active_solution GTest::gtest GTest::gtest_main Threads::Threads)
    
    add_test(NAME current_file_test COMMAND run_tests)
else()
    # Fallback: Collect EVERY .cpp file inside the tests directory
    file(GLOB_RECURSE ALL_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
    
    if(ALL_TEST_FILES)
        message(STATUS "No explicit test file specified. Registering all discovered tests.")
        
        # Loop through each discovered test file and create an isolated executable target for it
        foreach(TEST_PATH ${ALL_TEST_FILES})
            # Extract file name without path or extension (e.g., "test_p01_ring_buffer")
            get_filename_component(TEST_NAME ${TEST_PATH} NAME_WE)
            
            add_executable(${TEST_NAME} ${TEST_PATH})
            
            # Force explicit GTest include path injection into batch target compilation command strings
            target_include_directories(${TEST_NAME} PRIVATE ${GTEST_INCLUDE_DIRS})
            
            target_compile_options(${TEST_NAME} PRIVATE ${COMMON_FLAGS} ${COMMON_SANITIZERS})
            target_link_options(${TEST_NAME} PRIVATE ${COMMON_SANITIZERS})
            target_link_libraries(${TEST_NAME} PRIVATE active_solution GTest::gtest GTest::gtest_main Threads::Threads)
            
            # Register this test file with CTest explicitly
            add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
        endforeach()
    else()
        message(WARNING "No test files found in the tests/ directory. Only checking compilation.")
    endif()
endif()
