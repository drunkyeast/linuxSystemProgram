target=test
src=$(wildcard ./src/*.cpp)
obj=$(patsubst %.cpp, %.o, $(src))
cc=g++

lib_path=./lib
lib_src_path=./libSrc

$(target):$(obj) #目标与依赖, $@表示目标, $^表示全部依赖
	cd $(lib_src_path) && make && cd ../
	$(cc) $^ -L$(lib_path) -lsub -o $@

.PHONY:clean #告诉make这是一个目标, 而不是文件. 例如目录下有一个名叫clean的文件
clean:
	cd $(lib_src_path) && make clean && cd ../
	rm $(target) $(obj)