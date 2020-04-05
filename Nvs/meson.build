project('hauser_nvs', 'cpp',
         default_options: ['cpp_std=c++17', 'warning_level=3', 'werror=true'])

inc_dir = include_directories([get_option('include_dir'), 
                               get_option('asio_include_dir')])

srcClient = ['src/client/main.cpp']
srcServer = ['src/server/main.cpp']

thread_dep = dependency('threads')

executable('client',
            sources: srcClient,
            include_directories: inc_dir,
            dependencies: thread_dep)

executable('server',
            sources: srcServer,
            include_directories: inc_dir,
            dependencies: thread_dep)
