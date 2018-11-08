gtest = dependency('gtest', main: true)
test(
    'accounts.cc',
    executable(
        'accounts_test',
        sources: ['accounts_test.cc'],
        include_directories: src,
        dependencies: [gtest]
    )
)
