python3    = dependency('python')
py3        = import('python')

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
