gtest = dependency('gtest', main: true)
test(
    'parallel_sort.cc',
    executable(
        'parallel_sort',
        sources: ['parallel_sort_test.cc'],
        include_directories: src,
        dependencies: [gtest]
    )
)
