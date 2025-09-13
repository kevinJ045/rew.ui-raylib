gcc -shared -fPIC -o .artifacts/librayshim.so \
    shim/main.c \
    -I./shim/include \
    -lGL \
    -ldl \
    -lraylib \
    -lassimp
