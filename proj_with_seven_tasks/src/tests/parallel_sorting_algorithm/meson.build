gtest = dependency('gtest', main: true)
thread_dep = dependency('threads')

test(
    'parallel_sort.cc',
    executable(
        'parallel_sort.cc',
        sources: ['parallel_sort_test.cc'],
        include_directories: src,
        dependencies: [gtest, thread_dep]
    )
)
