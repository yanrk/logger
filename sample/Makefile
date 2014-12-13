project_home       = .
build_dir          = $(project_home)
bin_dir            = $(project_home)/bin/linux
object_dir         = $(project_home)/.objs
logger_home        = $(project_home)



# includes of local headers
logger_inc_path    = $(logger_home)/inc
logger_includes    = -I$(logger_inc_path)

# all includes that local solution needs
includes           = $(local_includes)



# source files of local solution
local_src_path     = $(project_home)
local_source       = $(filter %.cpp, $(shell find $(local_src_path) -depth -name "*.cpp"))



# objects of local solution
local_objects      = $(local_source:$(project_home)%.cpp=$(object_dir)%.o)



# system librarys
system_libs        =

# logger librarys
logger_lib_inc     = $(logger_home)/bin/linux
logger_libs        = -L$(logger_lib_inc) -lapr-1 -lexpat -laprutil-1 -llog4cxx -lstupid_logger

# local depends librarys
depend_libs        = $(system_libs)
depend_libs       += $(logger_libs)



# output execution
output_exec        = $(bin_dir)/logger_test



# my g++ not support nullptr and 64bits
# so no -m64, and add a macro -Dnullptr=0

# build flags for objects
build_obj_flags    = -std=c++0x -g -Wall -O1 -pipe -fPIC -Dnullptr=0

# build flags for execution
build_exec_flags   = $(build_obj_flags)



# build targets
targets            = mkln test

# let 'build' be default target, build all targets
build   : $(targets)

mkln    :
	chmod +x ./mkln.sh
	-./mkln.sh

test    : $(local_objects)
	@echo
	@echo "@@@@@  start making logger_test  @@@@@"
	g++ $(build_exec_flags) -o $(output_exec) $^ $(depend_libs)
	@echo "@@@@@  make logger_test success  @@@@@"
	@echo

run     :
	@export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(bin_dir) && $(output_exec)

rmln    :
	chmod +x ./rmln.sh
	-./rmln.sh

# it same as: @env LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(bin_dir) $(output_exec)

# build all objects
$(object_dir)/%.o:$(project_home)/%.cpp
	@dir=`dirname $@`;      \
    if [ ! -d $$dir ]; then \
        mkdir -p $$dir;     \
    fi
	g++ -c $(build_obj_flags) $(includes) -o $@ $<

clean    : rmln
	rm -rf $(object_dir) $(output_exec)

rebuild  : clean build
