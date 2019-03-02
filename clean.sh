make clean
rm -rf bin/
rm CMakeCache.txt cmake_install.cmake compile_commands.json Makefile
rm -rf CMakeFiles
cd generator
rm CMakeCache.txt cmake_install.cmake Makefile
rm -rf CMakeFiles
cd ../engine
rm CMakeCache.txt cmake_install.cmake Makefile
rm -rf CMakeFiles
cd ..
