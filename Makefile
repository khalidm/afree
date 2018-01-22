#
#* TARGETS : ./bin/afree

#directories
afree = .

#local directories
SRC = $(afree)/src
OBJ = $(afree)/obj
BIN = $(afree)/bin

#compiler options
CPP = g++
CPPFLAGS += -O3 -std=c++0x -Wno-narrowing
CPPFLAGS += -Wno-unused-value

LDFLAGS =
.cpp.o:
	$(CPP) $(CPPFLAGS) -c -o $@ $<

#macros
OBJECTS = $(OBJ)/globals.o $(OBJ)/protein.o \
          $(OBJ)/score.o $(OBJ)/sequence_info.o \
          $(OBJ)/radixLSD.o $(OBJ)/join_lists.o \
          $(OBJ)/sequence_tuples.o \
          $(OBJ)/main.o

ALL = $(BIN)/afree

#targets
all: $(ALL)

#------------------------------------------------------------------------------
$(BIN)/afree: $(OBJECTS)
	$(CPP) $(CPPFLAGS)  $(LDFLAGS) -o $@ $(OBJECTS)

$(OBJ)/globals.o: $(SRC)/globals.h $(SRC)/macros.h $(SRC)/globals.cpp
		$(CPP) $(CPPFLAGS) -c $(SRC)/globals.cpp -o $(OBJ)/globals.o

$(OBJ)/protein.o: $(SRC)/protein.h $(SRC)/macros.h $(SRC)/globals.h $(SRC)/protein.cpp
		$(CPP) $(CPPFLAGS) -c $(SRC)/protein.cpp -o $(OBJ)/protein.o

$(OBJ)/score.o: $(SRC)/score.h $(SRC)/macros.h $(SRC)/globals.h $(SRC)/score.cpp
		$(CPP) $(CPPFLAGS) -c $(SRC)/score.cpp -o $(OBJ)/score.o

$(OBJ)/sequence_info.o: $(SRC)/sequence_info.h $(SRC)/macros.h $(SRC)/globals.h $(SRC)/sequence_info.cpp
		$(CPP) $(CPPFLAGS) -c $(SRC)/sequence_info.cpp -o $(OBJ)/sequence_info.o

$(OBJ)/radixLSD.o: $(SRC)/radixLSD.h $(SRC)/radixLSD.cpp
		$(CPP) $(CPPFLAGS) -c $(SRC)/radixLSD.cpp -o $(OBJ)/radixLSD.o

$(OBJ)/join_lists.o: $(SRC)/join_lists.h $(SRC)/join_lists.cpp
		$(CPP) $(CPPFLAGS) -c $(SRC)/join_lists.cpp -o $(OBJ)/join_lists.o

$(OBJ)/sequence_tuples.o: $(SRC)/sequence_tuples.h $(SRC)/macros.h  $(SRC)/globals.h $(SRC)/sequence_tuples.cpp
		$(CPP) $(CPPFLAGS) -c $(SRC)/sequence_tuples.cpp -o $(OBJ)/sequence_tuples.o

$(OBJ)/main.o: $(SRC)/globals.h $(SRC)/main.cpp
		$(CPP) $(CPPFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

#------------------------------------------------------------------------------
clean:
	rm $(OBJ)/*.o

remove: clean
	rm  $(BIN)/afree
#------------------------------------------------------------------------------
