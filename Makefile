export CC=gcc
export CFLAGS=-I. -DSYMBOL1 -DSYMBOL2
export LDFLAGS=

ETAPE1_DIR=etape1
ETAPE2_DIR=etape2
ETAPE3_DIR=etape3
BIN_DIR=bin

EXEC= create_exec

all: $(EXEC)

create_exec:
	@(mkdir -p ./bin)
	@(cd $(ETAPE1_DIR) && (make))
	@(cd $(ETAPE2_DIR) && (make))
	@(cd $(ETAPE3_DIR) && (make))
	
clean:
	@(cd $(ETAPE1_DIR) && (make clean))
	@(cd $(ETAPE2_DIR) && (make clean))
	@(cd $(ETAPE3_DIR) && (make clean))

binclean:
	@(rm -r bin)
