gtest = dependency('gtest', main: true)
test(
    'rotation.h',
    executable(
        'rotation_test.cc',
        'main_fun_test.cc',
        sources: ['rotation_test.cc','main_fun_test.cc'],
        include_directories: src,
        dependencies: [gtest]
    )
)
