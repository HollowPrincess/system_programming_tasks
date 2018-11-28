parallel_sorting_algorithm_src = files([
 'parallel_sort.cc'
])

thread_dep = dependency('threads')

executable(
 'parallel_sorting_algorithm',
 include_directories: src,
 sources: parallel_sorting_algorithm_src,
 dependences: thread_dep,
 install: true
)
