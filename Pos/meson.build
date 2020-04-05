project('hauser_pos', 'cpp',
         default_options: ['cpp_std=c++17', 'warning_level=3', 'werror=true'])

inc_dir = include_directories([get_option('include_dir')])

src = ['src/main.cpp']

thread_dep = dependency('threads')


executable('hauser_pos',
            sources: src,
            include_directories: inc_dir,
            dependencies: thread_dep)
