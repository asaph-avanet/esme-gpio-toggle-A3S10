# --- Variables ---
PROG = esme-gpio-toggle
OBJS = $(PROG).o

# Répertoire d'installation. '?=' permet de le surcharger depuis la ligne de commande.
INSTALL_DIR ?= ./.install

# --- Flags de compilation et de liaison ---
# Utilise pkg-config pour ajouter les CFLAGS (-I...) et LDLIBS (-L... -l...)
CFLAGS += $(shell pkg-config --cflags libgpiod)
LDLIBS += $(shell pkg-config --libs libgpiod)

# --- Cibles principales ---

# Cible par défaut: 'all' dépend de l'exécutable
all: $(PROG)

# Règle de liaison explicite (dépend de l'objet)
# make utilisera les variables implicites (CC, LDFLAGS) et nos LDLIBS
$(PROG): $(OBJS)

# Aucune règle de compilation .c.o n'est nécessaire.
# make utilisera la règle implicite en appliquant nos CFLAGS.

# Cible d'installation
install: $(PROG)
	# Crée l'arborescence de destination
	@mkdir -p $(INSTALL_DIR)/usr/bin
	# Installe le binaire avec les droits d'exécution
	@install -m 0755 $(PROG) $(INSTALL_DIR)/usr/bin
	@echo "Installé dans $(INSTALL_DIR)/usr/bin"

# Cible de nettoyage
clean:
	# Supprime les objets, le binaire et le dossier d'install local
	@rm -f $(PROG) $(OBJS)
	@rm -rf $(INSTALL_DIR)
	@echo "Nettoyé."

# Déclare les cibles qui ne sont pas des fichiers (évite les conflits)
.PHONY: all install clean
