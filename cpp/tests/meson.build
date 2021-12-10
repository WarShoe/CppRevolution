incdir = include_directories(['..','../include'])
math = executable(
    'math',
    'math.cpp',
    include_directories : incdir,
    dependencies : [],
    link_with : [numerics_cpp]
)
test('Testing math.', math)

t1 = executable(
    't1',
    't1.cpp',
    include_directories : incdir,
    dependencies : [],
    link_with : [numerics_cpp]
)
test('Testing 1.', t1)
