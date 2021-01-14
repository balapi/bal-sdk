# BAL API application example
#
# This file demonstrates integrating an application directly in the BAL API source tree.
# hello_bal_app_static application is statically linked with all the required libraries.
#
bcm_module_name(hello_bal_app_static)
bcm_module_dependencies(PRIVATE host_api)
bcm_module_srcs(hello_bal.c)
bcm_create_app_target(fs)
