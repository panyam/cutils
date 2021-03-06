
###############  Changeable  Parameters  ##############

include ../Makefile.common

OUTPUT_DIR = ../bld

ifeq ($(MAIN_EXE_NAME),)
    MAIN_EXE_NAME     =   cutilstest
endif

###############  DO NOT MODIFY BELOW THIS   ##############

UNITTEST_PP_DIR     = ./UnitTest++
TEST_SOURCE_FOLDERS = .
INCLUDE_FOLDERS     = ../src 
TEST_SOURCES        := $(foreach dir,$(TEST_SOURCE_FOLDERS),$(wildcard $(dir)/*.cpp))
UNITTEST_PP_SOURCES := $(wildcard $(UNITTEST_PP_DIR)/*.cpp) $(wildcard $(UNITTEST_PP_DIR)/Posix/*.cpp)

ALL_SOURCES_IN_INCLUDE_FOLDERS  := $(shell find $(INCLUDE_FOLDERS) -name \*.[ch] )
SOURCES_WITH_TEST_TAGS          = $(shell grep -l "@test" $(ALL_SOURCES_IN_INCLUDE_FOLDERS) )

TEST_OBJS           = $(foreach obj, $(patsubst %.cpp,%.o,$(TEST_SOURCES)), $(OUTPUT_DIR)/tests/$(obj))
UNITTEST_PP_OBJS 		= $(patsubst %.cpp,%.o,$(UNITTEST_PP_SOURCES)) 
TEST_OUTPUT         = $(OUTPUT_DIR)/$(MAIN_EXE_NAME)
ARCHIVES            = # $(UNITTEST_PP_DIR)/libUnitTest++.a

LIBS                = 


###################     Begin Targets       ######################

# Implicit rule to build .o into the build directory from .cpp
$(OUTPUT_DIR)/tests/%.o : %.cpp
	@echo Building tests/$<  \-\>  $@ 
	@$(GPP) -I$(UNITTEST_PP_DIR) -I. -c $(CFLAGS) $< -o $@

$(UNITTEST_PP_DIR)/%.o : %.cpp
	@echo Building tests/$<  \-\>  $@ 
	@$(GPP) -I$(UNITTEST_PP_DIR) -I. -c $(CFLAGS) $< -o $@

.PHONY: clean cleanall distclean tests

tests: base $(TEST_OBJS) $(UNITTEST_PP_OBJS) 
	@echo Building Test with Static Libraries...
	@$(GPP) $(CFLAGS) $(TEST_OBJS) $(UNITTEST_PP_OBJS) $(OUTPUT_DIR)/libcutils.a $(ARCHIVES) -o $(TEST_OUTPUT) $(LIBS)
	@echo 
	@echo Running Tests...
	@echo 
	$(TEST_OUTPUT)

base:
	@echo Building test output directories...
	@mkdir -p "$(OUTPUT_DIR)/tests" "$(OUTPUT_DIR)/UnitTest++" "$(OUTPUT_DIR)/UnitTest++/Posix"

clean:
	@echo Tests Objs: $(TEST_OBJS)
	@rm -f $(TEST_OBJS)

cleanall: clean
	@rm -f "$(TEST_OUTPUT)"

distclean: cleanall
	@rm -f Makefile

dep:
	makedepend -Y -p"$(OUTPUT_DIR)/" $(INCLUDE_FLAGS)  -- $(TEST_SOURCES)
# DO NOT DELETE

../bld/./allocator.o: ../src/cutils.h ../src/cufwddefs.h ../src/cuallocator.h
../bld/./allocator.o: ../src/cuprototype.h ../src/cuobject.h ../src/cuerror.h
../bld/./allocator.o: ../src/cucollection.h ../src/culinkedlist.h
../bld/./allocator.o: ../src/culist.h ../src/cuarray.h ../src/cumap.h
../bld/./allocator.o: ../src/cuset.h ../src/custring.h ../src/custreams.h
../bld/./allocator.o: ../src/cuiterator.h ../src/cuconcurrency.h
../bld/./arraytests.o: ../src/cutils.h ../src/cufwddefs.h
../bld/./arraytests.o: ../src/cuallocator.h ../src/cuprototype.h
../bld/./arraytests.o: ../src/cuobject.h ../src/cuerror.h
../bld/./arraytests.o: ../src/cucollection.h ../src/culinkedlist.h
../bld/./arraytests.o: ../src/culist.h ../src/cuarray.h ../src/cumap.h
../bld/./arraytests.o: ../src/cuset.h ../src/custring.h ../src/custreams.h
../bld/./arraytests.o: ../src/cuiterator.h ../src/cuconcurrency.h
