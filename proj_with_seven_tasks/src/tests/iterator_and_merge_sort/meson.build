gtest = dependency('gtest', main: true)
test(
    'merge_sort.cc',
    executable(
        'merge_sort',
        sources: ['merge_sort_test.cc'],
        include_directories: src,
        dependencies: [gtest]
    )
)
