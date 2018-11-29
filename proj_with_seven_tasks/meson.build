project(
 'proj_with_seven_tasks',
 'cpp',
 version: '0.1.0',
 meson_version: '>=0.46',
 default_options: ['cpp_std=c++11']
)
subdir('src')

doxyfile = configuration_data() #ключ-значение
doxyfile.set('OUTPUT_DIRECTORY',meson.build_root())
configure_file(input:'Doxyfile.in', output:'Doxyfile',configuration: doxyfile)
#создание файла из шаблона
doxygen =find_program('doxygen')
if doxygen.found() #ninja doc генерирует документацию
 run_target('doc', command: [doxygen,
  join_paths(meson.build_root(),'Doxyfile')])
endif
