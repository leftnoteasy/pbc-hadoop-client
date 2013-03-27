CC = gcc
CFLAGS = -O2 -g
AR = ar rc

BUILD = build

.PHONY : all lib clean tool

LIBSRCS = main.c
LIBNAME = libhdclient.a

TESTSRCS = main.c pb_test.c

BUILD_O = $(BUILD)/o

all : ext-make lib test 

ext-make:
	make -C ext/pbc

lib : $(LIBNAME)

clean : clean-current clean-ext

clean-current:
	rm -rf $(BUILD)

clean-ext:
	rm -rf ext/pbc/$(BUILD)

$(BUILD) : $(BUILD_O)

$(BUILD_O) :
	mkdir -p $@

LIB_O :=

define BUILD_temp
  TAR :=  $(BUILD_O)/$(notdir $(basename $(1)))
  LIB_O := $(LIB_O) $$(TAR).o
  $$(TAR).o : | $(BUILD_O)
  -include $$(TAR).d
  $$(TAR).o : src/$(1)
	$(CC) $(CFLAGS) -c -Isrc -I. -o $$@ -MMD $$<
endef

$(foreach s,$(LIBSRCS),$(eval $(call BUILD_temp,$(s))))

$(LIBNAME) : $(LIB_O)
	cd $(BUILD) && $(AR) $(LIBNAME) $(addprefix ../,$^)

TEST :=

define TEST_temp
  TAR :=  $(BUILD)/$(notdir $(basename $(1)))
  TEST := $(TEST) $$(TAR)
  $$(TAR) : | $(BUILD)
  $$(TAR) : $(LIBNAME)
  $$(TAR) : test/$(1) 
	cd $(BUILD) && $(CC) $(CFLAGS) -I.. -L. -L../ext/pbc/build -o $$(notdir $$@) ../$$< -lhdclient -lpbc
endef

$(foreach s,$(TESTSRCS),$(eval $(call TEST_temp,$(s))))

test : $(TEST) 

.PHONY : all lib test clean

