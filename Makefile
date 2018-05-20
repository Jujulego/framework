# Variables
BUILD = build
EXEC  = run

# Commandes
CMAKE = /usr/local/bin/cmake

# Options
$(VERBOSE).SILENT:
.NOTPARALLEL:

# Compilation
all: $(BUILD)
	$(MAKE) -C $(BUILD) all
	cp $(BUILD)/src/$(EXEC) .

.PHONY: all

$(BUILD): src CMakeLists.txt
	echo "\033[35;03mConstruction du dossier $(BUILD)\033[m"
	[ -d "$(BUILD)" ] || mkdir $(BUILD)
	cd $(BUILD); $(CMAKE) ..

# Nettoyage
clean:
	[ -d "$(BUILD)" ] && $(MAKE) -C $(BUILD) clean

mrproper:
	[ -d "$(BUILD)" ] && rm -r $(BUILD)
