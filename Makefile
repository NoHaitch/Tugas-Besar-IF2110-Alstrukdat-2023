# TODO: Make header file as dependency

CC=gcc

MAIN = main.c
MAIN_OUT = $(call SRC_TO_BIN,$(MAIN))

BIN_PATH = bin
OBJ_PATH = $(BIN_PATH)/o

RECUR_WILDCARD=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call RECUR_WILDCARD,$d/,$2))

OBJ_FUN = $(OBJ_PATH)/$(patsubst %.c,%.o,$1) 
SRC_TO_OBJ = $(foreach f,$1,$(call OBJ_FUN,$f))
BIN_FUN = $(BIN_PATH)/$(patsubst %.c,%,$1)
SRC_TO_BIN = $(foreach f,$1,$(call BIN_FUN,$f))

TEST_PATH = test
TEST_BASE = $(TEST_PATH)/test.c
GET_TEST_PATH = $(TEST_PATH)/$1_test.c

IS_EXIST = $(wildcard $1)
H_TO_C = $(patsubst %.h,%.c,$1)
H_TO_OBJ = $(OBJ_PATH)/$(patsubst %.h,%.o,$1)
FILTER_C_DEP = $(if $(findstring .h,$1),$(call IS_EXIST,$(call H_TO_C,$1)),)
GET_C_DEP = $(patsubst $1,,$(foreach f,$(shell $(CC) -MM $1),$(call FILTER_C_DEP,$f)))
RESOLVE_PATH = $(patsubst $(CURDIR)/%,%,$(realpath $1))

RECUR_DEP = $(call SRC_TO_OBJ,$(call RECUR_DEP_1,,$1))
RECUR_DEP_1 = $2 $(call RECUR_DEP_2,$2 $1,$(call GET_C_DEP,$2))
RECUR_DEP_2 = $(call RECUR_DEP_3,$1,$(foreach f,$2,$(if $(findstring $f,$1),,$f)))
RECUR_DEP_3 = $(foreach f,$2,$(call RECUR_DEP_1,$1 $2,$(call RESOLVE_PATH,$f)))

.SECONDARY:
.SECONDEXPANSION:
.PHONY: build run clean all recompile %.test %.tmp

$(OBJ_PATH)/%.o : %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(MAIN_OUT) : $(call RECUR_DEP,$(MAIN))
	$(CC) $(CFLAGS) -o $@ $^

build: $(MAIN_OUT)

run:
	$(MAIN_OUT)

clean:
	rm -rf $(BIN_PATH)

all: build run
recompile: clean all

bin/tmp/% : $$(call RECUR_DEP,tmp/$$*.c)
	mkdir -p bin/tmp
	$(CC) $(CFLAGS) -o $@ $^

%.tmp : bin/tmp/%
	bin/tmp/$*

bin/test/% : $$(call RECUR_DEP,$$(call GET_TEST_PATH,$$*))
	mkdir -p bin/test
	$(CC) $(CFLAGS) -o $@ $^

%.test : bin/test/%
	bin/test/$*

test.all: $(patsubst %_test,%,$(call SRC_TO_BIN,$(call RECUR_WILDCARD,test,*_test.c)))
	echo ; for P in $^ ; do echo --- $${P} --- ; $${P} ; echo ; done ; echo
