#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/ubuntu/fourmacnum_car_ws/src/rosserial/rosserial_python"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/ubuntu/fourmacnum_car_ws/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/ubuntu/fourmacnum_car_ws/install/lib/python2.7/dist-packages:/home/ubuntu/fourmacnum_car_ws/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/ubuntu/fourmacnum_car_ws/build" \
    "/usr/bin/python2" \
    "/home/ubuntu/fourmacnum_car_ws/src/rosserial/rosserial_python/setup.py" \
     \
    build --build-base "/home/ubuntu/fourmacnum_car_ws/build/rosserial/rosserial_python" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/ubuntu/fourmacnum_car_ws/install" --install-scripts="/home/ubuntu/fourmacnum_car_ws/install/bin"
