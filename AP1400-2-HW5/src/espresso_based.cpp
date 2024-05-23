#include "espresso_based.h"
EspressoBased::EspressoBased() : name("") { }

EspressoBased::EspressoBased(const EspressoBased& esp) : name(esp.name) {
    size_t len = esp.ingredients.size();
    for (size_t i = 0; i < len; i++) {
        this->ingredients.push_back(esp.ingredients[i]);
    }

}
EspressoBased::~EspressoBased() {
    for (const auto& i : ingredients) {
        delete i;
    }
    ingredients.clear();
}

std::vector<Ingredient*>& EspressoBased::get_ingredients() {
    return ingredients;
}

void EspressoBased::operator=(const EspressoBased& esp) {
    for (const auto& i : ingredients) {
        delete i;
    }
    ingredients.clear();
    size_t len = esp.ingredients.size();
    for (size_t i = 0; i < len; i++) {
        this->ingredients.push_back(esp.ingredients[i]);
    }
}