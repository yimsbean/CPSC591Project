CXX=g++
CXXFLAGS= -std=c++17 -O3 -g
LINKFLAGS=-O3 -lglfw -lGLU -lGL -ldl -lpthread

#debug = true
ifdef debug
	CXXFLAGS +=-g
	LINKFLAGS += -flto
endif
# LIB ---
GLADVER=glad
GLADDIR=lib/$(GLADVER)
GLADLIB=$(patsubst %, -I%, $(GLADDIR))

GLEWVER=glew
GLEWDIR=lib/$(GLEWVER)/include/GL lib/glew-$(GLEWVER)/src
#GLEWLIB:=$(patsubst %, %$(GLEWDIR),-I)

GLFWVER=glfw
GLFWDIR=lib/$(GLFWVER)/include
GLFWLIB=$(patsubst %, -I%,$(GLFWDIR))

GLMVER=glm
GLMDIR=lib/$(GLMVER)
GLMLIB:=$(patsubst %, -I%,$(GLMDIR))

LIBDIR=-Ilib$(GLADLIB)$(GLEWLIB)$(GLFWLIB)$(GLMLIB)

# SRC, OBJ ---
SRCDIR=src
SRCDIRS=$(dir $(wildcard $(SRCDIR)/*)) $(dir $(wildcard $(SRCDIR)/*/*))
SRCLIST=$(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp) $(wildcard $(SRCDIR)/*/*/*.cpp)
SRCSOURCE=$(addprefix $(SRCDIRS)/%.cpp)

OBJDIR=obj
OBJLIST=$(addprefix $(OBJDIR)/,$(notdir $(SRCLIST:.cpp=.o))) $(OBJDIR)/glad.o

VPATH=$(SRCDIR) $(SRCDIRS)
INCDIR:=$(patsubst %, -I%,$(SRCDIRS))

EXECUTABLE= program.out

#----------------------------------------------------------

all: buildDirectories $(EXECUTABLE) 

$(EXECUTABLE): $(OBJLIST) 
	$(CXX) $(LINKFLAGS) $(OBJLIST) -o $@ $(LIBS) $(LIBDIR)
 
#glad
$(OBJDIR)/glad.o: $(GLADDIR)/glad.c
	$(CXX) -c $(CXXFLAGS) $(LIBDIR) $< -o $@

$(OBJDIR)/%.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $(INCDIR) $(LIBDIR) $< -o $@ 

#all other cpp files
#loopmake :
#	$(foreach srcfile, $(SRCLIST), $(CXX) -c $(CXXFLAGS) $(INCDIR) $(LIBDIR) $(srcfile) -o $(addprefix $(OBJDIR)/,$(notdir $(srcfile:.cpp=.o)));)

#----------------------------------------------------------

.PHONY: buildDirectories
buildDirectories:
	mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm -f *.out $(OBJDIR)/*.o; rmdir obj;
