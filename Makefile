CC := g++ -std=c++0x
SRCDIR := src
BUILDDIR := obj
TARGETDIR := bin
TARGET := bin/ipmt
 
SRCEXT := cc
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -O2 -Wall -Wextra -flto
LIB := 
INC :=

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo " Linking..."
	@echo " $(CC) $(CFLAGS) $^ -c -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGETDIR)"; $(RM) -r $(BUILDDIR) $(TARGET)

run:
	./$(TARGET) -p test/patt1.txt test/text1.txt ${args}

all:
	make clean $(TARGET)
	@echo "    ALL OK! :)"

.PHONY: clean, run
