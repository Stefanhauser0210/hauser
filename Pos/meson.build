project('hauser_pos', 'cpp',
         default_options: ['cpp_std=c++17', 'warning_level=3', 'werror=true'])


doctest_dir = include_directories([get_option('doctest_include_dir')])
inc_dir = include_directories([get_option('include_dir'), 
                               get_option('toml_include_dir'),
                               get_option('spdlog_include_dir'),
                               get_option('doctest_include_dir')])


src = ['src/main.cpp', 'src/PD_Automaton.cpp', 'src/Logger.cpp']

thread_dep = dependency('threads')


executable('hauser_pos',
            sources: src,
            include_directories: inc_dir,
            dependencies: thread_dep)


test_src = ['test/test.cpp', 'src/PD_Automaton.cpp', 'src/Logger.cpp']

test_exe = executable('test_exe',
                       sources: test_src,
                       include_directories : [inc_dir, doctest_dir])

test('test', test_exe)
