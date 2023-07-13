# pip3 install conan==1.*

mkdir build
cd build

conan install ..
#rem conan install --build missing ..

cmake ..

cmake --build .
