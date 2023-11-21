project('task-cad-1', 'cpp', default_options : ['cpp_std=c++23', 'warning_level=everything'])

openmp = dependency('openmp')

curves_lib = shared_library('curves-lib', 'src/curves.cpp', install: true)
executable('task-cad-1', 'src/main.cpp', dependencies : [openmp], link_with : [curves_lib], install: true)
