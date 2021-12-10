fmt        = dependency('fmt')
#gsl        = dependency('gsl')

numerics_cpp = static_library (
	'numerics-cpp',
	sources: [
	    'qf.cpp',
    ],
    dependencies : [fmt],
#    install : true,
)

subdir('tests')
