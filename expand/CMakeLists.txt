cmake_minimum_required( VERSION 2.20 )
 
project(bluez_hal)
 
set(GLIBC_INCLUDE /usr/include/glib-2.0 /usr/lib/x86_64-linux-gnu/glib-2.0/include) 
set(DBUS_INCLUDE /usr/include/dbus-1.0/ /usr/lib/x86_64-linux-gnu/dbus-1.0/include/)

set(GLIBC_LIB glib-2.0) 
set(DBUS_LIB dbus-1) 

include_directories(
    ${GLIBC_INCLUDE}
    ${DBUS_INCLUDE}
    ../
    ./hal
    ./impl
    ../gdbus
)

link_directories(${GLIBC_INCLUDE}) 

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY .)

add_library(${PROJECT_NAME} STATIC
    ../src/shared/util.c
    ../src/shared/util.h
    ../src/shared/timeout-glib.c
    ../src/shared/timeout.h
    ../gdbus/client.c 
    ../gdbus/mainloop.c  
    ../gdbus/object.c  
    ../gdbus/polkit.c  
    ../gdbus/watch.c
    ../src/shared/io-glib.c  
    ../src/shared/mainloop-glib.c  
    ../src/shared/mainloop-notify.h 
    ../src/shared/mainloop-notify.c

    hal/hal_ble.c 
    hal/hal_hw.c
    hal/hal_timer.c
    hal/hal_flash.c
    hal/hal_watchdog.c
    impl/advertising.c
    impl/client.c
    impl/gatt.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .)
 
add_executable(hal_test ./hal_test.c)
 
target_link_libraries(hal_test ${PROJECT_NAME} ${GLIBC_LIB} ${DBUS_LIB} pthread)
