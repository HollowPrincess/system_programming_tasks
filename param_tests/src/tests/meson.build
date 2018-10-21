gtest = dependency('gtest', main: true)
test(
    'MyArray2D.cc',
    executable(
        'array2D_test.cc',
        'mask_test.cc',
        sources: ['array2D_test.cc','mask_test.cc'],
        include_directories: src,
        dependencies: [gtest]
    )
)
