CC=gcc
BUILD_DIR=build
SRC_DIR=src
INC_DIR=include
INCLUDE=-I$(INC_DIR)
LIBS=-lm -lreadline -ldl
CFLAGS=-fdiagnostics-color=always -Wall -std=gnu17 -g -O0
TP_N=3
NOM_ZIP=TP$(TP_N)_SEBAN_Nicolas.zip
EXEC=rpn
CONTENU_ZIP=$(SRC_DIR) $(INC_DIR) .clang-format .clang-tidy Makefile rapport.pdf

SOURCES=$(wildcard $(SRC_DIR)/*.c)
HEADERS=$(wildcard $(INC_DIR)/*.h)

# On récupère tous les fichiers sources .c, et on leurs préfixe
# le chemin de build, et suffixe en .o :
OBJS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

PLUGINS_OPERATORS=$(wildcard $(SRC_DIR)/operators/*.c)
PLUGINS_OPERATORS_OBJS=$(patsubst $(SRC_DIR)/operators/%.c, $(BUILD_DIR)/plugins/operators/%.so, $(PLUGINS_OPERATORS))

$(info $(PLUGINS_OPERATORS_OBJS))

all: $(BUILD_DIR)/$(EXEC)

plugins: $(PLUGINS_OPERATORS_OBJS)

# Assemblage de l'exécutable final
$(BUILD_DIR)/$(EXEC): $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

# Dépendances
token.o: token.c operations.h utils.h
stack.o: stack.c
evaluator.o: evaluator.c stack.h token.h utils.h
operations.o: operations.c utils.h
utils.o: utils.c
vector.o: vector.c
interpretor.o: interpretor.c evaluator.h token.h coroutine.h stack.h utils.h

# Création des fichiers objets à partir des fichiers sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir --parents $(BUILD_DIR)
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

# Compilation des plugins

$(BUILD_DIR)/plugins/operators/%.so: $(SRC_DIR)/operators/%.c
	@mkdir --parents $(BUILD_DIR)/plugins/operators
	$(CC) $(INCLUDE) $(CFLAGS) -fPIC -shared $< -o $@ -lm


rapport: rapport.pdf

rapport.pdf: rapport.md
	@mkdir --parents logos
	@wget --quiet --show-progress --no-clobber -O logos/LogoLIGM.png "https://drive.google.com/uc?export=download&confirm=yes&id=1cZjxS6Rwp8LU4Eyahqz0eUS8aH0_VrVB" || true
	@wget --quiet --show-progress --no-clobber -O logos/namedlogoUGE.png "https://drive.google.com/uc?export=download&confirm=yes&id=1YGm1N7griuDbJhC6rSgBHrrcOsHKM5xg" || true
	pandoc --toc rapport.md -o rapport.pdf

format: $(SOURCES) $(HEADERS)
	clang-format -i --style=file $^
	clang-tidy --fix $^

clean:
	rm -f $(OBJS)

distclean:
	rm -rf $(BUILD_DIR)
	rm -f $(NOM_ZIP)

zip:
	zip -FSr $(NOM_ZIP) $(CONTENU_ZIP)

rendu:
	@$(MAKE) --no-print-directory rapport
	@$(MAKE) --no-print-directory zip

.PHONY: clean all
