target=libsub.so
cc=g++
src=$(wildcard *.cpp)
obj=$(patsubst %.cpp, %.o, $(src))

lib_path=../lib

$(target):$(obj)
	$(cc) -shared $^ -o $@
	mv $(target) $(lib_path)/

%.o:$.cpp
	$(cc) -fPIC -c $^

.PHONY:clean
clean:
	rm $(obj) $(lib_path)/$(target)