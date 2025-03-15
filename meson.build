project('libeasyrpn', 'c')

inc = include_directories('include')
install_headers('include/easyrpn.h')
libeasyrpn = static_library('libeasyrpn', 'easyrpn.c', include_directories: inc, install: true)

libeasyrpn_dep = declare_dependency(include_directories: inc, link_with: libeasyrpn)
