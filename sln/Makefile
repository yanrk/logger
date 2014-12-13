project_home         = ..
build_dir            = $(project_home)/sln
bin_dir              = $(project_home)/bin/linux
object_dir           = $(project_home)/.objs
logger_home          = $(project_home)



# includes of logger headers
logger_inc_path      = $(logger_home)/inc
logger_includes      = -I$(logger_inc_path)



# all includes that logger solution needs
includes             = $(logger_includes)



# source files of logger solution
logger_src_path      = $(logger_home)/src
logger_source        = $(filter %.cpp, $(shell find $(logger_src_path) -depth -name "*.cpp"))



# objects of logger solution
logger_objects       = $(logger_source:$(project_home)%.cpp=$(object_dir)%.o)



# system librarys
system_libs          =

# open librarys
open_libs_inc        = $(logger_home)/lib/linux
open_libs            = -L$(open_libs_inc) -lapr-1 -lexpat -laprutil-1 -llog4cxx

# logger depends librarys
logger_depend_libs   = $(system_libs)
logger_depend_libs  += $(open_libs)



# output librarys
logger_output_lib    = $(bin_dir)/libstupid_logger.so



# my g++ not support nullptr and 64bits
# so no -m64, and add a macro -Dnullptr=0

# build flags for objects
build_obj_flags      = -std=c++0x -g -Wall -O1 -pipe -fPIC -Dnullptr=0

# build flags for execution
build_exec_flags     = $(build_obj_flags)

# build flags for dynamic link librarys
build_so_flags       = -shared



# build targets
targets              = mkln logger

# let 'build' be default target, build all targets
build    : $(targets)

mkln    :
	chmod +x ./mkln.sh
	-./mkln.sh

logger   : $(logger_objects)
	@echo
	@echo "@@@@@  start making logger  @@@@@"
	g++ $(build_so_flags) -o $(logger_output_lib) $^ $(logger_depend_libs)
	@echo "@@@@@  make logger success  @@@@@"
	@echo

rmln    :
	chmod +x ./rmln.sh
	-./rmln.sh

# build all objects
$(object_dir)/%.o:$(project_home)/%.cpp
	@dir=`dirname $@`;      \
    if [ ! -d $$dir ]; then \
        mkdir -p $$dir;     \
    fi
	g++ -c $(build_obj_flags) $(includes) -o $@ $<

clean    : rmln
	rm -rf $(object_dir) $(logger_output_lib)

rebuild  : clean build
