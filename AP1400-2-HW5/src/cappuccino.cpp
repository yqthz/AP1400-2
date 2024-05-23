#include "cappuccino.h"
Cappuccino::Cappuccino() {
    this->name = "Cappuccino";
    Ingredient* esp = new Espresso(2);
    Ingredient* milk = new Milk(2);
    Ingredient* milk_foam = new MilkFoam(1);
    this->ingredients.push_back(esp);
    this->ingredients.push_back(milk);
    this->ingredients.push_back(milk_foam);
}

Cappuccino::Cappuccino(const Cappuccino& cap) {
    size_t len = cap.side_items.size();
    this->name = cap.name;
    
    Ingredient* esp = new Espresso(2);
    Ingredient* milk = new Milk(2);
    Ingredient* milk_foam = new MilkFoam(1);
    this->ingredients.push_back(esp);
    this->ingredients.push_back(milk);
    this->ingredients.push_back(milk_foam);

    for (size_t i = 0; i < len; i++) {
        size_t t = cap.side_items[i]->get_units();
        Cinnamon* cinnamon = dynamic_cast<Cinnamon*>(cap.side_items[i]);
        Chocolate* chocolate = dynamic_cast<Chocolate*>(cap.side_items[i]);
        Sugar* sugar = dynamic_cast<Sugar*>(cap.side_items[i]);
        Cookie* cookie = dynamic_cast<Cookie*>(cap.side_items[i]);
        Espresso* espresso = dynamic_cast<Espresso*>(cap.side_items[i]);
        Milk* milk = dynamic_cast<Milk*>(cap.side_items[i]);
        MilkFoam* milk_foam = dynamic_cast<MilkFoam*>(cap.side_items[i]);
        Water* water = dynamic_cast<Water*>(cap.side_items[i]);
        Ingredient* t1 = nullptr;
        if (cinnamon) {
            t1 = new Cinnamon(t);
            this->side_items.push_back(t1);
        }
        else if (chocolate) {
            t1 = new Chocolate(t);
            this->side_items.push_back(t1);
        }
        else if (sugar) {
            t1 = new Sugar(t);
            this->side_items.push_back(t1);
        }
        else if (cookie) {
            t1 = new Cookie(t);
            this->side_items.push_back(t1);
        }
        else if (espresso) {
            t1 = new Espresso(t);
            this->side_items.push_back(t1);
        }
        else if (milk) {
            t1 = new Milk(t);
            this->side_items.push_back(t1);
        }
        else if (milk_foam) {
            t1 = new MilkFoam(t);
            this->side_items.push_back(t1);
        }
        else if (water) {
            t1 = new Water(t);
            this->side_items.push_back(t1);
        }
    }
}
Cappuccino::~Cappuccino() {
    for (const auto& i : side_items) {
        delete i;
    }
    side_items.clear();
}

void Cappuccino::operator=(const Cappuccino& cap) {
    if (this == &cap) {
        return;
    }
    for (const auto& i : side_items) {
        delete i;
    }
    side_items.clear();

    size_t len = cap.side_items.size();
    for (size_t i = 0; i < len; i++) {
        size_t t = cap.side_items[i]->get_units();
        Cinnamon* cinnamon = dynamic_cast<Cinnamon*>(cap.side_items[i]);
        Chocolate* chocolate = dynamic_cast<Chocolate*>(cap.side_items[i]);
        Sugar* sugar = dynamic_cast<Sugar*>(cap.side_items[i]);
        Cookie* cookie = dynamic_cast<Cookie*>(cap.side_items[i]);
        Espresso* espresso = dynamic_cast<Espresso*>(cap.side_items[i]);
        Milk* milk = dynamic_cast<Milk*>(cap.side_items[i]);
        MilkFoam* milk_foam = dynamic_cast<MilkFoam*>(cap.side_items[i]);
        Water* water = dynamic_cast<Water*>(cap.side_items[i]);
        Ingredient* t1 = nullptr;
        if (cinnamon) {
            t1 = new Cinnamon(t);
            this->side_items.push_back(t1);
        }
        else if (chocolate) {
            t1 = new Chocolate(t);
            this->side_items.push_back(t1);
        }
        else if (sugar) {
            t1 = new Sugar(t);
            this->side_items.push_back(t1);
        }
        else if (cookie) {
            t1 = new Cookie(t);
            this->side_items.push_back(t1);
        }
        else if (espresso) {
            t1 = new Espresso(t);
            this->side_items.push_back(t1);
        }
        else if (milk) {
            t1 = new Milk(t);
            this->side_items.push_back(t1);
        }
        else if (milk_foam) {
            t1 = new MilkFoam(t);
            this->side_items.push_back(t1);
        }
        else if (water) {
            t1 = new Water(t);
            this->side_items.push_back(t1);
        }
    }
}

double Cappuccino::price() {
    double ans = 0;
    size_t len = this->ingredients.size();
    for (size_t i = 0; i < len; i++) {
        ans += ingredients[i]->get_price_unit() * ingredients[i]->get_units();
    }
    size_t len1 = side_items.size();
    for (size_t i = 0; i < len1; i++) {
        ans += side_items[i]->get_price_unit() * side_items[i]->get_units();
    }
    return ans;
}

std::string Cappuccino::get_name() {
    return this->name;
}

void Cappuccino::add_side_item(Ingredient* side) {
    side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items() {
    return side_items;
}