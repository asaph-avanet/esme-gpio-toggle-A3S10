# --- Variables ---
PROG = esme-gpio-toggle
OBJS = $(PROG).o

# Répertoire d'installation. '?=' permet de le surcharger depuis la ligne de commande.
INSTALL_DIR ?= ./.install

# --- Flags de compilation et de liaison ---
# Utilise pkg-config pour ajouter les CFLAGS (-I...) et LDLIBS (-L... -l...)
# Note : CFLAGS doit être utilisé pour la compilation, CPPFLAGS est plus correct
CPPFLAGS += $(shell pkg-config --cflags libgpiod)
LDLIBS += $(shell pkg-config --libs libgpiod)

# --- Cibles principales ---

# Cible par défaut: 'all' dépend de l'exécutable
all: $(PROG)

# Règle de liaison explicite (dépend de l'objet)
# make utilisera les variables implicites (CC, LDFLAGS) et nos LDLIBS
$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Aucune règle de compilation .c.o n'est nécessaire.
# make utilisera la règle implicite en appliquant nos CFLAGS/CPPFLAGS.

# Cible d'installation
install: $(PROG)
	# --- Installation du binaire ---
	@mkdir -p $(INSTALL_DIR)/usr/bin
	@install -m 0755 $(PROG) $(INSTALL_DIR)/usr/bin
	@echo "Installé $(PROG) dans $(INSTALL_DIR)/usr/bin"
	
	# --- AJOUT : Installation du script de démarrage ---
	@mkdir -p $(INSTALL_DIR)/etc/init.d
	@install -m 0755 esme-gpio26-toggle $(INSTALL_DIR)/etc/init.d/
	@echo "Installé esme-gpio26-toggle dans $(INSTALL_DIR)/etc/init.d"

# Cible de nettoyage
clean:
	# Supprime les objets, le binaire et le dossier d'install local
	@rm -f $(PROG) $(OBJS)
	@rm -rf $(INSTALL_DIR)
	@echo "Nettoyé."

# Déclare les cibles qui ne sont pas des fichiers (évite les conflits)
.PHONY: all install clean
