CXX=g++
CXXFLAGS= -std=c++17 -O3
LINKFLAGS= -lglfw -lGLU -lGL -ldl -lpthread

#debug = true
ifdef debug
	CXXFLAGS +=-g
	LINKFLAGS += -flto
endif
LIBDIR=lib
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

LIBDIRS=-Ilib$(GLADLIB)$(GLEWLIB)$(GLFWLIB)$(GLMLIB)

# SRC, OBJ ---
SRCDIR=src
SRCDIRS=$(sort $(dir $(wildcard $(SRCDIR)/*)) $(dir $(wildcard $(SRCDIR)/*/*)))
SRCLIST=$(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp) $(wildcard $(SRCDIR)/*/*/*.cpp)
SRCSOURCE=$(addprefix $(SRCDIRS)/%.cpp)

OBJDIR=obj
OBJLIST=$(addprefix $(OBJDIR)/,$(notdir $(SRCLIST:.cpp=.o))) $(OBJDIR)/glad.o $(OBJDIR)/specrend.o

VPATH=$(SRCDIR) $(SRCDIRS)
INCDIR:=$(patsubst %, -I%,$(SRCDIRS))

EXECUTABLE= program.out

#frequently changed headers
HEADERS=$(SRCDIR)/utilities/Constants.h
#----------------------------------------------------------

all: buildDirectories $(EXECUTABLE) 

$(EXECUTABLE): $(OBJLIST) 
	$(CXX) $(CXXFLAGS) $(LINKFLAGS) $(OBJLIST) -o $@ $(LIBS) $(LIBDIRS)
 
#spedcrend(wavelength->rgb)
$(OBJDIR)/specrend.o: $(LIBDIR)/specrend.c
	$(CXX) -c $(CXXFLAGS) $(LIBDIRS) $< -o $@

#glad
$(OBJDIR)/glad.o: $(GLADDIR)/glad.c
	$(CXX) -c $(CXXFLAGS) $(LIBDIRS) $< -o $@

$(OBJDIR)/%.o : %.cpp $(HEADERS)
	$(CXX) -c $(CXXFLAGS) $(INCDIR) $(LIBDIRS) $< -o $@ 

#all other cpp files
#loopmake :
#	$(foreach srcfile, $(SRCLIST), $(CXX) -c $(CXXFLAGS) $(INCDIR) $(LIBDIRS) $(srcfile) -o $(addprefix $(OBJDIR)/,$(notdir $(srcfile:.cpp=.o)));)

#----------------------------------------------------------

.PHONY: buildDirectories
buildDirectories:
	mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm -f *.out $(OBJDIR)/*.o; rmdir obj;
