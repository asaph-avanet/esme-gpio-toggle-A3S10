#include <gpiod.h>      // Pour la bibliothèque libgpiod
#include <stdio.h>      // Pour printf, perror, fprintf
#include <unistd.h>     // Pour sleep()
#include <string.h>     // Pour strcmp() (comparer les arguments)
#include <stdlib.h>     // Pour atoi() (convertir l'argument en nombre)

// GPIO 26 est la valeur par défaut, comme demandé
#define DEFAULT_GPIO_PIN 26
// Sur Raspberry Pi, la puce GPIO principale est presque toujours "gpiochip0"
#define GPIO_CHIP_NAME "gpiochip0"
// Nom du "consommateur" pour libgpiod
#define CONSUMER_NAME "esme-gpio-toggle"

/**
 * @brief Affiche comment utiliser le programme en cas d'erreur d'argument.
 */
void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s [--gpio <pin_number>]\n", prog_name);
    fprintf(stderr, "Example: %s --gpio 26\n", prog_name);
    fprintf(stderr, "If no arguments are provided, GPIO %d is used by default.\n", DEFAULT_GPIO_PIN);
}

/**
 * @brief Programme principal
 */
int main(int argc, char *argv[]) {
    
    unsigned int gpio_pin = DEFAULT_GPIO_PIN;
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    const char *chip_name = GPIO_CHIP_NAME;
    int value = 0; // Valeur initiale (importe peu)

    // --- 1. Analyse des arguments de la ligne de commande ---
    
    if (argc == 3) {
        // S'il y a 3 arguments (ex: ./prog --gpio 26)
        if (strcmp(argv[1], "--gpio") == 0) {
            gpio_pin = (unsigned int)atoi(argv[2]); // Convertit "26" en nombre
        } else {
            print_usage(argv[0]);
            return 1;
        }
    } else if (argc != 1) { 
        // Si ce n'est pas 1 argument (défaut) ou 3 (custom), c'est une erreur.
        print_usage(argv[0]);
        return 1;
    }

    printf("Starting GPIO toggle on pin %u (chip: %s)\n", gpio_pin, chip_name);

    // --- 2. Initialisation de libgpiod ---
    
    // Ouvre la puce GPIO (ex: "gpiochip0")
    chip = gpiod_chip_open_by_name(chip_name);
    if (!chip) {
        perror("Error opening GPIO chip");
        return 1;
    }

    // Récupère la ligne (la broche) spécifique
    line = gpiod_chip_get_line(chip, gpio_pin);
    if (!line) {
        perror("Error getting GPIO line");
        gpiod_chip_close(chip);
        return 1;
    }

    // Demande la ligne en mode "Sortie"
    // (Valeur initiale 0)
    if (gpiod_line_request_output(line, CONSUMER_NAME, 0) < 0) {
        perror("Error requesting line output");
        gpiod_line_release(line);
        gpiod_chip_close(chip);
        return 1;
    }

    printf("Toggling GPIO %u every second. Press Ctrl+C to stop.\n", gpio_pin);

    // --- 3. Boucle infinie ---
    
    while (1) {
        value = !value; // Inverse la valeur (0 -> 1, ou 1 -> 0)
        
        if (gpiod_line_set_value(line, value) < 0) {
            perror("Error setting line value");
        }
        
        sleep(1); // Attend 1 seconde
    }

    // Nettoyage (techniquement jamais atteint à cause de la boucle infinie)
    gpiod_line_release(line);
    gpiod_chip_close(chip);

    return 0;
}
