python3    = dependency('python3-devel')
py3        = import('python3-devel')

py3.extension_module (
    'numerics_py', [
        'binding.cpp',
    ],
    include_directories : ['../cpp'],
    link_with           : [numerics_cpp],
    dependencies        : [python3],
#	  install             : true,
#	  install_dir         : get_option('prefix')+'/lib/python3.8/site-packages/',
)
