
###############  Changeable  Parameters  ##############

include ../Makefile.common

OUTPUT_DIR = ../bld

###############  DO NOT MODIFY BELOW THIS   ##############

SHARED_LIB_NAME         = lib$(PRODUCT_NAME).so.$(VERSION)
STATIC_LIB_NAME         = lib$(PRODUCT_NAME).a.$(VERSION)

ifeq ($(BUILD_MODE), debug)
    SHARED_LIB_NAME     = lib$(PRODUCT_NAME)_debug.so.$(VERSION)
    STATIC_LIB_NAME     = lib$(PRODUCT_NAME)_debug.a.$(VERSION)
endif

SHARED_LIB_OUTPUT       =   "$(OUTPUT_DIR)/$(SHARED_LIB_NAME)"
STATIC_LIB_OUTPUT       =   "$(OUTPUT_DIR)/$(STATIC_LIB_NAME)"

SOURCE_FOLDERS  =   . utils core frontends frontends/chuck
INCLUDE_FOLDERS :=  $(foreach dir,$(SOURCE_FOLDERS),$(dir))
CUTILS_SOURCES   := $(foreach dir,$(SOURCE_FOLDERS),$(wildcard $(dir)/*.c))
CUTILS_OBJS      = $(foreach obj, $(patsubst %.c,%.o,$(CUTILS_SOURCES)), $(OUTPUT_DIR)/src/$(obj))
LIBS            = 

###################     Begin Targets       ######################

# Implicit rule to build .o into the build directory from .c
$(OUTPUT_DIR)/src/%.o : %.c
	@echo Building src/$<  \-\>  $@ 
	@$(GCC)  -std=c99 -c $(CFLAGS) $< -o $@

all: base static shared
	@echo LIB_INSTALL_DIR     = $(LIB_INSTALL_DIR)
	@echo INCLUDE_INSTALL_DIR = $(INCLUDE_INSTALL_DIR)

shared: base $(CUTILS_OBJS)
	@echo Creating Shared Library ...
	@$(GCC) -shared $(CFLAGS) $(CUTILS_OBJS) -o "$(SHARED_LIB_OUTPUT)" $(LIBS)
	@rm -f "$(OUTPUT_DIR)/lib$(PRODUCT_NAME).so"
	@ln -s "$(SHARED_LIB_NAME)" "$(OUTPUT_DIR)/lib$(PRODUCT_NAME).so"

static: base $(CUTILS_OBJS)
	@echo Creating Static Library ...
	@ar rcs "$(STATIC_LIB_OUTPUT)" $(CUTILS_OBJS)
	@rm -f "$(OUTPUT_DIR)/lib$(PRODUCT_NAME).a"
	@ln -s "$(STATIC_LIB_NAME)" "$(OUTPUT_DIR)/lib$(PRODUCT_NAME).a"

install: shared static
	@echo "Copying library files..."
	@mkdir -p "$(LIB_INSTALL_DIR)"
	@mkdir -p "$(INCLUDE_INSTALL_DIR)/lunarprobe"
	@cp -f "$(SHARED_LIB_OUTPUT)" "$(LIB_INSTALL_DIR)"
	@cp -f "$(STATIC_LIB_OUTPUT)" "$(LIB_INSTALL_DIR)"
	@rm -f "$(LIB_INSTALL_DIR)/lib$(PRODUCT_NAME).so"
	@ln -s "$(LIB_INSTALL_DIR)/$(SHARED_LIB_NAME)" "$(LIB_INSTALL_DIR)/lib$(PRODUCT_NAME).so"
	@echo "Copying header files..."
	@cp -f *.h $(INCLUDE_INSTALL_DIR)/lunarprobe

base:
	@echo Building output directories...
	@mkdir -p "$(OUTPUT_DIR)/src"
	@cd $(OUTPUT_DIR)/src ; mkdir -p $(SOURCE_FOLDERS)

.PHONY: clean cleanall distclean
clean:
	@rm -f $(CUTILS_OBJS) $(ENTRY_OBJS)

cleanall: clean
	@rm -f "$(SHARED_LIB_OUTPUT)" "$(STATIC_LIB_OUTPUT)"
	@rm -f "$(OUTPUT_DIR)/lib$(PRODUCT_NAME).so"
	@rm -f "$(OUTPUT_DIR)/lib$(PRODUCT_NAME).a"

distclean: cleanall
	@rm -f Makefile

dep:
	makedepend -Y -p"$(OUTPUT_DIR)/" $(INCLUDE_FLAGS) -- $(CUTILS_SOURCES)

# DO NOT DELETE

../bld/./cuallocator.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h
../bld/./cuallocator.o: cuobject.h cuerror.h cucollection.h culinkedlist.h
../bld/./cuallocator.o: culist.h cuarray.h cumap.h cuset.h custring.h
../bld/./cuallocator.o: custreams.h cuiterator.h cuconcurrency.h
../bld/./cuarray.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h
../bld/./cuarray.o: cuobject.h cuerror.h cucollection.h culinkedlist.h
../bld/./cuarray.o: culist.h cuarray.h cumap.h cuset.h custring.h custreams.h
../bld/./cuarray.o: cuiterator.h cuconcurrency.h
../bld/./cucollection.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h
../bld/./cucollection.o: cuobject.h cuerror.h cucollection.h culinkedlist.h
../bld/./cucollection.o: culist.h cuarray.h cumap.h cuset.h custring.h
../bld/./cucollection.o: custreams.h cuiterator.h cuconcurrency.h
../bld/./cuconcurrency.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h
../bld/./cuconcurrency.o: cuobject.h cuerror.h cucollection.h culinkedlist.h
../bld/./cuconcurrency.o: culist.h cuarray.h cumap.h cuset.h custring.h
../bld/./cuconcurrency.o: custreams.h cuiterator.h cuconcurrency.h
../bld/./cuerror.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h
../bld/./cuerror.o: cuobject.h cuerror.h cucollection.h culinkedlist.h
../bld/./cuerror.o: culist.h cuarray.h cumap.h cuset.h custring.h custreams.h
../bld/./cuerror.o: cuiterator.h cuconcurrency.h
../bld/./cuiterator.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h
../bld/./cuiterator.o: cuobject.h cuerror.h cucollection.h culinkedlist.h
../bld/./cuiterator.o: culist.h cuarray.h cumap.h cuset.h custring.h
../bld/./cuiterator.o: custreams.h cuiterator.h cuconcurrency.h
../bld/./culinkedlist.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h
../bld/./culinkedlist.o: cuobject.h cuerror.h cucollection.h culinkedlist.h
../bld/./culinkedlist.o: culist.h cuarray.h cumap.h cuset.h custring.h
../bld/./culinkedlist.o: custreams.h cuiterator.h cuconcurrency.h
../bld/./culist.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h
../bld/./culist.o: cuobject.h cuerror.h cucollection.h culinkedlist.h
../bld/./culist.o: culist.h cuarray.h cumap.h cuset.h custring.h custreams.h
../bld/./culist.o: cuiterator.h cuconcurrency.h
../bld/./cumap.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h cuobject.h
../bld/./cumap.o: cuerror.h cucollection.h culinkedlist.h culist.h cuarray.h
../bld/./cumap.o: cumap.h cuset.h custring.h custreams.h cuiterator.h
../bld/./cumap.o: cuconcurrency.h
../bld/./cuobject.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h
../bld/./cuobject.o: cuobject.h cuerror.h cucollection.h culinkedlist.h
../bld/./cuobject.o: culist.h cuarray.h cumap.h cuset.h custring.h
../bld/./cuobject.o: custreams.h cuiterator.h cuconcurrency.h
../bld/./cuprototype.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h
../bld/./cuprototype.o: cuobject.h cuerror.h cucollection.h culinkedlist.h
../bld/./cuprototype.o: culist.h cuarray.h cumap.h cuset.h custring.h
../bld/./cuprototype.o: custreams.h cuiterator.h cuconcurrency.h
../bld/./cuset.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h cuobject.h
../bld/./cuset.o: cuerror.h cucollection.h culinkedlist.h culist.h cuarray.h
../bld/./cuset.o: cumap.h cuset.h custring.h custreams.h cuiterator.h
../bld/./cuset.o: cuconcurrency.h
../bld/./custreams.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h
../bld/./custreams.o: cuobject.h cuerror.h cucollection.h culinkedlist.h
../bld/./custreams.o: culist.h cuarray.h cumap.h cuset.h custring.h
../bld/./custreams.o: custreams.h cuiterator.h cuconcurrency.h
../bld/./custring.o: cutils.h cufwddefs.h cuallocator.h cuprototype.h
../bld/./custring.o: cuobject.h cuerror.h cucollection.h culinkedlist.h
../bld/./custring.o: culist.h cuarray.h cumap.h cuset.h custring.h
../bld/./custring.o: custreams.h cuiterator.h cuconcurrency.h
