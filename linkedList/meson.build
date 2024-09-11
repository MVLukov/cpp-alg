project('linked_list', 'cpp', version: '1.0.0', default_options: ['cpp_std=c++17'])

# Specify where the source files are located
src = ['./src/main.cpp']
inc_dirs = include_directories('./src/include')
# Create an executable
add_project_arguments('-Wall', '-Wextra', '-Wshadow', '-Wno-unused-parameter', language: 'cpp')
executable('linked_list', src, include_directories: inc_dirs)

# Add optional compiler/linker flags if needed

# Optionally, you can define dependencies if you're using any external libraries
# dep = dependency('library_name')
# executable('my_executable', src, dependencies: [dep])
